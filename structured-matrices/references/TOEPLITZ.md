# Toeplitz Matrices

For `T in C^{n x n}`,

`T(i,j) = t[i-j]`.

Store the first column and first row, or a single displacement array indexed
from `-(n-1)` through `n-1`.

## Reference matvec

Implement the direct O(n^2) form first. It is the correctness oracle for
structured and FFT paths.

## FFT path

Embed T into a circulant matrix of sufficient size, pad x, FFT both embedded
kernel and x, multiply pointwise, inverse FFT, normalize, and crop.

Test nonsymmetric complex matrices; symmetric examples can hide offset/sign
bugs.
