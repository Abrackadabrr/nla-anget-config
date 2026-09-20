# Toeplitz matrices

For `T in C^{n x n}` use the signed displacement convention

`T(i,j)=t[i-j]`.

Store either:

- first column + first row (sharing t[0]); or
- one displacement array for `-(n-1) ... (n-1)`.

## Reference apply

Before FFT acceleration implement:

`y_i = sum_j t[i-j] x_j`.

Keep it obvious and O(n^2). This is a correctness oracle, not the production
large-n algorithm.

## Required tests

Use:

- real nonsymmetric Toeplitz;
- complex nonsymmetric Toeplitz;
- n=1;
- odd/even n;
- random vectors.

Symmetric examples alone can hide sign/reversal mistakes.

## Complexity

- explicit dense storage/apply: O(n^2) storage/work;
- displacement storage + direct apply: O(n) storage, O(n^2) work;
- circulant-embedded FFT apply: O(n) storage, O(n log n) work plus setup.

Keep setup and repeated apply timings separate.
