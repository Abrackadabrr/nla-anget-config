# Library or custom implementation?

## Decision procedure

1. Name the exact mathematical operation.
2. Identify exploitable structure and size regime.
3. Ask whether a mature library directly implements that operation without
   destroying the structure.
4. If yes, use the library kernel.
5. If no, implement the missing structure/orchestration and call mature kernels
   inside it.
6. Validate before optimizing.

## Typical mapping

| Need | Default |
| --- | --- |
| dense matrix-matrix | BLAS GEMM |
| dense matrix-vector | BLAS GEMV or Eigen, benchmark if hot |
| triangular multiple-RHS solve | BLAS TRSM |
| dense LU factor/solve | LAPACK GETRF + GETRS |
| SPD/HPD factor/solve | LAPACK POTRF + POTRS |
| dense QR | LAPACK GEQRF + related routines |
| dense SVD | LAPACK GESDD/GESVD |
| DFT / batched DFT | FFTW |
| C++ matrix views/glue | Eigen if it preserves layout/performance |
| general sparse direct solve | MUMPS or another sparse solver |
| Toeplitz storage | custom |
| circulant embedding | custom |
| block operator orchestration | custom |
| low-rank storage/application | custom + BLAS |

## Anti-patterns

Do not:

- materialize a structured O(N log N) operator as O(N^2) dense solely for API
  convenience;
- reimplement GEMM/LU/FFT from scratch without a research reason;
- add a generic abstraction hierarchy before the performance-critical data
  layout is known;
- copy/transpose entire matrices on every apply just to satisfy a backend API.
