#include <arrayfire.h>
#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an Array object of Float, Double, Int, Boolean, Long, Short or Byte.
 * @param elems Data used in order to create the array.
 * @param dims Cardinality of dimensions of the data.
 * @return The array reference.
 */
#define CREATE_T_ARRAY(Ty, ty, dty)                                                                              \
    JNIEXPORT jlong JNICALL Java_tsa_Array_createArrayFrom##Ty(JNIEnv *env, jobject thisObj, j##ty##Array elems, \
                                                               jlongArray dims);
CREATE_T_ARRAY(Float, float, tsa::dtype::f32)
CREATE_T_ARRAY(Double, double, tsa::dtype::f64)
CREATE_T_ARRAY(Int, int, tsa::dtype::s32)
CREATE_T_ARRAY(Boolean, boolean, tsa::dtype::b8)
CREATE_T_ARRAY(Long, long, tsa::dtype::s64)
CREATE_T_ARRAY(Short, short, tsa::dtype::s16)
CREATE_T_ARRAY(Byte, byte, tsa::dtype::u8)

#undef CREATE_T_ARRAY

/**
 * @brief Creates an Array object of Float Complex.
 * @param elems Data used in order to create the array.
 * @param dims Cardinality of dimensions of the data.
 * @return The array reference.
 */
JNIEXPORT jlong JNICALL Java_tsa_Array_createArrayFromFloatComplex(JNIEnv *env, jclass clazz, jobjectArray objs,
                                                                   jlongArray dims);

/**
 * @brief Creates an Array object of Double Complex.
 * @param elems Data used in order to create the array.
 * @param dims Cardinality of dimensions of the data.
 * @return The array reference.
 */
JNIEXPORT jlong JNICALL Java_tsa_Array_createArrayFromDoubleComplex(JNIEnv *env, jclass clazz, jobjectArray objs,
                                                                    jlongArray dims);

/**
 * @brief Retrieves data from the device to host(Float, Double, Int, Boolean, Long, Short or Byte).
 *
 * @param ref The Array that contains the data to be retrieved.
 * @return Array with the data.
 */
#define GET_T_FROM_ARRAY(Ty, ty) \
    JNIEXPORT j##ty##Array JNICALL Java_tsa_Array_get##Ty##FromArray(JNIEnv *env, jobject thisObj, jlong ref);
GET_T_FROM_ARRAY(Float, float)
GET_T_FROM_ARRAY(Double, double)
GET_T_FROM_ARRAY(Int, int)
GET_T_FROM_ARRAY(Boolean, boolean)
GET_T_FROM_ARRAY(Long, long)

#undef GET_T_FROM_ARRAY

/**
 * @brief Retrieves data from the device to host(Double Complex).
 *
 * @param ref The Array that contains the data to be retrieved.
 * @return Array with the data.
 */
JNIEXPORT jobjectArray JNICALL Java_tsa_Array_getDoubleComplexFromArray(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Retrieves data from the device to host(Float Complex).
 *
 * @param ref The Array that contains the data to be retrieved.
 * @return Array with the data.
 */
JNIEXPORT jobjectArray JNICALL Java_tsa_Array_getFloatComplexFromArray(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Gets the Array type.
 *
 * @return Integer representing the Array type.
 */
JNIEXPORT jint JNICALL Java_tsa_Array_getType(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Gets the Array dimensions.
 *
 * @param ref The Array reference.
 * @return The dimensions.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Array_getDims(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Prints the Array.
 *
 * @param ref The Array reference.
 * @return The updated reference.
 */
JNIEXPORT jlong JNICALL Java_tsa_Array_print(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Releases the array.
 *
 * @param ref The Array reference.
 */
JNIEXPORT void JNICALL Java_tsa_Array_deleteArray(JNIEnv *env, jobject thisObj, jlong ref);

#ifdef __cplusplus
}
#endif
