// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <math.h>
#include <tsa/features.h>
#include <tsa/normalization.h>
#include <tsa/polynomial.h>
#include <tsa/regression.h>
#include <tsa/regularization.h>
#include <tsa/statistics.h>

#define BATCH_SIZE 2048

af::array tsa::features::absEnergy(af::array base) {
    array p2 = af::pow(base, 2);
    af::array sp2 = af::sum(p2, 0);
    return sp2;
}

af::array tsa::features::absoluteSumOfChanges(af::array tss) {
    long n = tss.dims(0);
    // Calculating tss(t + 1) - tss(t) from 0 to the length of the time series minus 1
    af::array minus = tss(af::seq(std::min(1L, n - 1), n - 1), span) - tss(af::seq(0, std::max(0L, n - 2)), span);
    // Returning the sum of absolute values of the previous operation
    return af::sum(af::abs(minus), 0);
}

af::array tsa::features::aggregatedAutocorrelation(af::array tss,
                                                   af::array (*aggregationFunction)(const af::array &, const bool,
                                                                                    const dim_t)) {
    long n = tss.dims(0);
    af::array autocorrelations = tsa::features::autoCorrelation(tss, n, true)(af::seq(1, n - 1), span);
    return aggregationFunction(autocorrelations, true, 0);
}

af::array tsa::features::aggregatedAutocorrelation(af::array tss,
                                                   af::array (*aggregationFunction)(const af::array &, const int)) {
    long n = tss.dims(0);
    af::array autocorrelations = tsa::features::autoCorrelation(tss, n, true)(af::seq(1, n - 1), span);
    return aggregationFunction(autocorrelations, 0);
}

af::array tsa::features::aggregatedAutocorrelation(af::array tss,
                                                   af::array (*aggregationFunction)(const af::array &, const dim_t)) {
    long n = tss.dims(0);
    af::array autocorrelations = tsa::features::autoCorrelation(tss, n, true)(af::seq(1, n - 1), span);
    return aggregationFunction(autocorrelations, 0);
}

af::array aggregating(af::array input, af::array (*aggregationFunction)(const af::array &, const int)) {
    return aggregationFunction(input, -1);
}

af::array aggregating(af::array input, af::array (*aggregationFunction)(const af::array &, const dim_t)) {
    return aggregationFunction(input, -1);
}

af::array aggregatingOnChunks(af::array input, long chunkSize,
                              af::array (*aggregationFunction)(const af::array &, const int)) {
    // Calculating the chunk size to split the input data into. The rest of dividing the input data
    // length by the chunk size should be zero. In other words, input data length should be multiple
    // of the chunk size
    long size = (input.dims(0) % chunkSize == 0) ? 0 : chunkSize - input.dims(0) % chunkSize;
    // If it is not multiple, then pad with zeros at the end
    af::array inputChunks = af::join(0, input, af::constant(0, size, input.dims(1), input.type()));
    // Modify the array dimensions to split it by the chunk size
    inputChunks = af::moddims(inputChunks, chunkSize, inputChunks.dims(0) / chunkSize, inputChunks.dims(1));
    // Aggregate the data using the aggregation function specified as parameter, and then reorder
    // the resulting array to have the number of chunks in the 2nd dimension
    return af::reorder(af::transpose(aggregationFunction(inputChunks, 0)), 0, 2, 1, 3);
}

af::array aggregatingOnChunks(af::array input, long chunkSize,
                              af::array (*aggregationFunction)(const af::array &, const dim_t)) {
    // Calculating the chunk size to split the input data into. The rest of dividing the input data
    // length by the chunk size should be zero. In other words, input data length should be multiple
    // of the chunk size
    long size = (input.dims(0) % chunkSize == 0) ? 0 : chunkSize - input.dims(0) % chunkSize;
    // If it is not multiple, then pad with zeros at the end
    af::array inputChunks = af::join(0, input, af::constant(0, size, input.dims(1), input.type()));
    // Modify the array dimensions to split it by the chunk size
    inputChunks = af::moddims(inputChunks, chunkSize, inputChunks.dims(0) / chunkSize, inputChunks.dims(1));
    // Aggregate the data using the aggregation function specified as parameter, and then reorder
    // the resulting array to have the number of chunks in the 2nd dimension
    return af::reorder(af::transpose(aggregationFunction(inputChunks, 0)), 0, 2, 1, 3);
}

void tsa::features::aggregatedLinearTrend(af::array t, long chunkSize,
                                          af::array (*aggregationFunction)(const af::array &, const int),
                                          af::array &slope, af::array &intercept, af::array &rvalue, af::array &pvalue,
                                          af::array &stderrest) {
    // Aggregating the data using the specified chunk size and aggregation function
    af::array aggregateResult = aggregatingOnChunks(t, chunkSize, aggregationFunction);
    // Preparing the x vector for the linear regression. Tiling it to the number of time series
    // contained in t
    af::array x = af::tile(af::range(aggregateResult.dims(0)).as(t.type()), 1, t.dims(1));
    // Calculating the linear regression and storing the results in the parameters passed as reference
    tsa::regression::linear(x, aggregateResult, slope, intercept, rvalue, pvalue, stderrest);
}

void tsa::features::aggregatedLinearTrend(af::array t, long chunkSize,
                                          af::array (*aggregationFunction)(const af::array &, const dim_t),
                                          af::array &slope, af::array &intercept, af::array &rvalue, af::array &pvalue,
                                          af::array &stderrest) {
    // Aggregating the data using the specified chunk size and aggregation function
    af::array aggregateResult = aggregatingOnChunks(t, chunkSize, aggregationFunction);
    // Preparing the x vector for the linear regression. Tiling it to the number of time series
    // contained in t
    af::array x = af::tile(af::range(aggregateResult.dims(0)).as(t.type()), 1, t.dims(1));
    // Calculating the linear regression and storing the results in the parameters passed as reference
    tsa::regression::linear(x, aggregateResult, slope, intercept, rvalue, pvalue, stderrest);
}

af::array entropy(af::array tss, int m, float r) {
    long n = tss.dims(0);

    af::array std = af::stdev(tss);
    std *= r;

    const long chunkSizeH = 512;
    const long chunkSizeV = 512;
    long lastIterationSizeH = chunkSizeH;
    long lastIterationSizeV = chunkSizeV;

    af::array expandH = af::array(m, chunkSizeH, tss.dims(1), tss.type());
    af::array expandV = af::array(m, chunkSizeV, tss.dims(1), tss.type());

    // Calculate the matrix distance
    af::array distances = af::constant(af::Inf, chunkSizeV, chunkSizeH, tss.dims(1), tss.type());
    af::array sum_c = af::constant(0, 1, chunkSizeH, tss.dims(1), tss.type());
    af::array sum = af::constant(0, tss.dims(1), tss.type());

    // it performs a batching (or blocking) in the horizontal direction
    for (int i = 0; i < n - m + 1; i += chunkSizeH) {
        long startH = i;
        long iterationSizeH = std::min(chunkSizeH, n - m + 1 - startH);
        long endH = startH + iterationSizeH;
        // if our batching dimension does not match the dimesion of the remaining elements, modify dimensions
        if (iterationSizeH != chunkSizeH || iterationSizeH != lastIterationSizeH) {
            lastIterationSizeH = iterationSizeH;
            distances = af::constant(af::Inf, chunkSizeV, iterationSizeH, tss.dims(1), tss.type());
            sum_c = af::constant(0, 1, iterationSizeH, tss.dims(1), tss.type());
            expandH = af::array(m, iterationSizeH, tss.dims(1), tss.type());
        }

        gfor(af::seq j, tss.dims(1)) {
            for (int k = 0; k < m; k++) {
                expandH(k, span, j, span) = af::reorder(tss(af::seq(i + k, i + k + iterationSizeH - 1), j), 1, 0, 3, 2);
            }
        }
        // it performs a batching (or blocking) in the vertical direction
        for (int j = 0; j < n - m + 1; j += chunkSizeV) {
            long startV = j;
            long iterationSizeV = std::min(chunkSizeV, n - m + 1 - startV);
            long endV = startV + iterationSizeV;
            // if our batching dimension does not match the dimension of the remaining elements, modify dimensions
            if (iterationSizeV != chunkSizeV || iterationSizeV != lastIterationSizeV) {
                lastIterationSizeV = iterationSizeV;
                distances = af::constant(af::Inf, iterationSizeV, chunkSizeH, tss.dims(1), tss.type());
                expandV = af::array(m, iterationSizeV, tss.dims(1), tss.type());
            }

            gfor(af::seq k, tss.dims(1)) {
                for (int l = 0; l < m; l++) {
                    expandV(l, span, k, span) =
                        af::reorder(tss(af::seq(j + l, j + l + iterationSizeV - 1), k), 1, 0, 3, 2);
                }
            }
            // Get the maximum difference among all dimensions for each timeseries
            gfor(af::seq k, iterationSizeV) {
                af::array aux = af::tile(expandV(span, k, span), 1, iterationSizeH);
                distances = af::reorder(af::max(af::abs(aux - af::tile(expandH, 1, 1, 1, iterationSizeV))), 3, 1, 2, 0);
            }
            // sum the number of elements bigger than the threshhold given by (stdev*r)
            af::array count = distances <= af::tile(af::reorder(std, 0, 2, 1, 3), distances.dims(0), distances.dims(1));
            // we summarise all partial sums in sum; we accumulate all partial sums for each vertical dimension
            sum_c += af::sum(count, 0);
        }
        // Finally, we collapse (aggregate) all total sums for each timeseries, we can do it as sum is commutative and
        // associative.
        sum += af::reorder(af::sum(af::log(sum_c / (n - m + 1.0)), 1), 2, 0, 1, 3);
    }
    // Before returning the final value, we divide the total sum for each timeseries by (n - m + 1.0)
    sum /= (n - m + 1.0);

    return sum;
}

af::array tsa::features::approximateEntropy(af::array tss, int m, float r) {
    long n = tss.dims(0);
    if (r < 0) {
        throw std::invalid_argument("Parameter r must be positive ...");
    }

    if (n <= (m + 1)) {
        return 0;
    }

    return af::abs(entropy(tss, m, r) - entropy(tss, m + 1, r));
}

af::array tsa::features::crossCovariance(af::array xss, af::array yss, bool unbiased) {
    // To be used as divisor if unbiased is false
    long n = xss.dims(0);
    // To be used as divisor if unbiased is true and also to determine the size of the output
    long nobs = std::max(xss.dims(0), yss.dims(0));

    // Mean value of each time series contained in xss
    af::array meanXss = af::mean(xss, 0);
    // Mean value of each time series contained in yss
    af::array meanYss = af::mean(yss, 0);

    // Substracting the mean to all the elements in xss for all the time series
    af::array xsso = xss - af::tile(meanXss, xss.dims(0));
    // Substracting the mean to all the elements in yss flipped for all the time series.
    // The flip operation is required because we are using convolve later on
    af::array ysso = af::flip(yss, 0) - af::tile(meanYss, yss.dims(0));

    af::array d;

    // Determining which divisor to use
    if (unbiased) {
        d = af::flip(af::tile((af::range(nobs) + 1.0).as(xss.type()), 1, xss.dims(1)), 0);
    } else {
        d = af::constant(n, nobs, xss.dims(1), xss.type());
    }

    // The result is a cube with nobs in the first dimensions, that determines the number of lags.
    // And the number of time series in yss as 2nd dimension and the number of time series in
    //  xss as the 3rd dimension
    af::array result = af::array(nobs, yss.dims(1), xss.dims(1), xss.type());
    gfor(af::seq i, xss.dims(1)) {
        // Flipping the result of the convolve operation because we flipped the input data
        result(span, span, i, span) =
            af::flip(af::convolve(xsso(span, i), ysso, AF_CONV_EXPAND)(af::seq(nobs), span), 0) / d;
    }

    return result;
}

af::array tsa::features::autoCovariance(af::array xss, bool unbiased) {
    // Matrix with number of time series in xss as the 1st dimension and the number of time
    // series in yss as the 2nd dimension
    af::array result = af::array(xss.dims(0), xss.dims(1), xss.type());
    // Calculating all the covariances in parallel, returning only the first slice of
    // the cube since the others are just calculations that are not required.
    // With a sequential for loop we would remove such calculations, but it might be slower
    result = tsa::features::crossCovariance(xss, xss, unbiased)(span, span, 0);
    return result;
}

af::array tsa::features::crossCorrelation(af::array xss, af::array yss, bool unbiased) {
    // Standard deviation of the time series in xss
    af::array stdevXss = af::stdev(xss, 0);
    // Standard deviation of the time series in yss
    af::array stdevYss = af::stdev(yss, 0);

    // Cross covariance of the time series contained in css and yss
    af::array ccov = tsa::features::crossCovariance(xss, yss, unbiased);

    // Dviding by the product of their standard deviations
    return ccov / af::tile(stdevXss * stdevYss, ccov.dims(0));
}

af::array tsa::features::autoCorrelation(af::array tss, long maxLag, bool unbiased) {
    long n = tss.dims(0);

    // Calculating the auto covariance of tss
    af::array acov = tsa::features::autoCovariance(tss, unbiased);

    // Slicing up to maxLag and normalizing by the value of lag 0
    return acov(af::seq(maxLag), span) / af::tile(acov(0, span), maxLag);
}

af::array tsa::features::binnedEntropy(af::array tss, int max_bins) {
    int len = tss.dims(0);
    int nts = tss.dims(1);
    af::array res = af::constant(0, 1, nts, tss.type());

    gfor(af::seq i, nts) {
        af::array his = af::histogram(tss(span, i), max_bins);
        af::array probs = his / (float)len;
        af::array aux = probs * af::log(probs);
        af::array sum = af::sum(aux, 0);
        res(0, i) = sum;
    }
    return af::abs(res);
}

af::array tsa::features::c3(af::array tss, long lag) {
    // Product of shifting tss 2 * -lag times, with tss shifted -lag times, with the original tss
    af::array aux = af::shift(tss, 2 * -lag) * af::shift(tss, -lag) * tss;
    // Return the slice of the previous calculation up to the length of the time series minus 2 * lag
    return af::mean(aux(af::seq(tss.dims(0) - 2 * lag), span), 0);
}

af::array tsa::features::cidCe(af::array tss, bool zNormalize) {
    long n = tss.dims(0);
    // Apply z-normalization if specified
    if (zNormalize) {
        tsa::normalization::znormInPlace(tss);
    }

    // Calculating tss(t + 1) - tss(t) from 0 to the length of the time series minus 1
    af::array diff = tss(af::seq(std::min(1L, n - 1), n - 1), span) - tss(af::seq(0, std::max(0L, n - 2)), span);
    // Returning the square root of the sum of squares of diff
    return af::sqrt(af::sum(diff * diff));
}

af::array tsa::features::countAboveMean(af::array tss) {
    af::array mean = af::mean(tss, 0);
    af::array aboveMean = (tss > af::tile(mean, tss.dims(0))).as(af::dtype::u32);
    return af::sum(aboveMean, 0);
}

af::array tsa::features::countBelowMean(af::array tss) {
    // Calculating the mean of all the time series in tss
    af::array mean = af::mean(tss, 0);
    // Calculating the elements that are lower than the mean
    af::array belowMean = (tss < af::tile(mean, tss.dims(0))).as(af::dtype::u32);
    // Sum of all elements below the mean
    return af::sum(belowMean, 0);
}

af::array ricker(int points, int a) {
    // Calculating number PI
    float PIf = std::atan(1) * 4;
    float A = 2 / (std::sqrt(3 * a) * std::pow(PIf, 0.25));
    float wsq = std::pow(a, 2);
    af::array vec = af::range(af::dim4(points)) - ((points - 1) / 2.0);
    af::array xsq = af::pow(vec, 2);
    af::array mod = (1 - xsq / wsq);
    af::array gauss = af::exp(-xsq / (2 * wsq));
    af::array total = A * mod * gauss;
    return total;
}

af::array cwt(af::array data, af::array widths) {
    int nw = widths.dims(0);
    int len_data = data.dims(0);
    int cols = data.dims(1);
    af::array filter;
    af::array output = af::constant(0, widths.dims(0), data.dims(0), data.dims(1), data.type());

    for (int i = 0; i < nw; i++) {
        int w = widths(i).scalar<int>();
        int minimum = std::min(10 * w, len_data);
        af::array wavelet_data = ricker(minimum, w);
        output(i, span, span) = af::moddims(af::convolve(af::reorder(data, 0, 2, 1), wavelet_data), 1, len_data, cols);
    }
    return output;
}

af::array tsa::features::cwtCoefficients(af::array tss, af::array widths, int coeff, int w) {
    int len = tss.dims(0);
    int nts = tss.dims(1);
    if (len < coeff) {
        return af::constant(af::NaN, 1, nts);
    }
    if (len < coeff) {
        return af::constant(af::NaN, 1, nts);
    }
    af::array output = cwt(tss, widths);

    // To find w in widths
    af::array index;
    af::array maximum;
    af::array aux = af::abs(widths - w) * (-1);
    af::max(maximum, index, aux, 0);
    // WORKAROUND: Forcing movement of index to CPU mem, just to avoid problems with Intel GPU
    int i = index.scalar<int>();
    // Select the corresponding values of coeff and w
    return af::reorder(output(i, coeff, span), 0, 2, 1);
}

af::array tsa::features::energyRatioByChunks(af::array tss, long numSegments, long segmentFocus) {
    // Calculating the energy of all the time series
    af::array fullSeriesEnergy = tsa::features::absEnergy(tss);
    long n = tss.dims(0);
    // Calculating the segment length given the length of the time series and the number of segments
    long segmentLength = n / numSegments;
    // Positioning at the beginning of the segment to focus on
    long start = segmentFocus * segmentLength;
    // Calculating the end (which should be lower than the length of the time series)
    long end = std::min((segmentFocus + 1) * segmentLength, n);
    return tsa::features::absEnergy(tss(af::seq(start, end - 1), span)) / fullSeriesEnergy;
}

af::array calculateMoment(af::array tss, int moment) {
    af::array output;
    af::array a = af::tile(af::pow(af::range(tss.dims(0)), moment), 1, tss.dims(1));
    return af::sum(tss * a, 0) / af::sum(tss, 0);
}

af::array calculateCentroid(af::array tss) { return calculateMoment(tss, 1); }

af::array calculateVariance(af::array tss) { return calculateMoment(tss, 2) - af::pow(calculateCentroid(tss), 2); }

af::array calculateSkew(af::array tss) {
    // In the limit of a dirac delta, skew should be 0 and variance 0. However, in the discrete limit,
    // the skew blows up as variance-- > 0, hence return nan when variance is smaller than a resolution of 0.5:
    af::array variance = calculateVariance(tss);
    af::array cond = variance < 0.5;
    af::array b = af::constant(af::NaN, 1, tss.dims(1), tss.type());
    af::array a =
        (calculateMoment(tss, 3) - 3 * calculateCentroid(tss) * variance - af::pow(calculateCentroid(tss), 3)) /
        af::pow(calculateVariance(tss), 1.5).as(tss.type());
    af::array out = af::select(cond, b, a);
    return out;
}

af::array calculateKurtosis(af::array tss) {
    // In the limit of a dirac delta, kurtosis should be 3 and variance 0. However, in the discrete limit,
    // the kurtosis blows up as variance-- > 0, hence return nan when variance is smaller than a resolution of 0.5:
    af::array variance = calculateVariance(tss);
    af::array cond = variance < 0.5;
    af::array b = af::constant(af::NaN, 1, tss.dims(1), tss.type());
    af::array a = (calculateMoment(tss, 4) - 4 * calculateCentroid(tss) * calculateMoment(tss, 3) +
                   6 * calculateMoment(tss, 2) * af::pow(calculateCentroid(tss), 2) - 3 * calculateCentroid(tss)) /
                  af::pow(calculateVariance(tss), 2).as(tss.type());
    af::array out = af::select(cond, b, a);
    return out;
}

af::array tsa::features::fftAggregated(af::array tss) {
    af::array output;
    af::array fftComputed;
    // If n is even, the length of the transformed axis is (n/2)+1.
    // If n is odd, the length is (n + 1) / 2.
    // The output is Hermitian - symmetric, i.e.the negative frequency terms are just the complex
    // conjugates of the corresponding positive - frequency terms, and the negative - frequency
    // terms are therefore redundant
    if (tss.dims(0) % 2 == 0) {
        // number of elements is even
        int n = (tss.dims(0) / 2) + 1;
        fftComputed = af::abs(af::fft(tss, 0))(af::seq(0, n - 1), span);
    } else {
        // number of elements is odd
        int n = (tss.dims(0) + 1) / 2;
        fftComputed = af::abs(af::fft(tss, 0))(af::seq(0, n - 1), span);
    }
    output = af::constant(0, 4, tss.dims(1), tss.type());
    output(0, span) = calculateCentroid(fftComputed);
    output(1, span) = calculateVariance(fftComputed);
    output(2, span) = calculateSkew(fftComputed);
    output(3, span) = calculateKurtosis(fftComputed);
    return output;
}

void tsa::features::fftCoefficient(af::array tss, long coefficient, af::array &real, af::array &imag, af::array &abs,
                                   af::array &angle) {
    // Calculating the FFT of all the time series contained in tss
    af::array fft = af::fft(tss);
    // Slicing by the given coefficient
    af::array fftCoefficient = fft(coefficient, span);
    // Retrieving the real, imaginary, absolute value and angle of the complex number of the given coefficient
    real = af::real(fftCoefficient);
    imag = af::imag(fftCoefficient);
    abs = af::abs(real);
    angle = af::arg(fftCoefficient);
}

af::array tsa::features::firstLocationOfMaximum(af::array tss) {
    float len = tss.dims(0);
    af::array index;
    af::array maximum;

    af::max(maximum, index, tss, 0);

    return index.as(tss.type()) / len;
}

af::array tsa::features::firstLocationOfMinimum(af::array tss) {
    // Flipping the array because ArrayFire returns the last location of the minimum by default
    af::array flipped = af::flip(tss, 0);

    af::array minimum;
    af::array index;

    // Calculating the minimum and the ocurring index
    af::min(minimum, index, flipped, 0);

    // Complementing the index since we flipped the array before
    index = af::abs(index - tss.dims(0) + 1);

    // Dividing by the length of the time series because the result is relative
    return index.as(tss.type()) / tss.dims(0);
}

af::array tsa::features::hasDuplicates(af::array tss) {
    // Array with the number of input time series in the 1st dimension of type bool
    af::array result = af::array(tss.dims(1), af::dtype::b8);

    // Doing it sequentially because af::setUnique only works with vectors
    for (long i = 0; i < tss.dims(1); i++) {
        // Calculating the unique elements for each time series
        af::array uniq = af::setUnique(tss(span, i));
        // If the number of elements differ, then the time series has duplicates
        result(i) = tss.dims(0) != uniq.dims(0);
    }

    // Transposing the array to match the dimensions of the output
    return af::transpose(result);
}

af::array tsa::features::hasDuplicateMax(af::array tss) {
    af::array maximum = af::max(tss, 0);
    return af::sum(tss == af::tile(maximum, tss.dims(0)), 0) > 1;
}

af::array tsa::features::hasDuplicateMin(af::array tss) {
    // Calculating the minimum of each time series contained in tss
    af::array minimum = af::min(tss, 0);

    // Returning if the minimum appears more than once
    return af::sum(tss == af::tile(minimum, tss.dims(0)), 0) > 1;
}

af::array tsa::features::indexMaxQuantile(af::array tss, float q) {
    float len = tss.dims(0);

    af::array positives = af::abs(tss);
    af::array sums = af::sum(positives, 0);
    af::array acum = af::accum(positives, 0);
    af::array geQ = tsa::features::firstLocationOfMaximum((acum / af::tile(sums, len)) >= q).as(tss.type());
    af::array res = ((geQ * len) + 1) / len;

    return res;
}

af::array tsa::features::kurtosis(af::array tss) {
    // Using the kurtosis function of the statistics namespace
    return tsa::statistics::kurtosis(tss);
}

af::array tsa::features::largeStandardDeviation(af::array tss, float r) {
    return af::stdev(tss, 0) > (r * (af::max(tss, 0) - af::min(tss, 0)));
}

af::array tsa::features::lastLocationOfMaximum(af::array tss) {
    // Flipping the array because ArrayFire returns the last location of the minimum by default
    af::array flipped = af::flip(tss, 0);

    af::array maximum;
    af::array index;

    // Calculating the maximum and the occuring index
    af::max(maximum, index, flipped, 0);

    // Complementing the index since we flipped the array before
    index = af::abs(index - tss.dims(0) + 1);

    // Dividing by the length of the time series because the result is relative
    return (index.as(tss.type()) + 1) / tss.dims(0);
}

af::array tsa::features::lastLocationOfMinimum(af::array tss) {
    af::array minimum;
    af::array index;

    af::min(minimum, index, tss, 0);

    return (index.as(tss.type()) + 1) / tss.dims(0);
}

af::array tsa::features::length(af::array tss) {
    int n = tss.dims(0);
    // Returning an array containing as many ns as the number of input time series in tss
    return af::tile(af::array(1, &n), tss.dims(1));
}

void tsa::features::linearTrend(af::array tss, af::array &pvalue, af::array &rvalue, af::array &intercept,
                                af::array &slope, af::array &stderr) {
    int len = tss.dims(0);
    int ntss = tss.dims(1);
    af::array yss = af::tile(af::range(len).as(tss.type()), 1, ntss);
    tsa::regression::linear(yss, tss, slope, intercept, rvalue, pvalue, stderr);
}

af::array tsa::features::longestStrikeAboveMean(af::array tss) {
    // Calculating the mean of each time series contained in tss
    af::array mean = af::mean(tss, 0);
    // Checking the elements of tss that are greater than the mean
    af::array aboveMean = (tss > af::tile(mean, tss.dims(0))).as(tss.type());

    // Doing a scan by key with the same array as the values in order to sum the consecutive 1s in the aboveMean array
    af::array scanned = af::scanByKey(aboveMean.as(af::dtype::s32), aboveMean);

    // Returning the maximum of the sum of consecutive 1s
    return af::max(scanned, 0);
}

af::array tsa::features::longestStrikeBelowMean(af::array tss) {
    af::array mean = af::mean(tss, 0);
    af::array belowMean = (tss < af::tile(mean, tss.dims(0))).as(tss.type());

    af::array result = af::scanByKey(belowMean.as(af::dtype::s32), belowMean);

    return af::max(result, 0);
}

af::array estimateFriedrichCoefficients(af::array tss, int m, float r) {
    long n = tss.dims(0);

    af::array categories = tsa::statistics::quantilesCut(tss(af::seq(n - 1), span), r);

    af::array x = af::join(1, categories, af::reorder(tss(af::seq(n - 1), span), 0, 2, 1, 3));
    x = af::join(1, x, af::reorder(af::diff1(tss, 0), 0, 2, 1, 3));

    // Doing the groupBy per input time series in tss (tss are contained along the 2nd dimension).
    // The groupBy function cannot be applied to all time series in parallel because we do not
    // know a priori the number of groups in each series.

    af::array result = af::array(m + 1, tss.dims(1), tss.type());

    for (int i = 0; i < tss.dims(1); i++) {
        af::array groupped = tsa::regularization::groupBy(x(span, span, i), af::mean, 2, 2);
        result(span, i) = tsa::polynomial::polyfit(groupped.col(0), groupped.col(1), m);
    }

    return result;
}

af::array tsa::features::maxLangevinFixedPoint(af::array tss, int m, float r) {
    af::array coefficients = estimateFriedrichCoefficients(tss, m, r);

    af::array roots = tsa::polynomial::roots(coefficients);

    return af::max(af::real(roots)).as(tss.type());
}

af::array tsa::features::maximum(af::array tss) { return af::max(tss, 0); }

af::array tsa::features::mean(af::array tss) { return af::mean(tss, 0); }

af::array tsa::features::meanAbsoluteChange(af::array tss) {
    return (tsa::features::absoluteSumOfChanges(tss) / tss.dims(0)).as(tss.type());
}

af::array tsa::features::meanChange(af::array tss) {
    float n = tss.dims(0);
    return af::sum(af::diff1(tss, 0), 0) / n;
}

af::array tsa::features::meanSecondDerivativeCentral(af::array tss) {
    int n = tss.dims(0);
    // Calculating tss(t + 2) - 2 * tss(t + 1) + tss(t) from 0 to the length of the time series minus - 2
    af::array total = tss(af::seq(0, n - 3), span);
    total -= 2 * tss(af::seq(1, n - 2), span);
    total += tss(af::seq(2, n - 1), span);
    return af::sum(total, 0) / (2 * n);
}

af::array tsa::features::median(af::array tss) { return af::median(tss, 0); }

af::array tsa::features::minimum(af::array tss) { return af::min(tss, 0); }

af::array tsa::features::numberCrossingM(af::array tss, int m) {
    return af::sum(af::abs(af::diff1(tss > m)), 0).as(tss.type());
}

af::array tsa::features::numberPeaks(af::array tss, int n) {
    int length = tss.dims(0);

    af::array tssReduced = tss(af::seq(n, length - n - 1), span);

    // Initializing it to ones
    af::array res = tssReduced == tssReduced;
    for (int i = 1; i < n + 1; i++) {
        af::array rightShifted = af::shift(tss, i)(af::seq(n, length - n - 1), span);
        af::array leftShifted = af::shift(tss, -i)(af::seq(n, length - n - 1), span);

        res = res & ((tssReduced > rightShifted) & (tssReduced > leftShifted));
    }

    return af::sum(res.as(tss.type()), 0);
}

af::array tsa::features::percentageOfReoccurringDatapointsToAllDatapoints(af::array tss, bool isSorted) {
    af::array result = af::array(1, tss.dims(1), tss.type());
    // Doing it sequentially because the setUnique function can only be used with a vector
    for (int i = 0; i < tss.dims(1); i++) {
        af::array unique = af::setUnique(tss(span, i), isSorted);
        int n = unique.dims(0);
        // The chunk size cannot be greater than the length of the unique values
        int chunkSize = std::min(n, BATCH_SIZE);
        int nChunks = std::ceil((float)n / chunkSize);

        af::array tmpResult = af::array(0, tss.type());

        for (int j = 0; j < n; j += chunkSize) {
            // The iteration space cannot be greater than what is left (n - j)
            int iterationSize = std::min(chunkSize, n - j);
            af::array uniqueChunk = unique(af::seq(j, j + iterationSize - 1));

            af::array tssTiled = af::tile(tss(span, i), 1, uniqueChunk.dims(0));
            uniqueChunk = af::transpose(af::tile(uniqueChunk, 1, tss.dims(0)));

            tmpResult = af::join(0, tmpResult, af::sum(af::sum(uniqueChunk == tssTiled, 0) > 1, 1).as(tss.type()));
        }
        result(i) = af::sum(tmpResult, 0) / (float)unique.dims(0);
    }

    return result;
}

af::array tsa::features::quantile(af::array tss, af::array q, float precision) {
    return tsa::statistics::quantile(tss, q, precision);
}

af::array tsa::features::rangeCount(af::array tss, float min, float max) {
    af::array mins = (tss > min).as(tss.type());
    af::array maxs = (tss < max).as(tss.type());

    return af::sum(mins * maxs, 0);
}

af::array tsa::features::ratioBeyondRSigma(af::array tss, float r) {
    float n = tss.dims(0);

    af::array greaterThanRSigma =
        af::abs(tss - af::tile(af::mean(tss, 0), tss.dims(0))) > af::tile(r * af::stdev(tss, 0), tss.dims(0));

    return af::sum(greaterThanRSigma.as(tss.type()), 0) / n;
}

af::array tsa::features::sampleEntropy(af::array tss) {
    long n = tss.dims(0);

    af::array std = af::stdev(tss, 0);
    std *= 0.2;

    const long chunkSize = 32768;
    long lastIterationSize = chunkSize;

    af::array query = af::array(1, chunkSize, tss.dims(1), tss.type());
    af::array reference = af::array(1, chunkSize, tss.dims(1), tss.type());

    af::array A = af::constant(0, tss.dims(1), tss.type());
    af::array B = af::constant(0, tss.dims(1), tss.type());

    // it performs a batching (or blocking) in the horizontal direction
    for (int i = 0; i < n - 1; i++) {
        // it performs a batching (or blocking) in the vertical direction
        for (int j = i + 1; j < n; j += chunkSize) {
            long iterationSize = std::min(chunkSize, n - j);
            // if our batching dimension does not match the dimension of the remaining elements, modify dimensions
            if (iterationSize != chunkSize || iterationSize != lastIterationSize) {
                lastIterationSize = iterationSize;
                query = af::array(1, iterationSize, tss.dims(1), tss.type());
                reference = af::array(1, iterationSize, tss.dims(1), tss.type());
            }

            query = af::tile(af::reorder(tss(af::seq(i, i), span), 0, 2, 1, 3), 1, iterationSize);
            reference = af::reorder(tss(af::seq(j, j + iterationSize - 1), span), 2, 0, 1, 3);

            // Get the maximum difference among all dimensions for each time series
            af::array distances = af::abs(reference - query);
            // sum the number of elements bigger than the threshhold given by (stdev*r)
            af::array count = distances <= af::tile(af::reorder(std, 0, 2, 1, 3), distances.dims(0), distances.dims(1));
            // we summarise all partial sums in sum; we accumulate all partial sums for each vertical dimension
            A += af::reorder(af::sum(af::sum(count, 0), 1), 2, 0, 1, 3);
        }
    }

    float N = n * (n - 1) / 2.0;

    B = af::tile(af::array(1, &N), tss.dims(1)).as(tss.type());

    return -af::log(A / B);
}

af::array tsa::features::skewness(af::array tss) { return tsa::statistics::skewness(tss); }

af::array tsa::features::standardDeviation(af::array tss) { return af::stdev(tss, 0); }

af::array tsa::features::sumOfReoccurringDatapoints(af::array tss, bool isSorted) {
    af::array result = af::array(1, tss.dims(1), tss.type());
    // Doing it sequentially because the setUnique function can only be used with a vector
    for (int i = 0; i < tss.dims(1); i++) {
        af::array unique = af::setUnique(tss(span, i), isSorted);
        int n = unique.dims(0);
        // The chunk size cannot be greater than the length of the unique values
        int chunkSize = std::min(n, BATCH_SIZE);

        af::array counts = af::array(0, tss.type());

        for (int j = 0; j < n; j += chunkSize) {
            // The iteration space cannot be greater than what is left (n - j)
            int iterationSize = std::min(chunkSize, n - j);
            af::array uniqueChunk = unique(af::seq(j, j + iterationSize - 1));

            af::array tssTiled = af::tile(tss(span, i), 1, uniqueChunk.dims(0));
            uniqueChunk = af::transpose(af::tile(uniqueChunk, 1, tss.dims(0)));

            counts = af::join(0, counts, af::transpose(af::sum(uniqueChunk == tssTiled, 0).as(tss.type())));
        }
        counts(counts < 2) = 0.0;
        result(i) = af::sum(counts * unique, 0);
    }

    return result;
}

af::array tsa::features::symmetryLooking(af::array tss, float r) {
    // We need to do this since the min and max functions return different results in the OpenCL and CPU
    // backends.
    if (af::getActiveBackend() != af::Backend::AF_BACKEND_CPU) {
        tss = af::flip(tss, 0);
    }
    af::array meanMedianAbsDifference = af::abs(af::mean(tss, 0) - af::median(tss, 0));
    af::array maxMinDifference = af::max(tss, 0) - af::min(tss, 0);

    return meanMedianAbsDifference < (r * maxMinDifference);
}

af::array tsa::features::valueCount(af::array tss, float v) {
    af::array value = af::tile(af::array(1, &v), tss.dims());

    return af::sum((value == tss).as(af::dtype::u32), 0);
}

af::array tsa::features::varianceLargerThanStandardDeviation(af::array tss) {
    return af::var(tss, false, 0) > af::stdev(tss, 0);
}