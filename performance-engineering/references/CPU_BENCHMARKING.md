# CPU benchmarking checklist

## Build

Use release optimization. For machine-local research benchmarks,
architecture-specific compilation can be appropriate; do not silently ship
`-march=native` binaries intended for other machines.

Do not enable unsafe floating-point transformations such as fast-math merely
for speed unless their numerical semantics are acceptable to the task.

## Measure separately

- setup/planning/factorization;
- one apply/solve;
- repeated steady-state apply/solve;
- allocation/packing if it is part of the workload.

## Method

- warm up;
- use enough repetitions for stable timing;
- consume outputs;
- pin/control thread counts where relevant;
- record CPU/thread/backend configuration;
- benchmark representative sizes, not only one size;
- report median/min distribution rather than one lucky timing when possible.

## Diagnose before changing code

Use profiler/counters/compiler reports to decide whether the bottleneck is:

- memory bandwidth;
- cache misses;
- branch/control;
- scalar/nonvectorized compute;
- BLAS/FFT backend;
- synchronization;
- allocation;
- algorithmic complexity.

Re-run correctness checks after every optimization that changes data layout,
parallel ordering, approximations, or floating-point reduction order.
