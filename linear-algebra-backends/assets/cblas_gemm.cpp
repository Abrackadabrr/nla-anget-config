#include <cblas.h>
#include <iostream>

int main() {
    // Row-major: A is 2x3, B is 3x2, C is 2x2.
    const int m = 2, n = 2, k = 3;
    const double A[m * k] = {1, 2, 3,
                             4, 5, 6};
    const double B[k * n] = {1, 2,
                             3, 4,
                             5, 6};
    double C[m * n] = {};

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, n, k,
                1.0,
                A, k,   // lda: physical row stride of A
                B, n,   // ldb: physical row stride of B
                0.0,
                C, n);  // ldc: physical row stride of C

    for (double v : C) std::cout << v << ' ';
    std::cout << '\n';
}
