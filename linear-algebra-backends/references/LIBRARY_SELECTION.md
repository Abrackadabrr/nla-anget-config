# Library or Custom Implementation?

## Use a library when

The operation is a standard numerical kernel with a mature optimized
implementation and your data can be presented without destroying the relevant
structure.

Examples: GEMM, triangular solve, LU, QR, SVD, FFT.

## Implement it yourself when

The missing part is not the inner numerical kernel but the algorithmic
structure:

- block or multilevel Toeplitz indexing;
- circulant embedding;
- low-rank/block composition;
- mixed dense/Toeplitz/diagonal block operators;
- application-specific permutations;
- matrix-free operator application;
- custom batching.

Then call BLAS/FFTW/LAPACK inside that implementation where appropriate.

## Performance rule

Do not replace a high-level representation with a dense matrix merely to gain
API convenience. Materializing a structured O(N log N) or O(Nr) operator as an
O(N^2) dense matrix is usually an architectural regression.

## Correctness rule

A custom optimized path should have a small, obvious reference implementation.
Do not delete the reference path until the fast path is validated.
