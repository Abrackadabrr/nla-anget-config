# MUMPS 5.9.1: Practical C/C++ Reference

Source: official MUMPS 5.9.1 Users' Guide, July 20 2026.

MUMPS solves sparse square systems with unsymmetric, symmetric positive
definite, or general symmetric matrices. The main direct phases are analysis,
factorization, and solve. The parallel implementation uses MPI and can also use
OpenMP/multithreaded BLAS; the sequential build relies on BLAS/LAPACK.

## Minimal lifecycle

1. Initialize MPI.
2. Create `DMUMPS_STRUC_C id{}` (or S/C/Z arithmetic variant).
3. Set before initialization:
   - `id.comm_fortran = USE_COMM_WORLD` (or converted communicator);
   - `id.par`;
   - `id.sym`;
   - `id.job = -1`.
4. Call `dmumps_c(&id)`.
5. Provide matrix data.
6. Call phases:
   - `job=1`: analysis;
   - `job=2`: factorization;
   - `job=3`: solve;
   - `job=6`: analysis + factorization + solve for a one-shot problem.
7. After every phase inspect `id.infog[0]` / INFOG(1); negative means error.
8. Set `job=-2`, call MUMPS to destroy the instance.
9. Finalize MPI.

If the sparsity pattern is reused with changing numerical values, perform
analysis once, then repeat factorization/solve as allowed by the application.

## Centralized assembled input

Default assembled input uses:

- `id.n`;
- `id.nnz` (64-bit in current interface);
- `id.irn`, `id.jcn`;
- `id.a`.

C arrays `irn/jcn` contain Fortran-style 1-based matrix indices. Matrix entries
may be supplied in arbitrary order; duplicate entries are summed. For symmetric
modes, provide one triangle as documented.

The simple centralized case places matrix and RHS on the host rank.

## Distributed assembled input

Distribution is controlled by `ICNTL(18)`. Current documentation recommends
2 or 3, and calls 3 the simplest/natural distributed-entry mode.

For mode 3 provide on each participating rank:

- global `n`;
- local nonzero count `nnz_loc`;
- global index arrays `irn_loc/jcn_loc`;
- local values `a_loc`.

Use global, not local, matrix indices in these arrays.

## Arithmetic variants

- `smumps_c`: real single;
- `dmumps_c`: real double;
- `cmumps_c`: complex single;
- `zmumps_c`: complex double.

Choose the variant matching the project scalar type.
