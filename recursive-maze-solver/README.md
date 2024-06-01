# Maze Solver

This project is a maze-solving program implemented in C++ as a CS200 course assignment. The program uses recursion to find the correct path through a maze provided as a text file. The maze has a single starting point and a single finishing point.

## Features

- Solve mazes with a single start and finish point
- Input maze data from a text file
- Output the correct path through the maze
- Display the maze with the path

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++, clang)

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/mazesolver.git
    cd mazesolver
    ```

2. Compile the program:

    ```bash
    g++ mazesolver.cpp -o mazesolver
    ```

3. Run the program:

    ```bash
    ./mazesolver maze.txt
    ```

## Maze File Format

The maze is represented as a text file with the following format:
Rows: 6
Cols: 6
Start: (1,5)
Finish: (4,0)
(0,1)
(0,2)
(1,2)
(1,4)
(1,5)
(2,2)
(2,4)
(3,0)
(3,1)
(3,2)
(3,3)


- `Rows`: Number of rows in the maze
- `Cols`: Number of columns in the maze
- `Start`: Starting cell in the format (row, column)
- `Finish`: Finishing cell in the format (row, column)
- List of path cells in the format (row, column). By default, all cells are walls.

## Output Format

The program outputs the path through the maze and displays the maze with the path:

Success! The path is: [(1,5), (1,4), (2,4), (3,4), (3,3), (3,2), (3,1), (3,0), (4,0)]

0 1 2 3 4 5
0 X X X X
1 X X X P S
2 X X X P X
3 P P P P P X
4 F X X X X
5 X X


- `P`: Path
- `S`: Start
- `F`: Finish
- `X`: Wall

## Classes and Methods

### MazeSolver Class

- **Attributes:**
  - `maze` (2D array of bool): Represents the maze grid
  - `rows` (int): Number of rows in the maze
  - `cols` (int): Number of columns in the maze
  - `start` (pair<int, int>): Starting cell
  - `finish` (pair<int, int>): Finishing cell

- **Methods:**
  - `MazeSolver(const string& filename)`: Constructor that reads the maze from a file
  - `bool solveMaze(int row, int col, vector<pair<int, int>>& path)`: Recursively solves the maze
  - `void displayMaze(const vector<pair<int, int>>& path)`: Displays the maze with the path

## Usage

1. Create a maze file in the specified format.
2. Run the program with the maze file as an argument.
3. The program will output the path and display the maze.

## Acknowledgements

- This project is part of the CS200 course assignments.
- Thanks to the course instructors for their guidance and support.
