# BLAS Practical Reference

Source basis: Netlib BLAS and BLAS Technical Forum.

## Levels

- Level 1: vector-vector / scalar-vector operations. Usually low arithmetic
  intensity and memory-bandwidth limited.
- Level 2: matrix-vector operations such as GEMV. Often memory-bandwidth
  limited for large matrices.
- Level 3: matrix-matrix operations such as GEMM/TRSM. High data reuse and the
  preferred computational form when batching makes it possible.

## Performance-oriented recipe

1. Identify whether the kernel is Level 1, 2, or 3.
2. If many independent GEMVs use the same matrix, consider packing RHS vectors
   into a matrix and replacing them by one GEMM.
3. Use a vendor/optimized BLAS (OpenBLAS, MKL, BLIS, etc.), not the Netlib
   reference implementation, for performance measurements.
4. Avoid unnecessary copies/transposes around BLAS calls.
5. Confirm column/row-major conventions and leading dimensions.
6. Control threading explicitly; do not accidentally nest OpenMP outside a
   multithreaded BLAS.

## CBLAS

Use `cblas.h` when a C API is appropriate. Treat `lda/ldb/ldc` as physical
strides, not merely matrix dimensions. Verify `CblasRowMajor` versus
`CblasColMajor` and transpose flags together.

## What BLAS does not provide

BLAS does not provide a block-Toeplitz abstraction, circulant embedding, sparse
factorization, or application-specific composite operator. Build those layers
yourself and use BLAS for their dense kernels.
