# LAPACK Practical Reference

Source basis: Netlib LAPACK 3.12.1 and LAPACK Users' Guide.

LAPACK provides dense and banded linear-system solvers, least-squares,
eigenvalue and singular-value routines, and the associated LU/Cholesky/QR/SVD/
Schur factorizations. It does not target general sparse matrices.

## Recipe

1. Classify the matrix: general, symmetric/Hermitian, SPD/HPD, triangular,
   banded, etc.
2. Prefer the matching specialized driver/factorization.
3. Decide whether the operation is one-shot or repeated:
   - one-shot: driver routine may be sufficient;
   - repeated RHS: factor once, call the solve stage repeatedly.
4. Check the documented workspace query convention for the chosen routine.
5. Check `INFO` after every call.
6. Preserve factorization data if future solves are expected.
7. Benchmark with the linked optimized BLAS implementation.

## C/C++

LAPACKE is a C interface available with LAPACK distributions, but projects may
also call Fortran ABI routines directly or use Eigen frontends. Follow the
project's existing linkage convention rather than introducing another one
without reason.

## Do not use LAPACK for

- general sparse LU;
- Toeplitz FFT algorithms;
- multilevel structured storage;
- custom matrix-free operators.
