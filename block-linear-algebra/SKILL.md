---
name: block-linear-algebra
description: Design explicit heterogeneous block algorithms when different blocks are dense, low-rank, diagonal, sparse, Toeplitz, or matrix-free. Use for block composition, data layout, and kernel decomposition; do not trigger for a single homogeneous Toeplitz operator.
---

# Block linear algebra

Write the block equations before choosing storage.

For `A=[A_ij]` and block vector x:

`y_i=sum_j A_ij x_j`.

Choose the implementation of each block according to its own structure.

Default after correctness: prefer performance-transparent data layout and
explicit kernels over abstraction that hides copies or allocation.

Read:

- `references/BLOCK_ALGORITHMS.md` for composite apply/solve patterns;
- `references/DATA_LAYOUT.md` for physical storage and batching.
