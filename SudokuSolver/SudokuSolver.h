#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SudokuSolver.h"

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

private:
    Ui::SudokuSolverClass ui;

    void displayResult();
    void resetTableGrid();
};
