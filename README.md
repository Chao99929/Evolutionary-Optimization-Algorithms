# Evolutionary Optimization Algorithms

Original C++ implementations of DE, JADE, SHADE, L-SHADE and PSO for
continuous numerical optimization.

## Build and run

Requirements: `make` and a C++11 compiler. Compile each algorithm from the
repository root:

```sh
make -C DE
make -C JADE
make -C SHADE
make -C LSHADE
make -C PSO
```

Run examples:

```sh
./DE/de 2 100 10 20 0.5 0.9
./JADE/jade 10 2 2000 10 20
./SHADE/shade 10 2 2000 10 20 6
./LSHADE/lshade 10 2 2000 10 20 4 6
./PSO/pso 2000 20 10
```

Each directory has its own execution guide:

- [DE](DE/README.md)
- [JADE](JADE/README.md)
- [SHADE](SHADE/README.md)
- [L-SHADE](LSHADE/README.md)
- [PSO](PSO/README.md)

Supply all arguments in order. These original programs use `atoi()` and
`atof()` without argument validation. Evaluation limits and output behavior
are described in each guide; they differ between implementations.

Use `make -C DE clean` (or another algorithm directory) to remove its executable.

## Objective functions

DE and PSO use Ackley on [-32, 32]. JADE, SHADE and L-SHADE use the supplied
`Problem.h`, which dispatches IDs 1–13; ID 10 selects Ackley and ID 1 selects
Sphere. The shared objective definitions are the original supplied source.

## Repository structure

```text
DE/             DE sources, makefile and execution guide
JADE/           JADE sources, makefile and execution guide
SHADE/          SHADE sources, makefile and execution guide
LSHADE/         L-SHADE sources, makefile and execution guide
PSO/            PSO sources, makefile and execution guide
Problem.h       Original shared objective definitions
tool.h         Original shared utilities
```

Keep `Problem.h` and `tool.h` alongside the algorithm directories so relative
includes resolve. Build artifacts, output files and local backups are ignored
by Git.
