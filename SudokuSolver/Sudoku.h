#pragma once
#include <QString>
#include <vector>

class Sudoku {
public:
    Sudoku();
    bool solve();
    void setCell(int row, int col, int value);
    int getCell(int row, int col);
    bool isValidBoard() const;
    QString getStatus() const;

private:
    std::vector<std::vector<int>> grid;
    QString status;

    bool duplicateInRow(int row, int num) const;
    bool duplicateInCol(int col, int num) const;
    bool duplicateInBox(int boxStartRow, int boxStartCol, int num) const;

    bool solveSudoku();
    bool isSafe(int row, int col, int num) const;
    bool findUnassignedLocation(int& row, int& col) const;
};
