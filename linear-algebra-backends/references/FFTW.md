# FFTW 3.3.11 Practical Reference

Source basis: official FFTW 3.3.11 User Manual.

FFTW provides 1-D and multidimensional DFTs, real/complex transforms, multiple
and strided transforms, threaded transforms, MPI transforms, aligned allocation,
plans, and wisdom.

## Basic workflow

1. Allocate arrays with `fftw_malloc`/`fftw_alloc_complex` when practical to
   preserve SIMD alignment.
2. Create a plan once for the intended dimensions/layout.
3. Use a planner flag appropriate to setup-cost versus repeated-execution
   tradeoff.
4. Execute the plan repeatedly.
5. Destroy the plan and free aligned storage.
6. Reuse/import wisdom only when the environment and layout assumptions are
   compatible.

## Important facts

- FFTW uses row-major multidimensional C-array conventions in the C interface.
- FFTW transforms are not normalized. If your mathematical inverse requires a
  1/N factor, apply it explicitly.
- The advanced/guru interfaces are appropriate for batches, strides, and custom
  layouts.
- FFT planning can overwrite input for some planner modes; consult the exact
  plan routine contract.
- Plan creation and plan execution have different thread-safety concerns.
- Avoid creating plans inside an iterative solver loop.

## Toeplitz use

FFTW only computes transforms. For Toeplitz multiplication you must implement:

1. Toeplitz coefficient layout;
2. circulant embedding;
3. zero padding;
4. mapping of negative offsets;
5. FFT of the embedded kernel;
6. frequency-domain multiplication;
7. inverse FFT;
8. normalization and crop.

For block kernels, implement component coupling yourself and use FFTW for each
required transform/batch.
