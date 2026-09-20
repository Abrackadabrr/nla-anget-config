# Performance model

Before optimizing estimate or measure:

- FLOPs;
- bytes read/written from the relevant memory level;
- arithmetic intensity;
- working-set size;
- data reuse;
- allocation count;
- synchronization/communication;
- setup versus repeated-apply cost.

## Diagnose

If measured throughput follows memory bandwidth and arithmetic intensity is
low, reducing a handful of FLOPs is unlikely to matter.

If data is reused enough for compute to dominate, use tuned Level-3 kernels,
vectorization, or algorithmic blocking.

## High-value transformations

Often worth testing:

- many GEMV -> GEMM;
- reuse/factor once -> solve many;
- cache invariant FFT kernel spectra/plans;
- cache block factorizations;
- avoid repeated format conversion;
- fuse passes only when it reduces meaningful memory traffic;
- change algorithmic complexity before micro-optimizing loops.

Report the performance model assumptions with benchmark results.
