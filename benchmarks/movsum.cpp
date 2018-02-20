#include <benchmark/benchmark.h>
#include <set>
#include <vector>
#include <arrayfire.h>

static void MovingSumConvolve(benchmark::State& state) {
  af::setBackend(af::Backend::AF_BACKEND_OPENCL);
  af::array ts = af::randu(state.range(0));
  auto m = state.range(1);
  af::array filter = af::constant(1, m);
  while (state.KeepRunning()) {
    af::array cumSum = af::convolve(ts, filter, AF_CONV_EXPAND);
  }
  af::sync();
}

// Register the function as a benchmark
BENCHMARK(MovingSumConvolve)->Ranges({{16<<10, 132<<10}, {512, 512}});
BENCHMARK_MAIN();
