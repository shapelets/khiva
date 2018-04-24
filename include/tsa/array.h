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
 * @brief Create an Array object.
 *
 * @param data Data used in order to create the array.
 * @param ndims Number of dimensions of the data.
 * @param dims Cardinality of dimesions of the data.
 * @param result Array created.
 * @param type Data type.
 */
af::array createArray(void *data, unsigned ndims, dim_t *dims, const int type);

/**
 * @brief Retrieves the data from the device to the host.
 *
 * @param array The Array that contains the data to be retrieved.
 * @param data Pointer to previously allocated memory in the host.
 */
void getData(af::array array, void *data);

/**
 * @brief Get the Array dimensions.
 *
 * @param array Array from which to get the dimensions
 * @param dims The dimensions.
 */
af::dim4 getDims(af::array array);

/**
 * @brief Displays an Array.
 *
 * @param array The array to display.
 */
void displayArray(af::array array);

/**
 * @brief Decrease the references count of the given array.
 *
 * @param array The Array to release.
 */
void deleteArray(af_array array);

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
    Array() {
        x = 0;
        y = 1;
        w = 1;
        z = 1;
        dims = 0;
        data = NULL;
    }

    Array(af::array in) {
        x = in.dims(0);
        y = in.dims(1);
        w = in.dims(2);
        z = in.dims(3);
        data = in.host<T>();
        dims = in.numdims();
        af::sync();
    }

    ~Array() {
        if (!isEmpty()) {
            data = NULL;
        }
    }
    void setNumX(int val) { x = val; }
    void setNumY(int val) { y = val; }
    void setNumW(int val) { w = val; }
    void setNumZ(int val) { z = val; }
    void setData(T *pd) { data = pd; };

    int getNumX() { return x; };

    int getNumY() { return y; };

    int getNumW() { return w; };

    int getNumZ() { return z; };

    int getNumElements() { return std::max(1, x) * std::max(1, y) * std::max(1, w) * std::max(1, z); }

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

    T getElement(int row, int column) {
        if (dims != 2) {
            std::cout << "We only support this function for arrays with 2 dims." << std::endl;
            std::cout << "Your array has " << dims << " dimensions." << std::endl;
            exit(0);
        }

        return data[x * column + row];
    }

    T *getData() { return data; };

    bool isEmpty() { return data == NULL; }
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

template <typename T>
std::vector<int> getIndexMaxColums(std::vector<T> r) {
    std::vector<int> result;

    for (int i = 0; i < r.size(); i++) {
        if (r[i] == 1) {
            result.push_back(i);
        }
    }

    return result;
}

};  // namespace array
};  // namespace tsa
