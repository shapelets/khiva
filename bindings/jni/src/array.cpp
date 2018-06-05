// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/array.h>
#include <tsa_jni/array.h>
#include <cstring>

#ifdef __cplusplus
extern "C" {
#endif

#define CREATE_T_ARRAY(Ty, ty, dty)                                                                                   \
    JNIEXPORT jlong JNICALL Java_com_gcatsoft_tsa_Array_createArrayFrom##Ty(JNIEnv *env, jobject, j##ty##Array elems, \
                                                                            jlongArray dims) {                        \
        af_array ret = 0;                                                                                             \
        jlong *dimptr = env->GetLongArrayElements(dims, 0);                                                           \
        dim_t tdims[4] = {dimptr[0], dimptr[1], dimptr[2], dimptr[3]};                                                \
        void *inptr = (void *)env->Get##Ty##ArrayElements(elems, 0);                                                  \
        af_retain_array(&ret, tsa::array::createArray(inptr, 4, tdims, dty).get());                                   \
        env->ReleaseLongArrayElements(dims, dimptr, 0);                                                               \
        env->Release##Ty##ArrayElements(elems, (j##ty *)inptr, 0);                                                    \
        return jlong(ret);                                                                                            \
    }
CREATE_T_ARRAY(Float, float, tsa::dtype::f32)
CREATE_T_ARRAY(Double, double, tsa::dtype::f64)
CREATE_T_ARRAY(Int, int, tsa::dtype::s32)
CREATE_T_ARRAY(Boolean, boolean, tsa::dtype::b8)
CREATE_T_ARRAY(Long, long, tsa::dtype::s64)
CREATE_T_ARRAY(Short, short, tsa::dtype::s16)
CREATE_T_ARRAY(Byte, byte, tsa::dtype::u8)

#undef CREATE_T_ARRAY

JNIEXPORT jlong JNICALL Java_com_gcatsoft_tsa_Array_createArrayFromFloatComplex(JNIEnv *env, jclass, jobjectArray objs,
                                                                                jlongArray dims) {
    af_array ret = 0;
    jlong *dimptr = env->GetLongArrayElements(dims, 0);
    jint len = env->GetArrayLength(objs);

    static jclass cls;
    static jfieldID re, im;
    static bool isfirst = true;

    if (isfirst) {
        cls = env->FindClass("com/gcatsoft/tsa/FloatComplex");
        re = env->GetFieldID(cls, "real", "F");
        im = env->GetFieldID(cls, "imag", "F");
        isfirst = false;
    }

    af::af_cfloat *tmp = (af::af_cfloat *)malloc(len * sizeof(af::af_cfloat));

    for (int i = 0; i < len; i++) {
        jobject obj = env->GetObjectArrayElement(objs, i);
        jfloat real = env->GetFloatField(obj, re);
        jfloat imag = env->GetFloatField(obj, im);

        tmp[i].real = real;
        tmp[i].imag = imag;
    }

    dim_t tdims[4] = {dimptr[0], dimptr[1], dimptr[2], dimptr[3]};
    af_retain_array(&ret, tsa::array::createArray(af_array(tmp), 4, tdims, tsa::dtype::c32).get());

    delete[] tmp;
    env->ReleaseLongArrayElements(dims, dimptr, 0);
    return jlong(ret);
}

JNIEXPORT jlong JNICALL Java_com_gcatsoft_tsa_Array_createArrayFromDoubleComplex(JNIEnv *env, jclass, jobjectArray objs,
                                                                                 jlongArray dims) {
    af_array ret = 0;
    jlong *dimptr = env->GetLongArrayElements(dims, 0);
    jint len = env->GetArrayLength(objs);

    static jclass cls;
    static jfieldID re, im;
    static bool isfirst = true;

    if (isfirst) {
        cls = env->FindClass("com/gcatsoft/tsa/DoubleComplex");
        re = env->GetFieldID(cls, "real", "D");
        im = env->GetFieldID(cls, "imag", "D");
        isfirst = false;
    }

    af::af_cdouble *tmp = (af::af_cdouble *)malloc(len * sizeof(af::af_cdouble));

    for (int i = 0; i < len; i++) {
        jobject obj = env->GetObjectArrayElement(objs, i);
        jdouble real = env->GetDoubleField(obj, re);
        jdouble imag = env->GetDoubleField(obj, im);

        tmp[i].real = real;
        tmp[i].imag = imag;
    }

    dim_t tdims[4] = {dimptr[0], dimptr[1], dimptr[2], dimptr[3]};
    af_retain_array(&ret, tsa::array::createArray(af_array(tmp), 4, tdims, tsa::dtype::c64).get());

    delete[] tmp;
    env->ReleaseLongArrayElements(dims, dimptr, 0);
    return jlong(ret);
}

#define GET_T_FROM_ARRAY(Ty, ty)                                                                                  \
    JNIEXPORT j##ty##Array JNICALL Java_com_gcatsoft_tsa_Array_get##Ty##FromArray(JNIEnv *env, jobject thisObj) { \
        jclass clazz = env->GetObjectClass(thisObj);                                                              \
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");                                                 \
        jlong ref = env->GetLongField(thisObj, fidf);                                                             \
        j##ty##Array result;                                                                                      \
        dim_t elements = 0;                                                                                       \
        af_get_elements(&elements, (void *)ref);                                                                  \
        result = env->New##Ty##Array(static_cast<jsize>(elements));                                               \
        j##ty *resf = env->Get##Ty##ArrayElements(result, 0);                                                     \
        af_array a = (af_array)ref;                                                                               \
        af::array var = af::array(a);                                                                             \
        tsa::array::getData(var, resf);                                                                           \
        af_retain_array(&a, var.get());                                                                           \
        env->SetLongField(thisObj, fidf, jlong(a));                                                               \
        env->Release##Ty##ArrayElements(result, resf, 0);                                                         \
        return result;                                                                                            \
    }
GET_T_FROM_ARRAY(Float, float)
GET_T_FROM_ARRAY(Double, double)
GET_T_FROM_ARRAY(Int, int)
GET_T_FROM_ARRAY(Boolean, boolean)
GET_T_FROM_ARRAY(Long, long)
GET_T_FROM_ARRAY(Short, short)
GET_T_FROM_ARRAY(Byte, byte)
#undef GET_T_FROM_ARRAY

JNIEXPORT jobjectArray JNICALL Java_com_gcatsoft_tsa_Array_getDoubleComplexFromArray(JNIEnv *env, jobject thisObj) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    jobjectArray result;
    dim_t elements = 0;
    (af_get_elements(&elements, (void *)(ref)));

    jclass cls = env->FindClass("com/gcatsoft/tsa/DoubleComplex");
    jmethodID id = env->GetMethodID(cls, "<init>", "(DD)V");
    if (id == NULL) return NULL;

    result = env->NewObjectArray(static_cast<jsize>(elements), cls, NULL);

    af::af_cdouble *tmp = (af::af_cdouble *)malloc(sizeof(af::af_cdouble) * elements);
    af_array a = (af_array)ref;
    af::array var = af::array(a);
    tsa::array::getData(var, tmp);
    af_retain_array(&a, var.get());
    env->SetLongField(thisObj, fidf, jlong(a));

    for (int i = 0; i < elements; i++) {
        double re = tmp[i].real;
        double im = tmp[i].imag;
        jobject obj = env->NewObject(cls, id, re, im);
        env->SetObjectArrayElement(result, i, obj);
    }

    delete[] tmp;
    return result;
}

JNIEXPORT jobjectArray JNICALL Java_com_gcatsoft_tsa_Array_getFloatComplexFromArray(JNIEnv *env, jobject thisObj) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    jobjectArray result;
    dim_t elements = 0;
    (af_get_elements(&elements, (void *)(ref)));

    jclass cls = env->FindClass("com/gcatsoft/tsa/FloatComplex");
    jmethodID id = env->GetMethodID(cls, "<init>", "(FF)V");
    if (id == NULL) return NULL;

    result = env->NewObjectArray(static_cast<jsize>(elements), cls, NULL);

    af::af_cfloat *tmp = (af::af_cfloat *)malloc(sizeof(af::af_cfloat) * elements);
    af_array a = (af_array)ref;
    af::array var = af::array(a);
    tsa::array::getData(var, tmp);
    af_retain_array(&a, var.get());
    env->SetLongField(thisObj, fidf, jlong(a));

    for (int i = 0; i < elements; i++) {
        float re = tmp[i].real;
        float im = tmp[i].imag;
        jobject obj = env->NewObject(cls, id, re, im);
        env->SetObjectArrayElement(result, i, obj);
    }

    delete[] tmp;
    return result;
}

JNIEXPORT jint JNICALL Java_com_gcatsoft_tsa_Array_nativeGetType(JNIEnv *env, jobject thisObj) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array a = (af_array)ref;
    af::array var = af::array(a);
    jint t = tsa::array::getType(var);
    af_retain_array(&a, var.get());
    env->SetLongField(thisObj, fidf, jlong(a));
    return t;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Array_nativeGetDims(JNIEnv *env, jobject thisObj) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array a = (af_array)ref;
    af::array var = af::array(a);
    af::dim4 d = tsa::array::getDims(var);
    jlong result[4];
    jlongArray p = env->NewLongArray(4);

    memcpy(result, d.dims, sizeof(d.dims));

    af_retain_array(&a, var.get());
    env->SetLongField(thisObj, fidf, jlong(a));
    env->SetLongArrayRegion(p, 0, 4, &result[0]);

    return p;
}

JNIEXPORT void JNICALL Java_com_gcatsoft_tsa_Array_nativePrint(JNIEnv *env, jobject thisObj) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array a = (af_array)ref;
    af::array var = af::array(a);
    tsa::array::print(var);
    af_retain_array(&a, var.get());
    env->SetLongField(thisObj, fidf, jlong(a));
}

JNIEXPORT void JNICALL Java_com_gcatsoft_tsa_Array_deleteArray(JNIEnv *env, jobject thisObj) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    tsa::array::deleteArray((void *)&ref);
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Array_add(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);
    af_array rhs = (af_array)ref_rhs;
    af::array b = af::array(rhs);

    af::array c = a + b;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&rhs, b.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    jlong result[] = {(jlong)rhs, (jlong)af_p};
    jlongArray p = env->NewLongArray(2);
    env->SetLongArrayRegion(p, 0, 2, &result[0]);

    return p;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Array_mul(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);
    af_array rhs = (af_array)ref_rhs;
    af::array b = af::array(rhs);

    af::array c = a * b;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&rhs, b.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    jlong result[] = {(jlong)rhs, (jlong)af_p};
    jlongArray p = env->NewLongArray(2);
    env->SetLongArrayRegion(p, 0, 2, &result[0]);

    return p;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Array_sub(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);
    af_array rhs = (af_array)ref_rhs;
    af::array b = af::array(rhs);

    af::array c = a - b;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&rhs, b.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    jlong result[] = {(jlong)rhs, (jlong)af_p};
    jlongArray p = env->NewLongArray(2);
    env->SetLongArrayRegion(p, 0, 2, &result[0]);

    return p;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Array_div(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);
    af_array rhs = (af_array)ref_rhs;
    af::array b = af::array(rhs);

    af::array c = a / b;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&rhs, b.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    jlong result[] = {(jlong)rhs, (jlong)af_p};
    jlongArray p = env->NewLongArray(2);
    env->SetLongArrayRegion(p, 0, 2, &result[0]);

    return p;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Array_mod(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);
    af_array rhs = (af_array)ref_rhs;
    af::array b = af::array(rhs);

    af::array c = a % b;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&rhs, b.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    jlong result[] = {(jlong)rhs, (jlong)af_p};
    jlongArray p = env->NewLongArray(2);
    env->SetLongArrayRegion(p, 0, 2, &result[0]);

    return p;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Array_pow(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);
    af_array rhs = (af_array)ref_rhs;
    af::array b = af::array(rhs);

    af::array c = af::pow(a, b);
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&rhs, b.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    jlong result[] = {(jlong)rhs, (jlong)af_p};
    jlongArray p = env->NewLongArray(2);
    env->SetLongArrayRegion(p, 0, 2, &result[0]);

    return p;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Array_lt(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);
    af_array rhs = (af_array)ref_rhs;
    af::array b = af::array(rhs);

    af::array c = a < b;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&rhs, b.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    jlong result[] = {(jlong)rhs, (jlong)af_p};
    jlongArray p = env->NewLongArray(2);
    env->SetLongArrayRegion(p, 0, 2, &result[0]);

    return p;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Array_gt(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);
    af_array rhs = (af_array)ref_rhs;
    af::array b = af::array(rhs);

    af::array c = a > b;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&rhs, b.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    jlong result[] = {(jlong)rhs, (jlong)af_p};
    jlongArray p = env->NewLongArray(2);
    env->SetLongArrayRegion(p, 0, 2, &result[0]);

    return p;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Array_le(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);
    af_array rhs = (af_array)ref_rhs;
    af::array b = af::array(rhs);

    af::array c = a <= b;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&rhs, b.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    jlong result[] = {(jlong)rhs, (jlong)af_p};
    jlongArray p = env->NewLongArray(2);
    env->SetLongArrayRegion(p, 0, 2, &result[0]);

    return p;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Array_ge(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);
    af_array rhs = (af_array)ref_rhs;
    af::array b = af::array(rhs);

    af::array c = a >= b;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&rhs, b.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    jlong result[] = {(jlong)rhs, (jlong)af_p};
    jlongArray p = env->NewLongArray(2);
    env->SetLongArrayRegion(p, 0, 2, &result[0]);

    return p;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Array_eq(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);
    af_array rhs = (af_array)ref_rhs;
    af::array b = af::array(rhs);

    af::array c = a == b;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&rhs, b.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    jlong result[] = {(jlong)rhs, (jlong)af_p};
    jlongArray p = env->NewLongArray(2);
    env->SetLongArrayRegion(p, 0, 2, &result[0]);

    return p;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Array_ne(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);
    af_array rhs = (af_array)ref_rhs;
    af::array b = af::array(rhs);

    af::array c = a != b;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&rhs, b.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    jlong result[] = {(jlong)rhs, (jlong)af_p};
    jlongArray p = env->NewLongArray(2);
    env->SetLongArrayRegion(p, 0, 2, &result[0]);

    return p;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Array_bitAnd(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);
    af_array rhs = (af_array)ref_rhs;
    af::array b = af::array(rhs);

    af::array c = a & b;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&rhs, b.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    jlong result[] = {(jlong)rhs, (jlong)af_p};
    jlongArray p = env->NewLongArray(2);
    env->SetLongArrayRegion(p, 0, 2, &result[0]);

    return p;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Array_bitOr(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);
    af_array rhs = (af_array)ref_rhs;
    af::array b = af::array(rhs);

    af::array c = a | b;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&rhs, b.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    jlong result[] = {(jlong)rhs, (jlong)af_p};
    jlongArray p = env->NewLongArray(2);
    env->SetLongArrayRegion(p, 0, 2, &result[0]);

    return p;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Array_bitXor(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);
    af_array rhs = (af_array)ref_rhs;
    af::array b = af::array(rhs);

    af::array c = !a != !b;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&rhs, b.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    jlong result[] = {(jlong)rhs, (jlong)af_p};
    jlongArray p = env->NewLongArray(2);
    env->SetLongArrayRegion(p, 0, 2, &result[0]);

    return p;
}

JNIEXPORT jlong JNICALL Java_com_gcatsoft_tsa_Array_nativeBitShiftL(JNIEnv *env, jobject thisObj, jint n) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);

    af::array c = a << n;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    return (jlong)af_p;
}

JNIEXPORT jlong JNICALL Java_com_gcatsoft_tsa_Array_nativeBitShiftR(JNIEnv *env, jobject thisObj, jint n) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);

    af::array c = a >> n;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    return (jlong)af_p;
}

JNIEXPORT jlong JNICALL Java_com_gcatsoft_tsa_Array_nativeNot(JNIEnv *env, jobject thisObj) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);

    af::array c = !a;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    return (jlong)af_p;
}

JNIEXPORT jlong JNICALL Java_com_gcatsoft_tsa_Array_nativeTranspose(JNIEnv *env, jobject thisObj, jboolean conjugate) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);

    af::array c = af::transpose(a, conjugate);
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    return (jlong)af_p;
}

JNIEXPORT jlong JNICALL Java_com_gcatsoft_tsa_Array_nativeCol(JNIEnv *env, jobject thisObj, jint index) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);
    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);

    af::array c = a.col(index);
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    return (jlong)af_p;
}

JNIEXPORT jlong JNICALL Java_com_gcatsoft_tsa_Array_nativeCols(JNIEnv *env, jobject thisObj, jint first, jint last) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);

    af::array c = a.cols(first, last);
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    return (jlong)af_p;
}

JNIEXPORT jlong JNICALL Java_com_gcatsoft_tsa_Array_nativeRow(JNIEnv *env, jobject thisObj, jint index) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);

    af::array c = a.row(index);
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    return (jlong)af_p;
}

JNIEXPORT jlong JNICALL Java_com_gcatsoft_tsa_Array_nativeRows(JNIEnv *env, jobject thisObj, jint first, jint last) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);

    af::array c = a.rows(first, last);
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    return (jlong)af_p;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Array_matmul(JNIEnv *env, jobject thisObj, jlong ref_rhs) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);
    af_array rhs = (af_array)ref_rhs;
    af::array b = af::array(rhs);

    af::array c = af::matmul(a, b);
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&rhs, b.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    jlong result[] = {(jlong)rhs, (jlong)af_p};
    jlongArray p = env->NewLongArray(2);
    env->SetLongArrayRegion(p, 0, 2, &result[0]);

    return p;
}

JNIEXPORT jlong JNICALL Java_com_gcatsoft_tsa_Array_nativeCopy(JNIEnv *env, jobject thisObj) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);

    af::array c = a.copy();
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    return (jlong)af_p;
}

JNIEXPORT jlong JNICALL Java_com_gcatsoft_tsa_Array_as(JNIEnv *env, jobject thisObj, jint type) {
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    jlong ref = env->GetLongField(thisObj, fidf);

    af_array lhs = (af_array)ref;
    af::array a = af::array(lhs);

    tsa::dtype dt = static_cast<tsa::dtype>(type);
    af::array c = a.as(dt);
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&lhs, a.get());
    af_retain_array(&af_p, c.get());

    env->SetLongField(thisObj, fidf, jlong(lhs));

    return (jlong)af_p;
}

#ifdef __cplusplus
}
#endif