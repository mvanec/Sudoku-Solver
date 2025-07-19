#include "Sudoku.h"
#include <QDebug>

Sudoku::Sudoku()
    : grid(GRID_SIZE, std::vector<int>(GRID_SIZE, EMPTY_CELL))
{
}

void Sudoku::clear()
{
    for (auto& row : grid) {
        std::fill(row.begin(), row.end(), EMPTY_CELL);
    }
    status.clear();
}

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
    if (!isValidPosition(row, col)) {
        qDebug() << QString("Invalid position: (%1, %2)").arg(row).arg(col);
        return false;
    }

    if (!isValidValue(value, true)) {
        qDebug() << QString("Invalid value %1 at (%2, %3)").arg(value).arg(row).arg(col);
        return false;
    }

    grid[row][col] = value;
    return true;
}

int Sudoku::getCell(int row, int col) const
{
    if (!isValidPosition(row, col)) {
        qDebug() << QString("Invalid position: (%1, %2)").arg(row).arg(col);
        return -1;
    }
    return grid[row][col];
}

QString Sudoku::getStatus() const
{
    return status;
}

bool Sudoku::isValidPosition(int row, int col) const
{
    return row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE;
}

bool Sudoku::isValidValue(int value, bool allowEmpty) const
{
    if (allowEmpty && value == EMPTY_CELL) {
        return true;
    }
    return value >= MIN_VALUE && value <= MAX_VALUE;
}

bool Sudoku::isNumberPresentInRow(int row, int num, int excludeCol) const
{
    for (int col = 0; col < GRID_SIZE; col++) {
        if (col != excludeCol && grid[row][col] == num) {
            return true;
        }
    }
    return false;
}

bool Sudoku::isNumberPresentInCol(int col, int num, int excludeRow) const
{
    for (int row = 0; row < GRID_SIZE; row++) {
        if (row != excludeRow && grid[row][col] == num) {
            return true;
        }
    }
    return false;
}

bool Sudoku::isNumberPresentInBox(int boxStartRow, int boxStartCol, int num, int excludeRow, int excludeCol) const
{
    for (int row = 0; row < BOX_SIZE; row++) {
        for (int col = 0; col < BOX_SIZE; col++) {
            int actualRow = row + boxStartRow;
            int actualCol = col + boxStartCol;

            if ((actualRow != excludeRow || actualCol != excludeCol) &&
                grid[actualRow][actualCol] == num) {
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::isValidBoard() const
{
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            int num = grid[row][col];
            if (num == EMPTY_CELL) {
                continue;
            }

            // Check if this number appears elsewhere in the same row, column, or box
            if (isNumberPresentInRow(row, num, col) ||
                isNumberPresentInCol(col, num, row) ||
                isNumberPresentInBox(getBoxStart(row), getBoxStart(col), num, row, col)) {
                qDebug() << "Duplicate found in board for" << num << "at" << row << "," << col;
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::solveSudoku()
{
    int row, col;
    if (!findUnassignedLocation(row, col)) {
        status = "Solved";
        return true;
    }

    for (int num = MIN_VALUE; num <= MAX_VALUE; ++num) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku()) {
                return true;
            }
            grid[row][col] = EMPTY_CELL;
        }
    }

    status = "No solution";
    return false;
}

bool Sudoku::isSafe(int row, int col, int num) const
{
    return !isNumberPresentInRow(row, num) &&
           !isNumberPresentInCol(col, num) &&
           !isNumberPresentInBox(getBoxStart(row), getBoxStart(col), num);
}

bool Sudoku::findUnassignedLocation(int& row, int& col) const
{
    for (row = 0; row < GRID_SIZE; ++row) {
        for (col = 0; col < GRID_SIZE; ++col) {
            if (grid[row][col] == EMPTY_CELL) {
                return true;
            }
        }
    }
    return false;
}

