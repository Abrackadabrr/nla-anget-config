---
name: performance-engineering
description: Profile and optimize CPU numerical kernels for runtime, memory traffic, cache/SIMD, threading, BLAS efficiency, or scalability. Use when performance is being measured or improved; do not trigger merely because numerical code is being implemented.
---

# Performance engineering

Mandatory order:

1. correct implementation;
2. validation;
3. benchmark/profile;
4. bottleneck classification;
5. optimize dominant cost;
6. revalidate;
7. benchmark again.

Default optimization target after correctness is runtime and memory efficiency,
not API convenience, unless the user states otherwise.

## Reference routing

- Arithmetic intensity / Roofline reasoning:
  `references/PERFORMANCE_MODEL.md`.
- Memory, SIMD, OpenMP/BLAS/FFTW thread interaction:
  `references/MEMORY_SIMD_PARALLEL.md`.
- Benchmark methodology and compiler inspection:
  `references/CPU_BENCHMARKING.md`.
