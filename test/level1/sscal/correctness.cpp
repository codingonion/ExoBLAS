#include <vector>

#include <cblas.h>

#include "generate_buffer.h"
#include "correctness_helpers.h"

#include "exo_sscal.h"

void test_sscal(int N, float alpha, int incX) {
    printf("Running sscal test: N = %d, alpha = %f, incX = %d\n", N, alpha, incX);
    auto x = generate1d_sbuffer(N, incX);
    auto x_expected = x;

    exo_sscal(N, alpha, x.data(), incX);
    cblas_sscal(N, alpha, x_expected.data(), incX);

    for (int i = 0; i < x.size(); ++i) {
        if (!check_relative_error_okay(x[i], x_expected[i], 1.f / 10000.f)) {
            printf("Failed ! memory offset = %d, expected %f, got %f\n", i, x_expected[i], x[i]);
            exit(1);
        }
    }

    printf("Passed!\n");
}

int main () {
    std::vector<int> N {1, 2, 8, 100, 64 * 64 * 64, 10000000};
    std::vector<float> alphas {0, 1, 2, -3, 3.14};
    std::vector<std::tuple<float, int> > params {{1.2, 2}, {2.5, 3}, {0, -1},
                                                 {1, 4}, {1.3, 10}, {4.5, -2}};

    for (auto n : N) {
        for (auto alpha : alphas) {
            test_sscal(n, alpha, 1);
        }
    }
    
    for (auto n : N) {
        for (auto i : params) {
            test_sscal(n, std::get<0>(i), std::get<1>(i));
        }
    }
}
