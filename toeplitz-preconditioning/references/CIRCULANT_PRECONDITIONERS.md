# Strang and T. Chan circulant preconditioners

Fix Toeplitz convention:

`T(i,j)=t[i-j]`, i,j=0,...,n-1.

A circulant preconditioner is stored by its first column c and applied/inverted
with FFTs.

## Strang circulant: implementation recipe

Strang's construction keeps the Toeplitz diagonals closest to the main
diagonal and wraps them into a circulant.

Algorithm:

1. initialize c[0]=t[0];
2. for circular offset k, choose the Toeplitz diagonal representative with the
   smallest-magnitude signed displacement (with a documented tie convention
   when n is even);
3. set c[k] to that Toeplitz coefficient;
4. precompute `lambda=FFT(c)`;
5. apply `P^{-1}r` as FFT(r), divide by lambda, inverse FFT, normalize.

For even n explicitly document which middle diagonal is selected. Test the
assembled circulant against the intended paper/code convention.

## T. Chan Frobenius-optimal circulant

For the same displacement convention, the optimal circulant first column is:

`c[k] = ((n-k)*t[k] + k*t[k-n]) / n`,
for k=0,...,n-1,

where `t[k]` is the nonnegative displacement coefficient and `t[k-n]` the
negative displacement that maps to the same circular offset.

Recipe:

1. build c with the weighted formula;
2. FFT c once;
3. apply inverse by Fourier-space division;
4. validate P against explicit dense Frobenius projection on tiny matrices.

## Numerical inversion

Do not silently divide by near-zero Fourier eigenvalues.

If regularization is needed, make the threshold/shift part of the
preconditioner definition and report its effect.

## Krylov compatibility

CG/PCG requires the matrix/preconditioner properties required by that method.
For nonsymmetric/indefinite problems choose an appropriate Krylov solver rather
than assuming circulant preconditioning implies CG compatibility.
