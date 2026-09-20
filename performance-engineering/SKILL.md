---
name: performance-engineering
description: Optimize numerical linear algebra for runtime and memory traffic using measurement, BLAS-level reasoning, cache/SIMD, and parallelism.
---

# Performance Engineering

Default priority after correctness: performance, not API convenience.

Mandatory order:

1. implement a clear correct version;
2. validate;
3. benchmark/profile;
4. identify the bottleneck;
5. optimize the dominant cost;
6. revalidate;
7. benchmark again.

Never start by adding SIMD/OpenMP/FFT to an unvalidated algorithm.
