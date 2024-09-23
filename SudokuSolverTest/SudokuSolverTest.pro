include(gtest_dependency.pri)

QT += core
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt
CONFIG += core

SOURCES += \
        main.cpp \
        SudokuSolverTest.cpp

INCLUDEPATH += \
    $$PWD/../SudokuSolver

DEPENDPATH += \
    ../SudokuSolver

win32:CONFIG(debug, debug): LIBS += $$PWD/../build/Desktop_Qt_6_7_2_MSVC2019_64bit-Debug/SudokuSolver/debug/Sudoku.obj
else:!win32:CONFIG(debug, debug): LIBS += $$PWD/../build/Qt_6_7_2_for_macOS-Debug/SudokuSolver/Sudoku.o
# CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lQtDatabase
