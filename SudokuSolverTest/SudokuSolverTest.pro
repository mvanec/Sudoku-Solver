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

win32:CONFIG(debug, debug): LIBS += $$OUT_PWD/../SudokuSolver/SudokuSolver/debug/Sudoku.obj
else:!win32:CONFIG(debug, debug): LIBS += $$OUT_PWD/../SudokuSolver/Sudoku.o

macx: QMAKE_MACOSX_DEPLOYMENT_TARGET = 15.0
message(Targeting macOS: $$QMAKE_MACOSX_DEPLOYMENT_TARGET)
