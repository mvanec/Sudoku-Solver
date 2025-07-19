#include "pch.h"
#include "gtest/gtest.h"
#include "Sudoku.h"
#include <array>
#include <map>
#include <string>

// Test fixture for common test setup
class SudokuTest : public ::testing::Test {
protected:
    Sudoku sudoku;

    // Helper method to fill grid from raw array
    void fillGrid(const int inputGrid[9][9])
    {
        for (int row = 0; row < Sudoku::GRID_SIZE; row++) {
            for (int col = 0; col < Sudoku::GRID_SIZE; col++) {
                sudoku.setCell(row, col, inputGrid[row][col]);
            }
        }
    }
    // Helper method to fill grid from std::array
    void fillGrid(const std::array<std::array<int, 9>, 9>& inputGrid)
    {
        for (int row = 0; row < Sudoku::GRID_SIZE; row++) {
            for (int col = 0; col < Sudoku::GRID_SIZE; col++) {
                sudoku.setCell(row, col, inputGrid[row][col]);
            }
        }
    }

    // Helper method to verify grid matches expected values
    void verifyGrid(const int expectedGrid[9][9])
    {
        for (int row = 0; row < Sudoku::GRID_SIZE; row++) {
            for (int col = 0; col < Sudoku::GRID_SIZE; col++) {
                EXPECT_EQ(expectedGrid[row][col], sudoku.getCell(row, col))
                    << "Mismatch at position (" << row << ", " << col << ")";
            }
        }
    }
};


// Test setting a cell with invalid positions
TEST_F(SudokuTest, InvalidPositions)
{
    // Test invalid column
    EXPECT_FALSE(sudoku.setCell(0, Sudoku::GRID_SIZE, 1));
    EXPECT_FALSE(sudoku.setCell(0, -1, 1));

    // Test invalid row
    EXPECT_FALSE(sudoku.setCell(Sudoku::GRID_SIZE, 0, 1));
    EXPECT_FALSE(sudoku.setCell(-1, 0, 1));
}

// Test setting a cell with invalid values
TEST_F(SudokuTest, InvalidValues)
{
    EXPECT_FALSE(sudoku.setCell(0, 0, Sudoku::MAX_VALUE + 1));
    EXPECT_FALSE(sudoku.setCell(0, 0, -1));

    // Empty cell (0) should be allowed
    EXPECT_TRUE(sudoku.setCell(0, 0, Sudoku::EMPTY_CELL));
}

// Test setting valid cells
TEST_F(SudokuTest, ValidValues)
{
    for (int value = Sudoku::MIN_VALUE; value <= Sudoku::MAX_VALUE; value++) {
        EXPECT_TRUE(sudoku.setCell(0, 0, value));
        EXPECT_EQ(value, sudoku.getCell(0, 0));
    }
}

// Test an empty board
TEST_F(SudokuTest, BoardEmpty)
{
    EXPECT_TRUE(sudoku.isValidBoard());
}

// Test a board with a duplicate in a row
TEST_F(SudokuTest, DuplicateInRow)
{
    sudoku.setCell(4, 0, 1);
    sudoku.setCell(4, 5, 1);
    EXPECT_FALSE(sudoku.isValidBoard());
}

// Test a board with a duplicate in a column
TEST_F(SudokuTest, DuplicateInColumn)
{
    sudoku.setCell(1, 6, 2);
    sudoku.setCell(3, 6, 2);
    EXPECT_FALSE(sudoku.isValidBoard());
}

// Test a board with a duplicate in a box
TEST_F(SudokuTest, DuplicateInBox)
{
    sudoku.setCell(3, 3, 3);
    sudoku.setCell(5, 5, 3);
    EXPECT_FALSE(sudoku.isValidBoard());
}

// Test the clear functionality
TEST_F(SudokuTest, ClearBoard)
{
    // Fill some cells
    sudoku.setCell(0, 0, 5);
    sudoku.setCell(1, 1, 7);
    sudoku.setCell(2, 2, 9);

    // Clear the board
    sudoku.clear();

    // Verify all cells are empty
    for (int row = 0; row < Sudoku::GRID_SIZE; row++) {
        for (int col = 0; col < Sudoku::GRID_SIZE; col++) {
            EXPECT_EQ(Sudoku::EMPTY_CELL, sudoku.getCell(row, col));
        }
    }
}

// Test a known good board is solved correctly
TEST_F(SudokuTest, GoodBoard)
{
    // Test the given input grid
    const int inputGrid[9][9] = {
        { 0, 0, 1, 3, 0, 2, 0, 0, 0 },
        { 0, 0, 3, 0, 0, 7, 0, 4, 5 },
        { 0, 0, 7, 0, 0, 0, 0, 0, 9 },
        { 0, 0, 6, 5, 0, 0, 0, 7, 0 },
        { 2, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 0, 9, 0, 0, 0, 1, 4, 0, 0 },
        { 5, 0, 0, 0, 0, 0, 9, 0, 0 },
        { 6, 1, 0, 2, 0, 0, 8, 0, 0 },
        { 0, 0, 0, 9, 0, 8, 5, 0, 0 }
    };

    fillGrid(inputGrid);
    EXPECT_TRUE(sudoku.solve());
    EXPECT_EQ("Solved", sudoku.getStatus().toStdString());

    // Verify the solved grid
    const int solvedGrid[9][9] = {
        { 4, 5, 1, 3, 9, 2, 7, 8, 6 },
        { 9, 2, 3, 8, 6, 7, 1, 4, 5 },
        { 8, 6, 7, 1, 5, 4, 3, 2, 9 },
        { 1, 3, 6, 5, 4, 9, 2, 7, 8 },
        { 2, 4, 5, 7, 8, 3, 6, 9, 1 },
        { 7, 9, 8, 6, 2, 1, 4, 5, 3 },
        { 5, 8, 2, 4, 3, 6, 9, 1, 7 },
        { 6, 1, 9, 2, 7, 5, 8, 3, 4 },
        { 3, 7, 4, 9, 1, 8, 5, 6, 2 }
    };

    verifyGrid(solvedGrid);
}

// Test invalid boards with duplicates
TEST_F(SudokuTest, InvalidBoardDuplicateInRow)
{
    std::array<std::array<int, 9>, 9> grid;

    // Initialize all elements to 0
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            grid[i][j] = 0;
        }
    }

    // Add duplicate in row
    grid[2][4] = 9;
    grid[2][8] = 9;

    fillGrid(grid);
    EXPECT_FALSE(sudoku.solve());
    EXPECT_EQ("Invalid board: duplicate numbers in rows, columns, or boxes",
              sudoku.getStatus().toStdString());
}

TEST_F(SudokuTest, InvalidBoardDuplicateInColumn)
{
    std::array<std::array<int, 9>, 9> grid;

    // Initialize all elements to 0
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            grid[i][j] = 0;
        }
    }

    // Add duplicate in column
    grid[2][8] = 9;
    grid[4][8] = 9;

    fillGrid(grid);
    EXPECT_FALSE(sudoku.solve());
    EXPECT_EQ("Invalid board: duplicate numbers in rows, columns, or boxes",
              sudoku.getStatus().toStdString());
}

TEST_F(SudokuTest, InvalidBoardDuplicateInBox)
{
    std::array<std::array<int, 9>, 9> grid;

    // Initialize all elements to 0
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            grid[i][j] = 0;
        }
    }

    // Add duplicate in box
    grid[3][6] = 9;
    grid[4][8] = 9;

    fillGrid(grid);
    EXPECT_FALSE(sudoku.solve());
    EXPECT_EQ("Invalid board: duplicate numbers in rows, columns, or boxes",
              sudoku.getStatus().toStdString());
}

// Test edge cases
TEST_F(SudokuTest, GetCellInvalidPosition)
{
    EXPECT_EQ(-1, sudoku.getCell(-1, 0));
    EXPECT_EQ(-1, sudoku.getCell(0, -1));
    EXPECT_EQ(-1, sudoku.getCell(Sudoku::GRID_SIZE, 0));
    EXPECT_EQ(-1, sudoku.getCell(0, Sudoku::GRID_SIZE));
}

// Test that a nearly complete puzzle can be solved
TEST_F(SudokuTest, NearlyCompletePuzzle)
{
    // Create a puzzle that's almost complete with just one missing value
    const int puzzleGrid[9][9] = {
        { 1, 2, 3, 4, 5, 6, 7, 8, 0 },  // Row 0: missing value at (0,8)
        { 4, 5, 6, 7, 8, 9, 1, 2, 3 },
        { 7, 8, 9, 1, 2, 3, 4, 5, 6 },
        { 2, 1, 4, 3, 6, 5, 8, 9, 7 },
        { 3, 6, 5, 8, 9, 7, 2, 1, 4 },
        { 8, 9, 7, 2, 1, 4, 3, 6, 5 },
        { 5, 3, 1, 6, 4, 2, 9, 7, 8 },
        { 6, 4, 2, 9, 7, 8, 5, 3, 1 },
        { 9, 7, 8, 5, 3, 1, 6, 4, 2 }
    };

    fillGrid(puzzleGrid);

    // This puzzle should be solvable with just one missing value
    EXPECT_TRUE(sudoku.solve());
    EXPECT_EQ("Solved", sudoku.getStatus().toStdString());

    // Verify that the missing value (9) was placed at position (0,8)
    EXPECT_EQ(9, sudoku.getCell(0, 8));
}

// int main(int argc, char** argv)
// {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
