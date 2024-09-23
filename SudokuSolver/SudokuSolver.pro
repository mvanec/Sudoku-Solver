QT += core
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
CONFIG += lrelease
CONFIG += embed_translations

SOURCES += \
    LineEditDelegate.cpp \
    main.cpp \
    Sudoku.cpp \
    SudokuSolver.cpp

HEADERS += \
    LineEditDelegate.h \
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