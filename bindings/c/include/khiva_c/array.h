// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva_c/defines.h>

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
KHIVAAPI void create_array(void *data, unsigned *ndims, long long *dims, khiva_array *result, int *type);

/**
 * @brief Retrieves the data from the device to the host.
 *
 * @param array The Array that contains the data to be retrieved.
 * @param data Pointer to previously allocated memory in the host.
 */
KHIVAAPI void get_data(khiva_array *array, void *data);

/**
 * @brief Gets the Array dimensions.
 *
 * @param array Array from which to get the dimensions.
 * @param dims The dimensions.
 */
KHIVAAPI void get_dims(khiva_array *array, long long *dims);

/**
 * @brief Prints an Array.
 *
 * @param array The array to display.
 */
KHIVAAPI void print(khiva_array *array);

/**
 * @brief Decreases the references count of the given array.
 *
 * @param array The Array to release.
 */
KHIVAAPI void delete_array(khiva_array *array);

/**
 * @brief Gets the type of the array.
 *
 * @param array The array to obtain the type information from.
 * @param type Value of the Dtype enumeration.
 */
KHIVAAPI void get_type(khiva_array *array, int *t);

/**
 * @brief Adds two arrays.
 *
 * @param lhs Left-hand side KHIVA array for the operation.
 * @param rhs Right-hand side KHIVA array for the operation.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_add(khiva_array *lhs, khiva_array *rhs, khiva_array *result);

/**
 * @brief Multiplies two arrays.
 *
 * @param lhs Left-hand side KHIVA array for the operation.
 * @param rhs Right-hand side KHIVA array for the operation.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_mul(khiva_array *lhs, khiva_array *rhs, khiva_array *result);

/**
 * @brief Subtracts two arrays.
 *
 * @param lhs Left-hand side KHIVA array for the operation.
 * @param rhs Right-hand side KHIVA array for the operation.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_sub(khiva_array *lhs, khiva_array *rhs, khiva_array *result);

/**
 * @brief Divides lhs by rhs (element-wise).
 *
 * @param lhs Left-hand side KHIVA array for the operation.
 * @param rhs Right-hand side KHIVA array for the operation.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_div(khiva_array *lhs, khiva_array *rhs, khiva_array *result);

/**
 * @brief Performs the modulo operation of lhs by rhs.
 *
 * @param lhs Left-hand side KHIVA array for the operation.
 * @param rhs Right-hand side KHIVA array for the operation.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_mod(khiva_array *lhs, khiva_array *rhs, khiva_array *result);

/**
 * @brief Powers lhs with rhs.
 *
 * @param lhs Left-hand side KHIVA array for the operation. Base.
 * @param rhs Right-hand side KHIVA array for the operation. Exponent.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_pow(khiva_array *lhs, khiva_array *rhs, khiva_array *result);

/**
 * @brief Compares (element-wise) if lhs is lower than rhs.
 *
 * @param lhs Left-hand side KHIVA array for the operation.
 * @param rhs Right-hand side KHIVA array for the operation.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_lt(khiva_array *lhs, khiva_array *rhs, khiva_array *result);

/**
 * @brief Compares (element-wise) if lhs is greater than rhs.
 *
 * @param lhs Left-hand side KHIVA array for the operation.
 * @param rhs Right-hand side KHIVA array for the operation.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_gt(khiva_array *lhs, khiva_array *rhs, khiva_array *result);

/**
 * @brief Compares (element-wise) if lhs is lower or equal than rhs.
 *
 * @param lhs Left-hand side KHIVA array for the operation.
 * @param rhs Right-hand side KHIVA array for the operation.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_le(khiva_array *lhs, khiva_array *rhs, khiva_array *result);

/**
 * @brief Compares (element-wise) if lhs is greater or equal than rhs.
 *
 * @param lhs Left-hand side KHIVA array for the operation.
 * @param rhs Right-hand side KHIVA array for the operation.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_ge(khiva_array *lhs, khiva_array *rhs, khiva_array *result);

/**
 * @brief Compares (element-wise) if rhs is equal to rhs.
 *
 * @param lhs Left-hand side KHIVA array for the operation.
 * @param rhs Right-hand side KHIVA array for the operation.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_eq(khiva_array *lhs, khiva_array *rhs, khiva_array *result);

/**
 * @brief Compares (element-wise) if lhs is not equal to rhs.
 *
 * @param lhs Left-hand side KHIVA array for the operation.
 * @param rhs Right-hand side KHIVA array for the operation.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_ne(khiva_array *lhs, khiva_array *rhs, khiva_array *result);

/**
 * @brief Performs an AND operation (element-wise) with lhs and rhs.
 *
 * @param lhs Left-hand side KHIVA array for the operation.
 * @param rhs Right-hand side KHIVA array for the operation.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_bitand(khiva_array *lhs, khiva_array *rhs, khiva_array *result);

/**
 * @brief Performs an OR operation (element-wise) with lhs and rhs.
 *
 * @param lhs Left-hand side KHIVA array for the operation.
 * @param rhs Right-hand side KHIVA array for the operation.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_bitor(khiva_array *lhs, khiva_array *rhs, khiva_array *result);

/**
 * @brief Performs an eXclusive-OR operation (element-wise) with lhs and rhs.
 *
 * @param lhs Left-hand side KHIVA array for the operation.
 * @param rhs Right-hand side KHIVA array for the operation.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_bitxor(khiva_array *lhs, khiva_array *rhs, khiva_array *result);

/**
 * @brief Performs a left bit shift operation (element-wise) to array as many times as specified in the parameter n.
 *
 * @param array KHIVA Array to shift.
 * @param n Number of bits to be shifted.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_bitshiftl(khiva_array *array, int *n, khiva_array *result);

/**
 * @brief Performs a right bit shift operation (element-wise) to array as many times as specified in the parameter n.
 *
 * @param array KHIVA Array to shift.
 * @param n Number of bits to be shifted.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_bitshiftr(khiva_array *array, int *n, khiva_array *result);

/**
 * @brief Logical NOT operation to array.
 *
 * @param array KHIVA Array to negate.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_not(khiva_array *array, khiva_array *result);

/**
 * @brief Transposes array.
 *
 * @param array KHIVA Array to transpose.
 * @param conjugate If true a conjugate transposition is performed.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_transpose(khiva_array *array, bool *conjugate, khiva_array *result);

/**
 * @brief Retrieves a given column of array.
 *
 * @param array KHIVA Array.
 * @param index The column to be retrieved.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_col(khiva_array *array, int *index, khiva_array *result);

/**
 * @brief Retrieves a subset of columns of array, starting at first and finishing at last, both inclusive.
 *
 * @param array KHIVA Array.
 * @param first Start of the subset of columns to be retrieved.
 * @param last End of the subset of columns to be retrieved.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_cols(khiva_array *array, int *first, int *last, khiva_array *result);

/**
 * @brief Retrieves a given row of array.
 *
 * @param array KHIVA Array.
 * @param index The row to be retrieved.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_row(khiva_array *array, int *index, khiva_array *result);

/**
 * @brief Retrieves a subset of rows of array, starting at first and finishing at last, both inclusive.
 *
 * @param array KHIVA Array.
 * @param first Start of the subset of rows to be retrieved.
 * @param last End of the subset of rows to be retrieved.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_rows(khiva_array *array, int *first, int *last, khiva_array *result);

/**
 * @brief Creates a KHIVA array from an ArrayFire array.
 *
 * @param arrayfire ArrayFire array reference.
 * @param result KHIVA Array.
 */
KHIVAAPI void from_arrayfire(khiva_array *arrayfire, khiva_array *result);

/**
 * @brief Performs a matrix multiplication of lhs and rhs.
 *
 * @param lhs Left-hand side KHIVA array for the operation.
 * @param rhs Right-hand side KHIVA array for the operation.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_matmul(khiva_array *lhs, khiva_array *rhs, khiva_array *result);
/**
 * @brief Performs a deep copy of array.
 *
 * @param array KHIVA Array.
 * @param result KHIVA Array which contains a copy of array.
 */
KHIVAAPI void copy(khiva_array *array, khiva_array *result);
/**
 * @brief Changes the type of array.
 *
 * @param array KHIVA Array.
 * @param type Target type of the output array.
 * @param result KHIVA Array with the result of this operation.
 */
KHIVAAPI void khiva_as(khiva_array *array, const int *type, khiva_array *result);

#ifdef __cplusplus
}
#endif
