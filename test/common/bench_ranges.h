#include <benchmark/benchmark.h>

constexpr auto level_1_max_N = (1 << 28);
constexpr auto level_2_max_N = (1 << 14);

template <typename T>
T round_down(T a, T b) {
  return (a / b) * b;
}

auto level_1_pow_2 = benchmark::CreateRange(1, level_1_max_N, 2);
auto level_1_pow_7 = benchmark::CreateRange(7, round_down(level_1_max_N, 7), 7);

enum BENCH_TYPES : int { level_1 = 0, level_2_eq = 1, level_2_sq = 2 };
