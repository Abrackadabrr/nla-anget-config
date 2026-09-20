---
name: sparse-direct-solvers
description: Use, build, run, explain, and debug sparse direct solvers, with a practical focus on MUMPS C/C++ and MPI workflows.
---

# Sparse Direct Solvers

Use MUMPS when a general sparse direct factorization is required and the project
can accept its MPI/Fortran-linked dependency stack.

Do not replace a structured matrix-free O(N log N) iterative approach with a
sparse direct solver without considering fill, memory, and the intended problem
size.

For MUMPS tasks read all MUMPS reference notes first.
