// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGJAVA_ARRAY_H
#define KHIVA_BINDINGJAVA_ARRAY_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an Array object of Float, Double, Int, Boolean, Long, Short or Byte.
 *
 * @param elems Data used in order to create the array.
 * @param dims Cardinality of dimensions of the data.
 *
 * @return The array reference.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_createArrayFromFloat(JNIEnv *env, jobject, jfloatArray elems,
                                                                           jlongArray dims);

/**
 * @brief Creates an Array object of Double.
 *
 * @param elems Data used in order to create the array.
 * @param dims Cardinality of dimensions of the data.
 *
 * @return The array reference.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_createArrayFromDouble(JNIEnv *env, jobject, jdoubleArray elems,
                                                                           jlongArray dims);
/**
 * @brief Creates an Array object of Int.
 *
 * @param elems Data used in order to create the array.
 * @param dims Cardinality of dimensions of the data.
 *
 * @return The array reference.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_createArrayFromInt(JNIEnv *env, jobject, jintArray elems,
                                                                           jlongArray dims);
/**
 * @brief Creates an Array object of Boolean.
 *
 * @param elems Data used in order to create the array.
 * @param dims Cardinality of dimensions of the data.
 *
 * @return The array reference.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_createArrayFromBoolean(JNIEnv *env, jobject, jbooleanArray elems,
                                                                           jlongArray dims);

/**
 * @brief Creates an Array object of Long.
 *
 * @param elems Data used in order to create the array.
 * @param dims Cardinality of dimensions of the data.
 *
 * @return The array reference.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_createArrayFromLong(JNIEnv *env, jobject, jlongArray elems,
                                                                           jlongArray dims);

/**
 * @brief Creates an Array object of Short.
 *
 * @param elems Data used in order to create the array.
 * @param dims Cardinality of dimensions of the data.
 *
 * @return The array reference.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_createArrayFromShort(JNIEnv *env, jobject, jshortArray elems,
                                                                           jlongArray dims);

/**
 * @brief Creates an Array object of Byte.
 *
 * @param elems Data used in order to create the array.
 * @param dims Cardinality of dimensions of the data.
 *
 * @return The array reference.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_createArrayFromByte(JNIEnv *env, jobject, jbyteArray elems,
                                                                           jlongArray dims);

/**
 * @brief Creates an Array object of Float Complex.
 *
 * @param elems Data used in order to create the array.
 * @param dims Cardinality of dimensions of the data.
 *
 * @return The array reference.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_createArrayFromFloatComplex(JNIEnv *env, jclass,
                                                                                  jobjectArray objs, jlongArray dims);

/**
 * @brief Creates an Array object of Double Complex.
 *
 * @param elems Data used in order to create the array.
 * @param dims Cardinality of dimensions of the data.
 *
 * @return The array reference.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_createArrayFromDoubleComplex(JNIEnv *env, jclass,
                                                                                   jobjectArray objs, jlongArray dims);

/**
 * @brief Releases the array.
 */
JNIEXPORT void JNICALL Java_io_shapelets_khiva_Array_deleteArray(JNIEnv *env, jobject thisObj);

/**
 * @brief Retrieves data from the device to host.
 *
 * @return Array with the data.
 */
JNIEXPORT jfloatArray JNICALL Java_io_shapelets_khiva_Array_getFloatFromArray(JNIEnv *env, jobject thisObj);

/**
 * @brief Retrieves data from the device to host.
 *
 * @return Array with the data.
 */
JNIEXPORT jdoubleArray JNICALL Java_io_shapelets_khiva_Array_getDoubleFromArray(JNIEnv *env, jobject thisObj);

/**
 * @brief Retrieves data from the device to host.
 *
 * @return Array with the data.
 */
JNIEXPORT jintArray JNICALL Java_io_shapelets_khiva_Array_getIntFromArray(JNIEnv *env, jobject thisObj);

/**
 * @brief Retrieves data from the device to host.
 *
 * @return Array with the data.
 */
JNIEXPORT jbooleanArray JNICALL Java_io_shapelets_khiva_Array_getBooleanFromArray(JNIEnv *env, jobject thisObj);

/**
 * @brief Retrieves data from the device to host.
 *
 * @return Array with the data.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Array_getLongFromArray(JNIEnv *env, jobject thisObj);

/**
 * @brief Retrieves data from the device to host.
 *
 * @return Array with the data.
 */
JNIEXPORT jshortArray JNICALL Java_io_shapelets_khiva_Array_getShortFromArray(JNIEnv *env, jobject thisObj);

/**
 * @brief Retrieves data from the device to host.
 *
 * @return Array with the data.
 */
JNIEXPORT jbyteArray JNICALL Java_io_shapelets_khiva_Array_getByteFromArray(JNIEnv *env, jobject thisObj);

/**
 * @brief Retrieves data from the device to host (Double Complex).
 *
 * @return Array with the data.
 */
JNIEXPORT jobjectArray JNICALL Java_io_shapelets_khiva_Array_getDoubleComplexFromArray(JNIEnv *env, jobject thisObj);

/**
 * @brief Retrieves data from the device to host (Float Complex).
 *
 * @return Array with the data.
 */
JNIEXPORT jobjectArray JNICALL Java_io_shapelets_khiva_Array_getFloatComplexFromArray(JNIEnv *env, jobject thisObj);

/**
 * @brief Gets the Array dimensions.
 *
 * @return The dimensions.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Array_nativeGetDims(JNIEnv *env, jobject thisObj);

/**
 * @brief Gets the Array type.
 *
 * @return Integer representing the Array type.
 */
JNIEXPORT jint JNICALL Java_io_shapelets_khiva_Array_nativeGetType(JNIEnv *env, jobject thisObj);

/**
 * @brief Prints the Array.
 */
JNIEXPORT void JNICALL Java_io_shapelets_khiva_Array_nativePrint(JNIEnv *env, jobject thisObj);

/**
 * @brief Joins this array with the one specified as parameter along the specified dimension.
 *
 * @param dim The dimension along which the join occurs.
 * @param ref_rhs Reference to the right-hand side array for the operation.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_join(JNIEnv *env, jobject thisObj, jint dim, jlong ref_rhs);

/**
 * @brief Adds this array with the one specified as parameter.
 *
 * @param ref_rhs Reference to the right-hand side array for the operation.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_add(JNIEnv *env, jobject thisObj, jlong ref_rhs);

/**
 * @brief Multiplies this array with the one specified as parameter.
 *
 * @param ref_rhs Reference to the right-hand side array for the operation.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_mul(JNIEnv *env, jobject thisObj, jlong ref_rhs);

/**
 * @brief Subtracts this array with the one specified as parameter.
 *
 * @param ref_rhs Reference to the right-hand side array for the operation.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_sub(JNIEnv *env, jobject thisObj, jlong ref_rhs);

/**
 * @brief Divides this array with the one specified as parameter.
 *
 * @param ref_rhs Reference to the right-hand side array for the operation.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_div(JNIEnv *env, jobject thisObj, jlong ref_rhs);

/**
 * @brief Performs the modulo operation of this array between the one specified as parameter.
 *
 * @param ref_rhs Reference to the right-hand side array for the operation.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_mod(JNIEnv *env, jobject thisObj, jlong ref_rhs);

/**
 * @brief Powers this array with the one specified as parameter. This array is the base and the exponent is the
 * specified parameter.
 *
 * @param ref_rhs Reference to the right-hand side array for the operation.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_pow(JNIEnv *env, jobject thisObj, jlong ref_rhs);

/**
 * @brief Compares (element-wise) if this array is lower than the one specified as parameter.
 *
 * @param ref_rhs Reference to the right-hand side array for the operation.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_lt(JNIEnv *env, jobject thisObj, jlong ref_rhs);

/**
 * @brief Compares (element-wise) if this array is greater than the one specified as parameter.
 *
 * @param ref_rhs Reference to the right-hand side array for the operation.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_gt(JNIEnv *env, jobject thisObj, jlong ref_rhs);

/**
 * @brief Compares (element-wise) if this array is lower or equal than the one specified as parameter.
 *
 * @param ref_rhs Reference to the right-hand side array for the operation.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_le(JNIEnv *env, jobject thisObj, jlong ref_rhs);

/**
 * @brief Compares (element-wise) if this array is greater or equal than the one specified as parameter.
 *
 * @param ref_rhs Reference to the right-hand side array for the operation.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_ge(JNIEnv *env, jobject thisObj, jlong ref_rhs);

/**
 * @brief Compares (element-wise) if this array is equal to the one specified as parameter.
 *
 * @param ref_rhs Reference to the right-hand side array for the operation.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_eq(JNIEnv *env, jobject thisObj, jlong ref_rhs);

/**
 * @brief Compares (element-wise) if this array is not equal to the one specified as parameter.
 *
 * @param ref_rhs Reference to the right-hand side array for the operation.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_ne(JNIEnv *env, jobject thisObj, jlong ref_rhs);

/**
 * @brief Performs an AND operation with this array (element-wise) and the one specified as parameter.
 *
 * @param ref_rhs Reference to the right-hand side array for the operation.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_bitAnd(JNIEnv *env, jobject thisObj, jlong ref_rhs);

/**
 * @brief Performs an OR operation with this array (element-wise) and the one specified as parameter.
 *
 * @param ref_rhs Reference to the right-hand side array for the operation.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_bitOr(JNIEnv *env, jobject thisObj, jlong ref_rhs);

/**
 * @brief Performs an eXclusive-OR operation with this array (element-wise) and the one specified as parameter.
 *
 * @param ref_rhs Reference to the right-hand side array for the operation.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_bitXor(JNIEnv *env, jobject thisObj, jlong ref_rhs);

/**
 * @brief Performs a left bit shift operation to this array (element-wise) as many times as specified in the parameter
 * n.
 *
 * @param n Number of bits to be shifted.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_nativeBitShiftL(JNIEnv *env, jobject thisObj, jint n);

/**
 * @brief Performs a right bit shift operation to this array (element-wise) as many times as specified in the parameter
 * n.
 *
 * @param n Number of bits to be shifted.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_nativeBitShiftR(JNIEnv *env, jobject thisObj, jint n);

/**
 * @brief Logical NOT operation to this array.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_nativeNot(JNIEnv *env, jobject thisObj);

/**
 * @brief Transposes this array.
 *
 * @param conjugate If true a conjugate transposition is performed.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_nativeTranspose(JNIEnv *env, jobject thisObj, jboolean conjugate);

/**
 * @brief Retrieves a given column of this array.
 *
 * @param index The column to be retrieved.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_nativeCol(JNIEnv *env, jobject thisObj, jint index);

/**
 * @brief Retrieves a subset of columns of this array, starting at first and finishing at last, both inclusive.
 *
 * @param first Start of the subset of columns to be retrieved.
 * @param last End of the subset of columns to be retrieved.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_nativeCols(JNIEnv *env, jobject thisObj, jint first, jint last);

/**
 * @brief Retrieves a given row of this array.
 *
 * @param index The row to be retrieved.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_nativeRow(JNIEnv *env, jobject thisObj, jint index);

/**
 * @brief Retrieves a subset of rows of this array, starting at first and finishing at last, both inclusive.
 *
 * @param first Start of the subset of rows to be retrieved.
 * @param last End of the subset of rows to be retrieved.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_nativeRows(JNIEnv *env, jobject thisObj, jint first, jint last);

/**
 * @brief Performs a matrix multiplication of this array with the one specified as parameter.
 *
 * @param ref_rhs Reference to the right-hand side array for the operation.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_matmul(JNIEnv *env, jobject thisObj, jlong ref_rhs);

/**
 * @brief Performs a deep copy of this array. Both the data stored in the device and all the object properties in Java.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_nativeCopy(JNIEnv *env, jobject thisObj);

/**
 * @brief Changes the type of this array.
 *
 * @param type Target type of the output array.
 *
 * @return The reference of the resulting array.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Array_as(JNIEnv *env, jobject thisObj, jint type);

#ifdef __cplusplus
}
#endif

#endif
