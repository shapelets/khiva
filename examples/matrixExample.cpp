// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <../src/khiva/vectorUtil.h>
#include <../src/khiva/matrixInternal.h>
#include <arrayfire.h>
#include <khiva.h>

#include <iterator>
#include <numeric>
#include <vector>

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
    auto ta = af::randu(16, 3);
    //    auto ta = khiva::vector::createArray(
    //{-0.9247, 0.1808, 2.5441, 0.3516,-0.3452, 0.2191,-0.7687, 0.2413,-1.1948, 0.8927,-0.5378, 0.2270, 0.9354,-0.7613,
    // 0.5787,-0.6174, 0.5889, 0.7897,-0.0645, 0.9520,-1.1411, 0.8281,
    // -0.7363, -0.7446, -0.8415,  1.2991,  0.0883,  0.6588, -0.2788,  1.4143, -1.1650, -0.6629, -0.5807, -0.1699,
    // -0.7265, -0.1506, -0.2785, -0.0063,  0.4021,  1.3925, -0.2417,  0.1139, -1.6279,  0.1488}
    //, 									16, 2);

    //     auto tb = khiva::vector::createArray({0.2512, 0.6436,-2.3651,-0.7734,-0.0511, 1.6693, 1.9453,-1.9047,
    //     0.8149,-0.1831,-0.1542,-1.3490,
    // 1.2285,-1.0472, 0.3911,-0.0637,-1.2594,-2.2675, 0.7161,-2.5572, 0.7361, 0.1402,-0.0910, 0.3245,
    //-1.0920, 0.8766, 1.2113,-0.0861,-0.4919,-1.3485,-1.3932, 1.1820, 0.2298, 0.6310,-0.9343,-1.9329},
    //    									8, 2);
    af_print(ta);

    long m = 6;

    {
        af::array distance;
        af::array index;

        khiva::matrix::stomp(ta, m, distance, index);
        af_print(distance);
        af_print(index);
    }

    {
        af::array distance;
        af::array index;

        khiva::matrix::matrixProfile(ta, m, distance, index);
        af_print(distance);
        af_print(index);
    }
}
#include <fstream>
void printProfile(af::array distances, af::array indexes, const std::string &fileName) {
    std::ofstream ofs(fileName, std::ofstream::out);
    auto distVect = khiva::vectorutil::get<double>(distances);
    auto indexVect = khiva::vectorutil::get<unsigned int>(indexes);
    for (int i = 0; i < distances.dims(0); i++) {
        ofs << distVect[i] << ";" << indexVect[i] << "\n";
    }
}

void testLeftRight() {
    khiva::library::setBackend(khiva::library::Backend::KHIVA_BACKEND_CPU);
    int n = 128;
    int m = 12;
    auto ta = khiva::vectorutil::createArray(
        {-92.4662,  18.0826,   254.4097,  35.1582,   -34.5167,  21.9123,   -76.8666,  24.1255,   -119.4840, 89.2692,
         -53.7780,  22.6983,   93.5360,   -76.1285,  57.8707,   -61.7367,  58.8945,   78.9682,   -6.4519,   95.2034,
         -114.1063, 82.8133,   -73.6341,  -74.4575,  -84.1459,  129.9067,  8.8310,    65.8802,   -27.8835,  141.4345,
         -116.4987, -66.2915,  -58.0665,  -16.9934,  -72.6471,  -15.0601,  -27.8524,  -0.6336,   40.2054,   139.2524,
         -24.1727,  11.3927,   -162.7895, 14.8781,   25.1250,   64.3562,   -236.5118, -77.3420,  -5.1106,   166.9285,
         194.5296,  -190.4659, 81.4878,   -18.3076,  -15.4175,  -134.8966, 122.8539,  -104.7209, 39.1123,   -6.3669,
         -125.9402, -226.7495, 71.6115,   -255.7238, 73.6051,   14.0193,   -9.0993,   32.4544,   -109.1953, 87.6599,
         121.1325,  -8.6135,   -49.1869,  -134.8533, -139.3240, 118.1974,  22.9832,   63.0970,   -93.4303,  -193.2919,
         -43.6712,  -4.2870,   -93.5555,  -86.3817,  -26.6190,  94.3234,   -100.8066, 70.5622,   75.9013,   36.3536,
         -138.5388, 72.8221,   -145.1508, 73.7886,   -1.6499,   24.0054,   113.4099,  7.9198,    77.7093,   33.7550,
         -68.3262,  -126.4960, 120.4121,  -181.5796, -110.4838, 88.8343,   -256.1250, 3.1551,    125.7766,  -76.7836,
         0.5753,    -25.1363,  49.2497,   -74.0528,  -100.8634, -56.5037,  -75.5141,  -7.2044,   -51.6655,  -116.6414,
         182.3497,  -152.1112, 150.9720,  77.0329,   58.4420,   50.0252,   -36.1718,  -55.2495},
        n);

	//int n = 69875;
	//int m = 128;

	//auto ta = af::randn(n);

 //   {
 //       std::ofstream ofs("WholeInfo.csv", std::ofstream::out);
 //       for (int j = 0; j < n - m + 1; ++j) {
 //           for (int i = 0; i < n - m + 1; ++i) {
 //               auto input =
 //                   af::join(1, ta(af::seq(m) + static_cast<double>(j)), ta(af::seq(m) + static_cast<double>(i)));
 //               auto znormed = khiva::normalization::znorm(input);
 //               auto res = khiva::distances::euclidean(znormed);
 //               ofs << j << ";" << i << ";" << res(0, 1).scalar<double>() << "\n";
 //           }
 //       }
 //       ofs.close();
 //   }

 //   {
 //       std::ofstream ofs("WholeInfoMatrix.csv", std::ofstream::out);
 //       for (int j = 0; j < n - m + 1; ++j) {
 //           for (int i = 0; i < n - m + 1; ++i) {
 //               auto input =
 //                   af::join(1, ta(af::seq(m) + static_cast<double>(j)), ta(af::seq(m) + static_cast<double>(i)));
 //               auto znormed = khiva::normalization::znorm(input);
 //               auto res = khiva::distances::euclidean(znormed);
 //               ofs << res(0, 1).scalar<double>() << ";";
 //           }
	//		ofs << "\n";
 //       }
 //       ofs.close();
 //   }

 //   af::array distances;
 //   af::array indexes;
 //   khiva::matrix::matrixProfile(ta, m, distances, indexes);
 //   //printProfile(distances, indexes, "profile.csv");
 //   af_print(distances);
 //   af_print(indexes);

	////af_print(ta);

	af::array chains;
    khiva::matrix::getChains(ta, m, chains);
	auto chainValues = khiva::vectorutil::get<unsigned int>(chains(af::span, 0, 0));
	auto chainIndexes = khiva::vectorutil::get<unsigned int>(chains(af::span, 1, 0));
	int i = 0;
	while(chainIndexes[i] < 12) {
		std::cout << chainIndexes[i] << ";" << chainValues[i] << "\n";
		i++;
	}
}


int main() {
    testLeftRight();

    // testMultiple();
    // auto ta1 = af::randu(32);
    // auto ta2 = af::randu(32);
    // auto ta = af::join(1, ta1, ta2);
    //{

    //	//auto ta = khiva::vectorutil::createArray({   -0.9247, 0.1808, 2.5441, 0.3516, -0.3452, 0.2191, -0.7687, 0.2413,
    //-1.1948, 0.8927, -0.5378, 0.2270, 0.9354, -0.7613, 0.5787, -0.6174, 0.5889, 0.7897, -0.0645, 0.9520, -1.1411,
    // 0.8281, -0.7363, -0.7446, -0.8415, 1.2991, 0.0883, 0.6588, -0.2788, 1.4143, -1.1650, -0.6629},
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
    //	//auto ta = khiva::vector::createArray({   -0.9247, 0.1808, 2.5441, 0.3516, -0.3452, 0.2191, -0.7687, 0.2413,
    //-1.1948, 0.8927, -0.5378, 0.2270, 0.9354, -0.7613, 0.5787, -0.6174, 0.5889, 0.7897, -0.0645, 0.9520, -1.1411,
    // 0.8281, -0.7363, -0.7446, -0.8415, 1.2991, 0.0883, 0.6588, -0.2788, 1.4143, -1.1650, -0.6629},
    //	//									 32, 1);
    //	//									 //8, 2);
    //	long m = 7;

    //	af::array distance;
    //	af::array index;

    //	khiva::matrix::matrixProfile(ta, m, distance, index);
    //	af_print(distance);
    //	af_print(index);
    //}

    return 0;
}
