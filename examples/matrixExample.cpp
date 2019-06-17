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
void testMultiple() {
	//auto ta = khiva::vector::createArray({10, 10, 11, 11, 10, 11, 10, 10, 10, 10, 11, 11, 10, 11, 10, 10, 11, 10, 10, 11, 10, 11, 11, 10},
	//									8, 3);

	//auto tb = khiva::vector::createArray({10, 10, 11, 11, 10, 11, 10, 10, 11, 10, 10, 11, 10, 11, 11, 10},
	//									8, 2); 

	auto ta = af::randn(22, 2);
	auto tb = af::randn(12, 3);

    long m = 3;

	{
		af::array distance;
		af::array index;

		khiva::matrix::stomp(ta, tb, m, distance, index);
		af_print(distance);
		af_print(index);
	}

	{
		af::array distance;
		af::array index;

		khiva::matrix::matrixProfile(ta, tb, m, distance, index);
		af_print(distance);
		af_print(index);
	}
}

void testMass() {
	auto ta = af::randn(22);
	auto q = af::randn(12);

	{
		af::array distances;
		khiva::matrix::mass(q, ta, distances);
		af_print(distances);
	}

	{
		af::array distances;
		af::array indexes;
		khiva::matrix::matrixProfile(q, ta, q.dims(0), distances, indexes);
		af_print(distances);
	}
	
}

int main() {
	//testMultiple();
	testMass();
	//auto ta1 = af::randu(32);
	//auto ta2 = af::randu(32);
	//auto ta = af::join(1, ta1, ta2);
	//{

	//	//auto ta = khiva::vector::createArray({   -0.9247, 0.1808, 2.5441, 0.3516, -0.3452, 0.2191, -0.7687, 0.2413, -1.1948, 0.8927, -0.5378, 0.2270, 0.9354, -0.7613, 0.5787, -0.6174, 0.5889, 0.7897, -0.0645, 0.9520, -1.1411, 0.8281, -0.7363, -0.7446, -0.8415, 1.2991, 0.0883, 0.6588, -0.2788, 1.4143, -1.1650, -0.6629},
	//	//									 32, 1); 
	//	//									 //8, 2); 
	//	long m = 7;

	//	af::array distance;
	//	af::array index;

	//	khiva::matrix::stomp(ta, m, distance, index);
	//	af_print(distance);
	//	af_print(index);
	//}
	//{
	//	//auto ta = khiva::vector::createArray({   -0.9247, 0.1808, 2.5441, 0.3516, -0.3452, 0.2191, -0.7687, 0.2413, -1.1948, 0.8927, -0.5378, 0.2270, 0.9354, -0.7613, 0.5787, -0.6174, 0.5889, 0.7897, -0.0645, 0.9520, -1.1411, 0.8281, -0.7363, -0.7446, -0.8415, 1.2991, 0.0883, 0.6588, -0.2788, 1.4143, -1.1650, -0.6629},
	//	//									 32, 1); 
	//	//									 //8, 2); 
	//	long m = 7;

	//	af::array distance;
	//	af::array index;

	//	khiva::matrix::matrixProfile(ta, m, distance, index);
	//	af_print(distance);
	//	af_print(index);
	//}

	////{
	////
	////	int n = 32;
	////	int m = 7;
	////	auto ta = khiva::vector::createArray({   -0.9247, 0.1808, 2.5441, 0.3516, -0.3452, 0.2191, -0.7687, 0.2413, -1.1948, 0.8927, -0.5378, 0.2270, 0.9354, -0.7613, 0.5787, -0.6174, 0.5889, 0.7897, -0.0645, 0.9520, -1.1411, 0.8281, -0.7363, -0.7446, -0.8415, 1.2991, 0.0883, 0.6588, -0.2788, 1.4143, -1.1650, -0.6629},
	////										 n, 1); 
	////	for (int j = 0; j < n - m + 1; ++j) {
	////		std::cout << "INDEX: " << j << "\n";
	////		for (int i = 0; i < n - m + 1; ++i) {
	////			auto input = af::join(1, ta(af::seq(7) + static_cast<double>(j)), ta(af::seq(7) + static_cast<double>(i)));
	////			auto znormed = khiva::normalization::znorm(input);
	////			auto res = khiva::distances::euclidean(znormed);
	////			std::cout << "dist[" << i << "]: " << res(0, 1).scalar<double>() << "\n";
	////		}
	////	}
	////
	////}

	////af::array a = khiva::vector::createArray<int>({1, 2, 3, 4});

	////std::cout << "Vector \n";
	////{
	////	khiva::library::setBackend(khiva::library::Backend::KHIVA_BACKEND_OPENCL);
	////	auto a = af::randu(1000000);
	////	auto vect = khiva::vector::get<float>(a);
	////	std::cout << "Size:" << vect.size() << "\n"; 
	////}
	////std::cout << "END\n";

    return 0;
}

