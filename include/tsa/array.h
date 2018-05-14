// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <iostream>
#include <limits>

namespace tsa {
typedef af::dtype dtype;
namespace array {

/**
 * @brief Creates an af::array object.
 *
 * @param data Data used to create the af::array.
 * @param ndims Number of dimensions of data.
 * @param dims Cardinality of dimensions of data.
 * @param type Data type.
 *
 * @return af::array Containing the data.
 */
af::array createArray(void *data, unsigned ndims, dim_t *dims, const int type);

/**
 * @brief Retrieves the data from the device to the host.
 *
 * @param array The Array that contains the data to be retrieved.
 * @param data Pointer to previously allocated block of memory in the host.
 */
void getData(af::array array, void *data);

/**
 * @brief Gets the Array dimensions.
 *
 * @param array Array from which to get the dimensions.
 *
 * @return af::dim4 The dimensions.
 */
af::dim4 getDims(af::array array);

/**
 * @brief Prints the content of an array.
 *
 * @param array The array to be printed.
 */
void print(af::array array);

/**
 * @brief Decreases the references count of the given array.
 *
 * @param array The Array to release.
 */
void deleteArray(af_array array);

/**
 * @brief Gets the type of the array.
 *
 * @param array The array to obtain the type from.
 *
 * @return int Value of the Dtype enumeration.
 */
int getType(af::array array);

/**
 * @brief Array class, This class provides functionality manage Arrays on the host side.
 */
template <class T>
class Array {
   private:
    T *data;
    int x;
    int y;
    int w;
    int z;
    int dims;

   public:
    /**
     * @brief Default Constructor of Array class.
     */
    Array() {
        x = 0;
        y = 1;
        w = 1;
        z = 1;
        dims = 0;
        data = NULL;
    }

    /**
     * @brief Constructor of Array class wich receives and af::array.
     *
     * @param in The input af::array.
     */
    Array(af::array in) {
        x = static_cast<int>(in.dims(0));
        y = static_cast<int>(in.dims(1));
        w = static_cast<int>(in.dims(2));
        z = static_cast<int>(in.dims(3));
        data = in.host<T>();
        dims = in.numdims();
        af::sync();
    }

    /**
     * @brief Default destructor of Array class.
     */
    ~Array() {
        if (!isEmpty()) {
            data = NULL;
        }
    }

    /**
     * @brief Sets the cardinality of the first dimension.
     *
     * @param val The value to be set.
     */
    void setNumX(int val) { x = val; }

    /**
     * @brief Sets the cardinality of the second dimension.
     *
     * @param val The value to be set.
     */
    void setNumY(int val) { y = val; }

    /**
     * @brief Sets the cardinality of the third dimension.
     *
     * @param val The value to be set.
     */
    void setNumW(int val) { w = val; }

    /**
     * @brief Sets the cardinality of the fourth dimension.
     *
     * @param val The value to be set.
     */
    void setNumZ(int val) { z = val; }

    /**
     * @brief Sets the data to be stored in the Array.
     *
     * @param pd The data to be stored.
     */
    void setData(T *pd) { data = pd; };

    /**
     * @brief Gets the cardinality of the first dimension.
     *
     * @return int the Cardinality of the first dimension.
     */
    int getNumX() { return x; };

    /**
     * @brief Gets the cardinality of the second dimension.
     *
     * @return int the Cardinality of the second dimension.
     */
    int getNumY() { return y; };

    /**
     * @brief Gets the cardinality of the third dimension.
     *
     * @return int the Cardinality of the third dimension.
     */
    int getNumW() { return w; };

    /**
     * @brief Gets the cardinality of the fourth dimension.
     *
     * @return int the Cardinality of the fourth dimension.
     */
    int getNumZ() { return z; };

    /**
     * @brief Gets the number of elements in data.
     *
     * @return int the Cardinality of the number of elements.
     */
    int getNumElements() { return std::max(1, x) * std::max(1, y) * std::max(1, w) * std::max(1, z); }

    /**
     * @brief Gets the row number given by idx.
     *
     * @param idx The row number to be extracted.
     *
     * @return std::vector Containing the selected row.
     */
    std::vector<T> getRow(int idx) {
        if (dims > 2) {
            std::cout << "We only support this function for arrays with 2 dims." << std::endl;
            std::cout << "Your array has " << dims << " dimensions." << std::endl;
            exit(0);
        }

        std::vector<T> res;
        for (int i = 0; i < y; i++) {
            res.push_back(data[idx + i * x]);
        }
        return res;
    }

    /**
     * @brief Gets the column number given by idx.
     *
     * @param idx The column number to be extracted.
     *
     * @return std::vector Containing the selected column.
     */
    std::vector<T> getColumn(int idx) {
        if (dims != 2) {
            std::cout << "We only support this function for arrays with 2 dims." << std::endl;
            std::cout << "Your array has " << dims << " dimensions." << std::endl;
            exit(0);
        }
        std::vector<T> res;
        for (int i = 0; i < y; i++) {
            res.push_back(data[idx * x + i]);
        }
        return res;
    }

    /**
     * @brief Gets the element given by row and column.
     *
     * @param row The row number.
     * @param column The column number.
     *
     * @return T The element to be extracted.
     */
    T getElement(int row, int column) {
        if (dims != 2) {
            std::cout << "We only support this function for arrays with 2 dims." << std::endl;
            std::cout << "Your array has " << dims << " dimensions." << std::endl;
            exit(0);
        }

        return data[x * column + row];
    }

    /**
     * @brief Gets a pointer to the data stored in the array.
     *
     * @return T Pointer to data.
     */
    T *getData() { return data; };

    /**
     * @brief Checks whether The Array is empty or not.
     *
     * @return True if the Array is empty, false otherwise.
     */
    bool isEmpty() { return data == NULL; }

    /**
     * @brief Prints the content of the array.
     */
    void print() {
        if (isEmpty()) {
            std::cout << "<Empty>" << std::endl;
        } else {
            std::cout << "Dims: [" << x << " " << y << " " << w << " " << z << "]" << std::endl;
            for (int l = 0; l < std::max(1, z); l++) {
                for (int k = 0; k < std::max(1, w); k++) {
                    for (int i = 0; i < std::max(1, x); i++) {
                        for (int j = 0; j < std::max(1, y); j++) {
                            int base = i + (x * w * k) + (x * w * z * l);
                            std::cout << data[base + j * x] << "\t";
                        }
                        std::cout << std::endl;
                    }
                    if (k > 0) {
                        std::cout << std::endl;
                        std::cout << std::endl;
                    }
                }
                if (l > 0) {
                    std::cout << std::endl;
                    std::cout << std::endl;
                    std::cout << std::endl;
                }
            }
        }
    }
};

/**
 * @brief Gets the indices of all rows containing a maximal.
 *
 * @param a The input array.
 *
 * @return std::vector<int> with the indices of the rows with maximals.
 */
template <typename T>
std::vector<int> getRowsWithMaximals(tsa::array::Array<T> a) {
    std::vector<int> result;

    for (int i = 0; i < a.getNumX(); i++) {
        std::vector<T> row = a.getRow(i);
        for (int j = 0; j < a.getNumY(); j++) {
            if (row[j] == 1) {
                result.push_back(i);
                break;
            }
        }
    }
    return result;
}

/**
 * @brief Gets the indices of the columns with maximals.
 *
 * @param r The input row.
 *
 * @return std::vector<int> with the indices of the columns with maximals.
 */
template <typename T>
std::vector<int> getIndexMaxColums(std::vector<T> r) {
    std::vector<int> result;

    for (unsigned long i = 0; i < r.size(); i++) {
        if (r[i] == 1) {
            result.push_back(i);
        }
    }

    return result;
}

};  // namespace array
};  // namespace tsa
