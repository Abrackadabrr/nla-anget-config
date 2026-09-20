---
name: structured-matrices
description: Implement Toeplitz, block-Toeplitz, multilevel Toeplitz, circulant, or FFT-accelerated structured matrix operators and their storage/indexing. Use when displacement structure itself is central; do not trigger for arbitrary heterogeneous block systems with no Toeplitz/circulant structure.
---

# Structured matrices

Correctness first: implement a small direct/reference path before an FFT path.

For every structure define:

- logical dimensions;
- stored unique coefficients/blocks;
- signed displacement convention;
- flattening/component ordering;
- storage complexity;
- direct apply complexity;
- accelerated apply complexity.

## Reference routing

- Scalar/basic Toeplitz: `references/TOEPLITZ.md`.
- Block/multilevel/BTTB: `references/BLOCK_AND_MULTILEVEL_TOEPLITZ.md`.
- Circulant embedding/FFT: `references/CIRCULANT_FFT.md`.

For heterogeneous block compositions, use `block-linear-algebra`.
For FFTW API details, use `linear-algebra-backends`.
