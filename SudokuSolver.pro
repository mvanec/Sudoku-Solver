TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    SudokuSolver \
    SudokuSolverTest

SudokuSolverTest.depends += SudokuSolver
