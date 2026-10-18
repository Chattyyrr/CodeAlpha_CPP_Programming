/*
Internship Task 3: Sudoku Solver
- Represent the sudoku grid as a 2D array.
- Implement a backtracking algorithm to fill empty cells with valid numbers.
- Check for sudoku rules (row, column and 3x3 sub-grid constraints) before placing a number.
- Recursively try possible numbers until the puzzle is solved.
*/

#include <iostream>

#define N 9

bool isValid(int grid[N][N], int row, int col, int num) {
    for (int j = 0; j < N; ++j) {
        if (grid[row][j] == num)
            return false;
    }

    for (int i = 0; i < N; ++i) {
        if (grid[i][col] == num)
            return false;
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }

    return true;
}

bool findEmpty(int grid[N][N], int &row, int &col) {
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (grid[row][col] == 0)
                return true;
        }
    }
    return false;
}

bool solve(int grid[N][N]) {
    int row, col;

    if (!findEmpty(grid, row, col))
        return true;

    for (int num = 1; num <= 9; ++num) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;
            if (solve(grid))
                return true;
            grid[row][col] = 0;
        }
    }

    return false;
}

void print(int grid[N][N]) {
    for (int i = 0; i < N; ++i) {
        if (i % 3 == 0 && i != 0) {
            std::cout << "------+-------+------\n";
        }

        for (int j = 0; j < N; ++j) {
            if (j % 3 == 0 && j != 0) {
                std::cout << "| ";
            }

            if (grid[i][j] == 0) {
                std::cout << "  ";
            } else {
                std::cout << grid[i][j] << ' ';
            }

        }

        std::cout << '\n';
    }
}

int main() {
    int grid[N][N];

    std::cout << "=== SUDOKU SOLVER ===\n";
    std::cout << "Enter 9x9 grid (0 for empty cells):\n";

    for (int i = 0; i < N; ++i) {
        std::cout << "Row " << (i + 1) << ": ";
        
        for (int j = 0; j < N; ++j) {
            std::cin >> grid[i][j];
        }
    }

    std::cout << "------- Input -------\n";
    print(grid);

    std::cout << "Solving...\n";

    if (solve(grid)) {
        std::cout << "------- Solve -------\n";
        print(grid);
    } else {
        std::cout << "No solution exists.\n";
    }

    return 0;
}
