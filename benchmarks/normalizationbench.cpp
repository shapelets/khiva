// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <benchmark/benchmark.h>
#include <set>
#include <vector>
#include <arrayfire.h>
#include <tsa.h>
#include <float.h>

template<af::Backend BE> void ZNorm(benchmark::State& state) {
  af::setBackend(BE);

  auto n = state.range(0);
  auto ts = af::randu(n);
  while (state.KeepRunning()) {
    auto normalised = tsa::normalization::znorm(ts, DBL_MIN);
    normalised.eval();
    af::sync();
  }
}

template<af::Backend BE> void ZNormInPlace(benchmark::State& state) {
  af::setBackend(BE);

  auto n = state.range(0);
  auto ts = af::randu(n);
  while (state.KeepRunning()) {
    tsa::normalization::znormInPlace(ts, DBL_MIN);
    ts.eval();
    af::sync();
  }
}

BENCHMARK_TEMPLATE(ZNorm, af::Backend::AF_BACKEND_OPENCL)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(ZNorm, af::Backend::AF_BACKEND_CPU)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(ZNormInPlace, af::Backend::AF_BACKEND_OPENCL)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(ZNormInPlace, af::Backend::AF_BACKEND_CPU)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_MAIN();
