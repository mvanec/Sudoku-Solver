#include "Sudoku.h"

#include <QDebug>

constexpr auto MAX_SIZE = 9;
constexpr auto BOX_SIZE = 3;

Sudoku::Sudoku()
{
    grid.resize(9, std::vector<int>(9, 0));
    status = "";
}

// Solve the board. Check first if the board is valid, then execute the solver
bool Sudoku::solve()
{
    if (!isValidBoard()) {
        status = "Invalid board: duplicate numbers in rows, columns, or boxes";
        return false;
    }
    return solveSudoku();
}

bool Sudoku::setCell(int row, int col, int value)
{
    if (row < 0 || row >= 9 || col < 0 || col >= 9) {
        qDebug()
            << QString("Invalid row or column index: (%1, %2)").arg(row).arg(col);
        return false;
    }
    if (value < 0 || value > 9) {
        qDebug() << QString("Invalid cell value %1 in (%2, %3)")
                        .arg(value)
                        .arg(row)
                        .arg(col);
        return false;
    }
    grid[row][col] = value;
    return true;
}

int Sudoku::getCell(int row, int col)
{
    if (row < 0 || row >= 9 || col < 0 || col >= 9) {
        qDebug()
            << QString("Invalid row or column index: (%1, %2)").arg(row).arg(col);
        return -1;
    }
    return grid[row][col];
}

QString Sudoku::getStatus() const { return status; }

// Make sure the board is valid. It should not have any duplicate numbers
// in the same row, or in the same column, or in the same 3x3 box.
bool Sudoku::isValidBoard() const
{
    for (int row = 0; row < MAX_SIZE; row++) {
        for (int col = 0; col < MAX_SIZE; col++) {
            int num = grid[row][col];
            if (num == 0) {
                continue;
            }
            if (duplicateInRow(row, num) || duplicateInCol(col, num) || duplicateInBox(row - row % 3, col - col % 3, num)) {
                qDebug() << "Duplicate found in board for " << num;
                return false;
            }
        }
    }
    return true;
}

// Check if the number is duplicated in the row
bool Sudoku::duplicateInRow(int row, int num) const
{
    int count = 0;
    for (int col = 0; col < MAX_SIZE; col++) {
        if (grid[row][col] == num) {
            count++;
        }
        if (count > 1) {
            return true;
        }
    }
    return false;
}

// Check if the number is duplicated in the column
bool Sudoku::duplicateInCol(int col, int num) const
{
    int count = 0;

    for (int row = 0; row < MAX_SIZE; row++) {
        if (grid[row][col] == num) {
            count++;
        }
        if (count > 1) {
            return true;
        }
    }
    return false;
}

// Check if the number is duplicated in each 3x3 box in the board
bool Sudoku::duplicateInBox(int boxStartRow, int boxStartCol, int num) const
{
    int count = 0;
    for (int row = 0; row < BOX_SIZE; row++) {
        for (int col = 0; col < BOX_SIZE; col++) {
            if (grid[row + boxStartRow][col + boxStartCol] == num) {
                count++;
            }
            if (count > 1) {
                return true;
            }
        }
    }
    return false;
}

// The main solver method, using a recursive backtrace algorithm
bool Sudoku::solveSudoku()
{
    int row, col;
    if (!findUnassignedLocation(row, col)) {
        status = "Solved";
        return true; // All cells are filled
    }

    for (int num = 1; num <= 9; ++num) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku()) {
                return true;
            }
            grid[row][col] = 0; // Undo the assignment
        }
    }
    status = "No solution";
    return false;
}

// Check if the found number is safe or valid for the cell
// This is slightly different than the duplicateIn* methods
// as it checks if the number is in the row or column or box before
// adding the number to the grid at the specified location.
bool Sudoku::isSafe(int row, int col, int num) const
{
    // Check if 'num' is not in current row
    for (int x = 0; x < 9; ++x) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    // Check if 'num' is not in current column
    for (int x = 0; x < 9; ++x) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    // Check if 'num' is not in current 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool Sudoku::findUnassignedLocation(int& row, int& col) const
{
    for (row = 0; row < 9; ++row) {
        for (col = 0; col < 9; ++col) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

