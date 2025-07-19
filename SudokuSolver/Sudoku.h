#pragma once
#include <QString>
#include <vector>

class Sudoku {
public:
    static constexpr int GRID_SIZE = 9;
    static constexpr int BOX_SIZE = 3;
    static constexpr int EMPTY_CELL = 0;
    static constexpr int MIN_VALUE = 1;
    static constexpr int MAX_VALUE = 9;

    Sudoku();
    bool solve();
    bool setCell(int row, int col, int value);
    int getCell(int row, int col) const;
    bool isValidBoard() const;
    QString getStatus() const;
    void clear();

private:
    std::vector<std::vector<int>> grid;
    QString status;

    // Unified validation methods
    bool isValidPosition(int row, int col) const;
    bool isValidValue(int value, bool allowEmpty = true) const;
    bool isNumberPresentInRow(int row, int num, int excludeCol = -1) const;
    bool isNumberPresentInCol(int col, int num, int excludeRow = -1) const;
    bool isNumberPresentInBox(int boxStartRow, int boxStartCol, int num, int excludeRow = -1, int excludeCol = -1) const;

    // Helper method to get box start position
    static int getBoxStart(int pos) { return pos - (pos % BOX_SIZE); }

    // Solver methods
    bool solveSudoku();
    bool isSafe(int row, int col, int num) const;
    bool findUnassignedLocation(int& row, int& col) const;
};
