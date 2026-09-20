# LAPACK practical reference

LAPACK targets dense and banded numerical linear algebra and is built around
BLAS. It is not a general sparse solver.

## Routine-selection map

Use S/D/C/Z prefix matching scalar type.

| Problem | Computational path |
| --- | --- |
| general dense LU | xGETRF, then xGETRS |
| SPD/HPD solve | xPOTRF, then xPOTRS |
| QR factorization | xGEQRF |
| SVD | xGESDD or xGESVD |
| general eigenproblem | xGEEV |
| symmetric real eigenproblem | xSYEV/xSYEVD family |
| Hermitian complex eigenproblem | xHEEV/xHEEVD family |
| generalized nonsymmetric eigenproblem | xGGEV |

Prefer specialized structure-aware routines when assumptions are valid.

## Driver vs computational routines

A driver may perform an entire solve/decomposition workflow. Computational
routines expose reusable phases.

For repeated RHS:

1. factor once;
2. retain factorization and pivot data;
3. solve new RHS with the corresponding solve routine.

Do not refactor for every RHS.

## INFO

Check INFO after every LAPACK call.

- INFO=0: successful completion.
- INFO<0: invalid argument position.
- INFO>0: routine-specific numerical condition/failure described by that
  routine's documentation.

Do not reduce all INFO>0 cases to the same message.

## Workspace

Many LAPACK routines support or require workspace sizing. Follow the exact
routine documentation; use its documented workspace-query mechanism where
available rather than guessing a constant work array.

## C/C++

Possible interfaces:

- LAPACKE C interface;
- direct Fortran ABI wrapper;
- Eigen or another C++ frontend.

Follow the existing project interface unless changing it has a measured or
maintenance benefit.

See `assets/lapacke_lu.cpp` for a compact LAPACKE example; if the project does
not ship LAPACKE, adapt the same factor-once/solve-many logic to its existing
Fortran/C++ wrapper.
