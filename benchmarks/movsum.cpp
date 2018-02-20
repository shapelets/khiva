// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <benchmark/benchmark.h>
#include <set>
#include <vector>
#include <arrayfire.h>

template<af::Backend BE> void MovingSumConvolve(benchmark::State& state) {
  af::setBackend(BE);
  auto tsLen = state.range(0);
  auto m = state.range(1);

  af::array ts = af::randu(tsLen);
  af::array filter = af::constant(1, m);

  while (state.KeepRunning()) {
    af::array movSum = af::convolve(ts, filter, AF_CONV_EXPAND);
    benchmark::DoNotOptimize(movSum(af::seq(m-1, tsLen-1)));
  }
  af::sync();
}

template<af::Backend BE> void MovingSumScan(benchmark::State& state) {
  af::setBackend(BE);
  auto tsLen = state.range(0);
  auto m = state.range(1);
  af::array ts = af::randu(tsLen);
  while (state.KeepRunning()) {
    af::array cumsum = af::accum(ts);
    af::array exCumsum = af::scan(ts, 0, AF_BINARY_ADD, false);
    benchmark::DoNotOptimize(
      cumsum(af::seq(m - 1, tsLen - 1)) - exCumsum(af::seq(0, tsLen - m))
    );
  }
  af::sync();
}


// Register the function as a benchmark
BENCHMARK_TEMPLATE(MovingSumConvolve, af::Backend::AF_BACKEND_OPENCL)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}, {64, 512}});

BENCHMARK_TEMPLATE(MovingSumConvolve, af::Backend::AF_BACKEND_CPU)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}, {64, 512}});

BENCHMARK_TEMPLATE(MovingSumScan, af::Backend::AF_BACKEND_OPENCL)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}, {64, 512}});

BENCHMARK_TEMPLATE(MovingSumScan, af::Backend::AF_BACKEND_CPU)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}, {64, 512}});

BENCHMARK_MAIN();
