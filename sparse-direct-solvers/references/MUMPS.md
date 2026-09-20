# MUMPS practical reference

Check the installed MUMPS version for exact controls/defaults.

MUMPS supports sparse direct analysis/factorization/solve for unsymmetric and
symmetric problems in sequential or MPI environments.

## C interface lifecycle

For double real arithmetic use `DMUMPS_STRUC_C` and `dmumps_c`. Other
arithmetic families are S/C/Z.

Typical lifecycle:

1. initialize MPI when using the normal parallel interface;
2. zero/create the MUMPS struct;
3. set communicator, PAR, SYM;
4. `JOB=-1`: initialize MUMPS instance;
5. provide problem/input controls;
6. `JOB=1`: analysis;
7. `JOB=2`: factorization;
8. `JOB=3`: solve;
9. inspect INFOG after each phase;
10. `JOB=-2`: terminate instance;
11. finalize MPI.

`JOB=6` can combine analysis+factorization+solve for one-shot examples, but
explicit 1/2/3 phases are better for reusable production workflows.

## Reuse

Same sparsity pattern, changed numerical values:

- reuse analysis when allowed by the chosen controls/pattern;
- refactor numeric values;
- solve one or more RHS.

Same factorization, new RHS:

- keep factors;
- run solve phase only.

Do not rerun analysis/factorization by habit.

## Centralized assembled coordinate input

Conceptually provide:

- global n;
- number of nonzeros;
- row index array;
- column index array;
- value array.

MUMPS C coordinate indices are global matrix indices in the Fortran/MUMPS
1-based convention. Convert a 0-based application representation exactly once
at the adapter boundary.

Duplicates are allowed by MUMPS assembled input and are summed; do not rely on
this accidentally when duplicates indicate an assembly bug.

For symmetric modes, follow the exact documented triangle-storage contract.

## Distributed assembled input

Modern MUMPS supports distributed assembled entries using local coordinate
arrays with *global* row/column indices.

The `ICNTL(18)=3` style is the natural distributed-input path in recent MUMPS
documentation; verify the installed-version manual before hard-coding a
control value.

Each process provides its local nonzero count, global row/column index arrays,
and local values according to the selected distribution mode.

## Arithmetic variants

- SMUMPS: real single;
- DMUMPS: real double;
- CMUMPS: complex single;
- ZMUMPS: complex double.

Match project scalar type and headers/libraries.

## Errors

After every phase inspect at least the global status fields corresponding to
INFOG(1) and the companion diagnostic field. Negative status indicates an
error; interpret the exact code from the installed MUMPS manual.

Do not swallow MUMPS diagnostics in a C++ wrapper.
