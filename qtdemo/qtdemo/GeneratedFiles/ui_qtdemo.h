/********************************************************************************
** Form generated from reading UI file 'qtdemo.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTDEMO_H
#define UI_QTDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qtdemoClass
{
public:
    QWidget *centralWidget;
    QPushButton *btnHello;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qtdemoClass)
    {
        if (qtdemoClass->objectName().isEmpty())
            qtdemoClass->setObjectName(QStringLiteral("qtdemoClass"));
        qtdemoClass->resize(600, 400);
        centralWidget = new QWidget(qtdemoClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        btnHello = new QPushButton(centralWidget);
        btnHello->setObjectName(QStringLiteral("btnHello"));
        btnHello->setGeometry(QRect(170, 210, 93, 28));
        qtdemoClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qtdemoClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        qtdemoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qtdemoClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        qtdemoClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(qtdemoClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        qtdemoClass->setStatusBar(statusBar);

        retranslateUi(qtdemoClass);

        QMetaObject::connectSlotsByName(qtdemoClass);
    } // setupUi

    void retranslateUi(QMainWindow *qtdemoClass)
    {
        qtdemoClass->setWindowTitle(QApplication::translate("qtdemoClass", "qtdemo", 0));
        btnHello->setText(QApplication::translate("qtdemoClass", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class qtdemoClass: public Ui_qtdemoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTDEMO_H
