---
name: toeplitz-preconditioning
description: Construct and apply preconditioners for Toeplitz/block/multilevel Toeplitz or block systems, including Strang/Chan circulants, ILU(k), block diagonal, and block lower-triangular schemes. Use when preconditioning is explicit; do not trigger for plain Toeplitz matvec.
---

# Toeplitz and block preconditioning

Before coding:

1. state matrix structure and symmetry/definiteness;
2. choose Krylov method;
3. state left/right/split preconditioning;
4. implement `apply_P_inverse(r)` as a solve, never an explicit inverse;
5. validate on a tiny matrix;
6. measure setup, memory, apply time, iterations, and total solve time.

## Reference routing

- Strang/Chan scalar circulants:
  `references/CIRCULANT_PRECONDITIONERS.md`.
- Block/multilevel circulants:
  `references/BLOCK_MULTILEVEL_CIRCULANT.md`.
- ILU(k), block diagonal, block lower triangular:
  `references/ILU_AND_BLOCK_PRECONDITIONERS.md`.
- End-to-end checklist:
  `references/IMPLEMENTATION_CHECKLIST.md`.

ILU(k) is a sparse-pattern method; do not apply it directly to a fully dense
Toeplitz matrix unless a sparse surrogate/truncation has first been defined.
