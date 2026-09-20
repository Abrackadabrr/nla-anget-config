# Preconditioner implementation checklist

1. Implement/identify `apply_A(x)`.
2. Define P mathematically.
3. Implement `apply_P_inverse(r)` without explicit global inverse.
4. Validate P and P^{-1} on a tiny materialized system.
5. Choose left/right/split convention.
6. Choose Krylov solver compatible with the effective operator.
7. Cache FFT spectra/block factorizations/symbolic ILU analysis.
8. Benchmark setup separately from repeated application.
9. Compare against no preconditioner under the same stopping criterion.
10. Report true residual of the original system.
11. Report iteration count *and* total solve time.
12. Stress test problem sizes/parameters that make P nearly singular.
