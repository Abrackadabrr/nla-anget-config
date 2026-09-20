---
name: block-linear-algebra
description: Build explicit block algorithms and composite linear operators without unnecessarily materializing global dense matrices.
---

# Block Linear Algebra

Think at the level of blocks before writing scalar loops.

Given a block system, write each output block as the sum of block applications.
Choose the best implementation independently for each block.

Example:

- Toeplitz block -> FFT apply;
- low-rank block U V* -> two thin dense multiplies;
- diagonal block -> pointwise apply;
- dense block -> BLAS;
- sparse block -> sparse kernel/direct solver.

Do not create a global dense matrix unless the problem size or user request
makes that the correct representation.
