#include "SudokuSolver.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication::setStyle("Fusion");
    QApplication a(argc, argv);
    SudokuSolver w;
    w.show();
    return a.exec();
}
