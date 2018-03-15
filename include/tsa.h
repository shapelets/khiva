// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <jni.h>
#include <version.h>
#include <vector>

using namespace af;

namespace tsa {

const char *version();

namespace simplification {

/**
 * @brief Definition of Point structure to represent 2D points
 */
typedef std::pair<double, double> Point;

/**
 * @brief Simplifies a set of points by applying the RamerDouglasPeucker method
 * depending on the perpendicular distance of the points and epsilon, the greater epsilon,
 * ore points are deleted.
 *
 * @param epsilon It acts as  the threshold value to decide which points should be considered
 * meaningful or not.
 *
 * @return array Array with the same dimensions as tss where the time series have been
 * adjusted for zero mean and one as standard deviation.
 */
std::vector<tsa::simplification::Point> ramerDouglasPeucker(std::vector<tsa::simplification::Point> pointList,
                                                            double epsilon);

/**
 * @brief Simplifies a set of points by applying the RamerDouglasPeucker method
 * depending on the perpendicular distance of the points and epsilon, the greater epsilon,
 * ore points are deleted.
 *
 * @param epsilon It acts as  the threshold value to decide which points should be considered
 * meaningful or not.
 *
 * @return array Array with the same dimensions as tss where the time series have been
 * adjusted for zero mean and one as standard deviation.
 */
af::array ramerDouglasPeucker(af::array pointList, double epsilon);

/**
 * @brief Simplifies a set of points by applying the visvalingam method (minimun triangle area)
 * until the number of points is reduced to @num_points_allowed.
 *
 * @param pointList Expects an input array whose dimension zero is the length of the time
 * series.
 *
 * @param numPoints Sets the number of points in pointList after the execution of the method.
 *
 * @return a vector with the same dimensions as poinList where the number of points has been
 * reduced up to numPoints.
 */
std::vector<tsa::simplification::Point> visvalingam_simplify(std::vector<tsa::simplification::Point> pointList,
                                                             int numPoints);

/**
 * @brief Simplifies a set of points by applying the visvalingam method (minimun triangle area)
 * until the number of points is reduced to @num_points_allowed.
 *
 * @param pointList Expects an input array whose dimension zero is the length of the time
 * series.
 *
 * @param numPoints Sets the number of points in pointList after the execution of the method.
 *
 * @return a vector with the same dimensions as poinList where the number of points has been
 * reduced up to numPoints.
 */
af::array visvalingam_simplify(af::array pointList, int numPoints);
};  // namespace simplification

namespace regularization {

// array xyz(array source);
};  // namespace regularization

namespace normalization {

/**
 * @brief Calculates a new set of timeseries with zero mean and
 * standard deviation one.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 *
 * @param epsilon Minimum standard deviation to consider.  It acts a a gatekeeper for
 * those time series that may be constant or near constant.
 *
 * @return af::array Array with the same dimensions as tss where the time series have been
 * adjusted for zero mean and one as standard deviation.
 */
af::array znorm(af::array tss, double epsilon = 0.00000001);

/**
 * @brief Adjusts the time series in the given input and performs z-norm
 * inplace (without allocating further memory)
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 *
 * @param epsilon Minimum standard deviation to consider.  It acts a a gatekeeper for
 * those time series that may be constant or near constant.
 */
void znormInPlace(af::array &tss, double epsilon = 0.00000001);

/**
 * @brief Normalizes the given time series according to its minimum and maximun value and
 * adjusts each value within the range [low, high]
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 *
 * @param high Maximum final value.  Defaults to 1.0
 * @param low  Minimum final value.  Defaults to 0.0
 *
 * @param epsilon Safeguard for constant (or near constant) time series as the operation implies
 * a unit scale operation between min and max values in the tss.
 *
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * have been normalized by maximun and minimun values, and scaled as per high and low parameters.
 */
af::array maxMinNorm(af::array tss, double high = 1.0, double low = 0.0, double epsilon = 0.00000001);

/**
 * @brief Same as maxMinNorm, but it performs the operation in place, without allocating further memory.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 *
 * @param high Maximum final value.  Defaults to 1.0
 * @param low  Minimum final value.  Defaults to 0.0
 *
 * @param epsilon Safeguard for constant (or near constant) time series as the operation implies
 * a unit scale operation between min and max values in the tss.
 */
void maxMinNormInPlace(af::array &tss, double high = 1.0, double low = 0.0, double epsilon = 0.00000001);

/**
 * @brief Normalizes the given time series according to its maximun value and
 * adjusts each value within the range (-1, 1)
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of time series.
 *
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * have been normalized by dividing each number by 10^j, where j is the number of integer digits of
 * the max number in the timeseries
 */
af::array decimalScalingNorm(af::array tss);

/**
 * @brief Same as decimalScalingNorm, but it performs the operation in place, without allocating further
 *  memory.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of time series.
 */
void decimalScalingNormInPlace(af::array &tss);

// adaptive normalization
};  // namespace normalization

namespace features {

/**
 * @brief Calculates the sum over the square values of the timeseries
 *
 * @param base Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * contains the sum of the suares values in the timeseries
 */
af::array absEnergy(af::array base);

/**
 * @brief Calculates the sum over the absolute value of consecutive changes in the time series
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * contains absolute value of consecutive changes in the time series
 */
af::array absoluteSumOfChanges(af::array tss);

/**
 * @brief Calculates the value of an aggregation function f_agg (e.g. var or mean) of the autocorrelation
 * (Compare to http://en.wikipedia.org/wiki/Autocorrelation#Estimation), taken over different all possible
 * lags (1 to length of x)
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * contains the aggregated correaltion for each timeseries
 */
af::array aggregatedAutocorrelation(af::array ts,
                                    af::array (*aggregationFunction)(const af::array &, const bool, const dim_t));

/**
 * @brief Calculates the value of an aggregation function f_agg (e.g. var or mean) of the autocorrelation
 * (Compare to http://en.wikipedia.org/wiki/Autocorrelation#Estimation), taken over different all possible
 * lags (1 to length of x)
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * contains the aggregated correaltion for each timeseries
 */
af::array aggregatedAutocorrelation(af::array ts, af::array (*aggregationFunction)(const af::array &, const int));

/**
 * @brief Calculates the value of an aggregation function f_agg (e.g. var or mean) of the autocorrelation
 * (Compare to http://en.wikipedia.org/wiki/Autocorrelation#Estimation), taken over different all possible
 * lags (1 to length of x)
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * contains the aggregated correaltion for each timeseries
 */
af::array aggregatedAutocorrelation(af::array ts, af::array (*aggregationFunction)(const af::array &, const dim_t));

/**
 * @brief Calculates a linear least-squares regression for values of the time series that were aggregated
 * over chunks versus the sequence from 0 up to the number of chunks minus one
 *
 * @param t The time series to calculate the features of
 * @param chunkSize The chunkSize used to aggregate the data
 * @param aggregationFunction Function to be used in the aggregation
 * @param slope Slope of the regression line
 * @param intercept Intercept of the regression line
 * @param rvalue Correlation coefficient
 * @param pvalue Two-sided p-value for a hypothesis test whose null hypothesis is
 * that the slope is zero, using Wald Test with t-distribution of
 * the test statistic
 * @param stderrest Standard error of the estimated gradient
 */
void aggregatedLinearTrend(af::array t, long chunkSize, af::array (*aggregationFunction)(const af::array &, const int),
                           af::array &slope, af::array &intercept, af::array &rvalue, af::array &pvalue,
                           af::array &stderrest);

/**
 * @brief Calculates a linear least-squares regression for values of the time series that were aggregated
 * over chunks versus the sequence from 0 up to the number of chunks minus one
 *
 * @param t The time series to calculate the features of
 * @param chunkSize The chunkSize used to aggregate the data
 * @param aggregationFunction Function to be used in the aggregation
 * @param slope Slope of the regression line
 * @param intercept Intercept of the regression line
 * @param rvalue Correlation coefficient
 * @param pvalue Two-sided p-value for a hypothesis test whose null hypothesis is
 * that the slope is zero, using Wald Test with t-distribution of
 * the test statistic
 * @param stderrest Standard error of the estimated gradient
 */
void aggregatedLinearTrend(af::array t, long chunkSize,
                           af::array (*aggregationFunction)(const af::array &, const dim_t), af::array &slope,
                           af::array &intercept, af::array &rvalue, af::array &pvalue, af::array &stderrest);

/**
 * @brief Calculates a vectorized Approximate entropy algorithm.
 * https://en.wikipedia.org/wiki/Approximate_entropy
 * For short time-series this method is highly dependent on the parameters, but should be stable for N > 2000,
 * see: Yentes et al. (2012) - The Appropriate Use of Approximate Entropy and Sample Entropy with Short Data Sets
 * Other shortcomings and alternatives discussed in:
 * Richman & Moorman (2000) - Physiological time-series analysis using approximate entropy and sample entropy
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @param m Length of compared run of data
 * @param r Filtering level, must be positive
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * contains the vectorized Approximate entropy for all the input time series in tss
 */
af::array approximateEntropy(af::array tss, int m, float r);

/**
 * @brief Calculates the autocorrelation of the specified lag for the given time
 * series
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param lag The lag
 * @return af::array The autocorrelation value for the given time series
 */
af::array autocorrelation(af::array tss, long lag);

/**
 * @brief Calculates the binned entropy for the given time series and number of bins
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param max_bins The number of bins
 * @return af::array The binned entropy value for the given time series
 */
af::array binnedEntropy(af::array tss, int max_bins);

/**
 * @brief Calculates the Schreiber, T. and Schmitz, A. (1997) measure of non-linearity
 * for the given time series
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param lag The lag
 * @return af::array The non-linearity value for the given time series
 */
af::array c3(af::array tss, long lag);

/**
 * @brief Calculates an estimate for the time series complexity defined by
 * Batista, Gustavo EAPA, et al (2014). (A more complex time series has more peaks,
 * valleys, etc.)
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param zNormalize Controls whether the time series should be z-normalized or not
 * @return af::array The complexity value for the given time series
 */
af::array cidCe(af::array tss, bool zNormalize = false);

/**
 * @brief Calculates the number of values in the time series that are higher than
 * the mean
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array The number of values in the time series that are higher
 * than the mean
 */
af::array countAboveMean(af::array tss);

/**
 * @brief Calculates the number of values in the time series that are lower than
 * the mean
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array The number of values in the time series that are lower
 * than the mean
 */
af::array countBelowMean(af::array tss);

/**
 * @brief Calculates the sum of squares of chunk i out of N chunks expressed as a ratio
 * with the sum of squares over the whole series. segmentFocus should be lower
 * than the number of segments
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param numSegments The number of segments to divide the series into
 * @param segmentFocus The segment number (starting at zero) to return a feature on
 * @return af::array The energy ratio by chunk of the time series
 */
af::array energyRatioByChunks(af::array tss, long numSegments, long segmentFocus);

/**
 * @brief Calculates the fourier coefficients of the one-dimensional discrete
 * Fourier Transform for real input by fast fourier transformation algorithm
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param coefficient The coefficient to extract from the FFT
 * @param real The real part of the coefficient
 * @param imag The imaginary part of the cofficient
 * @param abs The absolute value of the coefficient
 * @param angle The angle of the coefficient
 */
void fftCoefficient(af::array tss, long coefficient, af::array &real, af::array &imag, af::array &_abs,
                    af::array &angle);

/**
 * @brief Calculates the first relative location of the maximal value for each timeseries.
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array The first relative location of the maximum value to the length of the timeseries,
 *  for each timeseries.
 */
af::array firstLocationOfMaximum(af::array tss);

/**
 * @brief Calculates the first location of the minimal value of each time series. The position
 * is calculated relatively to the length of the series
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array the first relative location of the minimal value of each series
 */
af::array firstLocationOfMinimum(af::array tss);

/**
 * @brief Calculates if the input time series contain duplicated elements
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array Array containing True if the time series contains duplicated elements
 * and false otherwise
 */
af::array hasDuplicates(af::array tss);

/**
 * @brief Calculates if the maximum within input time series is duplicated
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array Array containing True if the maximum value of the time series is duplicated
 * and false otherwise
 */
af::array hasDuplicateMax(af::array tss);

/**
 * @brief Calculates if the minimum of input time series is duplicated
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array Array containing True if the minimum of the time series is duplicated
 * and false otherwise
 */
af::array hasDuplicateMin(af::array tss);

/**
 * @brief Returns the kurtosis of tss (calculated with the adjusted Fisher-Pearson
 * standardized moment coefficient G2).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @param q The quantile
 * @return af::array The index mass of quantile q, for each timeseries in tss
 */
af::array indexMaxQuantile(af::array tss, float q);

/**
 * @brief Returns the kurtosis of tss (calculated with the adjusted Fisher-Pearson
 * standardized moment coefficient G2).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @return af::array The kurtosis of tss
 */
af::array kurtosis(af::array tss);

/**
 * @brief Calculates the last location of the maximum value of each time series. The position
 * is calculated relatively to the length of the series
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array The last relative location of the maximum value of each series
 */
af::array lastLocationOfMaximum(af::array tss);

/**
 * @brief Calculates the last location of the minimum value of each time series. The position
 * is calculated relatively to the length of the series
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array The last relative location of the minimum value of each series
 */
af::array lastLocationOfMinimum(af::array tss);

/**
 * @brief Returns the length of the input time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @return af::array The length of tss
 */
af::array length(af::array tss);

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Primitive of the cidCe function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length tss length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series in tss.
 * @param zNormalize Controls whether the time series should be z-normalized or not.
 * @param result The complexity value for the given time series.
 */
void cidCe(double *tss_time_series, long *tss_length, long *tss_number_of_tss, bool *zNormalize, double *result);

/**
 * @brief Primitive of the absEnergy function.
 *
 * @param time_series Time series concatenated in a single row.
 * @param time_series_length time_series length (All time series need to have the same length).
 * @param number_of_time_series Number of time series in time_series.
 * @param primitive_result Absolute Energy.
 */
void abs_energy(double *time_series, long *time_series_length, long *number_of_time_series, double *primitive_result);

/**
 * @brief Primitive of the absoluteSumOfChanges function.
 *
 * @param time_series  Time series concatenated in a single row.
 * @param time_series_length time_series length (All time series need to have the same length).
 * @param number_of_time_series  Number of time series.
 * @param primitive_result Absolute sum of changes.
 */
void absolute_sum_of_changes(double *time_series, long *time_series_length, long *number_of_time_series,
                             double *primitive_result);

/**
 * @brief Primitive of the c3 function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param lag The lag
 * @param result The non-linearity value for the given time series.
 */
void c3(double *tss, long *tss_length, long *tss_number_of_tss, long *lag, double *result);

/**
 * @brief JNI interface of the c3 function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series.
 * @param lag The lag
 * @param result The non-linearity value for the given time series.
 */
JNIEXPORT void JNICALL Java_tsa_TSA_c3(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                       jlong tssNumberOfTss, jlong lag, jdoubleArray result);

/**
 * @brief JNI interface of the cidCe function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength tss length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series in tss.
 * @param zNormalize Controls whether the time series should be z-normalized or not.
 * @param result The complexity value for the given time series.
 */
JNIEXPORT void JNICALL Java_tsa_TSA_cidCe(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                          jlong tssNumberOfTss, jboolean zNormalize, jdoubleArray result);

/**
 * @brief JNI interface of the absoluteSumOfChanges function.
 *
 * @param timeSeries  Time series concatenated in a single row.
 * @param timeSeriesLength Length of each time series.
 * @param numberOfTimeSeries Number of time series into timeSeries.
 * @param jResult Absolute sum of changes.
 */
JNIEXPORT void JNICALL Java_tsa_TSA_absoluteSumOfChanges(JNIEnv *env, jobject thisObj, jdoubleArray timeSeries,
                                                         jlong timeSeriesLength, jlong numberOfTimeSeries,
                                                         jdoubleArray jResult);

/**
 * @brief JNI interface of the absEnergy function.
 *
 * @param timeSeries Time series concatenated in a single row.
 * @param timeSeriesLength Length of each time series.
 * @param numberOfTimeSeries Number of time series into timeSeries.
 * @param jResult Absolute Energy.
 */
JNIEXPORT void JNICALL Java_tsa_TSA_absEnergy(JNIEnv *env, jobject thisObj, jdoubleArray timeSeries,
                                              jlong timeSeriesLength, jlong numberOfTimeSeries, jdoubleArray jResult);

#ifdef __cplusplus
}
#endif
};  // namespace features

namespace dimensionality {

/**
 * @brief Piecewise Aggregate Approximation. It reduces the dimensionality of the timeseries
 * given by @begin and @last iterators to a number equal to bins. This algorithim divides the
 * whole timeseries in @bins partitions and computes the average of each partition
 *
 * @param begin iterator to the first element
 *
 * @param last iterator to the last element
 *
 * @param bins sets the total number of divisions
 *
 * @return result A vector with the reduced dimensionality.
 */
af::array PAA(af::array a, int bins);

/**
 * @brief Piecewise Aggregate Approximation. It reduces the dimensionality of the timeseries
 * given by @begin and @last iterators to a number equal to bins. This algorithim divides the
 * whole timeseries in @bins partitions and computes the average of each partition
 *
 * @param begin iterator to the first element
 *
 * @param last iterator to the last element
 *
 * @param bins sets the total number of divisions
 *
 * @return result A vector with the reduced dimensionality.
 */
template <class InputIt>
std::vector<tsa::simplification::Point> PAA_CPU(InputIt begin, InputIt last, int bins) {
    double xrange = (*(last - 1)).first - (*begin).first;
    double width_bin = xrange / bins;
    double reduction = bins / xrange;

    std::vector<double> sum(bins, 0.0);
    std::vector<int> counter(bins, 0);
    std::vector<tsa::simplification::Point> result(bins, tsa::simplification::Point(0.0, 0.0));

    // Iterating over the  timeseries
    for (auto i = begin; i != last; i++) {
        int pos = std::min((*i).first * reduction, (double)(bins - 1));
        sum[pos] += (*i).second;
        counter[pos] = counter[pos] + 1;
    }

    // Compute the average per bin
    for (int i = 0; i < bins; i++) {
        result[i].first = (width_bin * i) + (width_bin / 2.0);
        result[i].second = sum[i] / counter[i];
    }
    return result;
}

/**
 * @brief Symbolic Aggregate approXimation. It transforms a numeric timeseries into
 * a timeseries of symbols with the same size.
 *
 * @param a, array with the input timeseries
 *
 * @param alphabet_size, number of element within the alphabet
 *
 * @return result An array of symbols.
 */
std::vector<int> SAX(af::array a, int alphabet_size);

/**
 * @brief Calculates the number of Perceptually Important Points in the time series.
 * Fu TC, Chung FL, Luk R, and Ng CM (2008) Representing financial time series based on data point
 * importance. Engineering Applications of Artificial Intelligence, 21(2):277-300
 *
 * @param pointList Expects an input array whose dimension zero is the length of the
 * time series
 * @param numberIPs The number of points to return
 * @return af::array with the numPoints most Perceptually Important
 */
af::array PIP(af::array ts, int numberIPs);

// PLA
// Principal Components A.
// Random Projections
};  // namespace dimensionality

namespace distances {

/**
 * @brief Calculates euclidean distances between timeseries.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 *
 * @return array Returns an upper triangular matrix where each position corresponds to the
 * distance between two time series. Diagonal elements will be zero.  For example:
 * Position row 0 column 1 will record the distance between time series 0
 * and time series 1.
 */
af::array euclidean(af::array tss);

/**
 * @brief Calculates non squared version of the euclidean distance.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 *
 * @return array Returns an upper triangular matrix where each position corresponds to the
 * distance between two time series. Diagonal elements will be zero.  For example:
 * Position row 0 column 1 will record the distance between time series 0
 * and time series 1.
 */
af::array squaredEuclidean(af::array tss);

// habituales + la ncc

// una funcion que dada un tipo de destiancia retorna
// una matriz triangular de distancias entre timeseries
};  // namespace distances

namespace matrix {
/**
 * @brief Calculates the sliding dot product of the time series 'q' against t
 *
 * @param q Array whose first dimension is the length of the query time series
 * and the last dimension is the number of time series to calculate
 * @param t Array with the second time series in the first dimension
 * @return array Returns an array with as many elements as 't' in the first dimension
 * and as many elements as the last dimension of 'q' in the last dimension
 */
af::array slidingDotProduct(af::array q, af::array t);

/**
 * @brief Calculates the moving average and standard deviation of the time series 't'.
 *
 * @param t Input time series. Multiple time series
 * @param a Auxiliary array to be used in the function calculateDistanceProfile. Use
 * the overloaded method without this parameter
 * @param m Window size
 * @param mean Output array containing the moving average
 * @param stdev Output array containing the moving standard deviation
 */
void meanStdev(af::array t, af::array &a, long m, af::array &mean, af::array &stdev);

/**
 * @brief Calculates the moving average and standard deviation of the time series 't'.
 *
 * @param t Input time series. Multiple time series
 * @param m Window size
 * @param mean Output array containing the moving average
 * @param stdev Output array containing the moving standard deviation
 */
void meanStdev(af::array t, long m, af::array &mean, af::array &stdev);

/**
 * @brief Function to generate a band matrix of batchSizeXtsLength with the offset batchStart
 *
 * @param m Subsequence length used to generate a band of m/2 at each side
 * @param batchSize size of the first dimension
 * @param batchStart offset of the band matrix
 * @param tsLength size of the second dimension of the matrix
 * @return af::array
 */
af::array generateMask(long m, long batchSize, long batchStart, long tsLength);

/**
 * @brief Calculates the distance between 'q' and the time series 't', which produced the sliding. Multiple queries can
 * be computed simultaneously in the last dimension of 'q'.
 * @param m Subsequence length (required to mask the minimum m/2 positions left and right in case ignoreTrivial is true)
 * @param qt The sliding dot product of 'q' and 't'
 * @param a Auxiliary array computed using the meanStdev function. This array contains a
 * precomputed fixed value to speed up the distance calculation
 * @param sum_q Sum of the values contained in 'q'
 * @param sum_q2 Sum of squaring the values contained in 'q'
 * @param mean_t Moving average of 't' using a window size equal to the number of elements
 * in 'q'
 * @param sigma_t Moving standard deviation of 't' using a window size equal to the number of elements
 * in 'q'
 * @param mask Mask band matrix to filter the trivial match of a subsequence with itself
 * @param distance Resulting minimal distance
 * @param index Position where the minimum is occurring
 * @param batchStart Indicates where the currently computed batch starts. Defaults to 0 for the parallel case. The
 * parameter is used to determine the mask for the trivial matches.
 */
void calculateDistanceProfile(long m, af::array qt, af::array a, af::array sum_q, af::array sum_q2, af::array mean_t,
                              af::array sigma_t, af::array mask, af::array &distance, af::array &index);

/**
 * @brief Calculates the distance between 'q' and the time series 't', which produced the sliding. Multiple queries can
 * be computed simultaneously in the last dimension of 'q'.
 * @param m Subsequence length (required to mask the minimum m/2 positions left and right in case ignoreTrivial is true)
 * @param qt The sliding dot product of 'q' and 't'
 * @param a Auxiliary array computed using the meanStdev function. This array contains a
 * precomputed fixed value to speed up the distance calculation
 * @param sum_q Sum of the values contained in 'q'
 * @param sum_q2 Sum of squaring the values contained in 'q'
 * @param mean_t Moving average of 't' using a window size equal to the number of elements
 * in 'q'
 * @param sigma_t Moving standard deviation of 't' using a window size equal to the number of elements
 * in 'q'
 * @param distance Resulting minimal distance
 * @param index Position where the minimum is occurring
 */
void calculateDistanceProfile(long m, af::array qt, af::array a, af::array sum_q, af::array sum_q2, af::array mean_t,
                              af::array sigma_t, af::array &distance, af::array &index);

/**
 * @brief
 *
 * @param q Array whose first dimension is the length of the query time series
 * and the last dimension is the number of time series to calculate
 * @param t Array with the second time series in the first dimension
 * @param m Subsequence length (required to mask the minimum m/2 positions left and right in case ignoreTrivial is true)
 * @param a Auxiliary array computed using the meanStdev function. This array contains a
 * precomputed fixed value to speed up the distance calculation
 * * @param mean_t Moving average of 't' using a window size equal to the number of elements
 * in 'q'
 * @param sigma_t Moving standard deviation of 't' using a window size equal to the number of elements
 * in 'q'
 * @param ignoreTrivial Boolean value that indicates whether the function should consider the trivial match of
 * a subsequence with itself or not
 * @param distance Resulting minimal distance
 * @param index Position where the minimum is occurring
 */
void mass(af::array q, af::array t, long m, af::array a, af::array mean_t, af::array sigma_t, af::array mask,
          af::array &distance, af::array &index);

/**
 * @brief
 *
 * @param q Array whose first dimension is the length of the query time series
 * and the last dimension is the number of time series to calculate
 * @param t Array with the second time series in the first dimension
 * @param m Subsequence length (required to mask the minimum m/2 positions left and right in case ignoreTrivial is true)
 * @param a Auxiliary array computed using the meanStdev function. This array contains a
 * precomputed fixed value to speed up the distance calculation
 * * @param mean_t Moving average of 't' using a window size equal to the number of elements
 * in 'q'
 * @param sigma_t Moving standard deviation of 't' using a window size equal to the number of elements
 * in 'q'
 * @param distance Resulting minimal distance
 * @param index Position where the minimum is occurring
 */
void mass(af::array q, af::array t, long m, af::array a, af::array mean_t, af::array sigma_t, af::array &distance,
          af::array &index);

/**
 * @brief STAMP algorithm to calculate the matrix profile between 'ta' and 'tb' using a subsequence length
 * of 'm'
 *
 * @param ta Query time series
 * @param tb Reference time series
 * @param m Subsequence length
 * @param profile The matrix profile, which reflects the distance to the closer element of the subsequence
 * from 'ta' in 'tb'
 * @param index The matrix profile index, which points to where the previously mentioned minimum is located
 */
void stomp(af::array ta, af::array tb, long m, af::array &profile, af::array &index);

/**
 * @brief STAMP algorithm to calculate the matrix profile between 't' and itself using a subsequence length
 * of 'm'. This method filters the trivial matches.
 *
 * @param t Query and reference time series
 * @param m Subsequence length
 * @param profile The matrix profile, which reflects the distance to the closer element of the subsequence
 * from 't' in a different location of itself
 * @param index The matrix profile index, which points to where the previously mentioned minimum is located
 */
void stomp(af::array t, long m, af::array &profile, af::array &index);

/**
 * @brief This function extracts the best N motifs from a previously calculated matrix profile
 *
 * @param profile The matrix profile containing the minimum distance of each subsequence
 * @param index The matrix profile index containing where each minimum occurs
 * @param n Number of motifs to extract
 * @param motifs The distance of the best N motifs
 * @param motifsIndices The indices of the best N motifs
 * @param subsequenceIndices The indices of the query sequences that produced the minimum reported in the motifs
 * output array
 */
void findBestNMotifs(af::array profile, af::array index, long n, af::array &motifs, af::array &motifsIndices,
                     af::array &subsequenceIndices);

/**
 * @brief This function extracts the best N discords from a previously calculated matrix profile
 *
 * @param profile The matrix profile containing the minimum distance of each subsequence
 * @param index The matrix profile index containing where each minimum occurs
 * @param n Number of discords to extract
 * @param discords The distance of the best N discords
 * @param discordIndices The indices of the best N discords
 * @param subsequenceIndices The indices of the query sequences that produced the discords reported in the discords
 * output array
 */
void findBestNDiscords(af::array profile, af::array index, long n, af::array &discords, af::array &discordsIndices,
                       af::array &subsequenceIndices);

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Primitive of the findBestNDiscords function.
 *
 * @param profile The matrix profile containing the minimum distance of each
 * subsequence
 * @param The matrix profile index containing the index of the most similar
 * subsequence
 * @param length_profile Length of the matrix profile
 * @param n Number of discords to extract
 * @param discord_distances The distance of the best N discords
 * @param discord_indices The indices of the best N discords
 * @param subsequence_indices The indices of the query sequences that produced
 * the "N" bigger discords.
 */
void find_best_n_discords(double *profile, unsigned int *index, long *length_profile, long *n,
                          double *discord_distances, int *discord_indices, int *subsequence_indices);

/**
 * @brief Primitive of the findBestNMotifs function.
 *
 * @param profile The matrix profile containing the minimum distance of each
 * subsequence
 * @param index The matrix profile index containing where each minimum occurs
 * @param length_profile Length of the matrix profile
 * @param n Number of motifs to extract
 * @param motif_distances The distance of the best N motifs
 * @param motif_indices The indices of the best N motifs
 * @param subsequence_indices The indices of the query sequences that produced
 * the minimum reported in the motifs
 */
void find_best_n_motifs(double *profile, unsigned int *index, long *length_profile, long *n, double *motif_distances,
                        int *motif_indices, int *subsequence_indices);

/**
 * @brief  Primitive of the STOMP algorithm.
 *
 * @param ta Pointer of an array of doubles with the first time series values.
 * @param tb Pointer of an array of doubles with the second time series values.
 * @param lta Pointer to an integer with the length of the first time series.
 * @param ltb Pointer to an integer with the length of the second time series.
 * @param m Pointer to a long with the length of the subsequence.
 * @param p Pointer to an initialized array of doubles for storing the distance
 * profile.
 * @param i Pointer to an initialized array of doubles for storing the index
 * profile.
 */
void stomp(double *ta, double *tb, long *lta, long *ltb, long *m, double *p, unsigned int *i);

/**
 * @brief Primitive of the STOMP self join algorithm.
 *
 * @param ta Pointer of an array of doubles with the first time series values.
 * @param lta Pointer to an integer with the length of the first time series.
 * @param m Pointer to a long with the length of the subsequence.
 * @param p Pointer to an initialized  array of doubles for storing the distance
 * profile.
 * @param i Pointer to an initialized  array of doubles for storing the index
 * profile.
 */
void stomp_self_join(double *ta, long *lta, long *m, double *p, unsigned int *i);

/**
 * @brief JNI interface of findBestNMotifs function.
 *
 * @param profile The matrix profile containing the minimum distance of each
 * subsequence
 * @param index The matrix profile index containing where each minimum occurs
 * @param lengthProfile Length of the matrix profile
 * @param n Number of motifs to extract
 * @param jMotifDistances The distance of the best N motifs
 * @param jMotifIndices The indices of the best N motifs
 * @param jSubsequenceIndices The indices of the query sequences that produced
 * the minimum reported in the motifs
 */
JNIEXPORT void JNICALL Java_tsa_TSA_findBestNMotifs(JNIEnv *env, jobject thisObj, jdoubleArray profile, jintArray index,
                                                    jlong lengthProfile, jlong n, jdoubleArray jMotifDistances,
                                                    jintArray jMotifIndices, jintArray jSubsequenceIndices);

/**
 * @brief JNI interface of findBestNDiscords function.
 *
 * @param profile The matrix profile containing the minimum distance of each
 * subsequence
 * @param index The matrix profile index containing where each maximum occurs
 * @param lengthProfile Length of the matrix profile
 * @param n Number of discords to extract
 * @param jDiscordDistances The distance of the best N discords
 * @param jDiscordIndices The indices of the best N discords
 * @param jSubsequenceIndices The indices of the query sequences that produced
 * the "N" bigger discords.
 */
JNIEXPORT void JNICALL Java_tsa_TSA_findBestNDiscords(JNIEnv *env, jobject thisObj, jdoubleArray profile,
                                                      jintArray index, jlong lengthProfile, jlong n,
                                                      jdoubleArray jDiscordDistances, jintArray jDiscordIndices,
                                                      jintArray jSubsequenceIndices);

/**
 * @brief JNI interface of the STOMP algorithm.
 *
 * @param ta Jarray of doubles with the first time series values.
 * @param tb Jarray of doubles with the second time series values.
 * @param lta Jinteger with the length of the first time series.
 * @param ltb Jinteger with the length of the second time series.
 * @param m Jong with the length of the subsequence.
 * @param p initialized Jarray of doubles for storing the distance profile.
 * @param i initialized Jarray of doubles for storing the index profile.
 */
JNIEXPORT void JNICALL Java_tsa_TSA_stomp(JNIEnv *env, jobject thisObj, jdoubleArray ta, jdoubleArray tb, jlong lta,
                                          jlong ltb, jlong m, jdoubleArray p, jintArray i);

/**
 * @brief JNI interface of the STOMP Self Join algorithm.
 *
 * @param ta Jarray of doubles with the first time series values.
 * @param lta Jinteger with the length of the first time series.
 * @param m Jlong with the length of the subsequence.
 * @param p Jarray of doubles for storing the distance profile.
 * @param i Jarray of doubles for storing the index profile.
 */
JNIEXPORT void JNICALL Java_tsa_TSA_stompSelfJoin(JNIEnv *env, jobject thisObj, jdoubleArray ta, jlong lta, jlong m,
                                                  jdoubleArray p, jintArray i);

#ifdef __cplusplus
}
#endif
};  // namespace matrix

namespace statistics {
/**
 * @brief Returns the covariance matrix of the time series contained in the two input arrays
 *
 * @param xss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @param yss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @return af::array The covariance matrix of the variables
 */
af::array covariance(af::array xss, af::array yss);

/**
 * @brief Returns the kth moment of the given time series
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @param k The specific moment to calculate
 * @return af::array The kth moment of the given time series
 */
af::array moment(af::array tss, int k);

/**
 * @brief Estimates standard deviation based on a sample.
 * The standard deviation is calculated using the "n-1" method
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @return af::array The sample standard deviation
 */
af::array sampleStdev(af::array tss);

/**
 * @brief Returns the kurtosis of tss (calculated with the adjusted Fisher-Pearson
 * standardized moment coefficient G2).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @return af::array The kurtosis of tss
 */
af::array kurtosis(af::array tss);
};  // namespace statistics

namespace regression {

/**
 * @brief Calculate a linear least-squares regression for two sets of measurements.
 * Both arrays should have the same length
 *
 * @param xss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @param yss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @param slope Slope of the regression line
 * @param intercept Intercept of the regression line
 * @param rvalue Correlation coefficient
 * @param pvalue Two-sided p-value for a hypothesis test whose null hypothesis is
 * that the slope is zero, using Wald Test with t-distribution of
 * the test statistic
 * @param stderrest Standard error of the estimated gradient
 */
void linear(af::array xss, af::array yss, af::array &slope, af::array &intercept, af::array &rvalue, af::array &pvalue,
            af::array &stderrest);
};  // namespace regression
};  // namespace tsa
