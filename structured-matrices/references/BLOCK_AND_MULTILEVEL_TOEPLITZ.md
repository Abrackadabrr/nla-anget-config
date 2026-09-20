# Block and multilevel Toeplitz

## Distinguish the structures

Do not conflate:

1. Toeplitz matrix with dense blocks:
   `A_ij=B_{i-j}`;
2. generic block matrix whose individual blocks are Toeplitz;
3. block Toeplitz with Toeplitz blocks (BTTB);
4. d-level Toeplitz from a d-dimensional translation grid;
5. small physical-component blocks attached to each multilevel displacement.

## d-level displacement rule

For multi-indices p,q:

`A_{p,q}=K_{p-q}`.

For a vector-valued operator, `K_delta` may be a small dense m-by-m block.

## Implementation recipe

1. choose logical grid dimensions;
2. choose flattening order;
3. define signed displacement per dimension;
4. define physical/block component order;
5. implement integer mapping functions separately;
6. store one coefficient block per reachable displacement;
7. implement direct structured apply;
8. compare to explicit dense materialization for tiny sizes;
9. only then implement multidimensional circulant embedding.

## Mapping tests

Test pure integer mappings independently:

- multi-index -> flat index -> multi-index;
- pair(p,q) -> displacement;
- displacement -> stored kernel index;
- negative displacement wrapping for circulant embedding.

This isolates indexing errors from floating-point errors.
