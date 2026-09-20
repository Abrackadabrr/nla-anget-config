---
name: numerical-validation
description: Build reference comparisons, residual/forward/backward error checks, convergence tests, and trustworthy benchmarks for numerical linear-algebra code. Use when validating or comparing implementations; do not trigger for ordinary implementation when no validation task is requested.
---

# Numerical validation

Separate:

1. mathematical correctness;
2. indexing/layout correctness;
3. floating-point numerical accuracy;
4. solver convergence;
5. performance.

Every optimized structured operator should have an independently understandable
small reference path.

Read `references/CORRECTNESS_AND_BENCHMARKING.md`.
