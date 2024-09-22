#include "SudokuSolver.h"
#include "Sudoku.h"
#include <QPair>

const int EMPTY = 0;
#define N 9

// Hold the numbers from the QTableWidget
int grid[N][N] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

// Used to color the cells of entered numbers after the puzzle is solved
int previousGrid[N][N] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

SudokuSolver::SudokuSolver(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.clearPushButton, SIGNAL(clicked()), this, SLOT(clearButtonClicked()));
    connect(ui.solvePushButton, SIGNAL(clicked()), this, SLOT(solveButtonClicked()));
    connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(quitAction()));
    ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    resetTableGrid();
}

SudokuSolver::~SudokuSolver()
{
}

void SudokuSolver::clearButtonClicked()
{
    ui.tableWidget->clearContents();
    resetTableGrid();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            grid[i][j] = EMPTY;
            previousGrid[i][j] = EMPTY;
        }
    }
    ui.statusBar->showMessage(" "); // Clear any previous message
}

void SudokuSolver::solveButtonClicked()
{
    ui.statusBar->showMessage(" ");

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            grid[i][j] = EMPTY;
            previousGrid[i][j] = EMPTY;
        }
    }

    Sudoku sudoku;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            QTableWidgetItem* cell = ui.tableWidget->item(i, j);

            if (cell && cell->text().length() > 0) {
                bool ok;
                int value = cell->text().toInt(&ok); // Attempt to convert text to int

                if (!ok) {
                    ui.statusBar->showMessage(QString("Cell contains a letter '%1'").arg(cell->text()));
                    return;
                }
                if (value < 0 || value > 9) {
                    ui.statusBar->showMessage(QString("Cell not between 1 and 9 inclusive: '%1'").arg(value));
                    return;
                }

                sudoku.setCell(i, j, value);
                grid[i][j] = value;
            }
            previousGrid[i][j] = grid[i][j];
        }
    }

    bool solved = sudoku.solve();
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            grid[row][col] = sudoku.getCell(row, col);
        }
    }

    displayResult();

    ui.statusBar->showMessage(sudoku.getStatus());
}

void SudokuSolver::quitAction()
{
    QApplication::quit();
}

void SudokuSolver::displayResult()
{
    ui.tableWidget->clearSelection();
    QColor highlight = QColor::fromString("#6FCFFF");

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] > 0) {
                QString str = QString::number(grid[i][j]);
                ui.tableWidget->item(i, j)->setText(str);
                if (previousGrid[i][j] > 0) {
                    ui.tableWidget->item(i, j)->setBackground(highlight);
                }
            }
        }
    }
    update();
}

void SudokuSolver::resetTableGrid()
{
    QColor text = QColor::fromString("#171FFF");
    QColor dark = QColor::fromString("#6E9CF0");
    QColor light = QColor::fromString("#BED0F0");
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setTextAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    item->setForeground(QBrush(text));
    ui.tableWidget->setItemPrototype(item);

    QList<QPair<int, int>> darks = { QPair<int, int> { 0, 0 },
        QPair<int, int> { 0, 6 },
        QPair<int, int> { 3, 3 },
        QPair<int, int> { 6, 0 },
        QPair<int, int> { 6, 6 } };

    QList<QPair<int, int>> lights = { QPair<int, int> { 0, 3 },
        QPair<int, int> { 3, 0 },
        QPair<int, int> { 3, 6 },
        QPair<int, int> { 6, 3 } };

    for (auto place : darks) {
        int startRow = place.first;
        int startCol = place.second;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                QTableWidgetItem* item = new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignCenter | Qt::AlignHCenter);
                item->setBackground(dark);
                item->setForeground(QBrush(text));
                ui.tableWidget->setItem((i + startRow), (j + startCol), item);
            }
        }
    }
    // Set the colors of the grid
    for (auto place : lights) {
        int startRow = place.first;
        int startCol = place.second;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                QTableWidgetItem* item = new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignCenter | Qt::AlignHCenter);
                item->setBackground(light);
                item->setForeground(QBrush(text));
                ui.tableWidget->setItem((i + startRow), (j + startCol), item);
            }
        }
    }
}
