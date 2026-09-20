# Sources

Primary documentation and literature used by the skills.

## Libraries

- BLAS: Netlib BLAS and BLAS Technical Forum, https://www.netlib.org/blas/
- LAPACK: Netlib LAPACK 3.12.1 documentation and Users' Guide,
  https://netlib.org/lapack/
- FFTW: FFTW 3.3.11 User Manual, https://www.fftw.org/fftw3_doc/
- MUMPS: MUMPS 5.9.1 Users' Guide, July 20 2026,
  https://mumps-solver.org/doc/userguide_5.9.1.pdf

## Toeplitz preconditioning

- G. Strang, "A Proposal for Toeplitz Matrix Calculations", Studies in Applied
  Mathematics 74(2), 171-176, 1986. DOI 10.1002/sapm1986742171.
- T. F. Chan, "An Optimal Circulant Preconditioner for Toeplitz Systems",
  SIAM J. Sci. Stat. Comput. 9(4), 766-771, 1988.
  DOI 10.1137/0909051.
- R. H. Chan and G. Strang, "Toeplitz Equations by Conjugate Gradients with
  Circulant Preconditioner", SIAM J. Sci. Stat. Comput. 10(1), 104-119, 1989.
  DOI 10.1137/0910009.
- T. F. Chan and J. A. Olkin, "Circulant preconditioners for Toeplitz-block
  matrices", Numerical Algorithms 6, 89-101, 1994.
  DOI 10.1007/BF02149764.
- R. H. Chan and X.-Q. Jin, "A Family of Block Preconditioners for Block
  Systems", SIAM J. Sci. Comput. 13(5), 1218-1235, 1992.
  DOI 10.1137/0913070.
- Y. Saad, *Iterative Methods for Sparse Linear Systems*, for ILU(k) and
  block-preconditioning background.

The reference notes summarize only the parts needed for implementation. For
version-sensitive API details, consult the linked official documentation.
