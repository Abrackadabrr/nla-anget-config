# ILU(k) and Classical Block Preconditioners

## ILU(k): implementation recipe

ILU(k) keeps fill entries according to level-of-fill.

Conceptually:

1. start with the sparse pattern of A and assign level 0 to original nonzeros;
2. perform Gaussian elimination in the chosen ordering;
3. when elimination would create/update entry (i,j) through pivot k, assign
   candidate level
   `level(i,k) + level(k,j) + 1`;
4. retain an entry only when its minimum discovered level is <= k;
5. store the resulting incomplete L and U factors;
6. apply the preconditioner by triangular solves, never by forming
   `(LU)^{-1}`.

Thus:
- ILU(0): original sparsity pattern only;
- ILU(1): one generation of fill allowed by the level rule;
- ILU(2): two levels.

Ordering strongly affects fill, stability, and convergence. Handle missing or
tiny pivots deliberately; do not silently divide by them.

## Block diagonal

For block partition `A=[A_ij]`:

`P = diag(A_11, A_22, ..., A_pp)`.

Recipe:

1. extract/factor each diagonal block;
2. apply P^{-1} with independent block solves;
3. parallelize block solves when appropriate.

Use exact small dense LU/Cholesky or another appropriate local solver.

## Block lower triangular

`P = tril(A)` or a selected block-lower approximation.

Apply P^{-1} by block forward substitution:

for i=1..p:
`rhs_i = r_i - sum_{j<i} P_ij z_j`;
solve `P_ii z_i = rhs_i`.

Factor diagonal blocks once. Do not form a global inverse.

## Comparison protocol

For each preconditioner measure:

- setup time;
- memory;
- apply time;
- Krylov iterations;
- total solve time;
- robustness across representative matrices.

A preconditioner with fewer iterations is not automatically faster.
