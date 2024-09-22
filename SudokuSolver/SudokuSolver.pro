QT += core
QT += gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
CONFIG += lrelease
CONFIG += embed_translations

SOURCES += \
    main.cpp \
    Sudoku.cpp \
    SudokuSolver.cpp

HEADERS += \
    Sudoku.h \
    SudokuSolver.h

FORMS += \
    SudokuSolver.ui \

 RESOURCES += \
    SudokuSolver.qrc \
    SudokuSolver.rc

DISTFILES += \
    License.txt \
    Readme.txt

TARGET = SudokuSolver