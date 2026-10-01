*This project has been created as part of the 42 curriculum by vpoka.*

# Philosophers

I never thought philosophy would be so deadly.

## Table of contents

- [Description](#description)
- [Instructions](#instructions)
- [How it works](#how-it-works)
- [Resources](#resources)
- [Project structure](#project-structure)
- [Testing](#testing)
- [Troubleshooting](#troubleshooting)
- [Status](#status)
- [License](#license)

## Description

**Philosophers** is the classic *Dining Philosophers* concurrency problem, solved
in C with POSIX threads and mutexes.

One or more philosophers sit at a round table with a bowl of spaghetti in the
middle and exactly as many forks as philosophers. Each philosopher repeats the
cycle **eat → sleep → think**, and needs **two forks** (left and right) to eat.
The simulation stops when a philosopher starves, or, optionally, when every
philosopher has eaten a given number of times. Philosophers never communicate
and cannot know whether a neighbour is about to die, so the program has to
schedule them so that nobody does.

The goal of the project is to learn the basics of threading a process: creating
threads and using mutexes to protect shared state, with no data races, no
deadlocks and no duplicated forks.

**Highlights:**

- One thread per philosopher, plus one monitor thread.
- One mutex per fork; the log output is serialized so messages never overlap.
- Death is detected and printed by the monitor, which polls every millisecond
  (the subject requires the message within 10 ms of the death).
- No global variables; all state lives in one `t_data` structure.
- Validated input and tracked initialization, so cleanup only releases what
  was actually created, even after a partial failure.

## Instructions

### Prerequisites

- A C compiler (`cc`)
- Make
- POSIX threads (`pthread`)

The project was developed and tested on Linux. No third-party libraries are
used.

### Build

All commands are run from the `philo/` directory, which contains the Makefile:

```sh
cd philo
make
```

This compiles with `cc -Wall -Wextra -Werror -pthread` and produces the `philo`
executable. Re-running `make` does not relink if nothing changed.

| Command          | Effect                                                              |
| ---------------- | ------------------------------------------------------------------- |
| `make`, `make all` | Build the `philo` executable                                      |
| `make clean`     | Remove object files (`obj/`) (alias `make c`)                       |
| `make fclean`    | Remove object files and all executables (alias `make f`)            |
| `make re`        | `fclean`, then `all`                                                |
| `make garbage`   | Build a debug executable named `garbage` with `-g` (alias `make g`) |
| `make sanitize`  | Build an executable named `sanitize` with `-g -fsanitize=thread` (alias `make s`) |

> `garbage` and `sanitize` reuse the same `obj/` directory as `philo`. Run
> `make fclean` before them (and again before going back to `make`), otherwise
> existing object files are linked as they are and are not rebuilt with the new
> flags.

### Run

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Meaning | Accepted values |
| -------- | ------- | --------------- |
| `number_of_philosophers` | Number of philosophers, and of forks | Digits only, at least 1, must fit in 16 bits |
| `time_to_die` | Milliseconds a philosopher can go without starting a meal before dying | Digits only, must fit in 64 bits |
| `time_to_eat` | Milliseconds spent eating (holding both forks) | Digits only, must fit in 64 bits |
| `time_to_sleep` | Milliseconds spent sleeping | Digits only, must fit in 64 bits |
| `number_of_times_each_philosopher_must_eat` | Optional. The simulation stops once every philosopher has eaten this many times | Digits only, at least 1, must fit in 16 bits |

Without the optional argument the simulation runs until a philosopher dies.

**Examples:**

```sh
./philo 5 800 200 200      # nobody should die; stop it with Ctrl+C
./philo 5 800 200 200 7    # stops once every philosopher has eaten 7 times
./philo 4 310 200 100      # too tight: a philosopher dies
./philo 1 800 200 200      # one fork only: takes it, then dies at 800 ms
```

**Output:** one line per state change, in the format required by the subject:

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

`timestamp_in_ms` is the time since the simulation started and `X` is the
philosopher number (1 to `number_of_philosophers`). Example, from
`./philo 1 800 200 200`:

```
0 1 has taken a fork
800 1 died
```

**Exit code:** `0` when the simulation ends normally (including a philosopher
dying or the meal limit being reached), `1` on invalid input or an internal
error, with a message on stderr.

## How it works

- **Threads.** `main` initializes the data, then `start_simulation` creates one
  thread per philosopher and one monitor thread. Start mutexes are locked while
  the threads are created and released together, so all of them begin at the
  same moment, after the simulation start time has been recorded.
- **Forks.** Each fork is a mutex. Philosophers with an even index take their
  own fork first and their neighbour's second; those with an odd index take
  them in the opposite order. This breaks the circular wait that causes
  deadlocks.
- **Staggered start.** Before their first meal, philosophers other than the
  first wait for a short "initial think" delay computed from their position,
  the parity of the philosopher count, `time_to_eat` and `time_to_sleep`. This
  spreads out the first fork grabs.
- **Monitor.** Every millisecond the monitor checks each philosopher's last meal
  time (protected by a per-philosopher mutex). If `time_to_die` has elapsed it
  prints the death and raises the termination flag. With a meal limit it also
  checks whether everybody is full.
- **Termination.** A shared flag, protected by its own mutex, tells every
  thread to stop. Sleeps are cut into slices of at most 10 ms that check the
  flag, so threads react quickly, and `print_state` refuses to print once the
  flag is set. That way nothing is printed after the death message.
- **Timing.** `precise_sleep` combines a short `usleep` with a polling loop on
  `gettimeofday` to limit oversleeping.
- **Cleanup.** Arrays record which mutexes and threads were successfully
  created, so on any failure only those are joined or destroyed before the
  memory is freed.

## Resources

- [Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem),
  background on the classic synchronization problem.
- Manual pages: `pthread_create(3)`, `pthread_join(3)`, `pthread_detach(3)`,
  `pthread_mutex_init(3)`, `pthread_mutex_lock(3)`, `pthread_mutex_destroy(3)`,
  `gettimeofday(2)`, `usleep(3)`.

### AI usage

AI assistants were used for:

- Creating documentation and commit messages.
- Creating test suites during development. These are not part of the
  repository anymore, but remain visible in older commits.
- Creating this README
- Likely also analyzing weaknesses and improving the performance of the code.

The exact tools used are not recalled.

## Project structure

```
.
└── philo/
    ├── Makefile
    ├── include/
    │   ├── philo.h               # prototypes and includes
    │   ├── structs.h             # simulation-wide data structures
    │   ├── structs_threads.h     # per-thread (philosopher / monitor) structures
    │   └── types.h               # t_ms, t_count, enums, constants
    └── src/
        ├── main.c                # entry point: init, run, clean up
        ├── cleanup/              # free data, join threads, destroy mutexes
        ├── initialization/       # input parsing, mutexes, philosopher and monitor data
        ├── simulation/           # start-up, philosopher actions, monitor
        └── utils/                # memory, mutex, output, string, thread and time helpers
```

Only the mandatory part (`philo/`) is implemented; there is no `philo_bonus/`.

## Testing

No tests are included in the current tree. Two ways to check the program:

1. **Race detection** with ThreadSanitizer (note the executable is `sanitize`):

   ```sh
   cd philo
   make fclean
   make sanitize
   ./sanitize 5 800 200 200 7
   ```

   ThreadSanitizer prints a report if it finds a data race. Run `make fclean`
   afterwards before building `philo` again.

2. **Manual scenarios**, using the examples above: a normal run, a meal-limit
   stop, a single philosopher, a tight timing that must produce a death, and a
   large philosopher count. For deaths, check that the `died` line is printed
   promptly and that no line follows it.

Earlier shell test scripts (`test_suite.sh` and `comprehensive_philo_test.sh`)
were removed in commit `9ccac2c` and can still be read from history, for
example `git show 9ccac2c^:test_suite.sh`.

## Troubleshooting

- **`Incorrect input: wrong amount of arguments`**: the program needs 4 or 5
  arguments: the philosopher count, the three times, and optionally the meal
  limit.
- **`Non-numeric character in argument` or `number is too large`**: arguments
  must be plain digits (no sign, no spaces) and must fit their type, which is
  16 bits for the philosopher count and meal limit.
- **`needs at least 1 philosopher` or `meal count has to be at least 1`**: a
  count of `0` is rejected.
- **A single philosopher always dies**: this is expected. There is only one
  fork, so the philosopher takes it, can never eat, and dies after
  `time_to_die` ms.
- **`make sanitize` seems to have no effect**: stale object files from an
  earlier build were reused. Run `make fclean` first.

## Status

Finished. Passed the 42 evaluation with a score of 100/100.
