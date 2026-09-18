# Cat-Population-Simulation
An interactive C++ console project that models a fictional cat population over simulated years. Cats have randomized attributes, age and reproduce, and may acquire special “Marvel” powers that affect their lifespan and behavior.

## Features

- Model shared animal attributes through a `Mammal` base class and a derived `Cat` class.
- Assign names from a text file and randomize gender, color, and special powers.
- Simulate aging, reproduction, and deaths.
- Allow special-powered cats to pass their powers to other cats.
- Offer an option to randomly remove half the population.
- Record population snapshots and events in text files.

## Project Files

| File | Purpose |
| --- | --- |
| `main.cpp` | Interactive menu and simulation loop |
| `mammal.h` | Base class containing age and gender |
| `cat.h` | Derived class containing name, color, and power attributes |
| `process.h` | Population management and simulation logic |
| `names.txt` | User-provided list of possible cat names |

## Requirements

- A C++11-compatible compiler or newer
- A `names.txt` file in the working directory

## Build and Run

Before compiling the supplied source:

1. In `main.cpp`, change `#include "Process.h"` to `#include "process.h"` to match the filename on case-sensitive systems.
2. Add `#include <numeric>` and `#include <functional>` to `process.h` for `std::iota` and `std::greater`.
3. Create `names.txt` with whitespace-separated names, for example:

```text
Luna
Milo
Bella
Oliver
```

Compile and run from the project directory:

```sh
g++ -Wall -Wextra -std=c++11 main.cpp -o cat_simulation
./cat_simulation
```

On Windows, run the resulting executable as `cat_simulation.exe`.

## Usage

At each prompt:

- Enter `1` to advance the simulation by one year.
- Enter `2` to advance one year and then randomly remove half the population.
- The menu offers other input to end the program, but the current outer loop can restart the prompt. Use Ctrl+C if needed.

Run the program from the directory containing `names.txt`. Generated logs are appended to existing files:

| Output | Contents |
| --- | --- |
| `output.txt` | Births, deaths, and population snapshots |
| `debugLog.txt` | Aging and power-transfer details |
| `populationCullLog.txt` | Population removal details |

## Simulation Rules

- Initialization generates five randomized cats.
- New cats have a 2% chance of receiving special powers.
- Ordinary cats reach their lifespan limit at age 10; powered cats at age 25.
- Each eligible female produces one kitten per eligible male during a yearly step. Eligible cats are at least two years old and do not have special powers.
- Kittens inherit their mother's color.

## Design and Current Limitations

The project uses inheritance, encapsulation, STL vectors and algorithms, random number generation, and file I/O. `Process` manages Cat objects alongside separate vectors of their attributes.

The current implementation is an academic prototype. Its constructor adds an initial Cat object without matching entries in the attribute vectors, which can cause population records to become inconsistent. Power-transfer indices are collected before removals and can become invalid afterward. The menu's exit behavior also needs refinement. Population growth is uncapped and can become rapid.

## Concepts Practiced

Object-oriented design, constructors, inheritance, collection management, simulation logic, randomized events, and persistent text logging.
