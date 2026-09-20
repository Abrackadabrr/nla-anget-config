# MUMPS build/run/debug checklist

## Linking

Packaging differs by platform. A parallel MUMPS configuration commonly links:

- arithmetic-specific MUMPS library;
- `mumps_common`;
- MPI;
- BLAS/LAPACK;
- ordering libraries selected at build time;
- possibly ScaLAPACK/BLACS depending on configuration.

Do not paste a distro-specific raw link line into a portable project unless
that project intentionally targets the distro.

Prefer an existing CMake package/config, pkg-config metadata, or project
wrapper if available.

## Run

For MPI build:

`mpirun -np P ./program`

Control BLAS/OpenMP threads explicitly to avoid P MPI ranks each spawning an
unintended full CPU thread team.

## Debug sequence

1. verify MPI initialization/lifetime;
2. verify correct MUMPS arithmetic header/library;
3. verify communicator/PAR/SYM before initialization;
4. verify n, nnz, pointers, and array lifetime;
5. verify 1-based global coordinate indices;
6. verify symmetric triangle convention if SYM != 0;
7. check INFOG after analysis;
8. check INFOG after factorization;
9. check INFOG after solve;
10. compute independent residual;
11. only after centralized one-rank correctness move to distributed input.

## Pattern reuse bugs

If sparsity pattern changes, previous symbolic analysis may no longer be valid.
Track pattern identity explicitly rather than assuming same nnz means same
pattern.

## Memory/fill problems

Inspect ordering, fill statistics, memory estimates, process/thread layout, and
problem structure before simply increasing memory limits.

Sparse direct methods can become memory-dominated because factor fill is not
the same as input nnz.
