#pragma once

#include <QtWidgets/QMainWindow>
#include <memory>
#include "ui_SudokuSolver.h"
#include "Sudoku.h"
#include "LineEditDelegate.h"

class SudokuSolver : public QMainWindow
{
    Q_OBJECT

public:
    SudokuSolver(QWidget* parent = nullptr);
    ~SudokuSolver();

private slots:
    void clearButtonClicked();
    void solveButtonClicked();
    void quitAction();
    void onGridChanged();

private:
    Ui::SudokuSolverClass ui;

        // Use vectors instead of C-style arrays
    std::vector<std::vector<int>> previousGrid;

        // Track if we have a complete solution
    bool hasSolution;

    // UI Color Constants
    static const QString COLOR_TEXT;
    static const QString COLOR_DARK;
    static const QString COLOR_LIGHT;
    static const QString COLOR_HIGHLIGHT;

    // Helper methods
    void displayResult(const Sudoku& sudoku);
    void resetTableGrid();
    void setupGridColors();
    bool readGridFromUI(Sudoku& sudoku);
    void setTableItemStyle(int row, int col, const QColor& backgroundColor);
    void clearGridData();
    void updateSolveButtonState();

    // Grid state management
    enum class GridState { Empty, Partial, Complete };
    GridState getGridState() const;

    // DRY helpers
    template<typename Func>
    void iterateGrid(Func func) const {
        for (int row = 0; row < Sudoku::GRID_SIZE; row++) {
            for (int col = 0; col < Sudoku::GRID_SIZE; col++) {
                func(row, col);
            }
        }
    }

    QTableWidgetItem* getCellItem(int row, int col) const;
};
