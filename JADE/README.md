# JADE

## Build and run

Requirements: `make` and a C++11 compiler. This implementation uses `../Problem.h` and `../tool.h`. Keep the repository directory structure intact.

From the repository root:

```sh
cd JADE
make
./jade 10 2 2000 10 20
```

Objective function IDs are defined in `../Problem.h`; the example uses ID 10 (Ackley).

## Arguments

```sh
./jade function runs max_evaluations dimension population
```

| Argument | Meaning |
| --- | --- |
| `function` | Objective function ID; 10 selects Ackley. |
| `runs` | Number of runs. |
| `max_evaluations` | Trial evaluation limit per run; initialization is counted separately. |
| `dimension` | Number of variables. |
| `population` | Population size; use at least 4. |

Supply every argument in the stated order and use positive integer counts.
The program does not validate missing or malformed arguments.
Use objective function IDs from 1 to 13.

## Output

The terminal prints best fitness, its running average and the number of trial evaluations. `output.txt` is overwritten each run and retains the last run. Full generations are processed, so the trial evaluation limit may be exceeded.

`output.txt`, where applicable, is written in the current working directory.

## Clean

```sh
make clean
```

This removes the compiled `jade` executable.
