---
name: sparse-direct-solvers
description: Write, build, run, explain, or debug sparse direct-solver code, with practical focus on MUMPS C/C++/MPI phases, sparse input formats, diagnostics, and repeated factor/solve workflows. Use only when sparse direct solving or MUMPS is relevant.
---

# Sparse direct solvers

Use MUMPS when a general sparse direct factorization is appropriate and its
fill/memory/dependency cost is acceptable.

## Reference routing

- Basic C/C++ lifecycle and input:
  read `references/MUMPS.md`.
- Minimal code structure:
  read `references/MUMPS_CODE_RECIPE.md` and
  `assets/mumps_minimal.cpp`.
- Build/link/runtime/debug failure:
  read `references/MUMPS_BUILD_AND_DEBUG.md`.
- Distributed assembled matrix input:
  use the distributed section of `references/MUMPS.md`.

Do not read all MUMPS notes for a simple API question.
Do not replace a matrix-free structured solver by sparse direct factorization
without considering fill and memory.
