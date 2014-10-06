/********************************************************************************
** Form generated from reading UI file 'qt_test.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_TEST_H
#define UI_QT_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Qt_testClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Qt_testClass)
    {
        if (Qt_testClass->objectName().isEmpty())
            Qt_testClass->setObjectName(QStringLiteral("Qt_testClass"));
        Qt_testClass->resize(600, 400);
        menuBar = new QMenuBar(Qt_testClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        Qt_testClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Qt_testClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Qt_testClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Qt_testClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Qt_testClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Qt_testClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Qt_testClass->setStatusBar(statusBar);

        retranslateUi(Qt_testClass);

        QMetaObject::connectSlotsByName(Qt_testClass);
    } // setupUi

    void retranslateUi(QMainWindow *Qt_testClass)
    {
        Qt_testClass->setWindowTitle(QApplication::translate("Qt_testClass", "Qt_test", 0));
    } // retranslateUi

};

namespace Ui {
    class Qt_testClass: public Ui_Qt_testClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_TEST_H
