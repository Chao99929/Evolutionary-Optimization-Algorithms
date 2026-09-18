# L-SHADE

## Build and run

Requirements: `make` and a C++11 compiler. This implementation uses `../Problem.h` and `../tool.h`. Keep the repository directory structure intact.

From the repository root:

```sh
cd LSHADE
make
./lshade 10 2 2000 10 20 4 6
```

Objective function IDs are defined in `../Problem.h`; the example uses ID 10 (Ackley).

`main.cpp` uses the original `test2lshade.h` implementation.

## Arguments

```sh
./lshade function runs max_evaluations dimension initial_population min_population history
```

| Argument | Meaning |
| --- | --- |
| `function` | Objective function ID; 10 selects Ackley. |
| `runs` | Number of runs. |
| `max_evaluations` | Trial evaluation limit per run; initialization is counted separately. |
| `dimension` | Number of variables. |
| `initial_population` | Initial population size; at least min_population. |
| `min_population` | Minimum population size; use at least 4. |
| `history` | Parameter memory size; use a positive integer. |

Supply every argument in the stated order and use positive integer counts.
The program does not validate missing or malformed arguments.
Use objective function IDs from 1 to 13.

## Output

The terminal prints best fitness and its running average. `output.txt` is overwritten each run and retains the last run. The original implementation stops before a generation that would exceed the trial evaluation limit; some budget may remain unused.

`output.txt`, where applicable, is written in the current working directory.

## Clean

```sh
make clean
```

This removes the compiled `lshade` executable.
