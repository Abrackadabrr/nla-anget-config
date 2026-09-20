# MUMPS Build, Run, and Debug Checklist

## Link dependencies

Exact library names depend on packaging, but MUMPS generally needs its
arithmetic library, `mumps_common`, and BLAS/LAPACK; parallel builds also need
MPI and may use ScaLAPACK/BLACS and ordering libraries.

Do not hard-code a distro-specific link line into generic code. Prefer CMake
package targets/pkg-config when the environment provides them; otherwise make
the dependency list explicit.

## Run

Parallel:
`mpirun -np <P> ./program`

Sequential MUMPS builds still use a MUMPS-compatible sequential MPI layer in
many source distributions; follow the installed package's interface.

## Debug recipe

1. Verify MPI is initialized before MUMPS.
2. Verify `comm_fortran`, `par`, and `sym` are set before `job=-1`.
3. Check `infog[0]` after every phase and print `infog[1]` too.
4. Verify n, nnz, pointer lifetimes, and scalar type.
5. Verify matrix indices are 1-based in the C MUMPS input arrays.
6. For symmetric input, verify only a consistent triangle is supplied.
7. Start with centralized assembled input on one MPI rank.
8. Validate the solution residual independently.
9. Only then switch to distributed `ICNTL(18)=3`.
10. If memory/factorization fails, inspect MUMPS memory estimates/statistics and
    ordering rather than blindly increasing limits.

## Common conceptual bugs

- passing 0-based row/column indices;
- freeing matrix arrays before the phase that needs them;
- changing sparsity pattern without rerunning analysis;
- using the wrong arithmetic variant;
- nested thread oversubscription;
- assuming a successful factorization proves an SPD claim;
- ignoring MUMPS INFO/INFOG diagnostics.
