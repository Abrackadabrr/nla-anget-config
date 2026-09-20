# Block Algorithms

For A=[A_ij] and x=[x_j]:

`y_i = sum_j A_ij x_j`.

## Recipe

1. Define block partitions and exact dimensions.
2. Identify the structure of every block.
3. Define storage/ownership for each block.
4. Implement and test each block apply.
5. Implement the composite apply without hidden materialization.
6. Fuse or batch compatible operations only after profiling.

## Repeated RHS

If many RHS vectors pass through the same dense/low-rank block, batch them into
a matrix when possible to convert repeated GEMV-like work into GEMM-like work.

## Low rank

For `A = U V^*`, apply as:

1. `tmp = V^* x`;
2. `y += U tmp`.

For multiple RHS use GEMM for both stages when dimensions justify it.
