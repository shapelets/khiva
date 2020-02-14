// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/features.h>
#include <khiva_c/features.h>
#include <khiva_c/internal/util.h>

void abs_energy(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::absEnergy(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("abs_energy", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("abs_energy", error_message, error_code, -1);
    }
}

void absolute_sum_of_changes(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::absoluteSumOfChanges(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("absolute_sum_of_changes", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("absolute_sum_of_changes", error_message, error_code, -1);
    }
}

void aggregated_autocorrelation(khiva_array *array, int *aggregation_function, khiva_array *result, int *error_code,
                                char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());

        switch (*aggregation_function) {
            case 0:
                af_retain_array(result, khiva::features::aggregatedAutocorrelation(var, af::mean).get());
                *error_code = 0;
                break;
            case 1:
                af_retain_array(result, khiva::features::aggregatedAutocorrelation(var, af::median).get());
                *error_code = 0;
                break;
            case 2:
                af_retain_array(result, khiva::features::aggregatedAutocorrelation(var, af::min).get());
                *error_code = 0;
                break;
            case 3:
                af_retain_array(result, khiva::features::aggregatedAutocorrelation(var, af::max).get());
                *error_code = 0;
                break;
            case 4:
                af_retain_array(result, khiva::features::aggregatedAutocorrelation(var, af::stdev).get());
                *error_code = 0;
                break;
            case 5:
                af_retain_array(result, khiva::features::aggregatedAutocorrelation(var, af::var).get());
                *error_code = 0;
                break;
            default:
                af_retain_array(result, khiva::features::aggregatedAutocorrelation(var, af::mean).get());
                *error_code = 0;
                break;
        }
    } catch (const std::exception &e) {
        fill_error("aggregated_autocorrelation", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("aggregated_autocorrelation", error_message, error_code, -1);
    }
}

void aggregated_linear_trend(khiva_array *array, long *chunkSize, int *aggregation_function, khiva_array *slope,
                             khiva_array *intercept, khiva_array *rvalue, khiva_array *pvalue, khiva_array *stderrest,
                             int *error_code, char *error_message) {
    try {
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
                khiva::features::aggregatedLinearTrend(var, *chunkSize, af::median, primitive_slope,
                                                       primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                       primitive_stderrest);
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

        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("aggregated_linear_trend", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("aggregated_linear_trend", error_message, error_code, -1);
    }
}

void approximate_entropy(khiva_array *array, int *m, float *r, khiva_array *result, int *error_code,
                         char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::approximateEntropy(var, *m, *r).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("approximate_entropy", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("approximate_entropy", error_message, error_code, -1);
    }
}

void cross_covariance(khiva_array *xss, khiva_array *yss, bool *unbiased, khiva_array *result, int *error_code,
                      char *error_message) {
    try {
        af::array var_xss;
        af::array var_yss;
        check_and_retain_arrays(xss, yss, var_xss, var_yss);
        af_retain_array(result, khiva::features::crossCovariance(var_xss, var_yss, *unbiased).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("cross_covariance", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("cross_covariance", error_message, error_code, -1);
    }
}

void auto_covariance(khiva_array *array, bool *unbiased, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::autoCovariance(var, *unbiased).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("auto_covariance", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("auto_covariance", error_message, error_code, -1);
    }
}

void cross_correlation(khiva_array *xss, khiva_array *yss, bool *unbiased, khiva_array *result, int *error_code,
                       char *error_message) {
    try {
        af::array var_xss;
        af::array var_yss;
        check_and_retain_arrays(xss, yss, var_xss, var_yss);
        af_retain_array(result, khiva::features::crossCorrelation(var_xss, var_yss, *unbiased).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("cross_correlation", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("cross_correlation", error_message, error_code, -1);
    }
}

void auto_correlation(khiva_array *array, long *max_lag, bool *unbiased, khiva_array *result, int *error_code,
                      char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::autoCorrelation(var, *max_lag, *unbiased).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("auto_correlation", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("auto_correlation", error_message, error_code, -1);
    }
}

void binned_entropy(khiva_array *array, int *max_bins, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::binnedEntropy(var, *max_bins).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("binned_entropy", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("binned_entropy", error_message, error_code, -1);
    }
}

void c3(khiva_array *array, long *lag, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::c3(var, *lag).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("c3", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("c3", error_message, error_code, -1);
    }
}

void cid_ce(khiva_array *array, bool *zNormalize, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::cidCe(var, *zNormalize).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("cid_ce", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("cid_ce", error_message, error_code, -1);
    }
}

void count_above_mean(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::countAboveMean(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("count_above_mean", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("count_above_mean", error_message, error_code, -1);
    }
}

void count_below_mean(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::countBelowMean(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("count_below_mean", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("count_below_mean", error_message, error_code, -1);
    }
}

void cwt_coefficients(khiva_array *array, khiva_array *width, int *coeff, int *w, khiva_array *result, int *error_code,
                      char *error_message) {
    try {
        af::array var;
        af::array var_width;
        check_and_retain_arrays(array, width, var, var_width);
        af_retain_array(result, khiva::features::cwtCoefficients(var, var_width, *coeff, *w).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("cwt_coefficients", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("cwt_coefficients", error_message, error_code, -1);
    }
}

void energy_ratio_by_chunks(khiva_array *array, long *num_segments, long *segment_focus, khiva_array *result,
                            int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::energyRatioByChunks(var, *num_segments, *segment_focus).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("energy_ratio_by_chunks", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("energy_ratio_by_chunks", error_message, error_code, -1);
    }
}

void fft_aggregated(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::fftAggregated(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("fft_aggregated", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("fft_aggregated", error_message, error_code, -1);
    }
}

void fft_coefficient(khiva_array *array, long *coefficient, khiva_array *real, khiva_array *imag, khiva_array *absolute,
                     khiva_array *angle, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af::array primitive_real, primitive_imag, primitive_abs, primitive_angle;
        khiva::features::fftCoefficient(var, *coefficient, primitive_real, primitive_imag, primitive_abs,
                                        primitive_angle);
        af_retain_array(real, primitive_real.get());
        af_retain_array(imag, primitive_imag.get());
        af_retain_array(absolute, primitive_abs.get());
        af_retain_array(angle, primitive_angle.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("fft_coefficient", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("fft_coefficient", error_message, error_code, -1);
    }
}

void first_location_of_maximum(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::firstLocationOfMaximum(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("first_location_of_maximum", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("first_location_of_maximum", error_message, error_code, -1);
    }
}

void first_location_of_minimum(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::firstLocationOfMinimum(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("first_location_of_minimum", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("first_location_of_minimum", error_message, error_code, -1);
    }
}

void friedrich_coefficients(khiva_array *array, int *m, float *r, khiva_array *result, int *error_code,
                            char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::friedrichCoefficients(var, *m, *r).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("friedrich_coefficients", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("friedrich_coefficients", error_message, error_code, -1);
    }
}

void has_duplicates(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::hasDuplicates(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("has_duplicates", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("has_duplicates", error_message, error_code, -1);
    }
}

void has_duplicate_max(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::hasDuplicateMax(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("has_duplicate_max", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("has_duplicate_max", error_message, error_code, -1);
    }
}

void has_duplicate_min(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::hasDuplicateMin(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("has_duplicate_min", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("has_duplicate_min", error_message, error_code, -1);
    }
}

void index_mass_quantile(khiva_array *array, float *q, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::indexMassQuantile(var, *q).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("index_mass_quantile", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("index_mass_quantile", error_message, error_code, -1);
    }
}

void kurtosis(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::kurtosis(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("kurtosis", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("kurtosis", error_message, error_code, -1);
    }
}

void large_standard_deviation(khiva_array *array, float *r, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::largeStandardDeviation(var, *r).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("large_standard_deviation", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("large_standard_deviation", error_message, error_code, -1);
    }
}

void last_location_of_maximum(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::lastLocationOfMaximum(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("last_location_of_maximum", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("last_location_of_maximum", error_message, error_code, -1);
    }
}

void last_location_of_minimum(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::lastLocationOfMinimum(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("last_location_of_minimum", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("last_location_of_minimum", error_message, error_code, -1);
    }
}

void length(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::length(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("length", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("length", error_message, error_code, -1);
    }
}

void linear_trend(khiva_array *array, khiva_array *pvalue, khiva_array *rvalue, khiva_array *intercept,
                  khiva_array *slope, khiva_array *stdrr, int *error_code, char *error_message) {
    try {
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
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("linear_trend", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("linear_trend", error_message, error_code, -1);
    }
}

void local_maximals(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::localMaximals(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("local_maximals", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("local_maximals", error_message, error_code, -1);
    }
}

void longest_strike_above_mean(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::longestStrikeAboveMean(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("longest_strike_above_mean", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("longest_strike_above_mean", error_message, error_code, -1);
    }
}

void longest_strike_below_mean(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::longestStrikeBelowMean(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("longest_strike_below_mean", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("longest_strike_below_mean", error_message, error_code, -1);
    }
}

void max_langevin_fixed_point(khiva_array *array, int *m, float *r, khiva_array *result, int *error_code,
                              char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::maxLangevinFixedPoint(var, *m, *r).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("max_langevin_fixed_point", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("max_langevin_fixed_point", error_message, error_code, -1);
    }
}

void maximum(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::maximum(af::array(var)).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("maximum", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("maximum", error_message, error_code, -1);
    }
}

void mean(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::mean(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("mean", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("mean", error_message, error_code, -1);
    }
}

void mean_absolute_change(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::meanAbsoluteChange(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("mean_absolute_change", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("mean_absolute_change", error_message, error_code, -1);
    }
}

void mean_change(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::meanChange(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("mean_change", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("mean_change", error_message, error_code, -1);
    }
}

void mean_second_derivative_central(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::meanSecondDerivativeCentral(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("mean_second_derivative_central", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("mean_second_derivative_central", error_message, error_code, -1);
    }
}

void median(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::median(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("median", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("median", error_message, error_code, -1);
    }
}

void minimum(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::minimum(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("minimum", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("minimum", error_message, error_code, -1);
    }
}

void number_crossing_m(khiva_array *array, int *m, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::numberCrossingM(var, *m).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("number_crossing_m", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("number_crossing_m", error_message, error_code, -1);
    }
}

void number_cwt_peaks(khiva_array *array, int *max_w, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::numberPeaks(var, *max_w).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("number_cwt_peaks", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("number_cwt_peaks", error_message, error_code, -1);
    }
}

void number_peaks(khiva_array *array, int *n, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::numberPeaks(var, *n).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("number_peaks", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("number_peaks", error_message, error_code, -1);
    }
}

void partial_autocorrelation(khiva_array *array, khiva_array *lags, khiva_array *result, int *error_code,
                             char *error_message) {
    try {
        af::array var;
        af::array var_lags;
        check_and_retain_arrays(array, lags, var, var_lags);
        af_retain_array(result, khiva::features::partialAutocorrelation(var, var_lags).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("partial_autocorrelation", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("partial_autocorrelation", error_message, error_code, -1);
    }
}

void percentage_of_reoccurring_datapoints_to_all_datapoints(khiva_array *array, bool *is_sorted, khiva_array *result,
                                                            int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result,
                        khiva::features::percentageOfReoccurringDatapointsToAllDatapoints(var, *is_sorted).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("percentage_of_reoccurring_datapoints_to_all_datapoints", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("percentage_of_reoccurring_datapoints_to_all_datapoints", error_message, error_code, -1);
    }
}

void percentage_of_reoccurring_values_to_all_values(khiva_array *array, bool *is_sorted, khiva_array *result,
                                                    int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::percentageOfReoccurringValuesToAllValues(var, *is_sorted).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("percentage_of_reoccurring_values_to_all_values", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("percentage_of_reoccurring_values_to_all_values", error_message, error_code, -1);
    }
}

void quantile(khiva_array *array, khiva_array *q, float *precision, khiva_array *result, int *error_code,
              char *error_message) {
    try {
        af::array var;
        af::array var_q;
        check_and_retain_arrays(array, q, var, var_q);
        af_retain_array(result, khiva::features::quantile(var, var_q, *precision).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("quantile", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("quantile", error_message, error_code, -1);
    }
}

void range_count(khiva_array *array, float *min, float *max, khiva_array *result, int *error_code,
                 char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::rangeCount(var, *min, *max).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("range_count", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("range_count", error_message, error_code, -1);
    }
}

void ratio_beyond_r_sigma(khiva_array *array, float *r, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::ratioBeyondRSigma(var, *r).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("ratio_beyond_r_sigma", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("ratio_beyond_r_sigma", error_message, error_code, -1);
    }
}

void ratio_value_number_to_time_series_length(khiva_array *array, khiva_array *result, int *error_code,
                                              char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::ratioValueNumberToTimeSeriesLength(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("ratio_value_number_to_time_series_length", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("ratio_value_number_to_time_series_length", error_message, error_code, -1);
    }
}

void sample_entropy(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::sampleEntropy(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("sample_entropy", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("sample_entropy", error_message, error_code, -1);
    }
}

void skewness(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::skewness(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("skewness", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("skewness", error_message, error_code, -1);
    }
}

void spkt_welch_density(khiva_array *array, int *coeff, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::spktWelchDensity(var, *coeff).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("spkt_welch_density", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("spkt_welch_density", error_message, error_code, -1);
    }
}

void standard_deviation(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::standardDeviation(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("standard_deviation", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("standard_deviation", error_message, error_code, -1);
    }
}

void sum_of_reoccurring_datapoints(khiva_array *array, bool *is_sorted, khiva_array *result, int *error_code,
                                   char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::sumOfReoccurringDatapoints(var, *is_sorted).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("sum_of_reoccurring_datapoints", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("sum_of_reoccurring_datapoints", error_message, error_code, -1);
    }
}

void sum_of_reoccurring_values(khiva_array *array, bool *is_sorted, khiva_array *result, int *error_code,
                               char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::sumOfReoccurringValues(var, *is_sorted).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("sum_of_reoccurring_values", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("sum_of_reoccurring_values", error_message, error_code, -1);
    }
}

void sum_values(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::sumValues(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("sum_values", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("sum_values", error_message, error_code, -1);
    }
}

void symmetry_looking(khiva_array *array, float *r, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::symmetryLooking(var, *r).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("symmetry_looking", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("symmetry_looking", error_message, error_code, -1);
    }
}

void time_reversal_asymmetry_statistic(khiva_array *array, int *lag, khiva_array *result, int *error_code,
                                       char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::timeReversalAsymmetryStatistic(var, *lag).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("time_reversal_asymmetry_statistic", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("time_reversal_asymmetry_statistic", error_message, error_code, -1);
    }
}

void value_count(khiva_array *array, float *v, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::valueCount(var, *v).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("value_count", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("value_count", error_message, error_code, -1);
    }
}

void variance(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::variance(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("variance", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("variance", error_message, error_code, -1);
    }
}

void variance_larger_than_standard_deviation(khiva_array *array, khiva_array *result, int *error_code,
                                             char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, khiva::features::varianceLargerThanStandardDeviation(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("variance_larger_than_standard_deviation", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("variance_larger_than_standard_deviation", error_message, error_code, -1);
    }
}
