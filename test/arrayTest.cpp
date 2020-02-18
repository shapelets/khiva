// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <khiva/array.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "khivaTest.h"

void arrayFloat() {
    float data[] = {0.0f, 1.0f, 2.0f, 3.0f, 6.0f,  7.0f,  8.0f, 9.0f, 2.0f, -2.0f, 4.0f, -4.0f,
                    8.0f, 5.0,  3.0,  1.0,  15.0f, 10.0f, 5.0f, 0.0f, 7.0f, -7.0,  1.0f, -1.0f};

    dim_t dimensions[] = {4, 6};

    af::array result = khiva::array::createArray(data, 2, dimensions, khiva::dtype::f32);

    float *calculated = (float *)malloc(24 * sizeof(float));
    khiva::array::getData(result, calculated);

    for (int i = 0; i < 24; i++) {
        ASSERT_EQ(calculated[i], data[i]);
    }

    free(calculated);

    ASSERT_EQ(static_cast<int>(khiva::dtype::f32), khiva::array::getType(result));
    af::dim4 dims = khiva::array::getDims(result);
    dim_t *calculatedDimensions = dims.get();

    ASSERT_EQ(2, dims.ndims());
    ASSERT_EQ(4, calculatedDimensions[0]);
    ASSERT_EQ(6, calculatedDimensions[1]);

    af_array arrayC = 0;
    af_retain_array(&arrayC, result.get());
    khiva::array::deleteArray(arrayC);
}

void arrayComplexFloat() {
    af::cfloat data[] = {af::af_cfloat(0.0f, 1.0f), af::af_cfloat(2.0f, 3.0f), af::af_cfloat(6.0f, 7.0f),
                         af::af_cfloat(8.0f, 9.0f)};

    dim_t dimensions[] = {2, 2};

    af::array result = khiva::array::createArray(data, 2, dimensions, khiva::dtype::c32);

    af::cfloat *calculated = (af::cfloat *)malloc(4 * sizeof(af::cfloat));
    khiva::array::getData(result, calculated);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(calculated[i].real, data[i].real);
        ASSERT_EQ(calculated[i].imag, data[i].imag);
    }

    free(calculated);

    ASSERT_EQ(static_cast<int>(khiva::dtype::c32), khiva::array::getType(result));
    af::dim4 dims = khiva::array::getDims(result);
    dim_t *calculatedDimensions = dims.get();

    ASSERT_EQ(2, dims.ndims());
    ASSERT_EQ(2, calculatedDimensions[0]);
    ASSERT_EQ(2, calculatedDimensions[1]);

    af_array arrayC = 0;
    af_retain_array(&arrayC, result.get());
    khiva::array::deleteArray(arrayC);
}

void arrayDouble() {
    double data[] = {0.0, 1.0, 2.0, 3.0, 6.0,  7.0,  8.0, 9.0, 2.0, -2.0, 4.0, -4.0,
                     8.0, 5.0, 3.0, 1.0, 15.0, 10.0, 5.0, 0.0, 7.0, -7.0, 1.0, -1.0};

    dim_t dimensions[] = {4, 6};

    af::array result = khiva::array::createArray(data, 2, dimensions, khiva::dtype::f64);

    double *calculated = (double *)malloc(24 * sizeof(double));
    khiva::array::getData(result, calculated);

    for (int i = 0; i < 24; i++) {
        ASSERT_EQ(calculated[i], data[i]);
    }

    free(calculated);

    ASSERT_EQ(static_cast<int>(khiva::dtype::f64), khiva::array::getType(result));
    af::dim4 dims = khiva::array::getDims(result);
    dim_t *calculatedDimensions = dims.get();

    ASSERT_EQ(2, dims.ndims());
    ASSERT_EQ(4, calculatedDimensions[0]);
    ASSERT_EQ(6, calculatedDimensions[1]);

    af_array arrayC = 0;
    af_retain_array(&arrayC, result.get());
    khiva::array::deleteArray(arrayC);
}

void arrayComplexDouble() {
    af::cdouble data[] = {af::af_cdouble(0.0, 1.0), af::af_cdouble(2.0, 3.0), af::af_cdouble(6.0, 7.0),
                          af::af_cdouble(8.0, 9.0)};

    dim_t dimensions[] = {2, 2};

    af::array result = khiva::array::createArray(data, 2, dimensions, khiva::dtype::c64);

    af::cdouble *calculated = (af::cdouble *)malloc(4 * sizeof(af::cdouble));
    khiva::array::getData(result, calculated);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(calculated[i].real, data[i].real);
        ASSERT_EQ(calculated[i].imag, data[i].imag);
    }

    free(calculated);

    ASSERT_EQ(static_cast<int>(khiva::dtype::c64), khiva::array::getType(result));
    af::dim4 dims = khiva::array::getDims(result);
    dim_t *calculatedDimensions = dims.get();

    ASSERT_EQ(2, dims.ndims());
    ASSERT_EQ(2, calculatedDimensions[0]);
    ASSERT_EQ(2, calculatedDimensions[1]);

    af_array arrayC = 0;
    af_retain_array(&arrayC, result.get());
    khiva::array::deleteArray(arrayC);
}

void arrayBoolean() {
    char data[] = {1, 0, 1, 0};

    dim_t dimensions[] = {2, 2};

    af::array result = khiva::array::createArray(data, 2, dimensions, khiva::dtype::b8);

    char *calculated = (char *)malloc(4 * sizeof(char));
    khiva::array::getData(result, calculated);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(calculated[i], data[i]);
    }

    free(calculated);

    ASSERT_EQ(static_cast<int>(khiva::dtype::b8), khiva::array::getType(result));
    af::dim4 dims = khiva::array::getDims(result);
    dim_t *calculatedDimensions = dims.get();

    ASSERT_EQ(2, dims.ndims());
    ASSERT_EQ(2, calculatedDimensions[0]);
    ASSERT_EQ(2, calculatedDimensions[1]);

    af_array arrayC = 0;
    af_retain_array(&arrayC, result.get());
    khiva::array::deleteArray(arrayC);
}

void arrayInt() {
    int data[] = {1, 0, 1, 0};

    dim_t dimensions[] = {2, 2};

    af::array result = khiva::array::createArray(data, 2, dimensions, khiva::dtype::s32);

    int *calculated = (int *)malloc(4 * sizeof(int));
    khiva::array::getData(result, calculated);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(calculated[i], data[i]);
    }

    free(calculated);

    ASSERT_EQ(static_cast<int>(khiva::dtype::s32), khiva::array::getType(result));
    af::dim4 dims = khiva::array::getDims(result);
    dim_t *calculatedDimensions = dims.get();

    ASSERT_EQ(2, dims.ndims());
    ASSERT_EQ(2, calculatedDimensions[0]);
    ASSERT_EQ(2, calculatedDimensions[1]);

    af_array arrayC = 0;
    af_retain_array(&arrayC, result.get());
    khiva::array::deleteArray(arrayC);
}

void arrayUnsignedInt() {
    unsigned int data[] = {1, 0, 1, 0};

    dim_t dimensions[] = {2, 2};

    af::array result = khiva::array::createArray(data, 2, dimensions, khiva::dtype::u32);

    unsigned int *calculated = (unsigned int *)malloc(4 * sizeof(unsigned int));
    khiva::array::getData(result, calculated);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(calculated[i], data[i]);
    }

    free(calculated);

    ASSERT_EQ(static_cast<int>(khiva::dtype::u32), khiva::array::getType(result));
    af::dim4 dims = khiva::array::getDims(result);
    dim_t *calculatedDimensions = dims.get();

    ASSERT_EQ(2, dims.ndims());
    ASSERT_EQ(2, calculatedDimensions[0]);
    ASSERT_EQ(2, calculatedDimensions[1]);

    af_array arrayC = 0;
    af_retain_array(&arrayC, result.get());
    khiva::array::deleteArray(arrayC);
}

void arrayUnsignedChar() {
    unsigned char data[] = {1, 0, 1, 0};

    dim_t dimensions[] = {2, 2};

    af::array result = khiva::array::createArray(data, 2, dimensions, khiva::dtype::u8);

    unsigned char *calculated = (unsigned char *)malloc(4 * sizeof(unsigned char));
    khiva::array::getData(result, calculated);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(calculated[i], data[i]);
    }

    free(calculated);

    ASSERT_EQ(static_cast<int>(khiva::dtype::u8), khiva::array::getType(result));
    af::dim4 dims = khiva::array::getDims(result);
    dim_t *calculatedDimensions = dims.get();

    ASSERT_EQ(2, dims.ndims());
    ASSERT_EQ(2, calculatedDimensions[0]);
    ASSERT_EQ(2, calculatedDimensions[1]);

    af_array arrayC = 0;
    af_retain_array(&arrayC, result.get());
    khiva::array::deleteArray(arrayC);
}

void arrayLong() {
    long long data[] = {1, 0, 1, 0};

    dim_t dimensions[] = {2, 2};

    af::array result = khiva::array::createArray(data, 2, dimensions, khiva::dtype::s64);

    long long *calculated = (long long *)malloc(4 * sizeof(long long));
    khiva::array::getData(result, calculated);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(calculated[i], data[i]);
    }

    free(calculated);

    ASSERT_EQ(static_cast<int>(khiva::dtype::s64), khiva::array::getType(result));
    af::dim4 dims = khiva::array::getDims(result);
    dim_t *calculatedDimensions = dims.get();

    ASSERT_EQ(2, dims.ndims());
    ASSERT_EQ(2, calculatedDimensions[0]);
    ASSERT_EQ(2, calculatedDimensions[1]);

    af_array arrayC = 0;
    af_retain_array(&arrayC, result.get());
    khiva::array::deleteArray(arrayC);
}

void arrayUnsignedLong() {
    unsigned long long data[] = {1, 0, 1, 0};

    dim_t dimensions[] = {2, 2};

    af::array result = khiva::array::createArray(data, 2, dimensions, khiva::dtype::u64);

    unsigned long long *calculated = (unsigned long long *)malloc(4 * sizeof(unsigned long long));
    khiva::array::getData(result, calculated);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(calculated[i], data[i]);
    }

    free(calculated);

    ASSERT_EQ(static_cast<int>(khiva::dtype::u64), khiva::array::getType(result));
    af::dim4 dims = khiva::array::getDims(result);
    dim_t *calculatedDimensions = dims.get();

    ASSERT_EQ(2, dims.ndims());
    ASSERT_EQ(2, calculatedDimensions[0]);
    ASSERT_EQ(2, calculatedDimensions[1]);

    af_array arrayC = 0;
    af_retain_array(&arrayC, result.get());
    khiva::array::deleteArray(arrayC);
}

void arrayShort() {
    short data[] = {1, 0, 1, 0};

    dim_t dimensions[] = {2, 2};

    af::array result = khiva::array::createArray(data, 2, dimensions, khiva::dtype::s16);

    short *calculated = (short *)malloc(4 * sizeof(short));
    khiva::array::getData(result, calculated);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(calculated[i], data[i]);
    }

    free(calculated);

    ASSERT_EQ(static_cast<int>(khiva::dtype::s16), khiva::array::getType(result));
    af::dim4 dims = khiva::array::getDims(result);
    dim_t *calculatedDimensions = dims.get();

    ASSERT_EQ(2, dims.ndims());
    ASSERT_EQ(2, calculatedDimensions[0]);
    ASSERT_EQ(2, calculatedDimensions[1]);

    af_array arrayC = 0;
    af_retain_array(&arrayC, result.get());
    khiva::array::deleteArray(arrayC);
}

void arrayUnsignedShort() {
    unsigned short data[] = {1, 0, 1, 0};

    dim_t dimensions[] = {2, 2};

    af::array result = khiva::array::createArray(data, 2, dimensions, khiva::dtype::u16);

    unsigned short *calculated = (unsigned short *)malloc(4 * sizeof(unsigned short));
    khiva::array::getData(result, calculated);

    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(calculated[i], data[i]);
    }

    free(calculated);

    ASSERT_EQ(static_cast<int>(khiva::dtype::u16), khiva::array::getType(result));
    af::dim4 dims = khiva::array::getDims(result);
    dim_t *calculatedDimensions = dims.get();

    ASSERT_EQ(2, dims.ndims());
    ASSERT_EQ(2, calculatedDimensions[0]);
    ASSERT_EQ(2, calculatedDimensions[1]);

    af_array arrayC = 0;
    af_retain_array(&arrayC, result.get());
    khiva::array::deleteArray(arrayC);
}

void arrayDefault() {
    float data[] = {0.0f, 1.0f, 2.0f, 3.0f, 6.0f,  7.0f,  8.0f, 9.0f, 2.0f, -2.0f, 4.0f, -4.0f,
                    8.0f, 5.0,  3.0,  1.0,  15.0f, 10.0f, 5.0f, 0.0f, 7.0f, -7.0,  1.0f, -1.0f};

    dim_t dimensions[] = {4, 6};

    af::array result = khiva::array::createArray(data, 2, dimensions, 200);

    float *calculated = (float *)malloc(24 * sizeof(float));
    khiva::array::getData(result, calculated);

    for (int i = 0; i < 24; i++) {
        ASSERT_EQ(calculated[i], data[i]);
    }

    free(calculated);

    ASSERT_EQ(static_cast<int>(khiva::dtype::f32), khiva::array::getType(result));
    af::dim4 dims = khiva::array::getDims(result);
    dim_t *calculatedDimensions = dims.get();

    ASSERT_EQ(2, dims.ndims());
    ASSERT_EQ(4, calculatedDimensions[0]);
    ASSERT_EQ(6, calculatedDimensions[1]);

    af_array arrayC = 0;
    af_retain_array(&arrayC, result.get());
    khiva::array::deleteArray(arrayC);
}

void arrayJoin() {
    float data1[] = {0.0f, 1.0f, 2.0f, 3.0f};

    dim_t dimensions[] = {4};

    af::array tss1 = khiva::array::createArray(data1, 1, dimensions, khiva::dtype::f32);

    float data2[] = {4.0f, 5.0f, 6.0f, 7.0f};

    af::array tss2 = khiva::array::createArray(data2, 1, dimensions, khiva::dtype::f32);

    af::array result = khiva::array::join(1, tss1, tss2);

    float *calculated = (float *)malloc(8 * sizeof(float));
    khiva::array::getData(result, calculated);

    for (int i = 0; i < 8; i++) {
        if (i < 4) {
            ASSERT_EQ(calculated[i], data1[i]);
        } else {
            ASSERT_EQ(calculated[i], data2[i - 4]);
        }
    }

    free(calculated);

    ASSERT_EQ(static_cast<int>(khiva::dtype::f32), khiva::array::getType(result));
    af::dim4 dims = khiva::array::getDims(result);
    dim_t *calculatedDimensions = dims.get();

    ASSERT_EQ(2, dims.ndims());
    ASSERT_EQ(4, calculatedDimensions[0]);
    ASSERT_EQ(2, calculatedDimensions[1]);

    af_array arrayC = 0;
    af_retain_array(&arrayC, result.get());
    khiva::array::deleteArray(arrayC);
}

KHIVA_TEST(ArrayTests, ArrayFloat, arrayFloat)
KHIVA_TEST(ArrayTests, ArrayComplexFloat, arrayComplexFloat)
KHIVA_TEST(ArrayTests, ArrayDouble, arrayDouble)
KHIVA_TEST(ArrayTests, ArrayComplexDouble, arrayComplexDouble)
KHIVA_TEST(ArrayTests, ArrayBoolean, arrayBoolean)
KHIVA_TEST(ArrayTests, ArrayInt, arrayInt)
KHIVA_TEST(ArrayTests, ArrayUnsignedInt, arrayUnsignedInt)
KHIVA_TEST(ArrayTests, ArrayUnsignedChar, arrayUnsignedChar)
KHIVA_TEST(ArrayTests, ArrayLong, arrayLong)
KHIVA_TEST(ArrayTests, ArrayUnsignedLong, arrayUnsignedLong)
KHIVA_TEST(ArrayTests, ArrayShort, arrayShort)
KHIVA_TEST(ArrayTests, ArrayUnsignedShort, arrayUnsignedShort)
KHIVA_TEST(ArrayTests, ArrayDefault, arrayDefault)
KHIVA_TEST(ArrayTests, ArrayJoin, arrayJoin)