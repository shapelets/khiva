// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/array.h>
#include <khiva_jni/array.h>

#include <array>
#include <cstring>

#define CREATE_T_ARRAY(Ty, ty, dty)                                                                           \
    jlong JNICALL Java_io_shapelets_khiva_Array_createArrayFrom##Ty(JNIEnv *env, jobject, j##ty##Array elems, \
                                                                    jlongArray dims) {                        \
        auto dimptr = env->GetLongArrayElements(dims, 0);                                                     \
        auto inptr = static_cast<void *>(env->Get##Ty##ArrayElements(elems, 0));                              \
        auto dims4 = af::dim4(dimptr[0], dimptr[1], dimptr[2], dimptr[3]);                                    \
        auto localArray = khiva::array::createArray(inptr, khiva::KHIVA_MAX_DIMS, dims4.get(), dty);          \
        auto arr = new af::array(localArray);                                                                 \
        env->ReleaseLongArrayElements(dims, dimptr, 0);                                                       \
        env->Release##Ty##ArrayElements(elems, static_cast<j##ty *>(inptr), 0);                               \
        return reinterpret_cast<jlong>(arr);                                                                  \
    }

CREATE_T_ARRAY(Float, float, khiva::dtype::f32)

CREATE_T_ARRAY(Double, double, khiva::dtype::f64)

CREATE_T_ARRAY(Int, int, khiva::dtype::s32)

CREATE_T_ARRAY(Boolean, boolean, khiva::dtype::b8)

CREATE_T_ARRAY(Long, long, khiva::dtype::s64)

CREATE_T_ARRAY(Short, short, khiva::dtype::s16)

CREATE_T_ARRAY(Byte, byte, khiva::dtype::u8)

#undef CREATE_T_ARRAY

jlong JNICALL Java_io_shapelets_khiva_Array_createArrayFromFloatComplex(JNIEnv *env, jclass, jobjectArray objs,
                                                                        jlongArray dims) {
    try {
        auto dimPtr = env->GetLongArrayElements(dims, nullptr);
        auto len = env->GetArrayLength(objs);
        static jclass cls;
        static jfieldID re, im;
        static bool isFirst = true;

        if (isFirst) {
            cls = env->FindClass("io/shapelets/khiva/FloatComplex");
            re = env->GetFieldID(cls, "real", "F");
            im = env->GetFieldID(cls, "imag", "F");
            isFirst = false;
        }

        std::vector<af::af_cfloat> tmp;
        tmp.reserve(len);

        for (int i = 0; i < len; ++i) {
            jobject obj = env->GetObjectArrayElement(objs, i);
            jfloat real = env->GetFloatField(obj, re);
            jfloat imag = env->GetFloatField(obj, im);
            tmp.emplace_back(real, imag);
        }

        auto dims4 = af::dim4(dimPtr[0], dimPtr[1], dimPtr[2], dimPtr[3]);
        auto result = new af::array(dims4, tmp.data());
        
        env->ReleaseLongArrayElements(dims, dimPtr, 0);
        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in createArrayFromFloatComplex. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_createArrayFromDoubleComplex(JNIEnv *env, jclass, jobjectArray objs,
                                                                         jlongArray dims) {
    try {
        auto dimPtr = env->GetLongArrayElements(dims, nullptr);
        auto len = env->GetArrayLength(objs);

        static jclass cls;
        static jfieldID re, im;
        static bool isFirst = true;

        if (isFirst) {
            cls = env->FindClass("io/shapelets/khiva/DoubleComplex");
            re = env->GetFieldID(cls, "real", "D");
            im = env->GetFieldID(cls, "imag", "D");
            isFirst = false;
        }

        std::vector<af::af_cdouble> tmp;
        tmp.reserve(len);

        for (int i = 0; i < len; i++) {
            jobject obj = env->GetObjectArrayElement(objs, i);
            jdouble real = env->GetDoubleField(obj, re);
            jdouble imag = env->GetDoubleField(obj, im);
            tmp.emplace_back(real, imag);
        }

        auto dims4 = af::dim4(dimPtr[0], dimPtr[1], dimPtr[2], dimPtr[3]);
        auto result = new af::array(dims4, tmp.data());

        env->ReleaseLongArrayElements(dims, dimPtr, 0);
        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in createArrayFromDoubleComplex. Unknown reason");
    }
    return 0;
}

void JNICALL Java_io_shapelets_khiva_Array_deleteArray(JNIEnv *env, jobject thisObj) {
    try {
        // Get the Arrayfire pointer
        auto clazz = env->GetObjectClass(thisObj);
        auto fieldId = env->GetFieldID(clazz, "reference", "J");
        auto ref = env->GetLongField(thisObj, fieldId);
        auto arrayPtr = reinterpret_cast<af::array*>(ref);
        delete arrayPtr;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in deleteArray. Unknown reason");
    }
}

#define GET_T_FROM_ARRAY(Ty, ty)                                                                          \
    j##ty##Array JNICALL Java_io_shapelets_khiva_Array_get##Ty##FromArray(JNIEnv *env, jobject thisObj) { \
        auto clazz = env->GetObjectClass(thisObj);                                                        \
        auto fidf = env->GetFieldID(clazz, "reference", "J");                                             \
        auto ref = env->GetLongField(thisObj, fidf);                                                      \
        auto a = *reinterpret_cast<af::array*>(ref);                                                      \
        auto elements = a.elements();                                                                     \
        auto result = env->New##Ty##Array(static_cast<jsize>(elements));                                  \
        auto resf = env->Get##Ty##ArrayElements(result, 0);                                              \
        a.host(resf);                                                                                     \
        env->Release##Ty##ArrayElements(result, resf, 0);                                                 \
        return result;                                                                                    \
    }

GET_T_FROM_ARRAY(Float, float)

GET_T_FROM_ARRAY(Double, double)

GET_T_FROM_ARRAY(Int, int)

GET_T_FROM_ARRAY(Boolean, boolean)

GET_T_FROM_ARRAY(Long, long)

GET_T_FROM_ARRAY(Short, short)

GET_T_FROM_ARRAY(Byte, byte)

#undef GET_T_FROM_ARRAY

jobjectArray JNICALL Java_io_shapelets_khiva_Array_getDoubleComplexFromArray(JNIEnv *env, jobject thisObj) {
    try {
        // Check Output class is available
        auto cls = env->FindClass("io/shapelets/khiva/DoubleComplex");
        auto id = env->GetMethodID(cls, "<init>", "(DD)V");
        if (id == nullptr) return nullptr;

        // Get the Arrayfire pointer
        auto clazz = env->GetObjectClass(thisObj);
        auto fieldId = env->GetFieldID(clazz, "reference", "J");
        auto ref = env->GetLongField(thisObj, fieldId);
        auto arr = *reinterpret_cast<af::array*>(ref);

        // Extract the elements from the af::array
        auto elements = arr.elements();
        std::vector<af::af_cdouble> tmp(elements);
        arr.host(tmp.data());
        
        // Build the Java array
        auto objectArray = env->NewObjectArray(static_cast<jsize>(elements), cls, nullptr);
        jsize i = 0;
        for (const auto &elem : tmp) {
            auto obj = env->NewObject(cls, id, elem.real, elem.imag);
            env->SetObjectArrayElement(objectArray, i++, obj);
        }
        return objectArray;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in getDoubleComplexFromArray. Unknown reason");
    }
    return nullptr;
}

jobjectArray JNICALL Java_io_shapelets_khiva_Array_getFloatComplexFromArray(JNIEnv *env, jobject thisObj) {
    try {
        // Check Output class is available
        jclass cls = env->FindClass("io/shapelets/khiva/FloatComplex");
        jmethodID id = env->GetMethodID(cls, "<init>", "(FF)V");
        if (id == nullptr) return nullptr;

        // Get the Arrayfire pointer
        auto clazz = env->GetObjectClass(thisObj);
        auto fieldId = env->GetFieldID(clazz, "reference", "J");
        auto ref = env->GetLongField(thisObj, fieldId);
        auto arr = *reinterpret_cast<af::array *>(ref);

        auto elements = arr.elements();
        std::vector<af::af_cfloat> tmp(elements);
        arr.host(tmp.data());
        
        // Build the Java array
        auto objectArray = env->NewObjectArray(static_cast<jsize>(elements), cls, nullptr);
        jsize i = 0;
        for (const auto &elem : tmp) {
            auto obj = env->NewObject(cls, id, elem.real, elem.imag);
            env->SetObjectArrayElement(objectArray, i++, obj);
        }
        return objectArray;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in getFloatComplexFromArray. Unknown reason");
    }
    return nullptr;
}

jlongArray JNICALL Java_io_shapelets_khiva_Array_nativeGetDims(JNIEnv *env, jobject thisObj) {
    try {
        // Get the Arrayfire pointer
        auto clazz = env->GetObjectClass(thisObj);
        auto fieldId = env->GetFieldID(clazz, "reference", "J");
        auto ref = env->GetLongField(thisObj, fieldId);
        auto arr = *reinterpret_cast<af::array*>(ref);
        
        // Extract the dims from the af::array
        auto dims = arr.dims();        
        std::array<jlong, khiva::KHIVA_MAX_DIMS> result{};
        std::copy(dims.get(), dims.get() + khiva::KHIVA_MAX_DIMS, result.begin());
        auto javaArrayPtr = env->NewLongArray(khiva::KHIVA_MAX_DIMS);

        env->SetLongArrayRegion(javaArrayPtr, 0, khiva::KHIVA_MAX_DIMS, result.data());
        return javaArrayPtr;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in nativeGetDims. Unknown reason");
    }
    return nullptr;
}

jint JNICALL Java_io_shapelets_khiva_Array_nativeGetType(JNIEnv *env, jobject thisObj) {
    try {
        // Get the Arrayfire pointer
        auto clazz = env->GetObjectClass(thisObj);
        auto fieldId = env->GetFieldID(clazz, "reference", "J");
        auto ref = env->GetLongField(thisObj, fieldId);
        auto arr = *reinterpret_cast<af::array*>(ref);
        return arr.type();
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in nativeGetType. Unknown reason");
    }
    return 0L;
}

void JNICALL Java_io_shapelets_khiva_Array_nativePrint(JNIEnv *env, jobject thisObj) {
    try {
        auto clazz = env->GetObjectClass(thisObj);
        auto fieldId = env->GetFieldID(clazz, "reference", "J");
        auto ref = env->GetLongField(thisObj, fieldId);
        auto arr = *reinterpret_cast<af::array*>(ref);
        khiva::array::print(arr);        
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in nativePrint. Unknown reason");
    }
}

jlong JNICALL Java_io_shapelets_khiva_Array_join(JNIEnv *env, jobject thisObj, jint dim, jlong ref_rhs) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto lhs = *reinterpret_cast<af::array*>(ref);        
        auto rhs = *reinterpret_cast<af::array*>(ref_rhs);

        af::array c = khiva::array::join(dim, lhs, rhs);        
        auto result = new af::array(c);
        
        return reinterpret_cast<jlong>(result);        
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_join. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_add(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array*>(ref);
        auto b = *reinterpret_cast<af::array*>(ref_rhs);
        
        af::array c = a + b;
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_add. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_mul(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array*>(ref);
        auto b = *reinterpret_cast<af::array*>(ref_rhs);
                
        af::array c = a * b;
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_mul. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_sub(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);
        auto b = *reinterpret_cast<af::array *>(ref_rhs);

        af::array c = a - b;
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_sub. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_div(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);
        auto b = *reinterpret_cast<af::array *>(ref_rhs);
                
        af::array c = a / b;
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_div. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_mod(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);
        auto b = *reinterpret_cast<af::array *>(ref_rhs);

        af::array c = a % b;
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_mod. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_pow(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);
        auto b = *reinterpret_cast<af::array *>(ref_rhs);

        af::array c = af::pow(a, b);
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_pow. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_lt(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);
        auto b = *reinterpret_cast<af::array *>(ref_rhs);

        af::array c = a < b;
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_lt. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_gt(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);
        auto b = *reinterpret_cast<af::array *>(ref_rhs);

        af::array c = a > b;
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_gt. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_le(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);
        auto b = *reinterpret_cast<af::array *>(ref_rhs);

        af::array c = a <= b;
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_le. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_ge(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);
        auto b = *reinterpret_cast<af::array *>(ref_rhs);

        af::array c = a >= b;
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_ge. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_eq(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);
        auto b = *reinterpret_cast<af::array *>(ref_rhs);
        
        af::array c = a == b;
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_eq. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_ne(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);
        auto b = *reinterpret_cast<af::array *>(ref_rhs);

        af::array c = a != b;
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_ne. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_bitAnd(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);
        auto b = *reinterpret_cast<af::array *>(ref_rhs);

        af::array c = a & b;
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_bitAnd. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_bitOr(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);
        auto b = *reinterpret_cast<af::array *>(ref_rhs);

        af::array c = a | b;
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_bitOr. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_bitXor(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);
        auto b = *reinterpret_cast<af::array *>(ref_rhs);

        af::array c = (!a) != !b;
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_bitXor. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_nativeBitShiftL(JNIEnv *env, jobject thisObj, jint n) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array*>(ref);

        af::array c = (a << n).as(a.type());
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_nativeBitShiftL. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_nativeBitShiftR(JNIEnv *env, jobject thisObj, jint n) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);        

        af::array c = (a >> n).as(a.type());
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_nativeBitShiftR. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_nativeNot(JNIEnv *env, jobject thisObj) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);

        af::array c = !a;
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_nativeNot. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_nativeTranspose(JNIEnv *env, jobject thisObj, jboolean conjugate) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);

        af::array c = af::transpose(a, conjugate);
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_nativeBTranspose. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_nativeCol(JNIEnv *env, jobject thisObj, jint index) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);

        af::array c = a.col(index);
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_nativeCol. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_nativeCols(JNIEnv *env, jobject thisObj, jint first, jint last) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);

        af::array c = a.cols(first, last);
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_nativeCols. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_nativeRow(JNIEnv *env, jobject thisObj, jint index) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);

        af::array c = a.row(index);
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_nativeRow. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_nativeRows(JNIEnv *env, jobject thisObj, jint first, jint last) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);

        af::array c = a.rows(first, last);
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_nativeRows. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_matmul(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);
        auto b = *reinterpret_cast<af::array *>(ref_rhs);

        af::array c = af::matmul(a, b);
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_matmul. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_nativeCopy(JNIEnv *env, jobject thisObj) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);

        af::array c = a.copy();
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_nativeCopy. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Array_as(JNIEnv *env, jobject thisObj, jint type) {
    try {
        jclass clazz = env->GetObjectClass(thisObj);
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
        jlong ref = env->GetLongField(thisObj, fidf);

        auto a = *reinterpret_cast<af::array *>(ref);

        auto dt = static_cast<khiva::dtype>(type);
        af::array c = a.as(dt);
        auto result = new af::array(c);

        return reinterpret_cast<jlong>(result);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Array_nativeArrayAs. Unknown reason");
    }
    return 0;
}
