# DE

## Build and run

Requirements: `make` and a C++11 compiler. This implementation uses `../tool.h`. Keep the repository directory structure intact.

From the repository root:

```sh
cd DE
make
./de 2 100 10 20 0.5 0.9
```

This program uses the Ackley function on [-32, 32].

## Arguments

```sh
./de runs generations dimension population F CR
```

| Argument | Meaning |
| --- | --- |
| `runs` | Number of runs. |
| `generations` | Number of generations per run. |
| `dimension` | Number of variables. |
| `population` | Population size; use at least 4. |
| `F` | Fixed mutation factor, e.g. 0.5. |
| `CR` | Fixed crossover rate between 0 and 1. |

Supply every argument in the stated order and use positive integer counts.
The program does not validate missing or malformed arguments.

## Output

The terminal prints the minimum and running average. The original implementation opens `output.txt` once and closes it after the first run, so only the first run writes a convergence trace.

`output.txt`, where applicable, is written in the current working directory.

## Clean

```sh
make clean
```

This removes the compiled `de` executable.
