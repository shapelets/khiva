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

TSAAPI void abs_energy(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::absEnergy(var).get());
}

TSAAPI void absolute_sum_of_changes(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::absoluteSumOfChanges(var).get());
}

TSAAPI void aggregated_autocorrelation(tsa_array *array, int *aggregation_function, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());

    switch (*aggregation_function) {
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

TSAAPI void aggregated_linear_trend(tsa_array *array, long *chunkSize, int *aggregation_function, tsa_array *slope,
                                    tsa_array *intercept, tsa_array *rvalue, tsa_array *pvalue, tsa_array *stderrest) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array primitive_slope;
    af::array primitive_intercept;
    af::array primitive_rvalue;
    af::array primitive_pvalue;
    af::array primitive_stderrest;

    switch (*aggregation_function) {
        case 0:
            tsa::features::aggregatedLinearTrend(var, *chunkSize, af::mean, primitive_slope, primitive_intercept,
                                                 primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
        case 1:
            tsa::features::aggregatedLinearTrend(var, *chunkSize, af::median, primitive_slope, primitive_intercept,
                                                 primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
        case 2:
            tsa::features::aggregatedLinearTrend(var, *chunkSize, af::min, primitive_slope, primitive_intercept,
                                                 primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
        case 3:
            tsa::features::aggregatedLinearTrend(var, *chunkSize, af::max, primitive_slope, primitive_intercept,
                                                 primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
        case 4:
            tsa::features::aggregatedLinearTrend(var, *chunkSize, af::stdev, primitive_slope, primitive_intercept,
                                                 primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
        default:
            tsa::features::aggregatedLinearTrend(var, *chunkSize, af::mean, primitive_slope, primitive_intercept,
                                                 primitive_rvalue, primitive_pvalue, primitive_stderrest);
            break;
    }
    af_retain_array(slope, primitive_slope.get());
    af_retain_array(intercept, primitive_intercept.get());
    af_retain_array(rvalue, primitive_rvalue.get());
    af_retain_array(pvalue, primitive_pvalue.get());
    af_retain_array(stderrest, primitive_stderrest.get());
}

TSAAPI void approximate_entropy(tsa_array *array, int *m, float *r, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::approximateEntropy(var, *m, *r).get());
}

TSAAPI void cross_covariance(tsa_array *xss, tsa_array *yss, bool *unbiased, tsa_array *result) {
    af::array var_xss = af::array(*xss);
    af_retain_array(xss, var_xss.get());
    af::array var_yss = af::array(*yss);
    af_retain_array(yss, var_yss.get());
    af_retain_array(result, tsa::features::crossCovariance(var_xss, var_yss, *unbiased).get());
}

TSAAPI void auto_covariance(tsa_array *array, bool *unbiased, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::autoCovariance(var, *unbiased).get());
}

TSAAPI void cross_correlation(tsa_array *xss, tsa_array *yss, bool *unbiased, tsa_array *result) {
    af::array var_xss = af::array(*xss);
    af_retain_array(xss, var_xss.get());
    af::array var_yss = af::array(*yss);
    af_retain_array(yss, var_yss.get());
    af_retain_array(result, tsa::features::crossCorrelation(var_xss, var_yss, *unbiased).get());
}

TSAAPI void auto_correlation(tsa_array *array, long *max_lag, bool *unbiased, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::autoCorrelation(var, *max_lag, *unbiased).get());
}

TSAAPI void binned_entropy(tsa_array *array, int *max_bins, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::binnedEntropy(var, *max_bins).get());
}

TSAAPI void c3(tsa_array *array, long *lag, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::c3(var, *lag).get());
}

TSAAPI void cid_ce(tsa_array *array, bool *zNormalize, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::cidCe(var, *zNormalize).get());
}

TSAAPI void count_above_mean(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::countAboveMean(var).get());
}

TSAAPI void count_below_mean(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::countBelowMean(var).get());
}

TSAAPI void cwt_coefficients(tsa_array *array, tsa_array *width, int *coeff, int *w, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array var_width = af::array(*width);
    af_retain_array(width, var_width.get());
    af_retain_array(result, tsa::features::cwtCoefficients(var, var_width, *coeff, *w).get());
}

TSAAPI void energy_ratio_by_chunks(tsa_array *array, long *num_segments, long *segment_focus, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::energyRatioByChunks(var, *num_segments, *segment_focus).get());
}

TSAAPI void fft_aggregated(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::fftAggregated(var).get());
}

TSAAPI void fft_coefficient(tsa_array *array, long *coefficient, tsa_array *real, tsa_array *imag, tsa_array *absolute,
                            tsa_array *angle) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array primitive_real, primitive_imag, primitive_abs, primitive_angle;
    tsa::features::fftCoefficient(var, *coefficient, primitive_real, primitive_imag, primitive_abs, primitive_angle);
    af_retain_array(real, primitive_real.get());
    af_retain_array(imag, primitive_imag.get());
    af_retain_array(absolute, primitive_abs.get());
    af_retain_array(angle, primitive_angle.get());
}

TSAAPI void first_location_of_maximum(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::firstLocationOfMaximum(var).get());
}

TSAAPI void first_location_of_minimum(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::firstLocationOfMinimum(var).get());
}

TSAAPI void friedrich_coefficients(tsa_array *array, int *m, float *r, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::friedrichCoefficients(var, *m, *r).get());
}

TSAAPI void has_duplicates(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::hasDuplicates(var).get());
}

TSAAPI void has_duplicate_max(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::hasDuplicateMax(var).get());
}

TSAAPI void has_duplicate_min(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::hasDuplicateMin(var).get());
}

TSAAPI void index_mass_quantile(tsa_array *array, float *q, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::indexMassQuantile(var, *q).get());
}

TSAAPI void kurtosis(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::kurtosis(var).get());
}

TSAAPI void large_standard_deviation(tsa_array *array, float *r, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::largeStandardDeviation(var, *r).get());
}

TSAAPI void last_location_of_maximum(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::lastLocationOfMaximum(var).get());
}

TSAAPI void last_location_of_minimum(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::lastLocationOfMinimum(var).get());
}

TSAAPI void length(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::length(var).get());
}

TSAAPI void linear_trend(tsa_array *array, tsa_array *pvalue, tsa_array *rvalue, tsa_array *intercept, tsa_array *slope,
                         tsa_array *stdrr) {
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

TSAAPI void local_maximals(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::localMaximals(var).get());
}

TSAAPI void longest_strike_above_mean(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::longestStrikeAboveMean(var).get());
}

TSAAPI void longest_strike_below_mean(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::longestStrikeBelowMean(var).get());
}

TSAAPI void max_langevin_fixed_point(tsa_array *array, int *m, float *r, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::maxLangevinFixedPoint(var, *m, *r).get());
}

TSAAPI void maximum(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::maximum(af::array(var)).get());
}

TSAAPI void mean(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::mean(var).get());
}

TSAAPI void mean_absolute_change(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::meanAbsoluteChange(var).get());
}

TSAAPI void mean_change(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::meanChange(var).get());
}

TSAAPI void mean_second_derivative_central(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::meanSecondDerivativeCentral(var).get());
}

TSAAPI void median(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::median(var).get());
}

TSAAPI void minimum(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::minimum(var).get());
}

TSAAPI void number_crossing_m(tsa_array *array, int *m, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::numberCrossingM(var, *m).get());
}

TSAAPI void number_cwt_peaks(tsa_array *array, int *max_w, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::numberPeaks(var, *max_w).get());
}

TSAAPI void number_peaks(tsa_array *array, int *n, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::numberPeaks(var, *n).get());
}

TSAAPI void partial_autocorrelation(tsa_array *array, tsa_array *lags, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array var_lags = af::array(*lags);
    af_retain_array(lags, var_lags.get());
    af_retain_array(result, tsa::features::partialAutocorrelation(var, var_lags).get());
}

TSAAPI void percentage_of_reoccurring_datapoints_to_all_datapoints(tsa_array *array, bool *is_sorted,
                                                                   tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::percentageOfReoccurringDatapointsToAllDatapoints(var, *is_sorted).get());
}

TSAAPI void percentage_of_reoccurring_values_to_all_values(tsa_array *array, bool *is_sorted, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::percentageOfReoccurringValuesToAllValues(var, *is_sorted).get());
}

TSAAPI void quantile(tsa_array *array, tsa_array *q, float *precision, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array var_q = af::array(*q);
    af_retain_array(q, var_q.get());
    af_retain_array(result, tsa::features::quantile(var, var_q, *precision).get());
}

TSAAPI void range_count(tsa_array *array, float *min, float *max, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::rangeCount(var, *min, *max).get());
}

TSAAPI void ratio_beyond_r_sigma(tsa_array *array, float *r, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::ratioBeyondRSigma(var, *r).get());
}

TSAAPI void ratio_value_number_to_time_series_length(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::ratioValueNumberToTimeSeriesLength(var).get());
}

TSAAPI void sample_entropy(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::sampleEntropy(var).get());
}

TSAAPI void skewness(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::skewness(var).get());
}

TSAAPI void spkt_welch_density(tsa_array *array, int *coeff, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::spktWelchDensity(var, *coeff).get());
}

TSAAPI void standard_deviation(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::standardDeviation(var).get());
}

TSAAPI void sum_of_reoccurring_datapoints(tsa_array *array, bool *is_sorted, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::sumOfReoccurringDatapoints(var, *is_sorted).get());
}

TSAAPI void sum_of_reoccurring_values(tsa_array *array, bool *is_sorted, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::sumOfReoccurringValues(var, *is_sorted).get());
}

TSAAPI void sum_values(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::sumValues(var).get());
}

TSAAPI void symmetry_looking(tsa_array *array, float *r, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::symmetryLooking(var, *r).get());
}

TSAAPI void time_reversal_asymmetry_statistic(tsa_array *array, int *lag, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::timeReversalAsymmetryStatistic(var, *lag).get());
}

TSAAPI void value_count(tsa_array *array, float *v, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::valueCount(var, *v).get());
}

TSAAPI void variance(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::variance(var).get());
}

TSAAPI void variance_larger_than_standard_deviation(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::features::varianceLargerThanStandardDeviation(var).get());
}

#ifdef __cplusplus
}
#endif
