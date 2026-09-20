# Block and Multilevel Toeplitz

## Block Toeplitz

`A_ij = B_{i-j}`, where each `B_k` is itself a matrix/operator.

Do not confuse:

- Toeplitz matrix with dense blocks;
- block matrix whose blocks are Toeplitz;
- block Toeplitz with Toeplitz blocks (BTTB);
- multilevel Toeplitz induced by a multidimensional grid.

## d-level Toeplitz

For multi-indices i,j,

`A_{i,j} = K_{i-j}`.

The coefficient object at each displacement may itself be a small dense block,
for example a 3x3 vector-component coupling matrix.

## Implementation recipe

1. Fix flattening order of logical indices.
2. Define signed displacement coordinates.
3. Store one coefficient block per reachable displacement.
4. Write direct structured matvec.
5. Validate against dense materialization for tiny sizes.
6. Only then implement multidimensional circulant embedding/FFT.
