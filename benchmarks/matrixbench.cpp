// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <benchmark/benchmark.h>
#include <tsa.h>

void addMemoryCounters(benchmark::State &state) {
  size_t bytes, buffers, lockedBytes, lockedBuffers;
  //This is already doing an af::sync();
  af::deviceMemInfo(&bytes, &buffers, &lockedBytes, &lockedBuffers);

  state.counters["Memory"] = bytes;
  state.counters["Buffers"] = buffers;
  state.counters["LockedMemory"] = lockedBytes;
  state.counters["LockedBuffers"] = lockedBuffers;

  af::deviceGC();
}

template <af::Backend BE> void SlidingDotProduct(benchmark::State &state) {
  af::setBackend(BE);

  auto n = state.range(0);
  auto m = state.range(1);

  auto t = af::randu(n, f64);
  auto q = t(seq(0, m));
  while (state.KeepRunning()) {
    auto sdp = tsa::matrix::slidingDotProduct(q, t);
    sdp.eval();
  }
  addMemoryCounters(state);
}

template <af::Backend BE> void SlidingDotProductParallel(benchmark::State &state) {
  af::setBackend(BE);

  auto n = state.range(0);
  auto m = state.range(1);

  auto t = af::randu(n, f64);

  auto indices = af::range(n - m);
  auto input = af::array(m, n - m, t.type());

  for (int i = 0; i < m; i++)
  {
    input(i, span, span, span) = t(seq(i, n - m - 1 + i));
  }

  while (state.KeepRunning())
  {
    gfor(seq idx, n - m)
    {
      auto sdp = tsa::matrix::slidingDotProduct(input(span, idx, span, span), t);
      sdp.eval();
    }
  }
  addMemoryCounters(state);
}

template <af::Backend BE> void MeanStdevAuxiliary(benchmark::State &state) {
  af::setBackend(BE);

  auto n = state.range(0);
  auto m = state.range(1);

  auto t = af::randu(n, f64);
  af::array a;
  auto q = t(seq(0, m));
  af::array mean;
  af::array stdev;
  while (state.KeepRunning())
  {
    tsa::matrix::meanStdev(t, &a, m, &mean, &stdev);
    mean.eval();
    stdev.eval();
  }
  addMemoryCounters(state);
}

template <af::Backend BE> void MeanStdev(benchmark::State &state) {
  af::setBackend(BE);

  auto n = state.range(0);
  auto m = state.range(1);

  auto t = af::randu(n, f64);
  af::array a;
  auto q = t(seq(0, m));
  af::array mean;
  af::array stdev;
  while (state.KeepRunning())
  {
    tsa::matrix::meanStdev(t, &a, m, &mean, &stdev);
    mean.eval();
    stdev.eval();
  }
  addMemoryCounters(state);
}

template <af::Backend BE> void CalculateDistanceProfile(benchmark::State &state) {
  af::setBackend(BE);

  auto n = state.range(0);
  auto m = state.range(1);

  auto t = af::randu(n, f64);
  af::array a;
  auto q = t(seq(0, m - 1));
  af::array mean;
  af::array stdev;

  tsa::matrix::meanStdev(t, &a, m, &mean, &stdev);

  auto qt = tsa::matrix::slidingDotProduct(q, t);

  auto sumQ = sum(q);
  auto sumQ2 = sum(pow(q, 2));

  af::array distance;
  af::array index;

  while (state.KeepRunning())
  {
    tsa::matrix::calculateDistanceProfile(qt, a, sumQ, sumQ2, mean, stdev, &distance, &index);
    distance.eval();
    index.eval();
  }
  addMemoryCounters(state);
}

template <af::Backend BE> void CalculateDistanceProfileParallel(benchmark::State &state) {
  af::setBackend(BE);

  auto n = state.range(0);
  auto m = state.range(1);

  auto t = af::randu(n, f64);
  af::array a;
  af::array mean;
  af::array stdev;

  tsa::matrix::meanStdev(t, &a, m, &mean, &stdev);

  auto indices = af::range(n - m);
  auto input = af::array(m, n - m, t.type());

  for (int i = 0; i < m; i++)
  {
    input(i, span, span, span) = t(seq(i, n - m - 1 + i));
  }

  af::array distance;
  af::array index;

  while (state.KeepRunning())
  {
    gfor(seq idx, n - m)
    {
      auto q = input(span, idx, span, span);
      auto sumQ = sum(q);
      auto sumQ2 = sum(pow(q, 2));
      auto qt = tsa::matrix::slidingDotProduct(q, t);
      tsa::matrix::calculateDistanceProfile(qt, a, sumQ, sumQ2, mean, stdev, &distance, &index);
      distance.eval();
      index.eval();
    } 
  }
  addMemoryCounters(state);
}

template <af::Backend BE> void Mass(benchmark::State &state) {
  af::setBackend(BE);

  auto n = state.range(0);
  auto m = state.range(1);

  auto t = af::randu(n, f64);
  auto q = t(af::seq(0, m - 1));

  af::array distance;
  af::array index;
  af::array aux;
  af::array mean;
  af::array stdev;

  tsa::matrix::meanStdev(t, &aux, m, &mean, &stdev);
  
  while (state.KeepRunning())
  {
    tsa::matrix::mass(q, t, aux, mean, stdev, &distance, &index);
    distance.eval();
    index.eval();
  }

  addMemoryCounters(state);
}

template <af::Backend BE> void Stamp(benchmark::State &state) {
  af::setBackend(BE);

  auto n = state.range(0);
  auto m = state.range(1);

  auto ta = af::randu(n, f64);
  auto tb = af::randu(n, f64);

  af::array profile;
  af::array index;
  
  while (state.KeepRunning())
  {
    tsa::matrix::stamp(ta, tb, m, &profile, &index);
    profile.eval();
    index.eval();
  }

  addMemoryCounters(state);
}

BENCHMARK_TEMPLATE(SlidingDotProduct, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(8)
    ->Ranges({{1 << 10, 128 << 10}, {16, 512}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(SlidingDotProduct, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(8)
    ->Ranges({{1 << 10, 128 << 10}, {16, 512}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(SlidingDotProductParallel, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 8 << 10}, {16, 512}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(SlidingDotProductParallel, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 8 << 10}, {16, 512}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(MeanStdevAuxiliary, af::Backend::AF_BACKEND_OPENCL)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}, {16, 512}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(MeanStdevAuxiliary, af::Backend::AF_BACKEND_CPU)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}, {16, 512}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(MeanStdev, af::Backend::AF_BACKEND_OPENCL)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}, {16, 512}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(MeanStdev, af::Backend::AF_BACKEND_CPU)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}, {16, 512}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(CalculateDistanceProfile, af::Backend::AF_BACKEND_OPENCL)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}, {16, 512}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(CalculateDistanceProfile, af::Backend::AF_BACKEND_CPU)
  ->RangeMultiplier(8)
  ->Ranges({{1<<10, 32<<10}, {16, 512}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(CalculateDistanceProfileParallel, af::Backend::AF_BACKEND_OPENCL)
  ->RangeMultiplier(2)
  ->Ranges({{1<<10, 4<<10}, {16, 512}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(CalculateDistanceProfileParallel, af::Backend::AF_BACKEND_CPU)
  ->RangeMultiplier(2)
  ->Ranges({{1<<10, 4<<10}, {16, 512}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(Mass, af::Backend::AF_BACKEND_OPENCL)
  ->RangeMultiplier(2)
  ->Ranges({{1<<10, 4<<10}, {16, 512}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(Mass, af::Backend::AF_BACKEND_CPU)
  ->RangeMultiplier(2)
  ->Ranges({{1<<10, 4<<10}, {16, 512}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(Stamp, af::Backend::AF_BACKEND_OPENCL)
  ->RangeMultiplier(2)
  ->Ranges({{1<<10, 8<<10}, {16, 512}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(Stamp, af::Backend::AF_BACKEND_CPU)
  ->RangeMultiplier(2)
  ->Ranges({{1<<10, 8<<10}, {16, 512}})
  ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_MAIN();