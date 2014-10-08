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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StuffFinderClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QTabWidget *tabWidget;
    QWidget *tab;
    QListWidget *listWidget;
    QWidget *tab_2;
    QListView *listView;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *StuffFinderClass)
    {
        if (StuffFinderClass->objectName().isEmpty())
            StuffFinderClass->setObjectName(QStringLiteral("StuffFinderClass"));
        StuffFinderClass->resize(1206, 751);
        centralWidget = new QWidget(StuffFinderClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(1050, 640, 93, 28));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(30, 70, 331, 551));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        listWidget = new QListWidget(tab);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 331, 531));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        listView = new QListView(tab_2);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(0, 0, 331, 531));
        tabWidget->addTab(tab_2, QString());
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(390, 90, 671, 531));
        StuffFinderClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(StuffFinderClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1206, 26));
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

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(StuffFinderClass);
    } // setupUi

    void retranslateUi(QMainWindow *StuffFinderClass)
    {
        StuffFinderClass->setWindowTitle(QApplication::translate("StuffFinderClass", "StuffFinder", 0));
        pushButton->setText(QApplication::translate("StuffFinderClass", "Hello!", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("StuffFinderClass", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("StuffFinderClass", "Tab 2", 0));
        menuFile->setTitle(QApplication::translate("StuffFinderClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class StuffFinderClass: public Ui_StuffFinderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUFFFINDER_H
