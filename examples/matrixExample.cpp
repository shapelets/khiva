// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva.h>
#include <../src/khiva/vector.h>

#include <vector>
#include <numeric>

void stompIgnoreTrivialOneSeries() {
    float data[] = {10, 10, 11, 11, 10, 11, 10, 10, 11, 11, 10, 11, 10, 10};
    af::array tss = af::array(14, data);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(tss, m, distance, index);

    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[12];
    index.host(&resultingIndex);
}

void stompIgnoreTrivialMultipleSeries() {
    float data[] = {10, 10, 11, 11, 10, 11, 10, 10, 11, 11, 10, 11, 10, 10,
                    11, 10, 10, 11, 10, 11, 11, 10, 11, 11, 10, 10, 11, 10};
    af::array tss = af::array(14, 2, data);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(tss, m, distance, index);

    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[24];
    index.host(&resultingIndex);
}

void stompConsiderTrivialOneSeries() {
    float data[] = {10, 10, 11, 11, 10, 11, 10, 10};
    af::array t = af::array(8, data);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(t, t, m, distance, index);

    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[6];
    index.host(&resultingIndex);
}

void stompConsiderTrivialMultipleSeries() {
    float dataA[] = {10, 10, 11, 11, 10, 11, 10, 10, 10, 10, 11, 11, 10, 11, 10, 10, 11, 10, 10, 11, 10, 11, 11, 10};
    af::array ta = af::array(8, 3, dataA);

    float dataB[] = {10, 10, 11, 11, 10, 11, 10, 10, 11, 10, 10, 11, 10, 11, 11, 10};
    af::array tb = af::array(8, 2, dataB);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(ta, tb, m, distance, index);

    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[36];
    index.host(&resultingIndex);
}

#include <khiva/library.h>

int main() {
	{
		auto ta = khiva::vector::createArray({ 10, 10, 11, 11, 10, 11, 10, 10, 20, 12, 34, 41, 0, 11, 20, 20, 31, 20, 10, 1, 110, 211, 11, 10 },
											 8, 1); 
											 //8, 2); 
		long m = 3;

		af::array distance;
		af::array index;

		khiva::matrix::stomp(ta, m, distance, index);
		af_print(distance);
		af_print(index);
	}
	{
		auto ta = khiva::vector::createArray({ 10, 10, 11, 11, 10, 11, 10, 10, 20, 12, 34, 41, 0, 11, 20, 20, 31, 20, 10, 1, 110, 211, 11, 10 },
											 8, 1); 
											 //8, 2); 
		long m = 3;

		af::array distance;
		af::array index;

		khiva::matrix::matrixProfile(ta, m, distance, index);
		af_print(distance);
		af_print(index);
	}

	//af::array a = khiva::vector::createArray<int>({1, 2, 3, 4});

	//std::cout << "Vector \n";
	//{
	//	khiva::library::setBackend(khiva::library::Backend::KHIVA_BACKEND_OPENCL);
	//	auto a = af::randu(1000000);
	//	auto vect = khiva::vector::get<float>(a);
	//	std::cout << "Size:" << vect.size() << "\n"; 
	//}
	//std::cout << "END\n";

    return 0;
}

