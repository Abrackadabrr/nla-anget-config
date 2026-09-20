# Strang and T. Chan Circulant Preconditioners

## Strang

For a Toeplitz matrix `T=(t_{i-j})`, Strang's circulant copies the central
Toeplitz diagonals and wraps them to form a circulant matrix.

Implementation recipe:

1. obtain the Toeplitz displacement coefficients;
2. keep the near/main diagonals assigned to their natural circulant offsets;
3. wrap the opposite-side coefficients into the remaining offsets;
4. form the first circulant column;
5. FFT it once to obtain circulant eigenvalues;
6. apply `C^{-1}` by FFT -> pointwise divide -> inverse FFT;
7. guard against zero/tiny eigenvalues according to the problem.

For even sizes, define the Nyquist/middle-diagonal convention explicitly and
test it.

Primary source: G. Strang (1986), DOI 10.1002/sapm1986742171.

## T. Chan optimal circulant

Chan defines the circulant `C` minimizing `||C-T||_F`.

For an n-by-n Toeplitz matrix, a convenient first-column formula is

`c_k = ((n-k) t_k + k t_{k-n}) / n`,  k=0,...,n-1,

with displacement notation consistent with `T(i,j)=t_{i-j}`.

Implementation recipe:

1. fix Toeplitz displacement convention;
2. for every circulant offset k combine the two Toeplitz diagonals that map to
   that circular offset with weights `(n-k)/n` and `k/n`;
3. FFT the first column;
4. apply inverse as pointwise division in Fourier space;
5. validate by explicitly minimizing/projection-checking on tiny matrices.

Primary source: T. F. Chan (1988), DOI 10.1137/0909051.

## Solver compatibility

PCG requires the effective preconditioner to satisfy the required Hermitian
positive-definite assumptions. For nonsymmetric/indefinite systems use an
appropriate Krylov method instead of assuming CG applicability.
