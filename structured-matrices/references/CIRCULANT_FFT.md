# Circulant embedding and FFT matvec

A circulant matrix is diagonalized by the DFT. Toeplitz multiplication is
implemented by embedding the linear convolution into a sufficiently large
circular convolution.

## Scalar 1-D recipe

Given first-column/first-row Toeplitz data:

1. build a circulant first column with positive and negative Toeplitz offsets
   in the correct wrapped positions;
2. choose FFT length at least the required linear-convolution support;
3. zero-pad x;
4. FFT embedded kernel once during setup;
5. each apply: FFT padded x;
6. multiply pointwise;
7. inverse FFT;
8. normalize according to FFT backend convention;
9. crop physical output.

Do not accidentally replace a Toeplitz physical operator by periodic wrap
around. The circulant is an embedding device unless the model is truly
periodic.

## d dimensions

Pad independently in each Toeplitz dimension. For a physical m-by-m block at
each displacement:

- FFT every required block channel/component;
- at each Fourier grid point apply the small m-by-m frequency-domain block;
- inverse-transform output components.

## Performance

Precompute/cache:

- embedded kernel;
- its Fourier transform;
- FFT plans;
- work buffers;
- small per-frequency factorizations if applying an inverse/preconditioner.

Avoid allocation and planning inside apply().

## Validation

Compare:

1. dense explicit matrix;
2. direct displacement-based structured apply;
3. FFT apply.

Use random complex vectors, odd/even non-power-of-two sizes, and non-cubic
multidimensional grids.
