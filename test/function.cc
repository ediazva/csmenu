#include <benchmark/benchmark.h>
#include <functional>
#include <menu/function.hpp>

static void foo() {
   for(int i = 0; i < 10; ++i);
}

static void STDFunction_Lambda(benchmark::State& state) {
   for(auto _ : state) {
      auto bar = [&]() {};
      std::function f(bar);
      f();
   }
}

static void STDFunction_Function(benchmark::State& state) {
   for(auto _ : state) {
      std::function f{foo};
      f();
   }
}

static void MENUFunction_Lambda(benchmark::State& state) {
   for(auto _ : state) {
      auto bar = [&]() {};
      menu::Function<void()> f(bar);
      f();
   }
}

static void MENUFunction_Function(benchmark::State& state) {
   for(auto _ : state) {
      menu::Function<void()> f(foo);
      f();
   }
}

BENCHMARK(STDFunction_Lambda);
BENCHMARK(STDFunction_Function);
BENCHMARK(MENUFunction_Lambda);
BENCHMARK(MENUFunction_Function);
BENCHMARK_MAIN();