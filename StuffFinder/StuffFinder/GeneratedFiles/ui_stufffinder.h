/********************************************************************************
** Form generated from reading UI file 'stufffinder.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUFFFINDER_H
#define UI_STUFFFINDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StuffFinderClass
{
public:
    QWidget *centralWidget;
    QPushButton *Create_db;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *StuffFinderClass)
    {
        if (StuffFinderClass->objectName().isEmpty())
            StuffFinderClass->setObjectName(QStringLiteral("StuffFinderClass"));
        StuffFinderClass->resize(600, 400);
        centralWidget = new QWidget(StuffFinderClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Create_db = new QPushButton(centralWidget);
        Create_db->setObjectName(QStringLiteral("Create_db"));
        Create_db->setGeometry(QRect(240, 160, 93, 28));
        StuffFinderClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(StuffFinderClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        StuffFinderClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(StuffFinderClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        StuffFinderClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(StuffFinderClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        StuffFinderClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());

        retranslateUi(StuffFinderClass);

        QMetaObject::connectSlotsByName(StuffFinderClass);
    } // setupUi

    void retranslateUi(QMainWindow *StuffFinderClass)
    {
        StuffFinderClass->setWindowTitle(QApplication::translate("StuffFinderClass", "StuffFinder", 0));
        Create_db->setText(QApplication::translate("StuffFinderClass", "Create DB", 0));
        menuFile->setTitle(QApplication::translate("StuffFinderClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class StuffFinderClass: public Ui_StuffFinderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUFFFINDER_H
