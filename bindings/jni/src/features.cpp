// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>
#include <khiva/features.h>
#include <khiva_jni/features.h>
#include <khiva_jni/util.h>

jlongArray JNICALL Java_io_shapelets_khiva_Features_absEnergy(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::absEnergy(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_absoluteSumOfChanges(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::absoluteSumOfChanges(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_aggregatedAutocorrelation(JNIEnv *env, jobject, jlong ref,
                                                                              jint aggregationFunction) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    switch (aggregationFunction) {
        case 0:
            af_retain_array(&af_p, khiva::features::aggregatedAutocorrelation(var, af::mean).get());
            break;
        case 1:
            af_retain_array(&af_p, khiva::features::aggregatedAutocorrelation(var, af::median).get());
            break;
        case 2:
            af_retain_array(&af_p, khiva::features::aggregatedAutocorrelation(var, af::min).get());

            break;
        case 3:
            af_retain_array(&af_p, khiva::features::aggregatedAutocorrelation(var, af::max).get());

            break;
        case 4:
            af_retain_array(&af_p, khiva::features::aggregatedAutocorrelation(var, af::stdev).get());

            break;
        case 5:
            af_retain_array(&af_p, khiva::features::aggregatedAutocorrelation(var, af::var).get());

            break;
        default:
            af_retain_array(&af_p, khiva::features::aggregatedAutocorrelation(var, af::mean).get());

            break;
    }
    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_aggregatedLinearTrend(JNIEnv *env, jobject, jlong ref,
                                                                          jlong chunkSize, jint aggregationFunction) {
    const jint l = 6;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer_slope = 0;
    af_array af_p_slope = (af_array)raw_pointer_slope;

    jlong raw_pointer_intercept = 0;
    af_array af_p_intercept = (af_array)raw_pointer_intercept;

    jlong raw_pointer_rvalue = 0;
    af_array af_p_rvalue = (af_array)raw_pointer_rvalue;

    jlong raw_pointer_pvalue = 0;
    af_array af_p_pvalue = (af_array)raw_pointer_pvalue;

    jlong raw_pointer_stderrest = 0;
    af_array af_p_stderrest = (af_array)raw_pointer_stderrest;

    af_retain_array(&arr, var.get());

    af::array primitive_slope;
    af::array primitive_intercept;
    af::array primitive_rvalue;
    af::array primitive_pvalue;
    af::array primitive_stderrest;
    switch (aggregationFunction) {
        case 0:
            khiva::features::aggregatedLinearTrend(var, static_cast<long>(chunkSize), af::mean, primitive_slope,
                                                   primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                   primitive_stderrest);
            break;
        case 1:
            khiva::features::aggregatedLinearTrend(var, static_cast<long>(chunkSize), af::median, primitive_slope,
                                                   primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                   primitive_stderrest);
            break;
        case 2:
            khiva::features::aggregatedLinearTrend(var, static_cast<long>(chunkSize), af::min, primitive_slope,
                                                   primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                   primitive_stderrest);
            break;
        case 3:
            khiva::features::aggregatedLinearTrend(var, static_cast<long>(chunkSize), af::max, primitive_slope,
                                                   primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                   primitive_stderrest);
            break;
        case 4:
            khiva::features::aggregatedLinearTrend(var, static_cast<long>(chunkSize), af::stdev, primitive_slope,
                                                   primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                   primitive_stderrest);
            break;
        default:
            khiva::features::aggregatedLinearTrend(var, static_cast<long>(chunkSize), af::mean, primitive_slope,
                                                   primitive_intercept, primitive_rvalue, primitive_pvalue,
                                                   primitive_stderrest);
            break;
    }
    af_retain_array(&af_p_slope, primitive_slope.get());
    af_retain_array(&af_p_intercept, primitive_intercept.get());
    af_retain_array(&af_p_rvalue, primitive_rvalue.get());
    af_retain_array(&af_p_pvalue, primitive_pvalue.get());
    af_retain_array(&af_p_stderrest, primitive_stderrest.get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p_slope;
    tmp[2] = (jlong)af_p_intercept;
    tmp[3] = (jlong)af_p_rvalue;
    tmp[4] = (jlong)af_p_pvalue;
    tmp[5] = (jlong)af_p_stderrest;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_approximateEntropy(JNIEnv *env, jobject, jlong ref, jint m,
                                                                       jfloat r) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::approximateEntropy(var, m, r).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_crossCovariance(JNIEnv *env, jobject, jlong ref_xss, jlong ref_yss,
                                                                    jboolean unbiased) {
    const jint l = 3;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array xss = (af_array)ref_xss;
    af::array var_xss;
    af_array yss = (af_array)ref_yss;
    af::array var_yss;

    check_and_retain_arrays(xss, yss, var_xss, var_yss);
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;
    af_retain_array(&af_p, khiva::features::crossCovariance(var_xss, var_yss, unbiased).get());

    tmp[0] = (jlong)xss;
    tmp[1] = (jlong)yss;
    tmp[2] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_autoCovariance(JNIEnv *env, jobject, jlong ref, jboolean unbiased) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::autoCovariance(var, unbiased).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_crossCorrelation(JNIEnv *env, jobject, jlong ref_xss, jlong ref_yss,
                                                                     jboolean unbiased) {
    const jint l = 3;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr_xss = (af_array)ref_xss;
    af::array var_xss;
    af_array arr_yss = (af_array)ref_yss;
    af::array var_yss;

    check_and_retain_arrays(arr_xss, arr_yss, var_xss, var_yss);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&af_p, khiva::features::crossCorrelation(var_xss, var_yss, unbiased).get());

    tmp[0] = (jlong)arr_xss;
    tmp[1] = (jlong)arr_yss;
    tmp[2] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_autoCorrelation(JNIEnv *env, jobject, jlong ref, jlong maxLag,
                                                                    jboolean unbiased) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::autoCorrelation(var, static_cast<long>(maxLag), unbiased).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_binnedEntropy(JNIEnv *env, jobject, jlong ref, jint max_bins) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::binnedEntropy(var, max_bins).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_c3(JNIEnv *env, jobject, jlong ref, jlong lag) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::c3(var, static_cast<long>(lag)).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_cidCe(JNIEnv *env, jobject, jlong ref, jboolean zNormalize) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::cidCe(var, zNormalize).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_countAboveMean(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::countAboveMean(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_countBelowMean(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::countBelowMean(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_cwtCoefficients(JNIEnv *env, jobject, jlong ref, jlong widths,
                                                                    jint coeff, jint w) {
    const jint l = 3;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var;

    af_array af_w = (af_array)widths;
    af::array var_w;

    check_and_retain_arrays(arr, af_w, var, var_w);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&af_p, khiva::features::cwtCoefficients(var, var_w, coeff, w).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_w;
    tmp[2] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_energyRatioByChunks(JNIEnv *env, jobject, jlong ref,
                                                                        jlong numSegments, jlong segmentFocus) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::energyRatioByChunks(var, static_cast<long>(numSegments),
                                                                static_cast<long>(segmentFocus))
                               .get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_fftAggregated(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::fftAggregated(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_fftCoefficient(JNIEnv *env, jobject, jlong ref, jlong coefficient) {
    const jint l = 5;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer_real = 0;
    af_array af_p_real = (af_array)raw_pointer_real;

    jlong raw_pointer_imag = 0;
    af_array af_p_imag = (af_array)raw_pointer_imag;

    jlong raw_pointer_absolute = 0;
    af_array af_p_absolute = (af_array)raw_pointer_absolute;

    jlong raw_pointer_angle = 0;
    af_array af_p_angle = (af_array)raw_pointer_angle;

    af_retain_array(&arr, var.get());

    af::array primitive_real;
    af::array primitive_imag;
    af::array primitive_absolute;
    af::array primitive_angle;

    khiva::features::fftCoefficient(var, static_cast<long>(coefficient), primitive_real, primitive_imag,
                                    primitive_absolute, primitive_angle);

    af_retain_array(&af_p_real, primitive_real.get());
    af_retain_array(&af_p_imag, primitive_imag.get());
    af_retain_array(&af_p_absolute, primitive_absolute.get());
    af_retain_array(&af_p_angle, primitive_angle.get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p_real;
    tmp[2] = (jlong)af_p_imag;
    tmp[3] = (jlong)af_p_absolute;
    tmp[4] = (jlong)af_p_angle;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_firstLocationOfMaximum(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::firstLocationOfMaximum(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_firstLocationOfMinimum(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::firstLocationOfMinimum(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_friedrichCoefficients(JNIEnv *env, jobject, jlong ref, jint m,
                                                                          jfloat r) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::friedrichCoefficients(var, m, r).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_hasDuplicates(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::hasDuplicates(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_hasDuplicateMax(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::hasDuplicateMax(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_hasDuplicateMin(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::hasDuplicateMin(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_indexMassQuantile(JNIEnv *env, jobject, jlong ref, jfloat q) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::indexMassQuantile(var, q).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_kurtosis(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::kurtosis(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_largeStandardDeviation(JNIEnv *env, jobject, jlong ref, jfloat r) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::largeStandardDeviation(var, r).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_lastLocationOfMaximum(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::lastLocationOfMaximum(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_lastLocationOfMinimum(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::lastLocationOfMinimum(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_length(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::length(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_linearTrend(JNIEnv *env, jobject, jlong ref) {
    const jint l = 6;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer_pvalue = 0;
    af_array af_p_pvalue = (af_array)raw_pointer_pvalue;

    jlong raw_pointer_rvalue = 0;
    af_array af_p_rvalue = (af_array)raw_pointer_rvalue;

    jlong raw_pointer_intercept = 0;
    af_array af_p_intercept = (af_array)raw_pointer_intercept;

    jlong raw_pointer_slope = 0;
    af_array af_p_slope = (af_array)raw_pointer_slope;

    jlong raw_pointer_stderr = 0;
    af_array af_p_stderr = (af_array)raw_pointer_stderr;

    af_retain_array(&arr, var.get());

    af::array primitive_pvalue;
    af::array primitive_rvalue;
    af::array primitive_intercept;
    af::array primitive_slope;
    af::array primitive_stderr;

    khiva::features::linearTrend(var, primitive_pvalue, primitive_rvalue, primitive_intercept, primitive_slope,
                                 primitive_stderr);

    af_retain_array(&af_p_pvalue, primitive_pvalue.get());
    af_retain_array(&af_p_rvalue, primitive_rvalue.get());
    af_retain_array(&af_p_intercept, primitive_intercept.get());
    af_retain_array(&af_p_slope, primitive_slope.get());
    af_retain_array(&af_p_stderr, primitive_stderr.get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p_pvalue;
    tmp[2] = (jlong)af_p_rvalue;
    tmp[3] = (jlong)af_p_intercept;
    tmp[4] = (jlong)af_p_slope;
    tmp[5] = (jlong)af_p_stderr;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_localMaximals(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::localMaximals(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_longestStrikeAboveMean(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::longestStrikeAboveMean(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_longestStrikeBelowMean(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::longestStrikeBelowMean(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_maxLangevinFixedPoint(JNIEnv *env, jobject, jlong ref, jint m,
                                                                          jfloat r) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::maxLangevinFixedPoint(var, m, r).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_maximum(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::maximum(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_mean(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::mean(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_meanAbsoluteChange(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::meanAbsoluteChange(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_meanChange(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::meanChange(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_meanSecondDerivativeCentral(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::meanSecondDerivativeCentral(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_median(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::median(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_minimum(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::minimum(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_numberCrossingM(JNIEnv *env, jobject, jlong ref, jint m) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::numberCrossingM(var, m).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_numberCwtPeaks(JNIEnv *env, jobject, jlong ref, jint maxW) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::numberCwtPeaks(var, maxW).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_numberPeaks(JNIEnv *env, jobject, jlong ref, jint n) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::numberPeaks(var, n).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_partialAutocorrelation(JNIEnv *env, jobject, jlong ref,
                                                                           jlong lags) {
    const jint l = 3;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var;
    af_array arr_lags = (af_array)lags;
    af::array var_lags;

    check_and_retain_arrays(arr, arr_lags, var, var_lags);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&af_p, khiva::features::partialAutocorrelation(var, var_lags).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)arr_lags;
    tmp[2] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_percentageOfReoccurringDatapointsToAllDatapoints(
    JNIEnv *env, jobject, jlong ref, jboolean isSorted) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::percentageOfReoccurringDatapointsToAllDatapoints(var, isSorted).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_percentageOfReoccurringValuesToAllValues(JNIEnv *env, jobject,
                                                                                             jlong ref,
                                                                                             jboolean isSorted) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::percentageOfReoccurringValuesToAllValues(var, isSorted).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_quantile(JNIEnv *env, jobject, jlong ref, jlong q,
                                                             jfloat precision) {
    const jint l = 3;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var;
    af_array arr_q = (af_array)q;
    af::array var_q;

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    check_and_retain_arrays(arr, arr_q, var, var_q);

    af_retain_array(&af_p, khiva::features::quantile(var, var_q, precision).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)arr_q;
    tmp[2] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_rangeCount(JNIEnv *env, jobject, jlong ref, jfloat min,
                                                               jfloat max) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::rangeCount(var, min, max).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_ratioBeyondRSigma(JNIEnv *env, jobject, jlong ref, jfloat r) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::ratioBeyondRSigma(var, r).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_ratioValueNumberToTimeSeriesLength(JNIEnv *env, jobject,
                                                                                       jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::ratioValueNumberToTimeSeriesLength(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_sampleEntropy(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::sampleEntropy(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_skewness(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::skewness(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_spktWelchDensity(JNIEnv *env, jobject, jlong ref, jint coeff) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::spktWelchDensity(var, coeff).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_standardDeviation(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::standardDeviation(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_sumOfReoccurringDatapoints(JNIEnv *env, jobject, jlong ref,
                                                                               jboolean isSorted) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::sumOfReoccurringDatapoints(var, isSorted).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_sumOfReoccurringValues(JNIEnv *env, jobject, jlong ref,
                                                                           jboolean isSorted) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::sumOfReoccurringValues(var, isSorted).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_sumValues(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::sumValues(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_symmetryLooking(JNIEnv *env, jobject, jlong ref, jfloat r) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::symmetryLooking(var, r).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_timeReversalAsymmetryStatistic(JNIEnv *env, jobject, jlong ref,
                                                                                   jint lag) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::timeReversalAsymmetryStatistic(var, lag).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_valueCount(JNIEnv *env, jobject, jlong ref, jfloat v) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::valueCount(var, v).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_variance(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::variance(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Features_varianceLargerThanStandardDeviation(JNIEnv *env, jobject,
                                                                                        jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::features::varianceLargerThanStandardDeviation(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}
