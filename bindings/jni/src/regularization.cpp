// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/regularization.h>
#include <khiva_jni/regularization.h>

jlongArray JNICALL Java_io_shapelets_khiva_Regularization_groupBy(JNIEnv *env, jobject, jlong ref,
                                                                  jint aggregationFunction, jint nColumnsKey,
                                                                  jint nColumnsValue) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        auto af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        switch (aggregationFunction) {
            case 0:
                af_retain_array(&af_p, khiva::regularization::groupBy(var, af::mean, nColumnsKey, nColumnsValue).get());
                break;
            case 1:
                af_retain_array(&af_p,
                                khiva::regularization::groupBy(var, af::median, nColumnsKey, nColumnsValue).get());
                break;
            case 2:
                af_retain_array(&af_p, khiva::regularization::groupBy(var, af::min, nColumnsKey, nColumnsValue).get());
                break;
            case 3:
                af_retain_array(&af_p, khiva::regularization::groupBy(var, af::max, nColumnsKey, nColumnsValue).get());
                break;
            case 4:
                af_retain_array(&af_p,
                                khiva::regularization::groupBy(var, af::stdev, nColumnsKey, nColumnsValue).get());
                break;
            case 5:
                af_retain_array(&af_p, khiva::regularization::groupBy(var, af::var, nColumnsKey, nColumnsValue).get());
                break;
            default:
                af_retain_array(&af_p, khiva::regularization::groupBy(var, af::mean, nColumnsKey, nColumnsValue).get());
                break;
        }
        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Regularization_groupBy. Unknown reason");
    }
    return nullptr;
}
