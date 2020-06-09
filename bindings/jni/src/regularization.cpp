// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/regularization.h>
#include <khiva_jni/regularization.h>

jlong JNICALL Java_io_shapelets_khiva_Regularization_groupBy(JNIEnv *env, jobject, jlong ref,
                                                                  jint aggregationFunction, jint nColumnsKey,
                                                                  jint nColumnsValue) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);

        af::array result;
        switch (aggregationFunction) {
            case 0:
                result = khiva::regularization::groupBy(arr, af::mean, nColumnsKey, nColumnsValue);
                break;
            case 1:
                result = khiva::regularization::groupBy(arr, af::median, nColumnsKey, nColumnsValue);
                break;
            case 2:
                result = khiva::regularization::groupBy(arr, af::min, nColumnsKey, nColumnsValue);
                break;
            case 3:
                result = khiva::regularization::groupBy(arr, af::max, nColumnsKey, nColumnsValue);
                break;
            case 4:
                result = khiva::regularization::groupBy(arr, af::stdev, nColumnsKey, nColumnsValue);
                break;
            default:
                result = khiva::regularization::groupBy(arr, af::mean, nColumnsKey, nColumnsValue);
                break;
        }
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Features_aggregatedLinearTrend. Unknown reason");
    }
    return 0;
}
