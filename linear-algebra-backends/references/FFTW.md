# FFTW 3 practical reference

FFTW computes Fourier transforms. It does not know about Toeplitz matrices,
circulant embedding, physical block semantics, or application masks.

## Lifecycle

1. choose dimensions, transform kind, strides/batches, and in/out-of-place;
2. allocate suitably aligned buffers (FFTW allocators are convenient);
3. create plan during setup;
4. execute it repeatedly;
5. destroy plan after the repeated workload;
6. free buffers.

Never create FFT plans inside a Krylov matvec loop.

## Planning flags

- `FFTW_ESTIMATE`: cheap planning, no runtime measurement of alternatives;
- `FFTW_MEASURE`: measures plans; higher setup cost, often useful for reused
  transforms;
- `FFTW_PATIENT` / `FFTW_EXHAUSTIVE`: more expensive search for heavily
  reused transforms;
- `FFTW_WISDOM_ONLY`: require applicable wisdom.

Important: measurement-oriented planning can overwrite input arrays. Create
plans before initializing production input, or follow the exact flag/routine
contract.

## Normalization

FFTW forward/backward transforms are unnormalized. Apply the mathematical
normalization exactly once where your algorithm requires it.

## Batched/strided transforms

Use `fftw_plan_many_dft` or guru interfaces when data represents many
component/block transforms with regular strides. Avoid manual loops of tiny
plans when one batched plan expresses the same layout.

Document:

- transform rank and dimensions;
- howmany;
- stride/distances;
- component ordering;
- padding/cropping.

## Threads

For threaded FFTW:

1. initialize FFTW threading;
2. select thread count before plan creation;
3. create plans from a controlled/single planning context;
4. execute planned transforms;
5. avoid oversubscription with outer OpenMP/BLAS threads.

Plan execution is designed for concurrent use; planner operations share global
state and require more care. Benchmark thread count: small transforms often do
not benefit.

## Wisdom

Wisdom can amortize expensive planning for repeated known layouts. Wisdom is
layout/stride/planning-condition dependent; do not treat it as a portable
binary plan across arbitrary machines/configurations.

## Toeplitz use

For Toeplitz FFT matvec, *you* implement:

1. coefficient/displacement storage;
2. circulant embedding;
3. zero padding;
4. negative-offset mapping;
5. frequency-domain block coupling;
6. inverse normalization;
7. cropping.

FFTW supplies the transforms only.

See `assets/fftw_many.cpp` for a minimal batched complex-transform example.
