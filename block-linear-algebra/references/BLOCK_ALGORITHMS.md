# Block algorithms

## Composite apply recipe

1. define row/column block partitions;
2. record exact dimensions;
3. identify each block structure;
4. implement/test each block apply independently;
5. accumulate `y_i += A_ij x_j` without global dense materialization;
6. only then fuse/batch operations.

Examples:

- dense -> BLAS;
- Toeplitz -> structured apply;
- low-rank `U V^*` -> `tmp=V^*x; y+=U tmp`;
- diagonal -> pointwise;
- sparse -> sparse kernel/solver;
- matrix-free -> callback/operator apply.

## Repeated RHS / repeated equal block

If the same dense block acts on many vector segments, reshape/pack those
segments into a thin matrix when worthwhile and use GEMM instead of repeated
GEMV.

Include packing/scatter cost in the benchmark.

## Block triangular solve

For lower block triangular P:

for i from 0 to nb-1:

`rhs_i = b_i - sum_{j<i} P_ij x_j`;

solve diagonal block `P_ii x_i=rhs_i`.

Factor diagonal blocks once when reused.
