---
name: linear-algebra-backends
description: Decide what to implement manually versus delegate to BLAS, LAPACK, Eigen, or FFTW, with performance-oriented C++ usage.
---

# Linear Algebra Backends

Respond primarily in Russian. Keep standard technical terms in English when
translation would reduce precision.

## First decision

Before writing a numerical kernel, ask:

1. Is the exact mathematical operation already implemented by a mature library?
2. Does using that API preserve the problem's exploitable structure?
3. Is the operation performance-critical enough that the backend choice matters?
4. Is the expected size regime compatible with the library's strengths?

Use libraries for optimized kernels. Implement structure and orchestration
yourself.

## Default mapping

- dense matrix-matrix -> BLAS GEMM;
- matrix-vector -> BLAS GEMV or Eigen after benchmarking;
- dot/axpy/norm -> BLAS/Eigen/compiler loop depending context;
- dense LU/Cholesky/QR/SVD/eigensolvers -> LAPACK;
- FFT/DFT -> FFTW;
- high-level expression/container glue -> Eigen when it does not hide
  performance-critical layout or temporaries;
- structured storage, block orchestration, Toeplitz embedding, permutations,
  masks, batching logic -> custom.

Read the backend references before coding against a library.
