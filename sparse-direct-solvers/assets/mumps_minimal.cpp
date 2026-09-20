#include <mpi.h>
#include "dmumps_c.h"

#include <cmath>
#include <iostream>

#ifndef USE_COMM_WORLD
#define USE_COMM_WORLD -987654
#endif

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    DMUMPS_STRUC_C id{};
    id.comm_fortran = USE_COMM_WORLD;
    id.par = 1;
    id.sym = 0;
    id.job = -1;
    dmumps_c(&id);

    // Centralized assembled 2x2 system on host:
    // [4 1] [x0] = [1]
    // [2 3] [x1]   [1]
    MUMPS_INT irn[4] = {1, 1, 2, 2};
    MUMPS_INT jcn[4] = {1, 2, 1, 2};
    double a[4] = {4.0, 1.0, 2.0, 3.0};
    double rhs[2] = {1.0, 1.0};

    if (rank == 0) {
        id.n = 2;
        id.nnz = 4;
        id.irn = irn;
        id.jcn = jcn;
        id.a = a;
    }

    id.job = 1;
    dmumps_c(&id);
    if (id.infog[0] < 0) goto cleanup;

    id.job = 2;
    dmumps_c(&id);
    if (id.infog[0] < 0) goto cleanup;

    if (rank == 0) id.rhs = rhs;
    id.job = 3;
    dmumps_c(&id);

    if (rank == 0 && id.infog[0] >= 0) {
        std::cout << "x = " << rhs[0] << ' ' << rhs[1] << '\n';
        const double r0 = 1.0 - (4.0 * rhs[0] + rhs[1]);
        const double r1 = 1.0 - (2.0 * rhs[0] + 3.0 * rhs[1]);
        std::cout << "residual norm = " << std::hypot(r0, r1) << '\n';
    }

cleanup:
    if (rank == 0 && id.infog[0] < 0)
        std::cerr << "MUMPS INFOG(1)=" << id.infog[0]
                  << " INFOG(2)=" << id.infog[1] << '\n';

    id.job = -2;
    dmumps_c(&id);
    MPI_Finalize();
    return 0;
}
