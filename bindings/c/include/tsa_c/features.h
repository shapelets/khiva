// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

namespace tsa {

namespace features {

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
 * @brief Primitive of the cross_correlation function.
 *
 * @param xss Time series concatenated in a single row.
 * @param xss_length Time series length (All time series need to have the same length).
 * @param xss_number_of_tss Number of time series.
 * @param yss Time series concatenated in a single row.
 * @param yss_length  yss time series length.
 * @param yss_number_of_tss yss Number of time series.
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false).
 * @param result The cross-correlation value for the given time series.
 */
void cross_correlation(double *xss, long *xss_length, long *xss_number_of_tss, double *yss, long *yss_length,
                       long *yss_number_of_tss, bool *unbiased, double *result);

/**
 * @brief Primitive of the autoCovariance function.
 *
 * @param xss Time series concatenated in a single row.
 * @param xss_length Time series length (All time series need to have the same length).
 * @param xss_number_of_tss Number of time series.
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false).
 * @param result The auto-covariance value for the given time series.
 */
void auto_covariance(double *xss, long *xss_length, long *xss_number_of_tss, bool *unbiased, double *result);

/**
 * @brief Primitive of the crossCovariance function.
 *
 * @param xss Time series concatenated in a single row.
 * @param xss_length xss Time series length (All time series need to have the same length).
 * @param xss_number_of_tss Number of time series in xss.
 * @param yss Time series concatenated in a single row.
 * @param yss_length yss Time series length.
 * @param yss_number_of_tss Number of time series in yss.
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false).
 * @result The cross-covariance value for the given time series.
 */
void cross_covariance(double *xss, long *xss_length, long *xss_number_of_tss, double *yss, long *yss_length,
                      long *yss_number_of_tss, bool *unbiased, double *result);

/**
 * @brief Primitive of the aproximateEntropy function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param m Length of compared run of data.
 * @param r Filtering level, must be positive.
 * @param result The vectorized approximate entropy for all the input time series in tss.
 */
void approximate_entropy(double *tss, long *tss_length, long *tss_number_of_tss, int *m, double *r, double *result);

/**
 * @brief Primitive of autoCorrelation function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param max_lag The maximum lag to compute.
 * @param unbiased Determines whether it divides by n - lag (if true) or n ( if false)
 * @param result The autocorrelation value for the given time series.
 */
void auto_correlation(double *tss, long *tss_length, long *tss_number_of_tss, long *max_lag, bool *unbiased,
                      double *result);

/**
 * @brief Primitive of binnedEntropy function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss NUmber of time series.
 * @param max_bins The number of bins.
 * @param result The binned entropy value for the given time series.
 */
void binned_entropy(double *tss, long *tss_length, long *tss_number_of_tss, int *max_bins, double *result);

/**
 * @brief Primitive of countAboveMean function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss NUmber of time series.
 * @param result The number of values in the time series that are higher
 * than the mean.
 */
void count_above_mean(double *tss, long *tss_length, long *tss_number_of_tss, unsigned int *result);

/**
 * @brief Primitive of countBelowMean function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param result The number of values in the time series that are lower
 * than the mean.
 */
void count_below_mean(double *tss, long *tss_length, long *tss_number_of_tss, unsigned int *result);

/**
 * @brief Primitive of energyRatioByChunks function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param num_segments The number of segments to divide the series into.
 * @param segment_focus The segment number (starting at zero) to return a feature on.
 * @param result The energy ratio by chunk of the time series.
 */
void energy_ratio_by_chunks(double *tss, long *tss_length, long *tss_number_of_tss, long *num_segments,
                            long *segment_focus, double *result);
#ifdef __cplusplus
}
#endif
};  // namespace features
};  // namespace tsa