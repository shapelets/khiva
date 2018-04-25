// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <tsa/features.h>
#include <tsa_c/features.h>

#ifdef __cplusplus
extern "C" {
#endif

void abs_energy(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::absEnergy(var).get());
}

void absolute_sum_of_changes(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::absoluteSumOfChanges(var).get());
}

void aggregated_autocorrelation(af_array *array, int aggregation_function, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());

    switch (aggregation_function) {
        case 0:
            af_retain_array(result, tsa::features::aggregatedAutocorrelation(var, af::mean).get());
            break;
        case 1:
            af_retain_array(result, tsa::features::aggregatedAutocorrelation(var, af::median).get());
            break;
        case 2:
            af_retain_array(result, tsa::features::aggregatedAutocorrelation(var, af::min).get());
            break;
        case 3:
            af_retain_array(result, tsa::features::aggregatedAutocorrelation(var, af::max).get());
            break;
        case 4:
            af_retain_array(result, tsa::features::aggregatedAutocorrelation(var, af::stdev).get());
            break;
        case 5:
            af_retain_array(result, tsa::features::aggregatedAutocorrelation(var, af::var).get());
            break;
        default:
            af_retain_array(result, tsa::features::aggregatedAutocorrelation(var, af::mean).get());
            break;
    }
}

void aggregated_linear_trend(af_array *array, long chunkSize, int aggregation_function, af_array *slope,
                             af_array *intercept, af_array *rvalue, af_array *pvalue, af_array *stderrest) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array primitive_slope;
    af::array primitive_intercept;
    af::array primitive_rvalue;
    af::array primitive_pvalue;
    af::array primitive_stderrest;

    switch (aggregation_function) {
        case 0:
            tsa::features::aggregatedLinearTrend(var, chunkSize, af::mean, primitive_slope, primitive_intercept,
                                                 primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
        case 1:
            tsa::features::aggregatedLinearTrend(var, chunkSize, af::median, primitive_slope, primitive_intercept,
                                                 primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
        case 2:
            tsa::features::aggregatedLinearTrend(var, chunkSize, af::min, primitive_slope, primitive_intercept,
                                                 primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
        case 3:
            tsa::features::aggregatedLinearTrend(var, chunkSize, af::max, primitive_slope, primitive_intercept,
                                                 primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
        case 4:
            tsa::features::aggregatedLinearTrend(var, chunkSize, af::stdev, primitive_slope, primitive_intercept,
                                                 primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
        default:
            tsa::features::aggregatedLinearTrend(var, chunkSize, af::mean, primitive_slope, primitive_intercept,
                                                 primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
    }
    af_retain_array(slope, primitive_slope.get());
    af_retain_array(intercept, primitive_intercept.get());
    af_retain_array(rvalue, primitive_rvalue.get());
    af_retain_array(pvalue, primitive_pvalue.get());
    af_retain_array(stderrest, primitive_stderrest.get());
}

void approximate_entropy(af_array *array, int m, float r, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::approximateEntropy(var, m, r).get());
}

void cross_covariance(af_array *xss, af_array *yss, bool unbiased, af_array *result) {
    af::array var_xss = af::array(*xss);
    af_retain_array(xss, var_xss.get());
    af::array var_yss = af::array(*yss);
    af_retain_array(yss, var_yss.get());
    af_retain_array(result, tsa::features::crossCovariance(var_xss, var_yss, unbiased).get());
}

void auto_covariance(af_array *array, bool unbiased, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::autoCovariance(var, unbiased).get());
}

void cross_correlation(af_array *xss, af_array *yss, bool unbiased, af_array *result) {
    af::array var_xss = af::array(*xss);
    af_retain_array(xss, var_xss.get());
    af::array var_yss = af::array(*yss);
    af_retain_array(yss, var_yss.get());
    af_retain_array(result, tsa::features::crossCorrelation(var_xss, var_yss, unbiased).get());
}

void auto_correlation(af_array *array, long max_lag, bool unbiased, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::autoCorrelation(var, max_lag, unbiased).get());
}

void binned_entropy(af_array *array, int max_bins, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::binnedEntropy(var, max_bins).get());
}

void c3(af_array *array, long lag, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::c3(var, lag).get());
}

void cid_ce(af_array *array, bool zNormalize, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::cidCe(var, zNormalize).get());
}

void count_above_mean(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::countAboveMean(var).get());
}

void count_below_mean(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::countBelowMean(var).get());
}

void cwt_coefficients(af_array *array, af_array *width, int coeff, int w, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array var_width = af::array(*width);
    af_retain_array(width, var_width.get());
    af_retain_array(result, tsa::features::cwtCoefficients(var, var_width, coeff, w).get());
}

void energy_ratio_by_chunks(af_array *array, long num_segments, long segment_focus, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::energyRatioByChunks(var, num_segments, segment_focus).get());
}

void fft_aggregated(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::fftAggregated(var).get());
}

void fft_coefficient(af_array *array, long coefficient, af_array *real, af_array *imag, af_array *absolute,
                    af_array *angle) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array primitive_real, primitive_imag, primitive_abs, primitive_angle;
    tsa::features::fftCoefficient(var, coefficient, primitive_real, primitive_imag, primitive_abs, primitive_angle);
    af_retain_array(real, primitive_real.get());
    af_retain_array(imag, primitive_imag.get());
    af_retain_array(absolute, primitive_abs.get());
    af_retain_array(angle, primitive_angle.get());
}

void first_location_of_maximum(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::firstLocationOfMaximum(var).get());
}

void first_location_of_minimum(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::firstLocationOfMinimum(var).get());
}

void has_duplicates(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::hasDuplicates(var).get());
}

void has_duplicate_max(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::hasDuplicateMax(var).get());
}

void has_duplicate_min(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::hasDuplicateMin(var).get());
}

void index_max_quantile(af_array *array, float q, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::indexMaxQuantile(var, q).get());
}

void kurtosis(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::kurtosis(var).get());
}

void large_standard_deviation(af_array *array, float r, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::largeStandardDeviation(var, r).get());
}

void last_location_of_maximum(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::lastLocationOfMaximum(var).get());
}

void last_location_of_minimum(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::lastLocationOfMinimum(var).get());
}

void length(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::length(var).get());
}

void linear_trend(af_array *array, af_array *pvalue, af_array *rvalue, af_array *intercept, af_array *slope,
                  af_array *stdrr) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array primitive_pvalue, primitive_rvalue, primitive_intercept, primitive_slope, primitive_stdrr;
    tsa::features::linearTrend(var, primitive_pvalue, primitive_rvalue, primitive_intercept, primitive_slope,
                               primitive_stdrr);
    af_retain_array(slope, primitive_slope.get());
    af_retain_array(intercept, primitive_intercept.get());
    af_retain_array(rvalue, primitive_rvalue.get());
    af_retain_array(pvalue, primitive_pvalue.get());
    af_retain_array(stdrr, primitive_stdrr.get());
}

void longest_strike_above_mean(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::longestStrikeAboveMean(var).get());
}

void longest_strike_below_mean(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::longestStrikeBelowMean(var).get());
}

void max_langevin_fixed_point(af_array *array, int m, float r, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::maxLangevinFixedPoint(var, m, r).get());
}

void maximum(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::maximum(af::array(var)).get());
}

void mean(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::mean(var).get());
}

void mean_absolute_change(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::meanAbsoluteChange(var).get());
}

void mean_change(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::meanChange(var).get());
}

void mean_second_derivative_central(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::meanSecondDerivativeCentral(var).get());
}

void median(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::median(var).get());
}

void minimum(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::minimum(var).get());
}

void number_peaks(af_array *array, int n, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::numberPeaks(var, n).get());
}

void number_crossing_m(af_array *array, int m, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::numberCrossingM(var, m).get());
}

void percentage_of_reoccurring_datapoints_to_all_datapoints(af_array *array, bool is_sorted, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::percentageOfReoccurringDatapointsToAllDatapoints(var, is_sorted).get());
}

void quantile(af_array *array, af_array *q, float precision, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array var_q = af::array(*q);
    af_retain_array(q, var_q.get());
    af_retain_array(result, tsa::features::quantile(var, var_q, precision).get());
}

void ratio_beyond_r_sigma(af_array *array, float r, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::ratioBeyondRSigma(var, r).get());
}

void sample_entropy(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::sampleEntropy(var).get());
}

void skewness(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::skewness(var).get());
}

void standard_deviation(af_array *array, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::standardDeviation(var).get());
}

void sum_of_reoccurring_datapoints(af_array *array, bool is_sorted, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::sumOfReoccurringDatapoints(var, is_sorted).get());
}

void symmetry_looking(af_array *array, float r, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::symmetryLooking(var, r).get());
}

void value_count(af_array *array, float v, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::valueCount(var, v).get());
}

#ifdef __cplusplus
}
#endif
