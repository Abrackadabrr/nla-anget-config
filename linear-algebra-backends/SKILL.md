---
name: linear-algebra-backends
description: Choose or correctly call BLAS, LAPACK, Eigen, or FFTW for dense kernels, factorizations, transforms, layouts, and library-vs-custom decisions. Use when a backend API or library choice matters; do not trigger for generic algorithm theory with no backend usage.
---

# Linear-algebra backends

Use optimized libraries for standard kernels; implement structure and
orchestration yourself.

## Reference routing

- Choosing custom vs library implementation:
  read `references/LIBRARY_SELECTION.md`.
- BLAS/CBLAS calls, leading dimensions, transpose/layout, batching:
  read `references/BLAS.md`.
- Dense factorizations/eigen/SVD and factor-once/solve-many:
  read `references/LAPACK.md`.
- Eigen expressions, Map/views, aliasing, and backend interaction:
  read `references/EIGEN.md`.
- FFT planning, layout, batching, threads, wisdom:
  read `references/FFTW.md`.

Do not read every backend reference for a single-library task.
