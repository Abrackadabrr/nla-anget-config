# Performance Model

Estimate before optimizing:

- operation count;
- bytes read/written;
- arithmetic intensity;
- working-set size;
- allocation count;
- reuse distance;
- synchronization/communication.

Use Roofline-style reasoning qualitatively or quantitatively.

A memory-bound kernel is not fixed by reducing a few FLOPs. A compute-bound
kernel is not fixed by prefetching data that is already reused efficiently.

Prefer transformations that increase reuse, especially conversion of repeated
Level-2 BLAS work into Level-3 BLAS work.
