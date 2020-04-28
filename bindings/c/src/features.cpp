// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/array.h>
#include <khiva/features.h>
#include <khiva/internal/util.h>
#include <khiva_c/features.h>
#include <khiva_c/internal/util.h>

using namespace khiva;
using namespace khiva::util;

void abs_energy(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto r = khiva::features::absEnergy(var);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void absolute_sum_of_changes(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto r = khiva::features::absoluteSumOfChanges(var);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void aggregated_autocorrelation(const khiva_array *array, const int *aggregation_function, khiva_array *result,
                                int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        af::array r;
        switch (*aggregation_function) {
            case 0:
                r = khiva::features::aggregatedAutocorrelation(var, af::mean);
                break;
            case 1:
                r = khiva::features::aggregatedAutocorrelation(var, af::median);
                break;
            case 2:
                r = khiva::features::aggregatedAutocorrelation(var, af::min);
                break;
            case 3:
                r = khiva::features::aggregatedAutocorrelation(var, af::max);
                break;
            case 4:
                r = khiva::features::aggregatedAutocorrelation(var, af::stdev);
                break;
            case 5:
                r = khiva::features::aggregatedAutocorrelation(var, af::var);
                break;
            default:
                r = khiva::features::aggregatedAutocorrelation(var, af::mean);
                break;
        }
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void aggregated_linear_trend(const khiva_array *array, const long *chunkSize, const int *aggregation_function,
                             khiva_array *slope, khiva_array *intercept, khiva_array *rvalue, khiva_array *pvalue,
                             khiva_array *stderrest, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
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
        *slope = array::increment_ref_count(primitive_slope.get());
        *intercept = array::increment_ref_count(primitive_intercept.get());
        *rvalue = array::increment_ref_count(primitive_rvalue.get());
        *pvalue = array::increment_ref_count(primitive_pvalue.get());
        *stderrest = array::increment_ref_count(primitive_stderrest.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void approximate_entropy(const khiva_array *array, const int *m, const float *r, khiva_array *result, int *error_code,
                         char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::approximateEntropy(var, *m, *r);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void cross_covariance(const khiva_array *xss, const khiva_array *yss, const bool *unbiased, khiva_array *result,
                      int *error_code, char *error_message) {
    try {
        auto var_xss = array::from_af_array(*xss);
        auto var_yss = array::from_af_array(*yss);
        auto r = khiva::features::crossCovariance(var_xss, var_yss, *unbiased);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void auto_covariance(const khiva_array *array, const bool *unbiased, khiva_array *result, int *error_code,
                     char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto r = khiva::features::autoCovariance(var, *unbiased);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void cross_correlation(const khiva_array *xss, const khiva_array *yss, const bool *unbiased, khiva_array *result,
                       int *error_code, char *error_message) {
    try {
        auto var_xss = array::from_af_array(*xss);
        auto var_yss = array::from_af_array(*yss);
        auto r = khiva::features::crossCorrelation(var_xss, var_yss, *unbiased);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void auto_correlation(const khiva_array *array, const long *max_lag, const bool *unbiased, khiva_array *result,
                      int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto r = khiva::features::autoCorrelation(var, *max_lag, *unbiased);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void binned_entropy(const khiva_array *array, const int *max_bins, khiva_array *result, int *error_code,
                    char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto r = khiva::features::binnedEntropy(var, *max_bins);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void c3(const khiva_array *array, const long *lag, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto r = khiva::features::c3(var, *lag);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void cid_ce(const khiva_array *array, const bool *zNormalize, khiva_array *result, int *error_code,
            char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto r = khiva::features::cidCe(var, *zNormalize);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void count_above_mean(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto r = khiva::features::countAboveMean(var);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void count_below_mean(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto r = khiva::features::countBelowMean(var);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void cwt_coefficients(const khiva_array *array, const khiva_array *width, const int *coeff, const int *w,
                      khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto var_width = array::from_af_array(*width);
        auto r = khiva::features::cwtCoefficients(var, var_width, *coeff, *w);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void energy_ratio_by_chunks(const khiva_array *array, const long *num_segments, const long *segment_focus,
                            khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto r = khiva::features::energyRatioByChunks(var, *num_segments, *segment_focus);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void fft_aggregated(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto r = khiva::features::fftAggregated(var);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void fft_coefficient(const khiva_array *array, const long *coefficient, khiva_array *real, khiva_array *imag,
                     khiva_array *absolute, khiva_array *angle, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        af::array primitive_real;
        af::array primitive_imag;
        af::array primitive_abs;
        af::array primitive_angle;
        khiva::features::fftCoefficient(var, *coefficient, primitive_real, primitive_imag, primitive_abs,
                                        primitive_angle);
        *real = array::increment_ref_count(primitive_real.get());
        *imag = array::increment_ref_count(primitive_imag.get());
        *absolute = array::increment_ref_count(primitive_abs.get());
        *angle = array::increment_ref_count(primitive_angle.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void first_location_of_maximum(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto r = khiva::features::firstLocationOfMaximum(var);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void first_location_of_minimum(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto r = khiva::features::firstLocationOfMinimum(var);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void friedrich_coefficients(const khiva_array *array, const int *m, const float *r, khiva_array *result,
                            int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::friedrichCoefficients(var, *m, *r);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void has_duplicates(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::hasDuplicates(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void has_duplicate_max(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::hasDuplicateMax(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void has_duplicate_min(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::hasDuplicateMin(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void index_mass_quantile(const khiva_array *array, const float *q, khiva_array *result, int *error_code,
                         char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::indexMassQuantile(var, *q);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void kurtosis(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::kurtosis(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void large_standard_deviation(const khiva_array *array, const float *r, khiva_array *result, int *error_code,
                              char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::largeStandardDeviation(var, *r);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void last_location_of_maximum(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::lastLocationOfMaximum(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void last_location_of_minimum(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::lastLocationOfMinimum(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void length(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::length(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void linear_trend(const khiva_array *array, khiva_array *pvalue, khiva_array *rvalue, khiva_array *intercept,
                  khiva_array *slope, khiva_array *stdrr, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        af::array primitive_pvalue;
        af::array primitive_rvalue;
        af::array primitive_intercept;
        af::array primitive_slope;
        af::array primitive_stdrr;
        khiva::features::linearTrend(var, primitive_pvalue, primitive_rvalue, primitive_intercept, primitive_slope,
                                     primitive_stdrr);
        *slope = array::increment_ref_count(primitive_slope.get());
        *intercept = array::increment_ref_count(primitive_intercept.get());
        *rvalue = array::increment_ref_count(primitive_rvalue.get());
        *pvalue = array::increment_ref_count(primitive_pvalue.get());
        *stdrr = array::increment_ref_count(primitive_stdrr.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void local_maximals(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::localMaximals(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void longest_strike_above_mean(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::longestStrikeAboveMean(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void longest_strike_below_mean(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::longestStrikeBelowMean(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void max_langevin_fixed_point(const khiva_array *array, const int *m, const float *r, khiva_array *result,
                              int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::maxLangevinFixedPoint(var, *m, *r);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void maximum(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::maximum(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void mean(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::mean(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void mean_absolute_change(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::meanAbsoluteChange(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void mean_change(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::meanChange(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void mean_second_derivative_central(const khiva_array *array, khiva_array *result, int *error_code,
                                    char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::meanSecondDerivativeCentral(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void median(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::median(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void minimum(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::minimum(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void number_crossing_m(const khiva_array *array, const int *m, khiva_array *result, int *error_code,
                       char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::numberCrossingM(var, *m);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void number_cwt_peaks(const khiva_array *array, const int *max_w, khiva_array *result, int *error_code,
                      char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::numberPeaks(var, *max_w);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void number_peaks(const khiva_array *array, const int *n, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::numberPeaks(var, *n);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void partial_autocorrelation(const khiva_array *array, const khiva_array *lags, khiva_array *result, int *error_code,
                             char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto var_lags = array::from_af_array(*lags);
        auto res = khiva::features::partialAutocorrelation(var, var_lags);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void percentage_of_reoccurring_datapoints_to_all_datapoints(const khiva_array *array, const bool *is_sorted,
                                                            khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::percentageOfReoccurringDatapointsToAllDatapoints(var, *is_sorted);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void percentage_of_reoccurring_values_to_all_values(const khiva_array *array, const bool *is_sorted,
                                                    khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::percentageOfReoccurringValuesToAllValues(var, *is_sorted);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void quantile(const khiva_array *array, const khiva_array *q, const float *precision, khiva_array *result,
              int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto var_q = array::from_af_array(*q);
        auto res = khiva::features::quantile(var, var_q, *precision);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void range_count(const khiva_array *array, const float *min, const float *max, khiva_array *result, int *error_code,
                 char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::rangeCount(var, *min, *max);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void ratio_beyond_r_sigma(const khiva_array *array, const float *r, khiva_array *result, int *error_code,
                          char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::ratioBeyondRSigma(var, *r);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void ratio_value_number_to_time_series_length(const khiva_array *array, khiva_array *result, int *error_code,
                                              char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::ratioValueNumberToTimeSeriesLength(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void sample_entropy(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::sampleEntropy(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void skewness(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::skewness(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void spkt_welch_density(const khiva_array *array, const int *coeff, khiva_array *result, int *error_code,
                        char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::spktWelchDensity(var, *coeff);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void standard_deviation(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::standardDeviation(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void sum_of_reoccurring_datapoints(const khiva_array *array, const bool *is_sorted, khiva_array *result,
                                   int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::sumOfReoccurringDatapoints(var, *is_sorted);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void sum_of_reoccurring_values(const khiva_array *array, const bool *is_sorted, khiva_array *result, int *error_code,
                               char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::sumOfReoccurringValues(var, *is_sorted);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void sum_values(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::sumValues(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void symmetry_looking(const khiva_array *array, const float *r, khiva_array *result, int *error_code,
                      char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::symmetryLooking(var, *r);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void time_reversal_asymmetry_statistic(const khiva_array *array, const int *lag, khiva_array *result, int *error_code,
                                       char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::timeReversalAsymmetryStatistic(var, *lag);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void value_count(const khiva_array *array, const float *v, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::valueCount(var, *v);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void variance(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::variance(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void variance_larger_than_standard_deviation(const khiva_array *array, khiva_array *result, int *error_code,
                                             char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto res = khiva::features::varianceLargerThanStandardDeviation(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}
