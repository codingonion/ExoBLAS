#include <cblas.h>
#include <math.h>

#include <vector>

#include "correctness_helpers.h"
#include "exo_snrm2.h"
#include "generate_buffer.h"

void test_snrm2(int N, int incX) {
  printf("Running snrm2 test: N = %d, incX = %d\n", N, incX);
  auto X = AlignedBuffer<float>(N, incX);
  auto X_expected = X;

  auto result = exo_snrm2(N, X.data(), incX);
  auto expected = cblas_snrm2(N, X_expected.data(), incX);

  auto epsilon = 1.f / 100.f;

  if (!check_relative_error_okay(result, expected, epsilon)) {
    printf("Failed! Expected %f, got %f\n", expected, result);
    exit(1);
  }
  printf("Passed!\n");
}

int main() {
  std::vector<int> N{1, 2, 8, 100, 64 * 64 * 64, 1000000};
  std::vector<int> inc{2, 3, 5};

  for (auto n : N) {
    test_snrm2(n, 1);
  }

  for (auto n : N) {
    for (auto i : inc) {
      test_snrm2(n, i);
    }
  }
}
