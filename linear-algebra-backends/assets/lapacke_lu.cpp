#include <lapacke.h>
#include <cmath>
#include <iostream>

int main() {
    constexpr lapack_int n = 2;
    // Row-major A = [[4,1],[2,3]].
    double A[n * n] = {4.0, 1.0,
                       2.0, 3.0};
    lapack_int ipiv[n];

    lapack_int info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR, n, n, A, n, ipiv);
    if (info != 0) {
        std::cerr << "dgetrf info=" << info << '\n';
        return 1;
    }

    double b[n] = {1.0, 1.0};
    info = LAPACKE_dgetrs(LAPACK_ROW_MAJOR, 'N', n, 1, A, n, ipiv, b, 1);
    if (info != 0) {
        std::cerr << "dgetrs info=" << info << '\n';
        return 1;
    }

    // Expected x=(0.2,0.2).
    std::cout << b[0] << ' ' << b[1] << '\n';
    return (std::abs(b[0] - 0.2) + std::abs(b[1] - 0.2) < 1e-12) ? 0 : 2;
}
