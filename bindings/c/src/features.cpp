// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/features.h>
#include <khiva_c/features.h>

#ifdef __cplusplus
extern "C" {
#endif

KHIVAAPI void abs_energy(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::absEnergy(var).get());
}

KHIVAAPI void absolute_sum_of_changes(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::absoluteSumOfChanges(var).get());
}

KHIVAAPI void aggregated_autocorrelation(khiva_array *array, int *aggregation_function, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());

    switch (*aggregation_function) {
        case 0:
            af_retain_array(result, khiva::features::aggregatedAutocorrelation(var, af::mean).get());
            break;
        case 1:
            af_retain_array(result, khiva::features::aggregatedAutocorrelation(var, af::median).get());
            break;
        case 2:
            af_retain_array(result, khiva::features::aggregatedAutocorrelation(var, af::min).get());
            break;
        case 3:
            af_retain_array(result, khiva::features::aggregatedAutocorrelation(var, af::max).get());
            break;
        case 4:
            af_retain_array(result, khiva::features::aggregatedAutocorrelation(var, af::stdev).get());
            break;
        case 5:
            af_retain_array(result, khiva::features::aggregatedAutocorrelation(var, af::var).get());
            break;
        default:
            af_retain_array(result, khiva::features::aggregatedAutocorrelation(var, af::mean).get());
            break;
    }
}

KHIVAAPI void aggregated_linear_trend(khiva_array *array, long *chunkSize, int *aggregation_function,
                                      khiva_array *slope, khiva_array *intercept, khiva_array *rvalue,
                                      khiva_array *pvalue, khiva_array *stderrest) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array primitive_slope;
    af::array primitive_intercept;
    af::array primitive_rvalue;
    af::array primitive_pvalue;
    af::array primitive_stderrest;

    switch (*aggregation_function) {
        case 0:
            khiva::features::aggregatedLinearTrend(var, *chunkSize, af::mean, primitive_slope, primitive_intercept,
                                                   primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
        case 1:
            khiva::features::aggregatedLinearTrend(var, *chunkSize, af::median, primitive_slope, primitive_intercept,
                                                   primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
        case 2:
            khiva::features::aggregatedLinearTrend(var, *chunkSize, af::min, primitive_slope, primitive_intercept,
                                                   primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
        case 3:
            khiva::features::aggregatedLinearTrend(var, *chunkSize, af::max, primitive_slope, primitive_intercept,
                                                   primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
        case 4:
            khiva::features::aggregatedLinearTrend(var, *chunkSize, af::stdev, primitive_slope, primitive_intercept,
                                                   primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
        default:
            khiva::features::aggregatedLinearTrend(var, *chunkSize, af::mean, primitive_slope, primitive_intercept,
                                                   primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
    }
    af_retain_array(slope, primitive_slope.get());
    af_retain_array(intercept, primitive_intercept.get());
    af_retain_array(rvalue, primitive_rvalue.get());
    af_retain_array(pvalue, primitive_pvalue.get());
    af_retain_array(stderrest, primitive_stderrest.get());
}

KHIVAAPI void approximate_entropy(khiva_array *array, int *m, float *r, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::approximateEntropy(var, *m, *r).get());
}

KHIVAAPI void cross_covariance(khiva_array *xss, khiva_array *yss, bool *unbiased, khiva_array *result) {
    af::array var_xss = af::array(*xss);
    af_retain_array(xss, var_xss.get());
    af::array var_yss = af::array(*yss);
    af_retain_array(yss, var_yss.get());
    af_retain_array(result, khiva::features::crossCovariance(var_xss, var_yss, *unbiased).get());
}

KHIVAAPI void auto_covariance(khiva_array *array, bool *unbiased, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::autoCovariance(var, *unbiased).get());
}

KHIVAAPI void cross_correlation(khiva_array *xss, khiva_array *yss, bool *unbiased, khiva_array *result) {
    af::array var_xss = af::array(*xss);
    af_retain_array(xss, var_xss.get());
    af::array var_yss = af::array(*yss);
    af_retain_array(yss, var_yss.get());
    af_retain_array(result, khiva::features::crossCorrelation(var_xss, var_yss, *unbiased).get());
}

KHIVAAPI void auto_correlation(khiva_array *array, long *max_lag, bool *unbiased, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::autoCorrelation(var, *max_lag, *unbiased).get());
}

KHIVAAPI void binned_entropy(khiva_array *array, int *max_bins, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::binnedEntropy(var, *max_bins).get());
}

KHIVAAPI void c3(khiva_array *array, long *lag, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::c3(var, *lag).get());
}

KHIVAAPI void cid_ce(khiva_array *array, bool *zNormalize, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::cidCe(var, *zNormalize).get());
}

KHIVAAPI void count_above_mean(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::countAboveMean(var).get());
}

KHIVAAPI void count_below_mean(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::countBelowMean(var).get());
}

KHIVAAPI void cwt_coefficients(khiva_array *array, khiva_array *width, int *coeff, int *w, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array var_width = af::array(*width);
    af_retain_array(width, var_width.get());
    af_retain_array(result, khiva::features::cwtCoefficients(var, var_width, *coeff, *w).get());
}

KHIVAAPI void energy_ratio_by_chunks(khiva_array *array, long *num_segments, long *segment_focus, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::energyRatioByChunks(var, *num_segments, *segment_focus).get());
}

KHIVAAPI void fft_aggregated(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::fftAggregated(var).get());
}

KHIVAAPI void fft_coefficient(khiva_array *array, long *coefficient, khiva_array *real, khiva_array *imag,
                              khiva_array *absolute, khiva_array *angle) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array primitive_real, primitive_imag, primitive_abs, primitive_angle;
    khiva::features::fftCoefficient(var, *coefficient, primitive_real, primitive_imag, primitive_abs, primitive_angle);
    af_retain_array(real, primitive_real.get());
    af_retain_array(imag, primitive_imag.get());
    af_retain_array(absolute, primitive_abs.get());
    af_retain_array(angle, primitive_angle.get());
}

KHIVAAPI void first_location_of_maximum(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::firstLocationOfMaximum(var).get());
}

KHIVAAPI void first_location_of_minimum(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::firstLocationOfMinimum(var).get());
}

KHIVAAPI void friedrich_coefficients(khiva_array *array, int *m, float *r, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::friedrichCoefficients(var, *m, *r).get());
}

KHIVAAPI void has_duplicates(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::hasDuplicates(var).get());
}

KHIVAAPI void has_duplicate_max(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::hasDuplicateMax(var).get());
}

KHIVAAPI void has_duplicate_min(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::hasDuplicateMin(var).get());
}

KHIVAAPI void index_mass_quantile(khiva_array *array, float *q, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::indexMassQuantile(var, *q).get());
}

KHIVAAPI void kurtosis(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::kurtosis(var).get());
}

KHIVAAPI void large_standard_deviation(khiva_array *array, float *r, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::largeStandardDeviation(var, *r).get());
}

KHIVAAPI void last_location_of_maximum(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::lastLocationOfMaximum(var).get());
}

KHIVAAPI void last_location_of_minimum(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::lastLocationOfMinimum(var).get());
}

KHIVAAPI void length(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::length(var).get());
}

KHIVAAPI void linear_trend(khiva_array *array, khiva_array *pvalue, khiva_array *rvalue, khiva_array *intercept,
                           khiva_array *slope, khiva_array *stdrr) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array primitive_pvalue, primitive_rvalue, primitive_intercept, primitive_slope, primitive_stdrr;
    khiva::features::linearTrend(var, primitive_pvalue, primitive_rvalue, primitive_intercept, primitive_slope,
                                 primitive_stdrr);
    af_retain_array(slope, primitive_slope.get());
    af_retain_array(intercept, primitive_intercept.get());
    af_retain_array(rvalue, primitive_rvalue.get());
    af_retain_array(pvalue, primitive_pvalue.get());
    af_retain_array(stdrr, primitive_stdrr.get());
}

KHIVAAPI void local_maximals(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::localMaximals(var).get());
}

KHIVAAPI void longest_strike_above_mean(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::longestStrikeAboveMean(var).get());
}

KHIVAAPI void longest_strike_below_mean(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::longestStrikeBelowMean(var).get());
}

KHIVAAPI void max_langevin_fixed_point(khiva_array *array, int *m, float *r, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::maxLangevinFixedPoint(var, *m, *r).get());
}

KHIVAAPI void maximum(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::maximum(af::array(var)).get());
}

KHIVAAPI void mean(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::mean(var).get());
}

KHIVAAPI void mean_absolute_change(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::meanAbsoluteChange(var).get());
}

KHIVAAPI void mean_change(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::meanChange(var).get());
}

KHIVAAPI void mean_second_derivative_central(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::meanSecondDerivativeCentral(var).get());
}

KHIVAAPI void median(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::median(var).get());
}

KHIVAAPI void minimum(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::minimum(var).get());
}

KHIVAAPI void number_crossing_m(khiva_array *array, int *m, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::numberCrossingM(var, *m).get());
}

KHIVAAPI void number_cwt_peaks(khiva_array *array, int *max_w, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::numberPeaks(var, *max_w).get());
}

KHIVAAPI void number_peaks(khiva_array *array, int *n, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::numberPeaks(var, *n).get());
}

KHIVAAPI void partial_autocorrelation(khiva_array *array, khiva_array *lags, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array var_lags = af::array(*lags);
    af_retain_array(lags, var_lags.get());
    af_retain_array(result, khiva::features::partialAutocorrelation(var, var_lags).get());
}

KHIVAAPI void percentage_of_reoccurring_datapoints_to_all_datapoints(khiva_array *array, bool *is_sorted,
                                                                     khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::percentageOfReoccurringDatapointsToAllDatapoints(var, *is_sorted).get());
}

KHIVAAPI void percentage_of_reoccurring_values_to_all_values(khiva_array *array, bool *is_sorted, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::percentageOfReoccurringValuesToAllValues(var, *is_sorted).get());
}

KHIVAAPI void quantile(khiva_array *array, khiva_array *q, float *precision, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array var_q = af::array(*q);
    af_retain_array(q, var_q.get());
    af_retain_array(result, khiva::features::quantile(var, var_q, *precision).get());
}

KHIVAAPI void range_count(khiva_array *array, float *min, float *max, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::rangeCount(var, *min, *max).get());
}

KHIVAAPI void ratio_beyond_r_sigma(khiva_array *array, float *r, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::ratioBeyondRSigma(var, *r).get());
}

KHIVAAPI void ratio_value_number_to_time_series_length(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::ratioValueNumberToTimeSeriesLength(var).get());
}

KHIVAAPI void sample_entropy(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::sampleEntropy(var).get());
}

KHIVAAPI void skewness(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::skewness(var).get());
}

KHIVAAPI void spkt_welch_density(khiva_array *array, int *coeff, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::spktWelchDensity(var, *coeff).get());
}

KHIVAAPI void standard_deviation(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::standardDeviation(var).get());
}

KHIVAAPI void sum_of_reoccurring_datapoints(khiva_array *array, bool *is_sorted, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::sumOfReoccurringDatapoints(var, *is_sorted).get());
}

KHIVAAPI void sum_of_reoccurring_values(khiva_array *array, bool *is_sorted, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::sumOfReoccurringValues(var, *is_sorted).get());
}

KHIVAAPI void sum_values(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::sumValues(var).get());
}

KHIVAAPI void symmetry_looking(khiva_array *array, float *r, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::symmetryLooking(var, *r).get());
}

KHIVAAPI void time_reversal_asymmetry_statistic(khiva_array *array, int *lag, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::timeReversalAsymmetryStatistic(var, *lag).get());
}

KHIVAAPI void value_count(khiva_array *array, float *v, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::valueCount(var, *v).get());
}

KHIVAAPI void variance(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::variance(var).get());
}

KHIVAAPI void variance_larger_than_standard_deviation(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, khiva::features::varianceLargerThanStandardDeviation(var).get());
}

#ifdef __cplusplus
}
#endif
