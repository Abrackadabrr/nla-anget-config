# nla-anget-config

Shared Codex skills for performance-oriented numerical linear algebra in C/C++.

The agent should prefer correctness first, then measurement, then optimization.
Unless the user explicitly prioritizes API convenience, genericity, or
maintainability, performance and memory traffic are the default optimization
targets.

This repository is laid out so that it can be mounted directly as
`.agents/skills`:

```bash
mkdir -p .agents
git submodule add https://github.com/Abrackadabrr/nla-anget-config.git .agents/skills
```

## Skills

- `linear-algebra-backends`: BLAS, LAPACK, Eigen, FFTW, and the
  library-vs-custom decision.
- `structured-matrices`: Toeplitz, block Toeplitz, multilevel Toeplitz,
  circulant embedding, FFT matvec.
- `block-linear-algebra`: explicit block algorithms, data layout, kernel
  decomposition, and composite operators.
- `performance-engineering`: memory hierarchy, BLAS levels, Roofline-style
  reasoning, SIMD, threading, allocation control.
- `numerical-validation`: correctness/reference implementations, numerical
  error, benchmarking, and revalidation.
- `toeplitz-preconditioning`: Strang/Chan circulant preconditioners,
  block/multilevel extensions, ILU(k), block diagonal and block triangular
  preconditioners.
- `sparse-direct-solvers`: practical MUMPS usage, build/run/debug workflow,
  sparse input, MPI and repeated factor/solve workflows.

## Core policy

Use mature libraries for optimized numerical kernels they already implement.
Implement the mathematical structure, orchestration, storage, permutations,
embedding, and composite algorithms that the libraries do not represent.

Examples:

- GEMM -> BLAS;
- LU/QR/SVD/eigensolvers -> LAPACK;
- FFT -> FFTW;
- block-Toeplitz storage -> custom;
- Toeplitz-to-circulant embedding -> custom;
- FFT Toeplitz matvec -> custom orchestration + FFTW;
- low-rank U(V^*x) -> custom orchestration + BLAS kernels.

Do not optimize an unvalidated implementation.
