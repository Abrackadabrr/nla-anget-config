---
name: structured-matrices
description: Design and implement Toeplitz, block-Toeplitz, multilevel Toeplitz, circulant, and FFT-accelerated matrix operators.
---

# Structured Matrices

Represent the mathematical structure explicitly. Do not materialize a dense
matrix by default.

For every structure define:

- logical dimensions;
- stored coefficients;
- index-to-displacement mapping;
- vector/component ordering;
- apply() complexity;
- storage complexity;
- reference dense constructor for tests.

Read the Toeplitz and FFT references before coding.
