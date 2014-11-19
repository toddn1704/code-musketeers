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
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StuffFinderClass
{
public:
    QAction *actionGenerate;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTreeWidget *itemsTreeWidget;
    QWidget *tab_2;
    QTreeWidget *categoryTreeWidget;
    QWidget *tab_3;
    QTreeWidget *search_result_treewidget;
    QGraphicsView *graphics_view;
    QLineEdit *Search;
    QPushButton *Search_button;
    QComboBox *layoutComboBox;
    QPushButton *addLayout;
    QLineEdit *graphic_view_status_text;
    QTabWidget *tabWidget_2;
    QWidget *tab_4;
    QTreeWidget *change_log_treewidget;
    QWidget *tab_5;
    QTreeWidget *notifications_treewidget;
    QPushButton *expand_button;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuShopping_List;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *StuffFinderClass)
    {
        if (StuffFinderClass->objectName().isEmpty())
            StuffFinderClass->setObjectName(QStringLiteral("StuffFinderClass"));
        StuffFinderClass->resize(1206, 700);
        actionGenerate = new QAction(StuffFinderClass);
        actionGenerate->setObjectName(QStringLiteral("actionGenerate"));
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
        itemsTreeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        categoryTreeWidget = new QTreeWidget(tab_2);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QStringLiteral("1"));
        categoryTreeWidget->setHeaderItem(__qtreewidgetitem1);
        categoryTreeWidget->setObjectName(QStringLiteral("categoryTreeWidget"));
        categoryTreeWidget->setGeometry(QRect(0, 0, 331, 531));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        search_result_treewidget = new QTreeWidget(tab_3);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem();
        __qtreewidgetitem2->setText(0, QStringLiteral("1"));
        search_result_treewidget->setHeaderItem(__qtreewidgetitem2);
        search_result_treewidget->setObjectName(QStringLiteral("search_result_treewidget"));
        search_result_treewidget->setGeometry(QRect(0, 0, 331, 531));
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
        graphic_view_status_text = new QLineEdit(centralWidget);
        graphic_view_status_text->setObjectName(QStringLiteral("graphic_view_status_text"));
        graphic_view_status_text->setGeometry(QRect(979, 600, 81, 20));
        graphic_view_status_text->setAutoFillBackground(false);
        graphic_view_status_text->setFrame(false);
        graphic_view_status_text->setReadOnly(true);
        tabWidget_2 = new QTabWidget(centralWidget);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(50, 640, 431, 111));
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        change_log_treewidget = new QTreeWidget(tab_4);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem();
        __qtreewidgetitem3->setText(0, QStringLiteral("1"));
        change_log_treewidget->setHeaderItem(__qtreewidgetitem3);
        change_log_treewidget->setObjectName(QStringLiteral("change_log_treewidget"));
        change_log_treewidget->setGeometry(QRect(0, 1, 426, 191));
        tabWidget_2->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        notifications_treewidget = new QTreeWidget(tab_5);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem();
        __qtreewidgetitem4->setText(0, QStringLiteral("1"));
        notifications_treewidget->setHeaderItem(__qtreewidgetitem4);
        notifications_treewidget->setObjectName(QStringLiteral("notifications_treewidget"));
        notifications_treewidget->setGeometry(QRect(0, 1, 431, 191));
        tabWidget_2->addTab(tab_5, QString());
        expand_button = new QPushButton(centralWidget);
        expand_button->setObjectName(QStringLiteral("expand_button"));
        expand_button->setGeometry(QRect(10, 644, 16, 15));
        StuffFinderClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(StuffFinderClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1206, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuShopping_List = new QMenu(menuBar);
        menuShopping_List->setObjectName(QStringLiteral("menuShopping_List"));
        StuffFinderClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(StuffFinderClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        StuffFinderClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuShopping_List->menuAction());

        retranslateUi(StuffFinderClass);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(StuffFinderClass);
    } // setupUi

    void retranslateUi(QMainWindow *StuffFinderClass)
    {
        StuffFinderClass->setWindowTitle(QApplication::translate("StuffFinderClass", "StuffFinder", 0));
        actionGenerate->setText(QApplication::translate("StuffFinderClass", "Generate", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("StuffFinderClass", "List View", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("StuffFinderClass", "Category view", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("StuffFinderClass", "Search Results", 0));
        Search_button->setText(QApplication::translate("StuffFinderClass", "Search", 0));
        addLayout->setText(QApplication::translate("StuffFinderClass", "Add Layout", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("StuffFinderClass", "Change Log", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QApplication::translate("StuffFinderClass", "Notifications", 0));
        expand_button->setText(QApplication::translate("StuffFinderClass", "V", 0));
        menuFile->setTitle(QApplication::translate("StuffFinderClass", "File", 0));
        menuShopping_List->setTitle(QApplication::translate("StuffFinderClass", "Shopping List", 0));
    } // retranslateUi

};

namespace Ui {
    class StuffFinderClass: public Ui_StuffFinderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUFFFINDER_H
