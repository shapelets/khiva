// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa.h>
#include <benchmark/benchmark.h>

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

template <af::Backend BE> void AbsoluteSumOfChanges(benchmark::State &state) {
  af::setBackend(BE);

  auto n = state.range(0);

  auto t = af::randu(n, f64);

  while (state.KeepRunning()) {
    auto asoc = tsa::features::absoluteSumOfChanges(t);
    asoc.eval();
    af::sync();
  }
  addMemoryCounters(state);
}

BENCHMARK_TEMPLATE(AbsoluteSumOfChanges, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(AbsoluteSumOfChanges, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_MAIN();