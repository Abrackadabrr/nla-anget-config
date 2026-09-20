# Eigen Practical Reference

Use Eigen as a C++ expression/container layer when it preserves the required
layout and does not introduce unwanted temporaries.

## Rules

- Use `.noalias()` where the expression contract permits it and aliasing is
  otherwise conservatively assumed.
- Prefer fixed-size Eigen objects for genuinely small compile-time kernels when
  that simplifies vectorization.
- For large dense kernels, know whether the build is configured to use an
  external BLAS and benchmark the actual path.
- Do not assume an Eigen expression is allocation-free: inspect or benchmark.
- Do not force a structured operator into `MatrixX*` solely to use Eigen
  syntax.
- Keep ownership and views explicit; `Map` can expose existing contiguous or
  strided storage without copying.

Eigen is not a replacement for an explicit structured-matrix design.
