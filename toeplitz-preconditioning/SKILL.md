---
name: toeplitz-preconditioning
description: Implement practical preconditioners for Toeplitz and block/multilevel Toeplitz systems, including Strang/Chan circulants, ILU(k), block diagonal, and block triangular schemes.
---

# Toeplitz and Block Preconditioning

This skill is an implementation-oriented theoretical reference.

Before coding a preconditioner:

1. state matrix structure and symmetry/definiteness;
2. state the Krylov solver;
3. define left/right/split preconditioning convention;
4. define how P^{-1} is applied without explicitly forming an inverse;
5. implement a small reference;
6. compare iteration count, setup time, apply time, and memory.

Read the recipe references before implementation.
