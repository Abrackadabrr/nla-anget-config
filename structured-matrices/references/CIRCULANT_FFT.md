# Circulant Embedding and FFT

A circulant matrix is diagonalized by the discrete Fourier transform. This is
the basis of fast Toeplitz matvecs and circulant preconditioners.

## Linear convolution embedding

For an n-by-n Toeplitz matrix, use an embedding size sufficient for the linear
convolution, commonly at least 2n-1 (often rounded to an FFT-friendly size).

For d dimensions, pad independently in every Toeplitz dimension.

## Debug checklist

- Does the embedded first column match the chosen DFT sign convention?
- Are negative offsets wrapped to the correct high indices?
- Is the inverse FFT normalized exactly once?
- Is the cropped range the physical output range?
- Are block/component channels ordered consistently?
- Are kernel FFTs cached across repeated matvecs?

Validate with random complex vectors and non-power-of-two/non-cubic sizes.
