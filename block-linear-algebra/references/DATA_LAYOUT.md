# Data Layout

Performance-critical block algorithms must document physical layout.

Specify:

- scalar type;
- row/column-major storage;
- block-major versus component-major ordering;
- strides and alignment;
- ownership/lifetime;
- whether subblocks are contiguous;
- thread partitioning.

Prefer contiguous storage for repeated kernels. Avoid pointer-heavy trees of
tiny heap allocations when a packed representation is possible.

Do not transpose/copy on every apply merely to satisfy a backend interface.
Either choose a compatible native layout or amortize an explicit packing step.
