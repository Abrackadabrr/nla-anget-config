# Data layout for block algorithms

Document:

- scalar type;
- row/column-major storage;
- block-major versus component-major ordering;
- contiguous dimensions;
- strides;
- alignment;
- ownership/lifetime;
- workspace reuse;
- thread partitioning.

## Principles

Prefer one/few contiguous allocations over pointer trees of tiny heap blocks
when the workload repeatedly traverses all blocks.

A logical block view should not imply a physical copy.

Use packing only when the downstream kernel reuses packed data enough to
amortize the packing cost.

For repeated equal blocks, choose a layout that exposes multiple vector
segments as a GEMM-friendly dense panel when possible.

## Performance audit

For a hot apply(), count:

- full-size temporary buffers;
- heap allocations per call;
- input rereads;
- output write/accumulation passes;
- non-unit-stride accesses;
- required format conversions.

Eliminate these before hand-writing SIMD.
