# Correctness and Benchmarking

## Correctness workflow

1. Build a tiny dense/reference version.
2. Test deterministic hand-checkable cases.
3. Test random real and complex cases.
4. Compare relative error, e.g.
   `||y_fast-y_ref||_2 / ||y_ref||_2`.
5. Add edge cases: n=1, odd/even sizes, non-square block grids, zero blocks,
   singular/ill-conditioned cases where relevant.
6. Only then optimize.

## Solver validation

Report both relative residual and, when a trusted solution is known, forward
error. Residual alone does not prove an accurate solution for an ill-conditioned
system.

## Benchmarking

- exclude setup when measuring repeated apply unless setup is part of the user
  workload;
- separately report setup/planning/factorization and repeated apply/solve;
- warm up;
- use multiple repetitions;
- control thread counts;
- avoid debug builds;
- ensure results are consumed so work is not optimized away;
- verify correctness in the benchmark executable or adjacent tests.
