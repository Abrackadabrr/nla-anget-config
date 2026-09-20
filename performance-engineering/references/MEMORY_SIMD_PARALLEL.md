# Memory, SIMD, and parallelism

## Memory first

- remove heap allocation from hot apply/iteration paths;
- reuse workspaces;
- keep reused data contiguous where practical;
- minimize whole-array temporaries;
- consider cache blocking when repeated reuse exists.

## SIMD

Before manual intrinsics:

1. compile optimized;
2. inspect compiler vectorization diagnostics or generated code for the hot
   loop;
3. fix aliasing/stride/control-flow barriers;
4. benchmark;
5. use intrinsics only if a material bottleneck remains.

Manual SIMD is not a substitute for choosing a better BLAS-level algorithm.

## Threads

Start with a one-thread benchmark.

Coordinate:

- OpenMP/task threads;
- BLAS threads;
- FFTW threads;
- MPI ranks.

Avoid accidental nested oversubscription.

For NUMA-sized buffers, consider first-touch and stable thread/data ownership.

## False sharing

When threads independently update nearby small outputs, inspect cache-line
sharing. Prefer thread-local accumulation followed by a controlled reduction
when that reduces contention and memory traffic.
