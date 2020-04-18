// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>
#include <khiva/features.h>
#include <khiva_jni/features.h>

#include <array>

jlong JNICALL Java_io_shapelets_khiva_Features_absEnergy(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::absEnergy(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_absEnergy. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_absoluteSumOfChanges(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::absoluteSumOfChanges(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_absoluteSumOfChanges. Unknown reason");
    }
    return 0;
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
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
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
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_aggregatedLinearTrend. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_approximateEntropy(JNIEnv *env, jobject, jlong ref, jint m, jfloat r) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::approximateEntropy(arr, m, r);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_approximateEntropy. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_crossCovariance(JNIEnv *env, jobject, jlong ref_xss, jlong ref_yss,
                                                               jboolean unbiased) {
    try {
        auto arr_xss = *reinterpret_cast<af::array *>(ref_xss);
        auto arr_yss = *reinterpret_cast<af::array *>(ref_yss);
        auto result = khiva::features::crossCovariance(arr_xss, arr_yss, unbiased);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_crossCovariance. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_autoCovariance(JNIEnv *env, jobject, jlong ref, jboolean unbiased) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::autoCovariance(arr, unbiased);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_autoCovariance. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_crossCorrelation(JNIEnv *env, jobject, jlong ref_xss, jlong ref_yss,
                                                                jboolean unbiased) {
    try {
        auto arr_xss = *reinterpret_cast<af::array *>(ref_xss);
        auto arr_yss = *reinterpret_cast<af::array *>(ref_yss);
        auto result = khiva::features::crossCorrelation(arr_xss, arr_yss, unbiased);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_crossCorrelation. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_autoCorrelation(JNIEnv *env, jobject, jlong ref, jlong maxLag,
                                                               jboolean unbiased) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::autoCorrelation(arr, static_cast<long>(maxLag), unbiased);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_autoCorrelation. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_binnedEntropy(JNIEnv *env, jobject, jlong ref, jint max_bins) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::binnedEntropy(arr, max_bins);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_binnedEntropy. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_c3(JNIEnv *env, jobject, jlong ref, jlong lag) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::c3(arr, static_cast<long>(lag));
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_c3. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_cidCe(JNIEnv *env, jobject, jlong ref, jboolean zNormalize) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::cidCe(arr, static_cast<long>(zNormalize));
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_cidCe. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_countAboveMean(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::countAboveMean(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_countAboveMean. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_countBelowMean(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::countAboveMean(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_countBelowMean. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_cwtCoefficients(JNIEnv *env, jobject, jlong ref, jlong widths,
                                                               jint coeff, jint w) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto arr_widths = *reinterpret_cast<af::array *>(widths);
        auto result = khiva::features::cwtCoefficients(arr, arr_widths, coeff, w);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_cwtCoefficients. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_energyRatioByChunks(JNIEnv *env, jobject, jlong ref, jlong numSegments,
                                                                   jlong segmentFocus) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result =
            khiva::features::energyRatioByChunks(arr, static_cast<long>(numSegments), static_cast<long>(segmentFocus));
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_energyRatioByChunks. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_fftAggregated(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::fftAggregated(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_fftAggregated. Unknown reason");
    }
    return 0;
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
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_fftCoefficient. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_firstLocationOfMaximum(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::firstLocationOfMaximum(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_firstLocationOfMaximum. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_firstLocationOfMinimum(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::firstLocationOfMinimum(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_firstLocationOfMinimum. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_friedrichCoefficients(JNIEnv *env, jobject, jlong ref, jint m,
                                                                     jfloat r) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::friedrichCoefficients(arr, m, r);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_friedrichCoefficients. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_hasDuplicates(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::hasDuplicates(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_hasDuplicates. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_hasDuplicateMax(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::hasDuplicateMax(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_hasDuplicateMax. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_hasDuplicateMin(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::hasDuplicateMin(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_hasDuplicateMin. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_indexMassQuantile(JNIEnv *env, jobject, jlong ref, jfloat q) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::indexMassQuantile(arr, q);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_indexMassQuantile. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_kurtosis(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::kurtosis(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_kurtosis. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_largeStandardDeviation(JNIEnv *env, jobject, jlong ref, jfloat r) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::largeStandardDeviation(arr, r);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_largeStandardDeviation. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_lastLocationOfMaximum(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::lastLocationOfMaximum(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_lastLocationOfMaximum. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_lastLocationOfMinimum(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::lastLocationOfMinimum(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_lastLocationOfMinimum. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_length(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::length(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_length. Unknown reason");
    }
    return 0;
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
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_linearTrend. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_localMaximals(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::localMaximals(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_localMaximals. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_longestStrikeAboveMean(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::longestStrikeAboveMean(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_longestStrikeAboveMean. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_longestStrikeBelowMean(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::longestStrikeBelowMean(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_longestStrikeBelowMean. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_maxLangevinFixedPoint(JNIEnv *env, jobject, jlong ref, jint m,
                                                                     jfloat r) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::maxLangevinFixedPoint(arr, m, r);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_maxLangevinFixedPoint. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_maximum(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::maximum(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_maximum. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_mean(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::mean(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_mean. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_meanAbsoluteChange(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::meanAbsoluteChange(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_meanAbsoluteChange. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_meanChange(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::meanChange(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_meanChange. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_meanSecondDerivativeCentral(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::meanSecondDerivativeCentral(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_meanSecondDerivativeCentral. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_median(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::median(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_median. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_minimum(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::minimum(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_minimum. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_numberCrossingM(JNIEnv *env, jobject, jlong ref, jint m) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::numberCrossingM(arr, m);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_numberCrossingM. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_numberCwtPeaks(JNIEnv *env, jobject, jlong ref, jint maxW) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::numberCwtPeaks(arr, maxW);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_numberCwtPeaks. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_numberPeaks(JNIEnv *env, jobject, jlong ref, jint n) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::numberPeaks(arr, n);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_numberPeaks. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_partialAutocorrelation(JNIEnv *env, jobject, jlong ref, jlong lags) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto arr_lags = *reinterpret_cast<af::array *>(lags);
        auto result = khiva::features::partialAutocorrelation(arr, arr_lags);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_partialAutocorrelation. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_percentageOfReoccurringDatapointsToAllDatapoints(JNIEnv *env, jobject,
                                                                                                jlong ref,
                                                                                                jboolean isSorted) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::percentageOfReoccurringDatapointsToAllDatapoints(arr, isSorted);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass,
                      "Error in Features_percentageOfReoccurringDatapointsToAllDatapoints. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_percentageOfReoccurringValuesToAllValues(JNIEnv *env, jobject, jlong ref,
                                                                                        jboolean isSorted) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::percentageOfReoccurringValuesToAllValues(arr, isSorted);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_percentageOfReoccurringValuesToAllValues. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_quantile(JNIEnv *env, jobject, jlong ref, jlong q, jfloat precision) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto arr_q = *reinterpret_cast<af::array *>(q);
        auto result = khiva::features::quantile(arr, arr_q, precision);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_quantile. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_rangeCount(JNIEnv *env, jobject, jlong ref, jfloat min, jfloat max) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::rangeCount(arr, min, max);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_rangeCount. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_ratioBeyondRSigma(JNIEnv *env, jobject, jlong ref, jfloat r) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::ratioBeyondRSigma(arr, r);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_ratioBeyondRSigma. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_ratioValueNumberToTimeSeriesLength(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::ratioValueNumberToTimeSeriesLength(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_ratioValueNumberToTimeSeriesLength. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_sampleEntropy(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::sampleEntropy(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_sampleEntropy. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_skewness(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::skewness(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_skewness. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_spktWelchDensity(JNIEnv *env, jobject, jlong ref, jint coeff) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::spktWelchDensity(arr, coeff);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_spktWelchDensity. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_standardDeviation(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::standardDeviation(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_standardDeviation. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_sumOfReoccurringDatapoints(JNIEnv *env, jobject, jlong ref,
                                                                          jboolean isSorted) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::sumOfReoccurringDatapoints(arr, isSorted);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_sumOfReoccurringDatapoints. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_sumOfReoccurringValues(JNIEnv *env, jobject, jlong ref,
                                                                      jboolean isSorted) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::sumOfReoccurringValues(arr, isSorted);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_sumOfReoccurringValues. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_sumValues(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::sumValues(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_sumValues. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_symmetryLooking(JNIEnv *env, jobject, jlong ref, jfloat r) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::symmetryLooking(arr, r);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_symmetryLooking. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_timeReversalAsymmetryStatistic(JNIEnv *env, jobject, jlong ref,
                                                                              jint lag) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::timeReversalAsymmetryStatistic(arr, lag);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_timeReversalAsymmetryStatistic. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_valueCount(JNIEnv *env, jobject, jlong ref, jfloat v) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::valueCount(arr, v);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_valueCount. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_variance(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::variance(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_variance. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Features_varianceLargerThanStandardDeviation(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::features::varianceLargerThanStandardDeviation(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Features_varianceLargerThanStandardDeviation. Unknown reason");
    }
    return 0;
}
