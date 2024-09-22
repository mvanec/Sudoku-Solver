/********************************************************************************
** Form generated from reading UI file 'SudokuSolver.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUDOKUSOLVER_H
#define UI_SUDOKUSOLVER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SudokuSolverClass
{
public:
    QAction *actionQuit;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *solvePushButton;
    QPushButton *clearPushButton;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *SudokuSolverClass)
    {
        if (SudokuSolverClass->objectName().isEmpty())
            SudokuSolverClass->setObjectName("SudokuSolverClass");
        SudokuSolverClass->resize(475, 574);
        actionQuit = new QAction(SudokuSolverClass);
        actionQuit->setObjectName("actionQuit");
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("application-exit")));
        actionQuit->setIcon(icon);
        centralWidget = new QWidget(SudokuSolverClass);
        centralWidget->setObjectName("centralWidget");
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 9)
            tableWidget->setColumnCount(9);
        if (tableWidget->rowCount() < 9)
            tableWidget->setRowCount(9);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setMinimumSize(QSize(451, 451));
        tableWidget->setBaseSize(QSize(451, 451));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        tableWidget->setFont(font);
        tableWidget->setAutoFillBackground(true);
        tableWidget->setFrameShadow(QFrame::Shadow::Sunken);
        tableWidget->setLineWidth(2);
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        tableWidget->setAlternatingRowColors(false);
        tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
        tableWidget->setWordWrap(false);
        tableWidget->setRowCount(9);
        tableWidget->setColumnCount(9);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setMinimumSectionSize(20);
        tableWidget->horizontalHeader()->setDefaultSectionSize(50);
        tableWidget->horizontalHeader()->setHighlightSections(false);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(50);

        verticalLayout->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        solvePushButton = new QPushButton(centralWidget);
        buttonGroup = new QButtonGroup(SudokuSolverClass);
        buttonGroup->setObjectName("buttonGroup");
        buttonGroup->addButton(solvePushButton);
        solvePushButton->setObjectName("solvePushButton");
        solvePushButton->setMinimumSize(QSize(85, 24));
        solvePushButton->setMaximumSize(QSize(85, 24));

        horizontalLayout->addWidget(solvePushButton);

        clearPushButton = new QPushButton(centralWidget);
        buttonGroup->addButton(clearPushButton);
        clearPushButton->setObjectName("clearPushButton");
        clearPushButton->setMinimumSize(QSize(85, 24));
        clearPushButton->setMaximumSize(QSize(85, 24));

        horizontalLayout->addWidget(clearPushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        SudokuSolverClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SudokuSolverClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 475, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        SudokuSolverClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(SudokuSolverClass);
        statusBar->setObjectName("statusBar");
        SudokuSolverClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionQuit);

        retranslateUi(SudokuSolverClass);

        QMetaObject::connectSlotsByName(SudokuSolverClass);
    } // setupUi

    void retranslateUi(QMainWindow *SudokuSolverClass)
    {
        SudokuSolverClass->setWindowTitle(QCoreApplication::translate("SudokuSolverClass", "Sudoku Solver", nullptr));
        actionQuit->setText(QCoreApplication::translate("SudokuSolverClass", "&Quit", nullptr));
#if QT_CONFIG(shortcut)
        actionQuit->setShortcut(QCoreApplication::translate("SudokuSolverClass", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        solvePushButton->setText(QCoreApplication::translate("SudokuSolverClass", "Solve", nullptr));
        clearPushButton->setText(QCoreApplication::translate("SudokuSolverClass", "Clear", nullptr));
        menuFile->setTitle(QCoreApplication::translate("SudokuSolverClass", "&File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SudokuSolverClass: public Ui_SudokuSolverClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUDOKUSOLVER_H
