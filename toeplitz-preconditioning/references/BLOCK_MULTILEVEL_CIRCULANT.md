# Block and Multilevel Circulant Extensions

Two common meanings must be separated.

## Dense blocks with Toeplitz block pattern

`A_ij = B_{i-j}`, with dense m-by-m blocks B.

Apply the Strang/Chan projection in the outer Toeplitz index. The resulting
block-circulant matrix is diagonalized in the outer index by FFT, leaving one
small m-by-m matrix per Fourier mode.

Application of P^{-1}:

1. FFT every block-vector component over the Toeplitz dimension;
2. for each Fourier mode solve the small dense block system;
3. inverse FFT.

Pre-factor the per-mode small matrices if P is reused.

## Multilevel Toeplitz / BTTB

Apply the circulant projection in each Toeplitz dimension. The resulting
multilevel block-circulant operator is diagonalized by a multidimensional FFT.
If a small dense physical/component block remains, solve that block separately
at each Fourier grid point.

## Optimal block projection

Chan/Jin-type block extensions minimize Frobenius distance over a chosen class
of block matrices with circulant blocks while preserving the outer block
structure. Do not confuse "block circulant" with "circulant blocks".

Sources:
- Chan & Jin, DOI 10.1137/0913070.
- Chan & Olkin, DOI 10.1007/BF02149764.

## Implementation test

For a tiny matrix explicitly assemble A and P, compare P with the structured
constructor, and verify structured `apply_inverse(r)` against a dense solve.
