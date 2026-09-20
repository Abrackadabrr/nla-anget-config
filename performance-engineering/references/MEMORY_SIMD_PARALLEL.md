# Memory, SIMD, and Parallelism

## Memory first

- eliminate repeated allocations from hot loops;
- keep frequently reused data contiguous;
- avoid full-size temporaries where a view/workspace suffices;
- consider blocking when the same data can be reused from cache.

## SIMD

Before manual intrinsics:

1. enable appropriate compiler optimization/architecture flags;
2. inspect whether simple loops auto-vectorize;
3. avoid aliasing/stride patterns that block vectorization;
4. use manual intrinsics only when measured benefit justifies complexity.

## Parallelism

Avoid oversubscription. Coordinate OpenMP, BLAS threads, FFTW threads, and MPI.

Benchmark one thread first. Then measure scaling rather than assuming more
threads are faster.

For NUMA-scale work, consider first-touch placement and partitioning of large
buffers.
