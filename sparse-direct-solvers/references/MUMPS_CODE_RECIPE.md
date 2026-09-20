# MUMPS C/C++ Coding Recipe

A minimal double-precision unsymmetric skeleton:

```cpp
#include <mpi.h>
#include "dmumps_c.h"

#define JOB_INIT -1
#define JOB_END  -2
#define USE_COMM_WORLD -987654

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    DMUMPS_STRUC_C id{};
    id.comm_fortran = USE_COMM_WORLD;
    id.par = 1;
    id.sym = 0;
    id.job = JOB_INIT;
    dmumps_c(&id);

    // On the host for centralized assembled input:
    // id.n = n;
    // id.nnz = nnz;
    // id.irn = row_indices_1_based;
    // id.jcn = col_indices_1_based;
    // id.a = values;
    // id.rhs = rhs;

    id.job = 6;              // one-shot analysis+factorization+solve
    dmumps_c(&id);

    if (id.infog[0] < 0) {
        // report INFOG(1), INFOG(2) before cleanup
    }

    id.job = JOB_END;
    dmumps_c(&id);

    MPI_Finalize();
}
```

For production code prefer explicit `job=1,2,3` when phases have different
lifetimes or repeated solves/factorizations are expected.

## Wrapper design

A C++ wrapper should own the MUMPS instance and factor lifecycle, but should not
hide:

- symmetry mode;
- communicator;
- matrix distribution;
- analysis/factor/solve phases;
- MUMPS error codes;
- index-base conversion.

Convert 0-based application indices to 1-based MUMPS indices exactly once in a
well-defined adapter layer.
