#include <fftw3.h>
#include <cmath>
#include <iostream>

int main() {
    constexpr int n = 8;
    constexpr int howmany = 3;

    auto* in = fftw_alloc_complex(n * howmany);
    auto* out = fftw_alloc_complex(n * howmany);

    for (int b = 0; b < howmany; ++b) {
        for (int i = 0; i < n; ++i) {
            in[b * n + i][0] = (b + 1) * (i + 1);
            in[b * n + i][1] = 0.0;
        }
    }

    int dims[1] = {n};
    // Three contiguous transforms; stride=1, distance=n.
    fftw_plan p = fftw_plan_many_dft(
        1, dims, howmany,
        in, nullptr, 1, n,
        out, nullptr, 1, n,
        FFTW_FORWARD, FFTW_ESTIMATE);

    if (!p) return 1;
    fftw_execute(p);

    std::cout << "first DC = " << out[0][0] << " + i " << out[0][1] << '\n';

    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);
}
