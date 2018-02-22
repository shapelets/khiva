// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <benchmark/benchmark.h>
#include <set>
#include <vector>
#include <arrayfire.h>

template<af::Backend BE> void ManualFFT(benchmark::State& state) {
  af::setBackend(BE);

  auto n = state.range(0);
  auto m = state.range(1);

  auto ts = af::randu(n);
  auto q = af::randu(m);
  auto ta = af::constant(0, 2*n, ts.type());
  auto qra = af::constant(0, 2*n, q.type());
  while (state.KeepRunning()) {
    ta(af::seq(0, n-1)) = ts;
    qra(af::seq(0, m-1)) = af::flip(q, 0);
    auto qraf = af::fft(qra);
    auto raf = af::fft(ta);
    auto prod = qraf * raf;
    af::ifft(prod).eval();
  }
  af::sync();
}

template<af::Backend BE> void ExpansionFFT(benchmark::State& state) {
  af::setBackend(BE);

  auto n = state.range(0);
  auto m = state.range(1);

  auto ts = af::randu(n);
  auto q = af::randu(m);
  auto qr = af::flip(q, 0);
  while (state.KeepRunning()) {
    auto qraf = af::fft(qr, 2*n);
    auto raf = af::fft(ts, 2*n);
    auto prod = qraf * raf;
    af::ifft(prod).eval();
  }
  af::sync();
}

template<af::Backend BE> void ConvolveOp(benchmark::State& state) {
  af::setBackend(BE);
  auto n = state.range(0);
  auto m = state.range(1);

  auto ts = af::randu(n);
  auto q = af::randu(m);

  while (state.KeepRunning()) {
    convolve(ts, flip(q, 0), AF_CONV_EXPAND).eval();
  }
  af::sync();
}


BENCHMARK_TEMPLATE(ConvolveOp, af::Backend::AF_BACKEND_OPENCL)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}, {64, 1<<10}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(ConvolveOp, af::Backend::AF_BACKEND_CPU)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}, {64, 1<<10}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(ExpansionFFT, af::Backend::AF_BACKEND_OPENCL)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}, {64, 1<<10}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(ExpansionFFT, af::Backend::AF_BACKEND_CPU)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}, {64, 1<<10}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

  BENCHMARK_TEMPLATE(ManualFFT, af::Backend::AF_BACKEND_OPENCL)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}, {64, 1<<10}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(ManualFFT, af::Backend::AF_BACKEND_CPU)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}, {64, 1<<10}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);
  

BENCHMARK_MAIN();
