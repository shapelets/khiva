// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/features.h>
#include <khiva_jni/features.h>
#include <khiva_jni/internal/utils.h>
#include <array>

jlong JNICALL Java_io_shapelets_khiva_Features_absEnergy(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::absEnergy, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_absoluteSumOfChanges(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::absoluteSumOfChanges, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_aggregatedAutocorrelation(JNIEnv *env, jobject, jlong ref,
                                                                         jint aggregationFunction) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        af::array result;
        switch (aggregationFunction) {
            case 0:
                result = khiva::features::aggregatedAutocorrelation(arr, af::mean);
                break;
            case 1:
                result = khiva::features::aggregatedAutocorrelation(arr, af::median);
                break;
            case 2:
                result = khiva::features::aggregatedAutocorrelation(arr, af::min);
                break;
            case 3:
                result = khiva::features::aggregatedAutocorrelation(arr, af::max);
                break;
            case 4:
                result = khiva::features::aggregatedAutocorrelation(arr, af::stdev);
                break;
            case 5:
                result = khiva::features::aggregatedAutocorrelation(arr, af::var);
                break;
            default:
                result = khiva::features::aggregatedAutocorrelation(arr, af::mean);
                break;
        }
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Features_aggregatedAutocorrelation. Unknown reason");
    }
    return 0;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_aggregatedLinearTrend(JNIEnv *env, jobject, jlong ref,
                                                                          jlong chunkSize, jint aggregationFunction) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);

        af::array primitive_slope;
        af::array primitive_intercept;
        af::array primitive_rvalue;
        af::array primitive_pvalue;
        af::array primitive_stderrest;
        switch (aggregationFunction) {
            case 0:
                khiva::features::aggregatedLinearTrend(arr, static_cast<long>(chunkSize), af::mean, primitive_slope,
                                                       primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                       primitive_stderrest);
                break;
            case 1:
                khiva::features::aggregatedLinearTrend(arr, static_cast<long>(chunkSize), af::median, primitive_slope,
                                                       primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                       primitive_stderrest);
                break;
            case 2:
                khiva::features::aggregatedLinearTrend(arr, static_cast<long>(chunkSize), af::min, primitive_slope,
                                                       primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                       primitive_stderrest);
                break;
            case 3:
                khiva::features::aggregatedLinearTrend(arr, static_cast<long>(chunkSize), af::max, primitive_slope,
                                                       primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                       primitive_stderrest);
                break;
            case 4:
                khiva::features::aggregatedLinearTrend(arr, static_cast<long>(chunkSize), af::stdev, primitive_slope,
                                                       primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                       primitive_stderrest);
                break;
            default:
                khiva::features::aggregatedLinearTrend(arr, static_cast<long>(chunkSize), af::mean, primitive_slope,
                                                       primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                       primitive_stderrest);
                break;
        }

        constexpr auto output_size = 5;
        std::array<jlong, output_size> output;
        output[0] = reinterpret_cast<jlong>(new af::array(primitive_slope));
        output[1] = reinterpret_cast<jlong>(new af::array(primitive_intercept));
        output[2] = reinterpret_cast<jlong>(new af::array(primitive_rvalue));
        output[3] = reinterpret_cast<jlong>(new af::array(primitive_pvalue));
        output[4] = reinterpret_cast<jlong>(new af::array(primitive_stderrest));

        auto pointers = env->NewLongArray(output_size);
        env->SetLongArrayRegion(pointers, 0, output_size, output.data());
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Features_aggregatedLinearTrend. Unknown reason");
    }
    return nullptr;
}

jlong JNICALL Java_io_shapelets_khiva_Features_approximateEntropy(JNIEnv *env, jobject, jlong ref, jint m, jfloat r) {
    return khiva::jni::KhivaCall(env, khiva::features::approximateEntropy, ref, m, r);
}

jlong JNICALL Java_io_shapelets_khiva_Features_crossCovariance(JNIEnv *env, jobject, jlong ref_xss, jlong ref_yss,
                                                               jboolean unbiased) {
    return khiva::jni::KhivaCallTwoArrays(env, khiva::features::crossCovariance, ref_xss, ref_yss, unbiased);
}

jlong JNICALL Java_io_shapelets_khiva_Features_autoCovariance(JNIEnv *env, jobject, jlong ref, jboolean unbiased) {
    return khiva::jni::KhivaCall(env, khiva::features::autoCovariance, ref, unbiased);
}

jlong JNICALL Java_io_shapelets_khiva_Features_crossCorrelation(JNIEnv *env, jobject, jlong ref_xss, jlong ref_yss,
                                                                jboolean unbiased) {
    return khiva::jni::KhivaCallTwoArrays(env, khiva::features::crossCorrelation, ref_xss, ref_yss, unbiased);
}

jlong JNICALL Java_io_shapelets_khiva_Features_autoCorrelation(JNIEnv *env, jobject, jlong ref, jlong maxLag,
                                                               jboolean unbiased) {
    return khiva::jni::KhivaCall(env, khiva::features::autoCorrelation, ref, maxLag, unbiased);
}

jlong JNICALL Java_io_shapelets_khiva_Features_binnedEntropy(JNIEnv *env, jobject, jlong ref, jint max_bins) {
    return khiva::jni::KhivaCall(env, khiva::features::binnedEntropy, ref, max_bins);
}

jlong JNICALL Java_io_shapelets_khiva_Features_c3(JNIEnv *env, jobject, jlong ref, jlong lag) {
    return khiva::jni::KhivaCall(env, khiva::features::c3, ref, lag);
}

jlong JNICALL Java_io_shapelets_khiva_Features_cidCe(JNIEnv *env, jobject, jlong ref, jboolean zNormalize) {
    return khiva::jni::KhivaCall(env, khiva::features::cidCe, ref, zNormalize);
}

jlong JNICALL Java_io_shapelets_khiva_Features_countAboveMean(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::countAboveMean, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_countBelowMean(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::countBelowMean, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_cwtCoefficients(JNIEnv *env, jobject, jlong ref, jlong widths,
                                                               jint coeff, jint w) {
    return khiva::jni::KhivaCallTwoArrays(env, khiva::features::cwtCoefficients, ref, widths, coeff, w);
}

jlong JNICALL Java_io_shapelets_khiva_Features_energyRatioByChunks(JNIEnv *env, jobject, jlong ref, jlong numSegments,
                                                                   jlong segmentFocus) {
    return khiva::jni::KhivaCall(env, khiva::features::energyRatioByChunks, ref, static_cast<long>(numSegments),
                                 static_cast<long>(segmentFocus));
}

jlong JNICALL Java_io_shapelets_khiva_Features_fftAggregated(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::fftAggregated, ref);
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_fftCoefficient(JNIEnv *env, jobject, jlong ref, jlong coefficient) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        af::array primitive_real;
        af::array primitive_imag;
        af::array primitive_absolute;
        af::array primitive_angle;

        khiva::features::fftCoefficient(arr, static_cast<long>(coefficient), primitive_real, primitive_imag,
                                        primitive_absolute, primitive_angle);
        constexpr auto output_size = 4;
        std::array<jlong, output_size> output;
        output[0] = reinterpret_cast<jlong>(new af::array(primitive_real));
        output[1] = reinterpret_cast<jlong>(new af::array(primitive_imag));
        output[2] = reinterpret_cast<jlong>(new af::array(primitive_absolute));
        output[3] = reinterpret_cast<jlong>(new af::array(primitive_angle));

        auto pointers = env->NewLongArray(output_size);
        env->SetLongArrayRegion(pointers, 0, output_size, output.data());
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Features_fftCoefficient. Unknown reason");
    }
    return nullptr;
}

jlong JNICALL Java_io_shapelets_khiva_Features_firstLocationOfMaximum(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::firstLocationOfMaximum, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_firstLocationOfMinimum(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::firstLocationOfMinimum, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_friedrichCoefficients(JNIEnv *env, jobject, jlong ref, jint m,
                                                                     jfloat r) {
    return khiva::jni::KhivaCall(env, khiva::features::friedrichCoefficients, ref, m, r);
}

jlong JNICALL Java_io_shapelets_khiva_Features_hasDuplicates(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::hasDuplicates, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_hasDuplicateMax(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::hasDuplicateMax, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_hasDuplicateMin(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::hasDuplicateMin, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_indexMassQuantile(JNIEnv *env, jobject, jlong ref, jfloat q) {
    return khiva::jni::KhivaCall(env, khiva::features::indexMassQuantile, ref, q);
}

jlong JNICALL Java_io_shapelets_khiva_Features_kurtosis(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::kurtosis, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_largeStandardDeviation(JNIEnv *env, jobject, jlong ref, jfloat r) {
    return khiva::jni::KhivaCall(env, khiva::features::largeStandardDeviation, ref, r);
}

jlong JNICALL Java_io_shapelets_khiva_Features_lastLocationOfMaximum(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::lastLocationOfMaximum, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_lastLocationOfMinimum(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::lastLocationOfMinimum, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_length(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::length, ref);
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_linearTrend(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);

        af::array primitive_pvalue;
        af::array primitive_rvalue;
        af::array primitive_intercept;
        af::array primitive_slope;
        af::array primitive_stderr;
        khiva::features::linearTrend(arr, primitive_pvalue, primitive_rvalue, primitive_intercept, primitive_slope,
                                     primitive_stderr);
        constexpr auto output_size = 5;
        std::array<jlong, output_size> output;
        output[0] = reinterpret_cast<jlong>(new af::array(primitive_pvalue));
        output[1] = reinterpret_cast<jlong>(new af::array(primitive_rvalue));
        output[2] = reinterpret_cast<jlong>(new af::array(primitive_intercept));
        output[3] = reinterpret_cast<jlong>(new af::array(primitive_slope));
        output[4] = reinterpret_cast<jlong>(new af::array(primitive_stderr));

        auto pointers = env->NewLongArray(output_size);
        env->SetLongArrayRegion(pointers, 0, output_size, output.data());
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Features_linearTrend. Unknown reason");
    }
    return nullptr;
}

jlong JNICALL Java_io_shapelets_khiva_Features_localMaximals(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::localMaximals, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_longestStrikeAboveMean(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::longestStrikeAboveMean, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_longestStrikeBelowMean(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::longestStrikeBelowMean, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_maxLangevinFixedPoint(JNIEnv *env, jobject, jlong ref, jint m,
                                                                     jfloat r) {
    return khiva::jni::KhivaCall(env, khiva::features::maxLangevinFixedPoint, ref, m, r);
}

jlong JNICALL Java_io_shapelets_khiva_Features_maximum(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::maximum, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_mean(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::mean, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_meanAbsoluteChange(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::meanAbsoluteChange, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_meanChange(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::meanChange, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_meanSecondDerivativeCentral(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::meanSecondDerivativeCentral, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_median(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::median, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_minimum(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::minimum, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_numberCrossingM(JNIEnv *env, jobject, jlong ref, jint m) {
    return khiva::jni::KhivaCall(env, khiva::features::numberCrossingM, ref, m);
}

jlong JNICALL Java_io_shapelets_khiva_Features_numberCwtPeaks(JNIEnv *env, jobject, jlong ref, jint maxW) {
    return khiva::jni::KhivaCall(env, khiva::features::numberCwtPeaks, ref, maxW);
}

jlong JNICALL Java_io_shapelets_khiva_Features_numberPeaks(JNIEnv *env, jobject, jlong ref, jint n) {
    return khiva::jni::KhivaCall(env, khiva::features::numberPeaks, ref, n);
}

jlong JNICALL Java_io_shapelets_khiva_Features_partialAutocorrelation(JNIEnv *env, jobject, jlong ref, jlong lags) {
    return khiva::jni::KhivaCallTwoArrays(env, khiva::features::partialAutocorrelation, ref, lags);
}

jlong JNICALL Java_io_shapelets_khiva_Features_percentageOfReoccurringDatapointsToAllDatapoints(JNIEnv *env, jobject,
                                                                                                jlong ref,
                                                                                                jboolean isSorted) {
    return khiva::jni::KhivaCall(env, khiva::features::percentageOfReoccurringDatapointsToAllDatapoints, ref, isSorted);
}

jlong JNICALL Java_io_shapelets_khiva_Features_percentageOfReoccurringValuesToAllValues(JNIEnv *env, jobject, jlong ref,
                                                                                        jboolean isSorted) {
    return khiva::jni::KhivaCall(env, khiva::features::percentageOfReoccurringValuesToAllValues, ref, isSorted);
}

jlong JNICALL Java_io_shapelets_khiva_Features_quantile(JNIEnv *env, jobject, jlong ref, jlong q, jfloat precision) {
    return khiva::jni::KhivaCallTwoArrays(env, khiva::features::quantile, ref, q, precision);
}

jlong JNICALL Java_io_shapelets_khiva_Features_rangeCount(JNIEnv *env, jobject, jlong ref, jfloat min, jfloat max) {
    return khiva::jni::KhivaCall(env, khiva::features::rangeCount, ref, min, max);
}

jlong JNICALL Java_io_shapelets_khiva_Features_ratioBeyondRSigma(JNIEnv *env, jobject, jlong ref, jfloat r) {
    return khiva::jni::KhivaCall(env, khiva::features::ratioBeyondRSigma, ref, r);
}

jlong JNICALL Java_io_shapelets_khiva_Features_ratioValueNumberToTimeSeriesLength(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::ratioValueNumberToTimeSeriesLength, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_sampleEntropy(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::sampleEntropy, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_skewness(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::skewness, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_spktWelchDensity(JNIEnv *env, jobject, jlong ref, jint coeff) {
    return khiva::jni::KhivaCall(env, khiva::features::spktWelchDensity, ref, coeff);
}

jlong JNICALL Java_io_shapelets_khiva_Features_standardDeviation(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::standardDeviation, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_sumOfReoccurringDatapoints(JNIEnv *env, jobject, jlong ref,
                                                                          jboolean isSorted) {
    return khiva::jni::KhivaCall(env, khiva::features::sumOfReoccurringDatapoints, ref, isSorted);
}

jlong JNICALL Java_io_shapelets_khiva_Features_sumOfReoccurringValues(JNIEnv *env, jobject, jlong ref,
                                                                      jboolean isSorted) {
    return khiva::jni::KhivaCall(env, khiva::features::sumOfReoccurringValues, ref, isSorted);
}

jlong JNICALL Java_io_shapelets_khiva_Features_sumValues(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::sumValues, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_symmetryLooking(JNIEnv *env, jobject, jlong ref, jfloat r) {
    return khiva::jni::KhivaCall(env, khiva::features::symmetryLooking, ref, r);
}

jlong JNICALL Java_io_shapelets_khiva_Features_timeReversalAsymmetryStatistic(JNIEnv *env, jobject, jlong ref,
                                                                              jint lag) {
    return khiva::jni::KhivaCall(env, khiva::features::timeReversalAsymmetryStatistic, ref, lag);
}

jlong JNICALL Java_io_shapelets_khiva_Features_valueCount(JNIEnv *env, jobject, jlong ref, jfloat v) {
    return khiva::jni::KhivaCall(env, khiva::features::valueCount, ref, v);
}

jlong JNICALL Java_io_shapelets_khiva_Features_variance(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::variance, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Features_varianceLargerThanStandardDeviation(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::features::varianceLargerThanStandardDeviation, ref);
}
