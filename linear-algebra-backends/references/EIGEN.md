# Eigen practical reference

Eigen is useful as a C++ matrix/vector/view/expression layer. It does not remove
the need to understand data layout or backend choice.

## Rules

- Use `.noalias()` only when the destination truly does not alias expression
  inputs.
- Use `Eigen::Map`/strided views to expose existing buffers without copies.
- Prefer fixed-size objects for genuinely small compile-time kernels when this
  helps generated code.
- For large dense products, benchmark the actual configuration and know whether
  Eigen is using its own kernels or an external BLAS.
- Inspect temporaries in hot expressions; convenience syntax is not proof of
  zero allocation/copy.
- Do not express a Toeplitz/matrix-free operator as `MatrixX*` merely to gain
  Eigen syntax.

## Solver boundary

Eigen iterative solvers can be useful orchestration, but a custom
performance-critical operator/preconditioner should expose a direct apply/solve
path with clear ownership and no hidden materialization.

If solver overhead becomes significant relative to matvec/preconditioner cost,
profile it rather than assuming the high-level solver remains negligible.
