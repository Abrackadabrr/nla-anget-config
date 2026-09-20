# MUMPS C/C++ coding recipe

## Production structure

Prefer explicit phases:

```text
MPI_Init
create/configure MUMPS handle
JOB=-1 initialize
set matrix structure
JOB=1 analyze
set/update matrix values
JOB=2 factor
set RHS
JOB=3 solve
independent residual check
JOB=-2 finalize MUMPS
MPI_Finalize
```

## Wrapper responsibilities

A C++ wrapper may use RAII but must keep visible:

- communicator;
- SYM/PAR;
- scalar arithmetic family;
- matrix ownership/lifetime;
- analysis/factor/solve state;
- index conversion;
- INFO/INFOG diagnostics.

Useful API shape:

```cpp
analyze(pattern);
factor(values);
solve(rhs);
```

rather than one opaque `solve_everything()` method.

## Index adapter

If application sparse indices are 0-based:

1. allocate MUMPS index arrays during setup;
2. convert each index +1;
3. validate min/max;
4. reuse those arrays for the pattern lifetime.

Do not repeatedly convert indices inside solve().

## Residual

After MUMPS returns x, independently compute

`r=b-Ax`

using the application matrix representation and report
`||r||/||b||`.

A successful MUMPS status is necessary but not a substitute for application
validation.
