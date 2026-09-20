# BLAS / CBLAS practical reference

BLAS provides standard optimized vector and dense-matrix kernels.

## Levels

- Level 1: vector-vector/scalar-vector; low arithmetic intensity.
- Level 2: matrix-vector; commonly bandwidth-limited.
- Level 3: matrix-matrix/triangular matrix-matrix; high reuse and usually the
  preferred form for repeated dense work.

When many GEMVs use the same matrix, consider grouping RHS vectors and using a
GEMM.

## Routine selection

| Mathematical operation | BLAS family |
| --- | --- |
| `y = alpha*x + y` | AXPY |
| dot product | DOT / DOTU / DOTC according to scalar/conjugation semantics |
| `y=alpha*A*x+beta*y` | GEMV |
| `C=alpha*op(A)*op(B)+beta*C` | GEMM |
| triangular matrix times matrix | TRMM |
| triangular solve with multiple RHS | TRSM |
| rank-1 update | GER / GERU / GERC |
| symmetric/Hermitian rank-k update | SYRK / HERK |

Prefixes: S, D, C, Z for real single, real double, complex single, complex
double where applicable.

## CBLAS GEMM contract

For `cblas_dgemm`/complex variants specify together:

- layout: RowMajor or ColMajor;
- TransA / TransB;
- M, N, K of the *logical* operation;
- alpha/beta;
- pointers A/B/C;
- lda/ldb/ldc = physical leading dimensions compatible with layout and
  transpose flags.

For complex CBLAS routines such as ZGEMM, alpha/beta and matrix pointers use
the CBLAS complex ABI expected by the installed implementation. Do not assume
that every BLAS exposes `std::complex<double>*` with identical headers/ABI;
check the project's existing wrapper or backend.

## Leading dimensions

Treat leading dimension as physical stride between adjacent rows/columns in the
backend's major dimension, not as “number of columns” by definition.

Derive lda/ldb/ldc from:

1. layout;
2. transpose flag;
3. physical storage shape.

Test non-square matrices so incorrect leading dimensions are exposed.

## LP64 vs ILP64

BLAS integer width is part of the library ABI. Do not mix LP64 and ILP64
headers/libraries. Use the integer typedef from the backend header where
available.

## Threading

Avoid nested oversubscription:

- OpenMP outer loop + multithreaded BLAS;
- multiple task threads each calling a large multithreaded GEMM.

Choose one parallel level deliberately and benchmark.

## Performance checklist

- use optimized BLAS, not reference BLAS, for performance claims;
- batch repeated RHS work into GEMM where useful;
- avoid packing/copying on every call;
- reuse aligned/contiguous buffers;
- separate packing cost from kernel time;
- benchmark one-thread and multithread behavior separately.

See `assets/cblas_gemm.cpp` for a minimal row-major example.
