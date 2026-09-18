# PSO

## Build and run

Requirements: `make` and a C++11 compiler. This implementation uses `main.cpp` and `PSO.h`.

From the repository root:

```sh
cd PSO
make
./pso 2000 20 10
```

This program uses the Ackley function on [-32, 32].

## Arguments

```sh
./pso max_evaluations population dimension
```

| Argument | Meaning |
| --- | --- |
| `max_evaluations` | Objective evaluation limit, including initialization. |
| `population` | Number of particles; use a positive integer. |
| `dimension` | Number of variables; use a positive integer. |

Supply every argument in the stated order and use positive integer counts.
The program does not validate missing or malformed arguments.

## Output

The terminal prints best and average fitness. No `output.txt` is created. Full swarm updates are processed, so the evaluation limit may be exceeded. The program performs one run with c1=c2=2.0, inertia=0.7 and initial velocities in [-12.8, 12.8]; velocity clamping is disabled in the original source.

`output.txt`, where applicable, is written in the current working directory.

## Clean

```sh
make clean
```

This removes the compiled `pso` executable.
