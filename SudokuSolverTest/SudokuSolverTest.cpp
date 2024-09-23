#include "pch.h"
#include "gtest/gtest.h"
#include "Sudoku.h"

// Test setting a cell with an invalid column index
TEST(TestSetCell, InvalidColumn)
{
    Sudoku sudoku;
    EXPECT_FALSE(sudoku.setCell(0, 9, 1));
}

// Test setting a cell with an invalid row index
TEST(TestSetCell, InvalidRow)
{
    Sudoku sudoku;
    EXPECT_FALSE(sudoku.setCell(9, 0, 1));
}

// Test setting a cell with a value over 9
TEST(TestSetCell, ValueTooHigh)
{
    Sudoku sudoku;
    EXPECT_FALSE(sudoku.setCell(0, 0, 10));
}

// Test setting a cell with a value under 1
TEST(TestSetCell, ValueTooLow)
{
    Sudoku sudoku;
    EXPECT_FALSE(sudoku.setCell(0, 0, -1));
}

// Test setting a valid cell
TEST(TestSetCell, ValidValue)
{
    Sudoku sudoku;
    EXPECT_TRUE(sudoku.setCell(0, 0, 1));
}

// Test an empty board
TEST(TestIsValidBoard, BoardEmpty)
{
    Sudoku sudoku;
    EXPECT_TRUE(sudoku.isValidBoard());
}

// Test a board with a duplicate in a row
TEST(TestIsValidBoard, DuplicateInRow)
{
    Sudoku sudoku;
    sudoku.setCell(4, 0, 1);
    sudoku.setCell(4, 5, 1);
    EXPECT_FALSE(sudoku.isValidBoard());
}

// Test a board with a duplicate in a column
TEST(TestIsValidBoard, DuplicateInColumn)
{
    Sudoku sudoku;
    sudoku.setCell(1, 6, 2);
    sudoku.setCell(3, 6, 2);
    EXPECT_FALSE(sudoku.isValidBoard());
}

// Test a board with a duplicate in a box
TEST(TestIsValidBoard, DuplicateInBox)
{
    Sudoku sudoku;
    sudoku.setCell(3, 3, 3);
    sudoku.setCell(5, 5, 3);
    EXPECT_FALSE(sudoku.isValidBoard());
}

// Test a known good board is solved correctly
TEST(TestIsValidBoard, GoodBoard)
{
    Sudoku sudoku;

    // Test the given input grid
    int inputGrid[9][9] = {
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

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            sudoku.setCell(row, col, inputGrid[row][col]);
        }
    }

    EXPECT_TRUE(sudoku.solve());

    // Verify the solved grid
    int solvedGrid[9][9] = {
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

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
           EXPECT_EQ(solvedGrid[row][col], sudoku.getCell(row, col));
        }
    }
}

// Test a known bad board is not solved with duplicates in rows
TEST(TestIsValidBoard, InvalidBoardRows)
{
    Sudoku sudoku;

    // Test the given input grid
    int inputGrid[9][9] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 9, 0, 0, 0, 9 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            sudoku.setCell(row, col, inputGrid[row][col]);
        }
    }

    EXPECT_FALSE(sudoku.solve());
}

// Test a known bad board is not solved with duplicates in columns
TEST(TestIsValidBoard, InvalidBoardColumns)
{
    Sudoku sudoku;

    // Test the given input grid
    int inputGrid[9][9] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 9 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 9 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            sudoku.setCell(row, col, inputGrid[row][col]);
        }
    }

    EXPECT_FALSE(sudoku.solve());
}

// Test a known bad board is not solved with duplicates in boxes
TEST(TestIsValidBoard, InvalidBoardBoxes)
{
    Sudoku sudoku;

    // Test the given input grid
    int inputGrid[9][9] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 9, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 9 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            sudoku.setCell(row, col, inputGrid[row][col]);
        }
    }

    EXPECT_FALSE(sudoku.solve());
}

// int main(int argc, char** argv)
// {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
