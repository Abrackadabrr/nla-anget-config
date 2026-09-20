# nla-anget-config

Shared Codex skills for performance-oriented numerical linear algebra and
scientific C/C++.

The repository is designed to be mounted directly under `.agents/skills`.

## Design philosophy

Correctness comes first. Optimization begins only after a clear reference path
works and is validated.

After correctness is established, runtime, memory traffic, and scalability are
the default priorities unless the user explicitly prioritizes convenience,
genericity, API simplicity, or maintainability.

Use mature libraries for optimized kernels they already implement. Implement
the mathematical structure and orchestration that those libraries do not
represent.

Examples:

- GEMM/TRSM -> BLAS;
- dense LU/QR/SVD/eigensolvers -> LAPACK;
- FFT/DFT -> FFTW;
- sparse multifrontal factorization -> MUMPS when appropriate;
- Toeplitz/multilevel storage -> custom;
- Toeplitz-to-circulant embedding -> custom;
- FFT Toeplitz matvec -> custom orchestration + FFTW;
- block operator composition/permutations -> custom;
- low-rank U(V^*x) -> custom orchestration + BLAS kernels.

## Skills

- `linear-algebra-backends`: choose and use BLAS/LAPACK/Eigen/FFTW.
- `structured-matrices`: Toeplitz, block/multilevel Toeplitz, circulant, FFT
  operators.
- `block-linear-algebra`: heterogeneous block operators and explicit block
  algorithms.
- `performance-engineering`: profiling/optimization after correctness.
- `numerical-validation`: reference checks, residual/error tests, benchmark
  validation.
- `toeplitz-preconditioning`: circulant, ILU(k), block preconditioners.
- `sparse-direct-solvers`: MUMPS-oriented sparse direct solving.

## Scope boundary

This repository explains generic numerical-linear-algebra implementation.
Application-domain reasons for matrix structure belong to the consuming domain
skills (for example electromagnetic integral equations).
