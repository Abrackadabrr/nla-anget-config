# ILU(k) and classical block preconditioners

## ILU(k)

ILU(k) is defined from a sparse matrix graph and level-of-fill.

### Level construction

1. original nonzeros receive level 0;
2. during elimination through pivot p, a potential fill (i,j) receives
   candidate level
   `level(i,p)+level(p,j)+1`;
3. retain the minimum level discovered for that position;
4. discard entries whose level exceeds k.

Thus:

- ILU(0): no structural fill beyond original sparsity;
- ILU(1): one fill level;
- ILU(2): two fill levels.

### Implementation recipe

1. choose/reorder sparse matrix;
2. build symbolic level-k pattern;
3. perform incomplete numeric elimination restricted to that pattern;
4. handle tiny/zero pivots explicitly;
5. store L/U factors;
6. apply with triangular solves.

Never form `(LU)^{-1}`.

### Dense Toeplitz warning

A dense Toeplitz matrix has O(n^2) nonzeros despite O(n) structural storage.
Converting it to a general sparse matrix and applying ILU(k) normally destroys
the intended Toeplitz complexity.

Use ILU only after a meaningful sparse approximation/surrogate has been
defined, or when the original matrix is genuinely sparse.

## Block diagonal

For `A=[A_ij]`:

`P=diag(A_11,...,A_pp)`.

Setup:

1. select diagonal blocks;
2. factor each once;
3. cache factors.

Apply: independent block solves.

When diagonal blocks are identical, store/factor one representative and reuse
it where the algebra truly matches.

## Block lower triangular

Choose a lower block approximation P.

Apply by forward substitution:

for i:
`rhs_i=r_i-sum_{j<i}P_ij z_j`;
solve `P_ii z_i=rhs_i`.

Factor diagonal blocks once.

## Evaluation

Compare setup, memory, one apply, Krylov iterations, and total time. Fewer
iterations alone is not a performance result.
