#include <arrayfire.h>
#include <iostream>
#include <chrono>
#include <string>
#include <iostream>
#include <iomanip>

// std::string asString (const std::chrono::system_clock::time_point& tp)
// {
//      // convert to system time:
//      std::time_t t = std::chrono::system_clock::to_time_t(tp);
//      std::string ts = std::ctime(&t);// convert to calendar time
//      ts.resize(ts.size()-1);         // skip trailing newline
//      return ts;
// }

// template <typename C>
// void printClockData ()
// {
//     using namespace std;

//     cout << "- precision: ";
//     // if time unit is less or equal one millisecond
//     typedef typename C::period P;// type of time unit
//     if (ratio_less_equal<P,milli>::value) {
//        // convert to and print as milliseconds
//        typedef typename ratio_multiply<P,kilo>::type TT;
//        cout << fixed << double(TT::num)/TT::den << " milliseconds" << endl;
//     }
//     else {
//         // print as seconds
//         cout << fixed << double(P::num)/P::den << " seconds" << endl;
//     }
//     cout << "- is_steady: " << boolalpha << C::is_steady << endl;
// }

int main()
{

    /*
    Flatten image and weight to 1D.
    map the image pixels to a bin by dividing by the number of bins
    sort by key (key being the result from previous step, value being the weight)
    scan by key
    diff1 + af.where to get the indices
    index the out values from scan by key
*/

    af::setBackend(af::Backend::AF_BACKEND_CPU);

    long long keys[] = {10000, 10000, 10010, 10010, 10000, 10000, std::numeric_limits<long long>::max()};
    float data[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f,  std::numeric_limits<float>::quiet_NaN()};

    af::array k(7, keys);
    af::array v(7, data);

    af::array sortedKeys, sortedValues;
    af::sort(sortedKeys, sortedValues, k, v, 0, true);

    auto ones = af::constant(1, 7, v.type());

    af_print(sortedKeys);
    af_print(sortedValues);

    auto accAdd = af::scanByKey(sortedKeys, sortedValues, 0, af::binaryOp::AF_BINARY_ADD, true);
    auto accMin = af::scanByKey(sortedKeys, sortedValues, 0, af::binaryOp::AF_BINARY_MIN, true);
    auto accMax = af::scanByKey(sortedKeys, sortedValues, 0, af::binaryOp::AF_BINARY_MAX, true);
    auto accPowAdd = af::scanByKey(sortedKeys, sortedValues * sortedValues, 0, af::binaryOp::AF_BINARY_ADD, true);
    auto count = af::scanByKey(sortedKeys, ones, 0, af::binaryOp::AF_BINARY_ADD, true);
    auto extractIndices = af::where(af::diff1(sortedKeys));
    af_print(extractIndices);
    af_print(sortedKeys(extractIndices));
    af_print(accPowAdd(extractIndices));
    af_print(accMax(extractIndices));
    af_print(accMin(extractIndices));
    af_print(accAdd(extractIndices));
    af_print(count(extractIndices));
    // std::cout << "system_clock: " << std::endl;
    // printClockData<std::chrono::system_clock>();
    // std::cout << "\nhigh_resolution_clock: " << std::endl;
    // printClockData<std::chrono::high_resolution_clock>();
    // std::cout << "\nsteady_clock: " << std::endl;
    // printClockData<std::chrono::steady_clock>();

    // // print the epoch of this system clock:
    // std::chrono::system_clock::time_point tp;
    // std::cout << "epoch: " << asString(tp) << std::endl;

    // // print current time:
    // tp = std::chrono::system_clock::now();
    // std::cout << "now:   " << asString(tp) << std::endl;

    // // print minimum time of this system clock:
    // tp = std::chrono::system_clock::time_point::min();
    // std::cout << "min:   " << asString(tp) << std::endl;

    // // print maximum time of this system clock:
    // tp = std::chrono::system_clock::time_point::max();
    // std::cout << "max:   " << asString(tp) << std::endl;

    // af::setBackend(af::Backend::AF_BACKEND_OPENCL);

    // int keys[] = {10000, 10000, 10010, 10010, 10000, 10000};
    // float data[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
    // af::array k(6, 1, keys);
    // af::array v(6, 1, data);

    // af::array sortedKeys, sortedValues;
    // af::sort(sortedKeys, sortedValues, k, v, 0, true);

    // auto ones = af::constant(1, sortedKeys.dims(0), v.type());

    // auto sums = af::scanByKey(sortedKeys, sortedValues, 0, af::binaryOp::AF_BINARY_ADD);
    // auto counts = af::scanByKey()

    // auto vc = af::join(1, v, ones);
    // auto kk = af::join(1, k, k);

    //    af_print(kk);
    //    af_print(vc);
    //    af_print(af::scanByKey(kk, vc, 0, af::binaryOp::AF_BINARY_ADD, true));

    //     af::array input = af::randu(10, 1);
    //     af::array pos   = input.dims(0) * af::randu(10, 1);
    //     af::array out = af::approx1(input, pos, AF_INTERP_NEAREST);

    // af_print(input);
    // af_print(pos);
    // af_print(out);

    //     input = af::randu(1, 1, largeDim);
    //     pos   = input.dims(0) * af::randu(1, 1, largeDim);
    //     out   = af::approx1(input, pos, AF_INTERP_NEAREST);
    // af_print(input);
    // af_print(pos);
    // af_print(out);

    //     input = af::randu(1, 1, 1, largeDim);
    //     pos   = input.dims(0) * af::randu(1, 1, 1, largeDim);
    //     out   = af::approx1(input, pos, AF_INTERP_NEAREST);
    // af_print(input);
    // af_print(pos);
    // af_print(out);

    std::cout << "press a [enter] to end..." << std::endl;
    std::cin.get();

    return 0;
}