// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa_c/defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an Array object.
 *
 * @param data Data used in order to create the array.
 * @param ndims Number of dimensions of the data.
 * @param dims Cardinality of dimensions of the data.
 * @param result Array created.
 * @param type Data type.
 */
TSAAPI void create_array(void *data, unsigned *ndims, long long *dims, tsa_array *result, int *type);

/**
 * @brief Retrieves the data from the device to the host.
 *
 * @param array The Array that contains the data to be retrieved.
 * @param data Pointer to previously allocated memory in the host.
 */
TSAAPI void get_data(tsa_array *array, void *data);

/**
 * @brief Gets the Array dimensions.
 *
 * @param array Array from which to get the dimensions.
 * @param dims The dimensions.
 */
TSAAPI void get_dims(tsa_array *array, long long *dims);

/**
 * @brief Prints an Array.
 *
 * @param array The array to display.
 */
TSAAPI void print(tsa_array *array);

/**
 * @brief Decreases the references count of the given array.
 *
 * @param array The Array to release.
 */
TSAAPI void delete_array(tsa_array *array);

/**
 * @brief Gets the type of the array.
 *
 * @param array The array to obtain the type information from.
 * @param type Value of the Dtype enumeration.
 */
TSAAPI void get_type(tsa_array *array, int *t);

/**
 * @brief Adds two arrays.
 *
 * @param lhs Left-hand side TSA array for the operation.
 * @param rhs Right-hand side TSA array for the operation.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_add(tsa_array *lhs, tsa_array *rhs, tsa_array *result);

/**
 * @brief Multiplies two arrays.
 *
 * @param lhs Left-hand side TSA array for the operation.
 * @param rhs Right-hand side TSA array for the operation.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_mul(tsa_array *lhs, tsa_array *rhs, tsa_array *result);

/**
 * @brief Subtracts two arrays.
 *
 * @param lhs Left-hand side TSA array for the operation.
 * @param rhs Right-hand side TSA array for the operation.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_sub(tsa_array *lhs, tsa_array *rhs, tsa_array *result);

/**
 * @brief Divides lhs by rhs (element-wise).
 *
 * @param lhs Left-hand side TSA array for the operation.
 * @param rhs Right-hand side TSA array for the operation.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_div(tsa_array *lhs, tsa_array *rhs, tsa_array *result);

/**
 * @brief Performs the modulo operation of lhs by rhs.
 *
 * @param lhs Left-hand side TSA array for the operation.
 * @param rhs Right-hand side TSA array for the operation.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_mod(tsa_array *lhs, tsa_array *rhs, tsa_array *result);

/**
 * @brief Powers lhs with rhs.
 *
 * @param lhs Left-hand side TSA array for the operation. Base.
 * @param rhs Right-hand side TSA array for the operation. Exponent.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_pow(tsa_array *lhs, tsa_array *rhs, tsa_array *result);

/**
 * @brief Compares (element-wise) if lhs is lower than rhs.
 *
 * @param lhs Left-hand side TSA array for the operation.
 * @param rhs Right-hand side TSA array for the operation.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_lt(tsa_array *lhs, tsa_array *rhs, tsa_array *result);

/**
 * @brief Compares (element-wise) if lhs is greater than rhs.
 *
 * @param lhs Left-hand side TSA array for the operation.
 * @param rhs Right-hand side TSA array for the operation.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_gt(tsa_array *lhs, tsa_array *rhs, tsa_array *result);

/**
 * @brief Compares (element-wise) if lhs is lower or equal than rhs.
 *
 * @param lhs Left-hand side TSA array for the operation.
 * @param rhs Right-hand side TSA array for the operation.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_le(tsa_array *lhs, tsa_array *rhs, tsa_array *result);

/**
 * @brief Compares (element-wise) if lhs is greater or equal than rhs.
 *
 * @param lhs Left-hand side TSA array for the operation.
 * @param rhs Right-hand side TSA array for the operation.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_ge(tsa_array *lhs, tsa_array *rhs, tsa_array *result);

/**
 * @brief Compares (element-wise) if rhs is equal to rhs.
 *
 * @param lhs Left-hand side TSA array for the operation.
 * @param rhs Right-hand side TSA array for the operation.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_eq(tsa_array *lhs, tsa_array *rhs, tsa_array *result);

/**
 * @brief Compares (element-wise) if lhs is not equal to rhs.
 *
 * @param lhs Left-hand side TSA array for the operation.
 * @param rhs Right-hand side TSA array for the operation.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_ne(tsa_array *lhs, tsa_array *rhs, tsa_array *result);

/**
 * @brief Performs an AND operation (element-wise) with lhs and rhs.
 *
 * @param lhs Left-hand side TSA array for the operation.
 * @param rhs Right-hand side TSA array for the operation.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_bitand(tsa_array *lhs, tsa_array *rhs, tsa_array *result);

/**
 * @brief Performs an OR operation (element-wise) with lhs and rhs.
 *
 * @param lhs Left-hand side TSA array for the operation.
 * @param rhs Right-hand side TSA array for the operation.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_bitor(tsa_array *lhs, tsa_array *rhs, tsa_array *result);

/**
 * @brief Performs an eXclusive-OR operation (element-wise) with lhs and rhs.
 *
 * @param lhs Left-hand side TSA array for the operation.
 * @param rhs Right-hand side TSA array for the operation.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_bitxor(tsa_array *lhs, tsa_array *rhs, tsa_array *result);

/**
 * @brief Performs a left bit shift operation (element-wise) to array as many times as specified in the parameter n.
 *
 * @param array TSA Array to shift.
 * @param n Number of bits to be shifted.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_bitshiftl(tsa_array *array, int *n, tsa_array *result);

/**
 * @brief Performs a right bit shift operation (element-wise) to array as many times as specified in the parameter n.
 *
 * @param array TSA Array to shift.
 * @param n Number of bits to be shifted.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_bitshiftr(tsa_array *array, int *n, tsa_array *result);

/**
 * @brief Logical NOT operation to array.
 *
 * @param array TSA Array to negate.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_not(tsa_array *array, tsa_array *result);

/**
 * @brief Transposes array.
 *
 * @param array TSA Array to transpose.
 * @param conjugate If true a conjugate transposition is performed.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_transpose(tsa_array *array, bool *conjugate, tsa_array *result);

/**
 * @brief Retrieves a given column of array.
 *
 * @param array TSA Array.
 * @param index The column to be retrieved.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_col(tsa_array *array, int *index, tsa_array *result);

/**
 * @brief Retrieves a subset of columns of array, starting at first and finishing at last, both inclusive.
 *
 * @param array TSA Array.
 * @param first Start of the subset of columns to be retrieved.
 * @param last End of the subset of columns to be retrieved.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_cols(tsa_array *array, int *first, int *last, tsa_array *result);

/**
 * @brief Retrieves a given row of array.
 *
 * @param array TSA Array.
 * @param index The row to be retrieved.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_row(tsa_array *array, int *index, tsa_array *result);

/**
 * @brief Retrieves a subset of rows of array, starting at first and finishing at last, both inclusive.
 *
 * @param array TSA Array.
 * @param first Start of the subset of rows to be retrieved.
 * @param last End of the subset of rows to be retrieved.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_rows(tsa_array *array, int *first, int *last, tsa_array *result);

/**
 * @brief Creates a TSA array from an ArrayFire array.
 *
 * @param arrayfire ArrayFire array reference.
 * @param result TSA Array.
 */
TSAAPI void from_arrayfire(tsa_array *arrayfire, tsa_array *result);

/**
 * @brief Performs a matrix multiplication of lhs and rhs.
 *
 * @param lhs Left-hand side TSA array for the operation.
 * @param rhs Right-hand side TSA array for the operation.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_matmul(tsa_array *lhs, tsa_array *rhs, tsa_array *result);
/**
 * @brief Performs a deep copy of array.
 *
 * @param array TSA Array.
 * @param result TSA Array which contains a copy of array.
 */
TSAAPI void copy(tsa_array *array, tsa_array *result);
/**
 * @brief Changes the type of array.
 *
 * @param array TSA Array.
 * @param type Target type of the output array.
 * @param result TSA Array with the result of this operation.
 */
TSAAPI void tsa_as(tsa_array *array, const int *type, tsa_array *result);

#ifdef __cplusplus
}
#endif