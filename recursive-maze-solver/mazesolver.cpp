// Assumption: Maze file is formatted exactly like test case and is case sensitive(Cols: Rows: Start: Finish:)

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// Reads file data and places the coordinates in a maze. Also records all relevant variables
void readFile(bool ***maze, const string &filename, int &total_rows, int &total_columns, int &start_x, int &start_y, int &finish_x, int &finish_y)
{
    ifstream file(filename);
    if (file.fail())
    {
        cerr << "File did not open!" << endl;
        exit(0);
    }
    string line;
    int row = 0;
    while (getline(file, line))
    {
        if (line.size() >= 6 && line.substr(0, 5) == "Rows:")
        {
            total_rows = stoi(line.substr(6));
        }
        else if (line.size() >= 6 && line.substr(0, 5) == "Cols:")
        {
            total_columns = stoi(line.substr(6));
            (*maze) = new bool *[total_rows];
            for (int i = 0; i < total_rows; i++)
            {
                (*maze)[i] = new bool[total_columns];
                for (int j = 0; j < total_columns; j++)
                {
                    (*maze)[i][j] = false; // Initialize maze cells to empty
                }
            }
        }
        else if (line.size() >= 6 && line.substr(0, 6) == "Start:")
        {
            start_x = stoi(line.substr(8));
            start_y = stoi(line.substr(10));
        }
        else if (line.size() >= 7 && line.substr(0, 7) == "Finish:")
        {
            finish_x = stoi(line.substr(9));
            finish_y = stoi(line.substr(11));
        }
        else if (line.size() >= 2 && line[0] == '(')
        {
            int x, y;
            x = stoi(line.substr(1));
            y = stoi(line.substr(3));
            (*maze)[x][y] = true;
        }
    }
}
// Prints the maze
void printMaze(bool **maze, int total_rows, int total_columns)
{
    for (int i = 0; i < total_rows; i++)
    {
        for (int j = 0; j < total_columns; j++)
        {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
// Checks if the recursive function has left the bounds of the maze
bool boundCheck(bool **maze, int start_x, int start_y, int total_rows, int total_columns)
{
    if (start_x >= 0 && start_x < total_rows && start_y >= 0 && start_y < total_columns && maze[start_x][start_y] == true)
    {
        return true;
    }
    return false;
}
// The recursive function that uses backtracking to reach the finish coordinates
bool solve(bool **maze, int start_x, int start_y, int total_rows, int total_columns, int finish_x, int finish_y, bool **solution)
{
    if (start_x == finish_x && start_y == finish_y)
    {
        solution[finish_x][finish_y] = true;
        return true;
    }
    if (boundCheck(maze, start_x, start_y, total_rows, total_columns) == true)
    {
        if (solution[start_x][start_y] == 1)
        {
            return false;
        }
        solution[start_x][start_y] = 1;
        if (solve(maze, start_x + 1, start_y, total_rows, total_columns, finish_x, finish_y, solution) == true)
        {
            return true;
        }
        if (solve(maze, start_x - 1, start_y, total_rows, total_columns, finish_x, finish_y, solution) == true)
        {
            return true;
        }
        if (solve(maze, start_x, start_y + 1, total_rows, total_columns, finish_x, finish_y, solution) == true)
        {
            return true;
        }
        if (solve(maze, start_x, start_y - 1, total_rows, total_columns, finish_x, finish_y, solution) == true)
        {
            return true;
        }
        solution[start_x][start_y] = 0;
        return false;
    }
    return false;
}
// The recursive function that the solution maze and a temporary maze to print the coordinates
bool output(bool **maze, int start_x, int start_y, int total_rows, int total_columns, int finish_x, int finish_y, bool **solution)
{
    if (start_x == finish_x && start_y == finish_y)
    {
        solution[finish_x][finish_y] = true;
        cout << "(" << start_x << "," << start_y << ")]" << endl;
        return true;
    }
    if (boundCheck(maze, start_x, start_y, total_rows, total_columns) == true)
    {
        if (solution[start_x][start_y] == 1)
        {
            return false;
        }
        solution[start_x][start_y] = 1;
        cout << "(" << start_x << "," << start_y << "), ";
        if (output(maze, start_x + 1, start_y, total_rows, total_columns, finish_x, finish_y, solution) == true)
        {
            return true;
        }
        if (output(maze, start_x - 1, start_y, total_rows, total_columns, finish_x, finish_y, solution) == true)
        {
            return true;
        }
        if (output(maze, start_x, start_y + 1, total_rows, total_columns, finish_x, finish_y, solution) == true)
        {
            return true;
        }
        if (output(maze, start_x, start_y - 1, total_rows, total_columns, finish_x, finish_y, solution) == true)
        {
            return true;
        }
        solution[start_x][start_y] = 0;
        return false;
    }
    return false;
}
// Main solver function that calls the resursive function
bool mazeSolver(bool **maze, int starting_x, int starting_y, int total_rows, int total_columns, int finish_x, int finish_y, bool ***solution, bool ***temp)
{
    (*solution) = new bool *[total_rows];
    for (int i = 0; i < total_rows; i++)
    {
        (*solution)[i] = new bool[total_columns];
        for (int j = 0; j < total_columns; j++)
        {
            (*solution)[i][j] = false; 
        }
    }
    solve(maze, starting_x, starting_y, total_rows, total_columns, finish_x, finish_y, (*solution));

    (*temp) = new bool *[total_rows];
    for (int i = 0; i < total_rows; i++)
    {
        (*temp)[i] = new bool[total_columns];
        for (int j = 0; j < total_columns; j++)
        {
            (*temp)[i][j] = false;
        }
    }

    for (int i = 0; i < total_rows; i++)
    {
        for (int j = 0; j < total_columns; j++)
        {
            if ((*solution)[i][j] == true)
            {
                cout << "-----SolvedMaze-----" << endl;
                printMaze((*solution), total_rows, total_columns);
                cout << "Success! The path is: [";
                output((*solution), starting_x, starting_y, total_rows, total_columns, finish_x, finish_y, (*temp));
                return 0;
            }
        }
    }
    cout << "Maze has no solution!" << endl;
    return 0;
}
// Main function
int main()
{
    bool **maze;
    int total_rows, total_columns;
    int starting_x, starting_y;
    int finish_x, finish_y;
    bool **solution;
    bool **temp;

    readFile(&maze, "maze.txt", total_rows, total_columns, starting_x, starting_y, finish_x, finish_y);
    cout << "-----InitialMaze-----" << endl;
    printMaze(maze, total_rows, total_columns);
    mazeSolver(maze, starting_x, starting_y, total_rows, total_columns, finish_x, finish_y, &solution, &temp);
    return 0;
}