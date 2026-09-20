# Skill-routing evaluation prompts

Maintenance tests for skill descriptions.

| Prompt | Expected skills |
| --- | --- |
| “How should I call zgemm for these matrices?” | linear-algebra-backends |
| “Implement a 3-level block-Toeplitz matvec.” | structured-matrices |
| “My 2x2 operator has dense, Toeplitz, and low-rank blocks.” | block-linear-algebra; structured-matrices |
| “This loop is too slow; profile and optimize it.” | performance-engineering |
| “Compare my FFT matvec to a dense reference.” | numerical-validation; structured-matrices |
| “Build a Chan preconditioner for BTTB.” | toeplitz-preconditioning; structured-matrices |
| “MUMPS gives INFOG(1)=-9.” | sparse-direct-solvers |
| “Solve a dense 500x500 LU system.” | linear-algebra-backends |
| “Explain the spectral theorem.” | no automatic skill |
| “Write ordinary application code with Eigen vectors.” | linear-algebra-backends only if backend details matter |
