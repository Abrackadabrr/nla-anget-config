# Preconditioner Implementation Checklist

1. Write `apply_A(x)`.
2. Write `apply_P_inverse(r)` as a solve/application, not an explicit inverse.
3. Test both independently.
4. Pick a Krylov solver compatible with matrix/preconditioner properties.
5. State left/right preconditioning:
   - left: `P^{-1} A x = P^{-1} b`;
   - right: `A P^{-1} y = b, x=P^{-1}y`.
6. Count preconditioner setup separately from one application.
7. Cache FFT spectra/factorizations used by repeated applications.
8. Protect pointwise Fourier divisions against numerical singularity where
   mathematically justified.
9. Compare with no preconditioner on the same stopping criterion.
10. Report true residual of the original system, not only the internal
    preconditioned residual.
