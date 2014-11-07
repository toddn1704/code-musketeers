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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StuffFinderClass
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTreeWidget *itemsTreeWidget;
    QWidget *tab_3;
    QTreeWidget *categoryTreeWidget;
    QGraphicsView *graphics_view;
    QLineEdit *Search;
    QPushButton *Search_button;
    QComboBox *layoutComboBox;
    QPushButton *addLayout;
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
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(30, 70, 331, 551));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        itemsTreeWidget = new QTreeWidget(tab);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        itemsTreeWidget->setHeaderItem(__qtreewidgetitem);
        itemsTreeWidget->setObjectName(QStringLiteral("itemsTreeWidget"));
        itemsTreeWidget->setGeometry(QRect(0, 0, 331, 531));
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        categoryTreeWidget = new QTreeWidget(tab_3);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QStringLiteral("1"));
        categoryTreeWidget->setHeaderItem(__qtreewidgetitem1);
        categoryTreeWidget->setObjectName(QStringLiteral("categoryTreeWidget"));
        categoryTreeWidget->setGeometry(QRect(0, 0, 331, 531));
        tabWidget->addTab(tab_3, QString());
        graphics_view = new QGraphicsView(centralWidget);
        graphics_view->setObjectName(QStringLiteral("graphics_view"));
        graphics_view->setGeometry(QRect(390, 90, 671, 531));
        graphics_view->setMouseTracking(true);
        Search = new QLineEdit(centralWidget);
        Search->setObjectName(QStringLiteral("Search"));
        Search->setGeometry(QRect(480, 40, 461, 20));
        Search_button = new QPushButton(centralWidget);
        Search_button->setObjectName(QStringLiteral("Search_button"));
        Search_button->setGeometry(QRect(960, 40, 75, 23));
        layoutComboBox = new QComboBox(centralWidget);
        layoutComboBox->setObjectName(QStringLiteral("layoutComboBox"));
        layoutComboBox->setGeometry(QRect(30, 40, 151, 22));
        addLayout = new QPushButton(centralWidget);
        addLayout->setObjectName(QStringLiteral("addLayout"));
        addLayout->setGeometry(QRect(190, 40, 93, 28));
        StuffFinderClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(StuffFinderClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1206, 21));
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

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(StuffFinderClass);
    } // setupUi

    void retranslateUi(QMainWindow *StuffFinderClass)
    {
        StuffFinderClass->setWindowTitle(QApplication::translate("StuffFinderClass", "StuffFinder", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("StuffFinderClass", "List View", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("StuffFinderClass", "Category view", 0));
        Search_button->setText(QApplication::translate("StuffFinderClass", "Search", 0));
        addLayout->setText(QApplication::translate("StuffFinderClass", "Add Layout", 0));
        menuFile->setTitle(QApplication::translate("StuffFinderClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class StuffFinderClass: public Ui_StuffFinderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUFFFINDER_H
