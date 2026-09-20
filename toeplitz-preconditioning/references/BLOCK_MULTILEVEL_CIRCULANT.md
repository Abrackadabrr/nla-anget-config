# Block and multilevel circulant preconditioners

## Block Toeplitz with dense m-by-m blocks

Let

`A_ij=B[i-j]`.

Construct a circulant approximation in the *outer Toeplitz index*, preserving
the dense m-by-m block at each circular displacement.

After FFT over the outer index, the preconditioner becomes one m-by-m matrix
per Fourier mode.

### Apply inverse

Setup:

1. construct circulant block column C[k];
2. FFT every scalar block channel `C_ab[k]`;
3. for every Fourier mode q assemble small matrix `C_hat(q)`;
4. factor each `C_hat(q)` once (LU/Cholesky as appropriate).

Apply:

1. FFT each component sequence of r;
2. for every q solve `C_hat(q) z_hat(q)=r_hat(q)`;
3. inverse FFT each component;
4. normalize.

This is not scalar pointwise division unless m=1 or the block is diagonal in
physical components.

## Multilevel/BTTB

For d Toeplitz dimensions:

1. perform the chosen Strang/Chan projection in each structured dimension;
2. obtain a BCCB/multilevel-circulant approximation;
3. diagonalize structured dimensions with a d-D FFT;
4. solve any remaining small physical/component block independently at each
   Fourier grid point.

Cache frequency-block factorizations when reused.

## Validation

For a tiny problem:

- explicitly materialize A;
- explicitly materialize P;
- compare structured P construction;
- compare `apply_P_inverse` with a dense solve;
- then test inside the Krylov method.

Do not confuse “block circulant” (outer pattern) with “circulant blocks”
(inner block structure).
