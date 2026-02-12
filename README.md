# Routing Program - DA Project 1

A C++ graph-based routing engine developed for the **Desenho de Algoritmos (DA)** course at **FEUP (Faculdade de Engenharia da Universidade do Porto)**, academic year 2024/2025.

The program implements **Dijkstra's Algorithm** to calculate optimal routes between locations, supporting various constraints such as avoiding specific nodes/edges or ensuring a specific node is included in the path.

## Authors
*   **João Júnior**
*   **Mário Pereira**
*   **Vasco Sá**

## Features
- **Shortest Path**: Computes the most efficient route between two points.
- **Alternative Route**: Calculates a secondary route by excluding the primary shortest path.
- **Restricted Routing**:
    - **Avoid Nodes**: Find paths that do not pass through specific locations.
    - **Avoid Segments**: Find paths that avoid specific road segments.
    - **Include Node**: Ensure the calculated path passes through a specific intermediate location.
- **Flexible Input**: Supports both interactive command-line input and batch processing via `input.txt`.
- **CSV Data Loading**: Dynamic graph construction from `Locations.csv` and `Distances.csv`.

## Project Structure
```text
.
├── bin/            # Compiled executables
├── data/           # CSV datasets (Locations and Distances)
├── docs/           # Doxygen configuration (Doxyfile)
├── include/        # Header files (.h)
│   ├── data_structs/   # Custom Graph and Priority Queue classes
│   └── helper/         # Routing logic and CSV loaders
├── src/            # Source code (.cpp)
├── Makefile        # Build script
├── input.txt       # Input file for batch testing
└── README.md       # Project documentation
```

## How to Compile
You can compile the project using the provided `Makefile`. Open your terminal in the root directory and run:

```bash
make
```

Alternatively, you can compile manually using `g++`:

```bash
g++ -std=c++11 -Wall -Wextra -Iinclude src/best-route.cpp -o bin/best-route.exe
```

## Usage
Run the executable located in the `bin` folder:

```bash
./bin/best-route.exe
```

### Input Modes
1.  **`cmd`**: Interactive mode. Enter parameters directly into the console.
    - Format: `mode source destination avoidNodes avoidSegments includeNode`
    - Use `_` for empty restricted fields.
2.  **`file`**: Reads parameters from a file named `input.txt` in the root directory.

### Output
- For `cmd` mode, results are displayed in the console.
- For `file` mode, results are written to `output.txt`.

## Requirements
- C++11 compliant compiler (e.g., `g++`).
- `make` (optional, for build automation).
- Doxygen (optional, for generating documentation).

## Credits
- Original Graph and MutablePriorityQueue classes provided by **Gonçalo Leão**.
- Developed as part of the **DA 2024/2025** course at **FEUP**.
