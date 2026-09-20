# nla-anget-config

Shared Codex skills for performance-oriented numerical linear algebra and scientific C/C++.

The repository is designed to be mounted directly under .agents/skills in a working repository. It gives Codex practical guidance for choosing between custom algorithms and mature numerical libraries, implementing structured/block operators, validating numerical code, and optimizing only after correctness is established.

## Design philosophy

The default workflow is:

~~~text
clear reference implementation
        ↓
correctness / numerical validation
        ↓
benchmark and profile
        ↓
identify the dominant bottleneck
        ↓
optimize the dominant path
        ↓
revalidate
        ↓
benchmark again
~~~

Correctness comes first. Optimization begins only after a clear reference path works and has been validated.

After correctness is established, runtime, memory traffic, and scalability are the default priorities unless the user explicitly prioritizes convenience, genericity, API simplicity, portability, or maintainability.

Use mature libraries for optimized kernels they already implement. Implement the mathematical structure and orchestration that those libraries do not represent.

Typical split of responsibilities:

- GEMM/TRSM and other dense kernels → BLAS;
- dense LU/QR/SVD/eigensolvers → LAPACK;
- FFT/DFT → FFTW;
- sparse multifrontal factorization → MUMPS when appropriate;
- Eigen → C++ containers, expressions, views, and glue where it does not hide performance-critical layout or temporaries;
- Toeplitz/multilevel storage → custom;
- Toeplitz-to-circulant embedding → custom;
- FFT Toeplitz matvec → custom orchestration + FFTW;
- block operator composition/permutations → custom;
- low-rank U(V* x) → custom orchestration + BLAS kernels.

A central rule of the configuration is:

> Use libraries for kernels; implement structure yourself.

## Skills

### linear-algebra-backends

Use when choosing or calling BLAS, LAPACK, Eigen, or FFTW.

Covers BLAS levels and routine selection, GEMM/GEMV/TRSM and batching, row/column-major layout and leading dimensions, LAPACK factorization/solve workflows, Eigen aliasing and Map/views, FFTW plans, batching, strides, normalization, threading, wisdom, and the decision between custom code and a library implementation.

Small API examples are available under the skill's assets directory.

### structured-matrices

Use when the matrix/operator itself has Toeplitz, block-Toeplitz, multilevel-Toeplitz, BTTB, circulant, or related displacement structure.

Covers signed displacement indexing, compact storage, direct structured reference matvec, multilevel flattening/index maps, Toeplitz-to-circulant embedding, FFT-accelerated matvec, vector/component block channels, and dense-vs-structured-vs-FFT validation.

### block-linear-algebra

Use for heterogeneous block systems where different blocks have different representations: dense, low-rank, Toeplitz, diagonal, sparse, or matrix-free.

The skill emphasizes explicit block equations, transparent data layout, GEMM-friendly batching, and avoiding unnecessary global matrix materialization.

### performance-engineering

Use when profiling or optimizing an already working numerical implementation.

Covers arithmetic intensity and Roofline-style reasoning, memory traffic, BLAS-level transformations, cache reuse, SIMD/compiler vectorization, OpenMP/BLAS/FFTW/MPI thread interaction, oversubscription, NUMA concerns, and reproducible CPU benchmarking.

This skill should not trigger merely because numerical code is being written.

### numerical-validation

Use when testing or comparing numerical implementations.

Covers reference implementations, normwise/componentwise error, residual, forward/backward error, conditioning-aware interpretation, index/layout tests, approximate/compressed operators, and reproducible benchmark methodology.

### toeplitz-preconditioning

Use for preconditioning Toeplitz, block-Toeplitz, multilevel-Toeplitz, or related block systems.

Covers Strang and T. Chan circulants, block/multilevel circulant analogues, BCCB-style frequency-domain block solves, ILU(0/1/2), block-diagonal and block lower-triangular preconditioners, plus setup/apply/iteration/total-time comparison.

The skill explicitly warns against applying sparse ILU directly to a fully dense Toeplitz matrix without first defining a meaningful sparse surrogate.

### sparse-direct-solvers

Use for sparse direct solving, especially MUMPS.

Covers MUMPS C/C++ lifecycle, analysis/factorization/solve phases, centralized and distributed assembled input, 1-based MUMPS indexing, MPI execution, factorization reuse, diagnostics, and build/link/debug workflow.

A minimal MUMPS example is provided under assets.

## How Codex should combine skills

The skills are intentionally composable.

~~~text
"Implement a 3-level Toeplitz FFT matvec"
    structured-matrices
    + linear-algebra-backends

"Optimize that matvec"
    structured-matrices
    + performance-engineering
    + numerical-validation

"Build a Chan preconditioner for a block-Toeplitz operator"
    toeplitz-preconditioning
    + structured-matrices

"My block system has Toeplitz, dense, and low-rank blocks"
    block-linear-algebra
    + structured-matrices
    + linear-algebra-backends

"MUMPS factorization fails"
    sparse-direct-solvers
~~~

The root ROUTING_EVALS.md contains additional prompts for checking that skill descriptions route Codex to the intended subset of the repository.

## Installation

If this is the only shared skill repository:

~~~bash
mkdir -p .agents
git submodule add https://github.com/Abrackadabrr/nla-anget-config.git .agents/skills
~~~

If a project combines this repository with another skill repository, keep both as independent submodules and expose their individual skill directories under one flat .agents/skills namespace, for example through symlinks.

Conceptually:

~~~text
project/
├── AGENTS.md
├── .agent-config/
│   ├── nla/                  # this repository
│   └── domain/               # another skill repository
└── .agents/
    └── skills/
        ├── structured-matrices -> ../../.agent-config/nla/structured-matrices
        ├── linear-algebra-backends -> ../../.agent-config/nla/linear-algebra-backends
        └── ...
~~~

## Repository layout

~~~text
nla-anget-config/
├── README.md
├── SOURCES.md
├── ROUTING_EVALS.md
├── linear-algebra-backends/
│   ├── SKILL.md
│   ├── references/
│   └── assets/
├── structured-matrices/
│   ├── SKILL.md
│   └── references/
├── block-linear-algebra/
│   ├── SKILL.md
│   └── references/
├── performance-engineering/
│   ├── SKILL.md
│   └── references/
├── numerical-validation/
│   ├── SKILL.md
│   └── references/
├── toeplitz-preconditioning/
│   ├── SKILL.md
│   └── references/
└── sparse-direct-solvers/
    ├── SKILL.md
    ├── references/
    └── assets/
~~~

## Scope boundary

This repository explains generic numerical-linear-algebra implementation and performance engineering.

Application-domain reasons for matrix structure belong to the consuming domain skills. For example, an electromagnetic skill should explain why a discretized operator is translation invariant or block-Toeplitz; this repository explains how to store, apply, precondition, validate, and optimize that operator.

## Maintenance rule

Keep SKILL.md files short and focused on routing. Put detailed formulas, library notes, implementation recipes, and examples in references or assets.

When adding a new skill, update ROUTING_EVALS.md with both positive and negative trigger examples so the skill set remains selective rather than loading unnecessary context.
