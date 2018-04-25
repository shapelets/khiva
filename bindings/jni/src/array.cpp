
#include <tsa/array.h>
#include <tsa_jni/array.h>
#ifdef __cplusplus
extern "C" {
#endif

#define CREATE_T_ARRAY(Ty, ty, dty)                                                                              \
    JNIEXPORT jlong JNICALL Java_tsa_Array_createArrayFrom##Ty(JNIEnv *env, jobject thisObj, j##ty##Array elems, \
                                                               jlongArray dims) {                                \
        af_array ret = 0;                                                                                        \
        jlong *dimptr = env->GetLongArrayElements(dims, 0);                                                      \
        dim_t tdims[4] = {dimptr[0], dimptr[1], dimptr[2], dimptr[3]};                                           \
        void *inptr = (void *)env->Get##Ty##ArrayElements(elems, 0);                                             \
        af_retain_array(&ret, tsa::array::createArray(inptr, 4, tdims, dty).get());                              \
        env->ReleaseLongArrayElements(dims, dimptr, 0);                                                          \
        env->Release##Ty##ArrayElements(elems, (j##ty *)inptr, 0);                                               \
        return jlong(ret);                                                                                       \
    }
CREATE_T_ARRAY(Float, float, tsa::dtype::f32)
CREATE_T_ARRAY(Double, double, tsa::dtype::f64)
CREATE_T_ARRAY(Int, int, tsa::dtype::s32)
CREATE_T_ARRAY(Boolean, boolean, tsa::dtype::b8)
CREATE_T_ARRAY(Long, long, tsa::dtype::s64)
CREATE_T_ARRAY(Short, short, tsa::dtype::s16)
CREATE_T_ARRAY(Byte, byte, tsa::dtype::u8)

#undef CREATE_T_ARRAY

JNIEXPORT jlong JNICALL Java_tsa_Array_createArrayFromDoubleComplex(JNIEnv *env, jclass clazz, jobjectArray objs,
                                                                    jlongArray dims) {
    af_array ret = 0;
    jlong *dimptr = env->GetLongArrayElements(dims, 0);
    jint len = env->GetArrayLength(objs);

    static jclass cls;
    static jfieldID re, im;
    static bool isfirst = true;

    if (isfirst) {
        cls = env->FindClass("tsa/DoubleComplex");
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

    free(tmp);
    env->ReleaseLongArrayElements(dims, dimptr, 0);
    return jlong(ret);
}

JNIEXPORT jlong JNICALL Java_tsa_Array_createArrayFromFloatComplex(JNIEnv *env, jclass clazz, jobjectArray objs,
                                                                   jlongArray dims) {
    af_array ret = 0;
    jlong *dimptr = env->GetLongArrayElements(dims, 0);
    jint len = env->GetArrayLength(objs);

    static jclass cls;
    static jfieldID re, im;
    static bool isfirst = true;

    if (isfirst) {
        cls = env->FindClass("tsa/FloatComplex");
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

    free(tmp);
    env->ReleaseLongArrayElements(dims, dimptr, 0);
    return jlong(ret);
}

JNIEXPORT void JNICALL Java_tsa_Array_deleteArray(JNIEnv *env, jobject thisObj, jlong ref) {
    tsa::array::deleteArray((void *)&ref);
}

JNIEXPORT jint JNICALL Java_tsa_Array_getType(JNIEnv *env, jobject thisObj, jlong ref) {
    af_array a = (af_array)ref;
    af::array var = af::array(a);
    jint t = tsa::array::getType(var);
    af_retain_array(&a, var.get());
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    env->SetLongField(thisObj, fidf, jlong(a));
    return t;
}

#define GET_T_FROM_ARRAY(Ty, ty)                                                                                \
    JNIEXPORT j##ty##Array JNICALL Java_tsa_Array_get##Ty##FromArray(JNIEnv *env, jobject thisObj, jlong ref) { \
        j##ty##Array result;                                                                                    \
        dim_t elements = 0;                                                                                     \
        af_get_elements(&elements, (void *)ref);                                                                \
        result = env->New##Ty##Array(elements);                                                                 \
        j##ty *resf = env->Get##Ty##ArrayElements(result, 0);                                                   \
        af_array a = (af_array)ref;                                                                             \
        af::array var = af::array(a);                                                                           \
        tsa::array::getData(var, resf);                                                                         \
        af_retain_array(&a, var.get());                                                                         \
        jclass clazz = env->GetObjectClass(thisObj);                                                            \
        jfieldID fidf = env->GetFieldID(clazz, "reference", "J");                                               \
        env->SetLongField(thisObj, fidf, jlong(a));                                                             \
        env->Release##Ty##ArrayElements(result, resf, 0);                                                       \
        return result;                                                                                          \
    }
GET_T_FROM_ARRAY(Float, float)
GET_T_FROM_ARRAY(Double, double)
GET_T_FROM_ARRAY(Int, int)
GET_T_FROM_ARRAY(Boolean, boolean)
GET_T_FROM_ARRAY(Long, long)
GET_T_FROM_ARRAY(Short, short)
GET_T_FROM_ARRAY(Byte, byte)
#undef GET_T_FROM_ARRAY

JNIEXPORT jobjectArray JNICALL Java_tsa_Array_getDoubleComplexFromArray(JNIEnv *env, jobject thisObj, jlong ref) {
    jobjectArray result;
    dim_t elements = 0;
    (af_get_elements(&elements, (void *)(ref)));

    jclass cls = env->FindClass("tsa/DoubleComplex");
    jmethodID id = env->GetMethodID(cls, "<init>", "(DD)V");
    if (id == NULL) return NULL;

    result = env->NewObjectArray(elements, cls, NULL);

    af::af_cdouble *tmp = (af::af_cdouble *)malloc(sizeof(af::af_cdouble) * elements);
    af_array a = (af_array)ref;
    af::array var = af::array(a);
    tsa::array::getData(var, tmp);
    af_retain_array(&a, var.get());
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    env->SetLongField(thisObj, fidf, jlong(a));

    for (int i = 0; i < elements; i++) {
        double re = tmp[i].real;
        double im = tmp[i].imag;
        jobject obj = env->NewObject(cls, id, re, im);
        env->SetObjectArrayElement(result, i, obj);
    }

    free(tmp);
    return result;
}

JNIEXPORT jobjectArray JNICALL Java_tsa_Array_getFloatComplexFromArray(JNIEnv *env, jobject thisObj, jlong ref) {
    jobjectArray result;
    dim_t elements = 0;
    (af_get_elements(&elements, (void *)(ref)));

    jclass cls = env->FindClass("tsa/FloatComplex");
    jmethodID id = env->GetMethodID(cls, "<init>", "(FF)V");
    if (id == NULL) return NULL;

    result = env->NewObjectArray(elements, cls, NULL);

    af::af_cfloat *tmp = (af::af_cfloat *)malloc(sizeof(af::af_cfloat) * elements);
    af_array a = (af_array)ref;
    af::array var = af::array(a);
    tsa::array::getData(var, tmp);
    af_retain_array(&a, var.get());
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    env->SetLongField(thisObj, fidf, jlong(a));

    for (int i = 0; i < elements; i++) {
        float re = tmp[i].real;
        float im = tmp[i].imag;
        jobject obj = env->NewObject(cls, id, re, im);
        env->SetObjectArrayElement(result, i, obj);
    }

    free(tmp);
    return result;
}

JNIEXPORT jlong JNICALL Java_tsa_Array_print(JNIEnv *env, jobject thisObj, jlong ref) {
    af_array a = (af_array)ref;
    af::array var = af::array(a);
    tsa::array::print(var);
    af_retain_array(&a, var.get());
    return jlong(a);
}

JNIEXPORT jlongArray JNICALL Java_tsa_Array_getDims(JNIEnv *env, jobject thisObj, jlong ref) {
    af_array a = (af_array)ref;
    af::array var = af::array(a);
    af::dim4 d = tsa::array::getDims(var);
    jlong result[4];
    jlongArray p = env->NewLongArray(4);

    memcpy(result, d.dims, sizeof(d.dims));

    af_retain_array(&a, var.get());
    jclass clazz = env->GetObjectClass(thisObj);
    jfieldID fidf = env->GetFieldID(clazz, "reference", "J");
    env->SetLongField(thisObj, fidf, jlong(a));
    env->SetLongArrayRegion(p, 0, 4, &result[0]);

    return p;
}

#ifdef __cplusplus
}
#endif