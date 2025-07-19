#include "SudokuSolver.h"
#include <QPair>
#include <QTableWidgetItem>
#include "LineEditDelegate.h"

// Define color constants
const QString SudokuSolver::COLOR_TEXT = "#171FFF";
const QString SudokuSolver::COLOR_DARK = "#6E9CF0";
const QString SudokuSolver::COLOR_LIGHT = "#BED0F0";
const QString SudokuSolver::COLOR_HIGHLIGHT = "#6FCFFF";

SudokuSolver::SudokuSolver(QWidget* parent)
    : QMainWindow(parent),
      previousGrid(Sudoku::GRID_SIZE, std::vector<int>(Sudoku::GRID_SIZE, Sudoku::EMPTY_CELL)),
      hasSolution(false)
{
    ui.setupUi(this);

    // Connect signals
    connect(ui.clearPushButton, SIGNAL(clicked()), this, SLOT(clearButtonClicked()));
    connect(ui.solvePushButton, SIGNAL(clicked()), this, SLOT(solveButtonClicked()));
    connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(quitAction()));

        // Connect table widget signals to update solve button state
    connect(ui.tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)),
            this, SLOT(onGridChanged()));

    // Setup table view
    ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Create and set the delegate for all columns
    LineEditDelegate *delegate = new LineEditDelegate(this);
    ui.tableWidget->setItemDelegate(delegate);

    resetTableGrid();

    // Initialize solve button state
    updateSolveButtonState();
}

SudokuSolver::~SudokuSolver()
{
}

void SudokuSolver::clearButtonClicked()
{
    ui.tableWidget->clearContents();
    resetTableGrid();
    clearGridData();
    hasSolution = false;
    ui.statusBar->clearMessage();
    updateSolveButtonState();
}

void SudokuSolver::solveButtonClicked()
{
    ui.statusBar->clearMessage();

    Sudoku sudoku;

    if (!readGridFromUI(sudoku)) {
        return; // Error message already set in readGridFromUI
    }

    // Solve the puzzle
    bool solved = sudoku.solve();

    // Display results
    displayResult(sudoku);
    ui.statusBar->showMessage(sudoku.getStatus());

    // Update solution state
    hasSolution = solved && sudoku.getStatus() == "Solved";

    // Update solve button state based on solution status
    updateSolveButtonState();
}

bool SudokuSolver::readGridFromUI(Sudoku& sudoku)
{
    clearGridData();
    bool hasError = false;
    QString errorMessage;

    iterateGrid([this, &sudoku, &hasError, &errorMessage](int row, int col) {
        if (hasError) return; // Skip if error already found

        QTableWidgetItem* cell = getCellItem(row, col);

        if (cell && !cell->text().isEmpty()) {
            bool ok;
            int value = cell->text().toInt(&ok);

            if (!ok) {
                errorMessage = QString("Cell (%1,%2) contains invalid input: '%3'")
                    .arg(row).arg(col).arg(cell->text());
                hasError = true;
                return;
            }

            // The Sudoku class will validate the value range
            if (!sudoku.setCell(row, col, value)) {
                errorMessage = QString("Invalid value %1 at cell (%2,%3)")
                    .arg(value).arg(row).arg(col);
                hasError = true;
                return;
            }

            previousGrid[row][col] = value;
        }
    });

    if (hasError) {
        ui.statusBar->showMessage(errorMessage);
        return false;
    }

    // Reset solution state when reading from UI (user modified the grid)
    hasSolution = false;

    return true;
}

void SudokuSolver::displayResult(const Sudoku& sudoku)
{
    ui.tableWidget->clearSelection();
    QColor highlight = QColor::fromString(COLOR_HIGHLIGHT);

    iterateGrid([this, &sudoku, &highlight](int row, int col) {
        int value = sudoku.getCell(row, col);

        if (value > 0) {
            getCellItem(row, col)->setText(QString::number(value));

            // Highlight cells that were pre-filled
            if (previousGrid[row][col] > 0) {
                getCellItem(row, col)->setBackground(highlight);
            }
        }
    });
    update();
}

void SudokuSolver::quitAction()
{
    QApplication::quit();
}

void SudokuSolver::resetTableGrid()
{
    setupGridColors();
}

void SudokuSolver::setTableItemStyle(int row, int col, const QColor& backgroundColor)
{
    QColor textColor = QColor::fromString(COLOR_TEXT);

    QTableWidgetItem* item = new QTableWidgetItem();
    item->setTextAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    item->setBackground(backgroundColor);
    item->setForeground(QBrush(textColor));
    ui.tableWidget->setItem(row, col, item);
}

void SudokuSolver::setupGridColors()
{
    QColor dark = QColor::fromString(COLOR_DARK);
    QColor light = QColor::fromString(COLOR_LIGHT);

    // Define which 3x3 boxes should be dark
    static const QList<QPair<int, int>> darkBoxes = {
        {0, 0}, {0, 6}, {3, 3}, {6, 0}, {6, 6}
    };

    static const QList<QPair<int, int>> lightBoxes = {
        {0, 3}, {3, 0}, {3, 6}, {6, 3}
    };

    // Color dark boxes
    for (const auto& boxStart : darkBoxes) {
        for (int i = 0; i < Sudoku::BOX_SIZE; ++i) {
            for (int j = 0; j < Sudoku::BOX_SIZE; ++j) {
                setTableItemStyle(boxStart.first + i, boxStart.second + j, dark);
            }
        }
    }

    // Color light boxes
    for (const auto& boxStart : lightBoxes) {
        for (int i = 0; i < Sudoku::BOX_SIZE; ++i) {
            for (int j = 0; j < Sudoku::BOX_SIZE; ++j) {
                setTableItemStyle(boxStart.first + i, boxStart.second + j, light);
            }
        }
    }
}

void SudokuSolver::clearGridData()
{
    for (auto& row : previousGrid) {
        std::fill(row.begin(), row.end(), Sudoku::EMPTY_CELL);
    }
}

void SudokuSolver::onGridChanged()
{
    // Reset solution state when user modifies the grid
    hasSolution = false;
    updateSolveButtonState();
}

QTableWidgetItem* SudokuSolver::getCellItem(int row, int col) const
{
    return ui.tableWidget->item(row, col);
}

SudokuSolver::GridState SudokuSolver::getGridState() const
{
    int filledCells = 0;
    int totalCells = Sudoku::GRID_SIZE * Sudoku::GRID_SIZE;

    iterateGrid([&filledCells, this](int row, int col) {
        QTableWidgetItem* cell = getCellItem(row, col);
        if (cell && !cell->text().isEmpty()) {
            filledCells++;
        }
    });

    if (filledCells == 0) {
        return GridState::Empty;
    } else if (filledCells == totalCells) {
        return GridState::Complete;
    } else {
        return GridState::Partial;
    }
}

void SudokuSolver::updateSolveButtonState()
{
    // Enable solve button if grid has numbers but no solution yet
    bool shouldEnable = (getGridState() != GridState::Empty) && !hasSolution;
    ui.solvePushButton->setEnabled(shouldEnable);
}
