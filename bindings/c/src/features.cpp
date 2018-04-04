// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/features.h>

#ifdef __cplusplus
extern "C" {
#endif

void abs_energy(double *time_series, long *time_series_length, long *number_of_time_series, double *primitive_result) {
    af::array result;
    result = tsa::features::absEnergy(af::array(*time_series_length, *number_of_time_series, time_series));
    result.host(primitive_result);
}

void absolute_sum_of_changes(double *time_series, long *time_series_length, long *number_of_time_series,
                             double *primitive_result) {
    af::array result;
    result = tsa::features::absoluteSumOfChanges(af::array(*time_series_length, *number_of_time_series, time_series));
    result.host(primitive_result);
}

void aggregated_autocorrelation(double *tss, long *tss_l, long *tss_n, int *aggregation_function, double *result) {
    af::array primitive_result;

    switch (*aggregation_function) {
        case 0:
            primitive_result = tsa::features::aggregatedAutocorrelation(af::array(*tss_l, *tss_n, tss), af::mean);
            break;
        case 1:
            primitive_result = tsa::features::aggregatedAutocorrelation(af::array(*tss_l, *tss_n, tss), af::median);
            break;
        case 2:
            primitive_result = tsa::features::aggregatedAutocorrelation(af::array(*tss_l, *tss_n, tss), af::min);
            break;
        case 3:
            primitive_result = tsa::features::aggregatedAutocorrelation(af::array(*tss_l, *tss_n, tss), af::max);
            break;
        case 4:
            primitive_result = tsa::features::aggregatedAutocorrelation(af::array(*tss_l, *tss_n, tss), af::stdev);
            break;
        case 5:
            primitive_result = tsa::features::aggregatedAutocorrelation(af::array(*tss_l, *tss_n, tss), af::var);
            break;
        default:
            primitive_result = tsa::features::aggregatedAutocorrelation(af::array(*tss_l, *tss_n, tss), af::mean);
            break;
    }
    primitive_result.host(result);
}

void aggregated_linear_trend(double *t, long *t_l, long *t_n, long *chunkSize, int *aggregation_function, double *slope,
                             double *intercept, double *rvalue, double *pvalue, double *stderrest) {
    af::array primitive_slope;
    af::array primitive_intercept;
    af::array primitive_rvalue;
    af::array primitive_pvalue;
    af::array primitive_stderrest;
    switch (*aggregation_function) {
        case 0:
            tsa::features::aggregatedLinearTrend(af::array(*t_l, *t_n, t), *chunkSize, af::mean, primitive_slope,
                                                 primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                 primitive_stderrest);
            break;
        case 1:
            tsa::features::aggregatedLinearTrend(af::array(*t_l, *t_n, t), *chunkSize, af::median, primitive_slope,
                                                 primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                 primitive_stderrest);
            break;
        case 2:
            tsa::features::aggregatedLinearTrend(af::array(*t_l, *t_n, t), *chunkSize, af::min, primitive_slope,
                                                 primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                 primitive_stderrest);
            break;
        case 3:
            tsa::features::aggregatedLinearTrend(af::array(*t_l, *t_n, t), *chunkSize, af::max, primitive_slope,
                                                 primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                 primitive_stderrest);
            break;
        case 4:
            tsa::features::aggregatedLinearTrend(af::array(*t_l, *t_n, t), *chunkSize, af::stdev, primitive_slope,
                                                 primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                 primitive_stderrest);
            break;
        default:
            tsa::features::aggregatedLinearTrend(af::array(*t_l, *t_n, t), *chunkSize, af::mean, primitive_slope,
                                                 primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                 primitive_stderrest);
            break;
    }

    primitive_slope.host(slope);
    primitive_intercept.host(intercept);
    primitive_rvalue.host(rvalue);
    primitive_pvalue.host(pvalue);
    primitive_stderrest.host(stderrest);
}

void approximate_entropy(double *tss, long *tss_length, long *tss_number_of_tss, int *m, double *r, double *result) {
    af::array primitive_result;
    float r_f = (float)*r;
    primitive_result = tsa::features::approximateEntropy(af::array(*tss_length, *tss_number_of_tss, tss), *m, r_f);
    primitive_result.host(result);
}

void cross_covariance(double *xss, long *xss_length, long *xss_number_of_tss, double *yss, long *yss_length,
                      long *yss_number_of_tss, bool *unbiased, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::crossCovariance(af::array(*xss_length, *xss_number_of_tss, xss),
                                                      af::array(*yss_length, *yss_number_of_tss, yss), *unbiased);
    primitive_result.host(result);
}

void auto_covariance(double *xss, long *xss_length, long *xss_number_of_tss, bool *unbiased, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::autoCovariance(af::array(*xss_length, *xss_number_of_tss, xss), *unbiased);
    primitive_result.host(result);
}

void cross_correlation(double *xss, long *xss_length, long *xss_number_of_tss, double *yss, long *yss_length,
                       long *yss_number_of_tss, bool *unbiased, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::crossCorrelation(af::array(*xss_length, *xss_number_of_tss, xss),
                                                       af::array(*yss_length, *yss_number_of_tss, yss), *unbiased);
    primitive_result.host(result);
}

void auto_correlation(double *tss, long *tss_length, long *tss_number_of_tss, long *max_lag, bool *unbiased,
                      double *result) {
    af::array primitive_result;
    primitive_result =
        tsa::features::autoCorrelation(af::array(*tss_length, *tss_number_of_tss, tss), *max_lag, *unbiased);
    primitive_result.host(result);
}

void binned_entropy(double *tss, long *tss_length, long *tss_number_of_tss, int *max_bins, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::binnedEntropy(af::array(*tss_length, *tss_number_of_tss, tss), *max_bins);
    primitive_result.host(result);
}

void c3(double *tss, long *tss_length, long *tss_number_of_tss, long *lag, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::c3(af::array(*tss_length, *tss_number_of_tss, tss), *lag);
    primitive_result.host(result);
}

void cidCe(double *tss, long *tss_length, long *tss_number_of_tss, bool *zNormalize, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::cidCe(af::array(*tss_length, *tss_number_of_tss, tss), *zNormalize);
    primitive_result.host(result);
}

void count_above_mean(double *tss, long *tss_length, long *tss_number_of_tss, unsigned int *result) {
    af::array primitive_result;
    primitive_result = tsa::features::countAboveMean(af::array(*tss_length, *tss_number_of_tss, tss));
    primitive_result.host(result);
}

void count_below_mean(double *tss, long *tss_length, long *tss_number_of_tss, unsigned int *result) {
    af::array primitive_result;
    primitive_result = tsa::features::countBelowMean(af::array(*tss_length, *tss_number_of_tss, tss));
    primitive_result.host(result);
}

void cwt_coefficients(double *tss, long *tss_l, long *tss_n, int *widths, long *widths_l, long *widths_n, int *coeff,
                      int *w, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::cwtCoefficients(af::array(*tss_l, *tss_n, tss),
                                                      af::array(*widths_l, *widths_n, widths), *coeff, *w);
    primitive_result.host(result);
}

void energy_ratio_by_chunks(double *tss, long *tss_length, long *tss_number_of_tss, long *num_segments,
                            long *segment_focus, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::energyRatioByChunks(af::array(*tss_length, *tss_number_of_tss, tss),
                                                          *num_segments, *segment_focus);
    primitive_result.host(result);
}

void fftCoefficient(double *tss, long *tss_length, long *tss_number_of_tss, long *coefficient, double *real,
                    double *imag, double *absolute, double *angle) {
    af::array primitive_real, primitive_imag, primitive_abs, primitive_angle;
    tsa::features::fftCoefficient(af::array(*tss_length, *tss_number_of_tss, tss), *coefficient, primitive_real,
                                  primitive_imag, primitive_abs, primitive_angle);
    primitive_real.host(real);
    primitive_imag.host(imag);
    primitive_abs.host(absolute);
    primitive_angle.host(angle);
}

void first_location_of_maximum(double *tss, long *tss_length, long *tss_number_of_tss, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::firstLocationOfMaximum(af::array(*tss_length, *tss_number_of_tss, tss));
    primitive_result.host(result);
}

void first_location_of_minimum(double *tss, long *tss_length, long *tss_number_of_tss, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::firstLocationOfMinimum(af::array(*tss_length, *tss_number_of_tss, tss));
    primitive_result.host(result);
}

void has_duplicates(double *tss, long *tss_length, long *tss_number_of_tss, bool *result) {
    af::array primitive_result;
    primitive_result = tsa::features::hasDuplicates(af::array(*tss_length, *tss_number_of_tss, tss));
    primitive_result.host(result);
}

void has_duplicate_max(double *tss, long *tss_length, long *tss_number_of_tss, bool *result) {
    af::array primitive_result;
    primitive_result = tsa::features::hasDuplicateMax(af::array(*tss_length, *tss_number_of_tss, tss));
    primitive_result.host(result);
}

void has_duplicate_min(double *tss, long *tss_length, long *tss_number_of_tss, bool *result) {
    af::array primitive_result;
    primitive_result = tsa::features::hasDuplicateMin(af::array(*tss_length, *tss_number_of_tss, tss));
    primitive_result.host(result);
}

void index_max_quantile(double *tss, long *tss_length, long *tss_number_of_tss, double *q, double *result) {
    af::array primitive_result;
    float q_f = (float)*q;
    primitive_result = tsa::features::indexMaxQuantile(af::array(*tss_length, *tss_number_of_tss, tss), q_f);
    primitive_result.host(result);
}

void kurtosis(double *tss, long *tss_length, long *tss_number_of_tss, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::kurtosis(af::array(*tss_length, *tss_number_of_tss, tss));
    primitive_result.host(result);
}

void large_standard_deviation(double *tss, long *tss_length, long *tss_number_of_tss, double *r, bool *result) {
    af::array primitive_result;
    float r_f = (float)*r;
    primitive_result = tsa::features::largeStandardDeviation(af::array(*tss_length, *tss_number_of_tss, tss), r_f);
    primitive_result.host(result);
}

void last_location_of_maximum(double *tss, long *tss_length, long *tss_number_of_tss, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::lastLocationOfMaximum(af::array(*tss_length, *tss_number_of_tss, tss));
    primitive_result.host(result);
}

void last_location_of_minimum(double *tss, long *tss_length, long *tss_number_of_tss, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::lastLocationOfMinimum(af::array(*tss_length, *tss_number_of_tss, tss));
    primitive_result.host(result);
}

void length(double *tss, long *tss_length, long *tss_number_of_tss, int *result) {
    af::array primitive_result;
    primitive_result = tsa::features::length(af::array(*tss_length, *tss_number_of_tss, tss));
    primitive_result.host(result);
}

void linear_trend(double *tss, long *tss_length, long *tss_number_of_tss, double *pvalue, double *rvalue,
                  double *intercept, double *slope, double *stdrr) {
    af::array primitive_pvalue, primitive_rvalue, primitive_intercept, primitive_slope, primitive_stdrr;
    tsa::features::linearTrend(af::array(*tss_length, *tss_number_of_tss, tss), primitive_pvalue, primitive_rvalue,
                               primitive_intercept, primitive_slope, primitive_stdrr);
    primitive_pvalue.host(pvalue);
    primitive_rvalue.host(rvalue);
    primitive_intercept.host(intercept);
    primitive_slope.host(slope);
    primitive_stdrr.host(stdrr);
}

void longest_strike_above_mean(double *tss, long *tss_length, long *tss_number_of_tss, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::longestStrikeAboveMean(af::array(*tss_length, *tss_number_of_tss, tss));
    primitive_result.host(result);
}

void longest_strike_below_mean(double *tss, long *tss_length, long *tss_number_of_tss, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::longestStrikeBelowMean(af::array(*tss_length, *tss_number_of_tss, tss));
    primitive_result.host(result);
}

void max_langevin_fixed_point(double *tss, long *tss_l, long *tss_n, int *m, double *r, double *result) {
    af::array primitive_result;
    float r_f = (float)*r;
    primitive_result = tsa::features::maxLangevinFixedPoint(af::array(*tss_l, *tss_n, tss), *m, r_f);
    primitive_result.host(result);
}

void maximum(double *tss, long *tss_length, long *tss_number_of_tss, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::maximum(af::array(*tss_length, *tss_number_of_tss, tss));
    primitive_result.host(result);
}

void mean(double *tss, long *tss_l, long *tss_n, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::mean(af::array(*tss_l, *tss_n, tss));
    primitive_result.host(result);
}

void mean_absolute_change(double *tss, long *tss_length, long *tss_number_of_tss, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::meanAbsoluteChange(af::array(*tss_length, *tss_number_of_tss, tss));
    primitive_result.host(result);
}

void mean_change(double *tss, long *tss_l, long *tss_n, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::meanChange(af::array(*tss_l, *tss_n, tss));
    primitive_result.host(result);
}

void mean_second_derivative_central(double *tss, long *tss_l, long *tss_n, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::meanSecondDerivativeCentral(af::array(*tss_l, *tss_n, tss));
    primitive_result.host(result);
}

void median(double *tss, long *tss_l, long *tss_n, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::median(af::array(*tss_l, *tss_n, tss));
    primitive_result.host(result);
}

void minimum(double *tss, long *tss_l, long *tss_n, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::minimum(af::array(*tss_l, *tss_n, tss));
    primitive_result.host(result);
}

void number_crossing_m(double *tss, long *tss_l, long *tss_n, int *m, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::numberCrossingM(af::array(*tss_l, *tss_n, tss), *m);
    primitive_result.host(result);
}

#ifdef __cplusplus
}
#endif
