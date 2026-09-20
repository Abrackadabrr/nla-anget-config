# Correctness and benchmarking

## Operator workflow

1. build tiny dense/reference implementation;
2. test hand-checkable cases;
3. test random real and complex cases;
4. compare normwise relative error;
5. separately test integer/index mappings;
6. test awkward sizes (1, odd/even, rectangular/non-cubic);
7. only then optimize.

For a fast matvec:

`rel = ||y_fast-y_ref||_2 / ||y_ref||_2`.

Also inspect componentwise errors when cancellation/local scaling matters.

## Linear-system validation

Report true original-system residual:

`||b-Ax|| / ||b||`.

If a trusted solution is known, report forward error as well.

For ill-conditioned systems, a small residual does not imply small forward
error. Interpret the expected error using conditioning and floating-point
precision.

Where useful, report a backward-error measure rather than only raw residual.

## Approximate/compressed operators

If solving with `A_tilde`, report separately:

- `||A_tilde x-A x||` on test vectors;
- residual for the system actually solved;
- residual in the original A system if A can be applied;
- physical/application observable error.

## Reproducibility

Record:

- random seed;
- scalar precision;
- backend/library;
- thread count;
- tolerance;
- stopping rule;
- size/problem generator.
