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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StuffFinderClass
{
public:
    QWidget *centralWidget;
    QPushButton *Create_db;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTreeWidget *itemsTreeWidget;
    QWidget *tab_2;
    QListView *listView;
    QPushButton *Add_cancel;
    QPushButton *Add_save;
    QGroupBox *groupBox;
    QLabel *label_4;
    QLineEdit *Item_quant;
    QCheckBox *Track_box;
    QLabel *label_6;
    QLineEdit *Min_quant;
    QLabel *label_7;
    QLineEdit *Item_cost;
    QGroupBox *groupBox_2;
    QLineEdit *Item_name;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_3;
    QTextEdit *Item_descript;
    QComboBox *Category_menu;
    QGraphicsView *graphicsView;
    QLineEdit *search;
    QPushButton *Search_button;
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
        Create_db = new QPushButton(centralWidget);
        Create_db->setObjectName(QStringLiteral("Create_db"));
        Create_db->setGeometry(QRect(1000, 630, 93, 28));
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
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        listView = new QListView(tab_2);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(0, 0, 331, 531));
        Add_cancel = new QPushButton(tab_2);
        Add_cancel->setObjectName(QStringLiteral("Add_cancel"));
        Add_cancel->setGeometry(QRect(130, 360, 75, 23));
        Add_save = new QPushButton(tab_2);
        Add_save->setObjectName(QStringLiteral("Add_save"));
        Add_save->setGeometry(QRect(210, 360, 75, 23));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 220, 291, 131));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 30, 51, 16));
        Item_quant = new QLineEdit(groupBox);
        Item_quant->setObjectName(QStringLiteral("Item_quant"));
        Item_quant->setGeometry(QRect(70, 30, 41, 20));
        Track_box = new QCheckBox(groupBox);
        Track_box->setObjectName(QStringLiteral("Track_box"));
        Track_box->setGeometry(QRect(130, 30, 131, 17));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setEnabled(true);
        label_6->setGeometry(QRect(10, 60, 101, 16));
        label_6->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
        Min_quant = new QLineEdit(groupBox);
        Min_quant->setObjectName(QStringLiteral("Min_quant"));
        Min_quant->setGeometry(QRect(110, 60, 41, 20));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 90, 91, 16));
        Item_cost = new QLineEdit(groupBox);
        Item_cost->setObjectName(QStringLiteral("Item_cost"));
        Item_cost->setGeometry(QRect(100, 90, 71, 20));
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 10, 291, 191));
        Item_name = new QLineEdit(groupBox_2);
        Item_name->setObjectName(QStringLiteral("Item_name"));
        Item_name->setGeometry(QRect(90, 30, 113, 20));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 30, 61, 16));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 60, 51, 16));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 100, 61, 16));
        Item_descript = new QTextEdit(groupBox_2);
        Item_descript->setObjectName(QStringLiteral("Item_descript"));
        Item_descript->setGeometry(QRect(90, 100, 181, 71));
        Category_menu = new QComboBox(groupBox_2);
        Category_menu->setObjectName(QStringLiteral("Category_menu"));
        Category_menu->setGeometry(QRect(90, 60, 131, 22));
        tabWidget->addTab(tab_2, QString());
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(390, 90, 671, 531));
        search = new QLineEdit(centralWidget);
        search->setObjectName(QStringLiteral("search"));
        search->setGeometry(QRect(480, 40, 461, 20));
        Search_button = new QPushButton(centralWidget);
        Search_button->setObjectName(QStringLiteral("Search_button"));
        Search_button->setGeometry(QRect(960, 40, 75, 23));
        StuffFinderClass->setCentralWidget(centralWidget);
        tabWidget->raise();
        graphicsView->raise();
        Create_db->raise();
        search->raise();
        Search_button->raise();
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

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(StuffFinderClass);
    } // setupUi

    void retranslateUi(QMainWindow *StuffFinderClass)
    {
        StuffFinderClass->setWindowTitle(QApplication::translate("StuffFinderClass", "StuffFinder", 0));
        Create_db->setText(QApplication::translate("StuffFinderClass", "Create DB", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("StuffFinderClass", "List View", 0));
        Add_cancel->setText(QApplication::translate("StuffFinderClass", "Cancel", 0));
        Add_save->setText(QApplication::translate("StuffFinderClass", "Save", 0));
        groupBox->setTitle(QApplication::translate("StuffFinderClass", "Shopping List Options", 0));
        label_4->setText(QApplication::translate("StuffFinderClass", "Quantity:", 0));
        Track_box->setText(QApplication::translate("StuffFinderClass", "Track for shopping list", 0));
        label_6->setText(QApplication::translate("StuffFinderClass", "Minimum Quantity:", 0));
        label_7->setText(QApplication::translate("StuffFinderClass", "Estimated Cost:", 0));
        groupBox_2->setTitle(QApplication::translate("StuffFinderClass", "Add/Edit Item", 0));
        Item_name->setText(QString());
        label_2->setText(QApplication::translate("StuffFinderClass", "Item Name:", 0));
        label_5->setText(QApplication::translate("StuffFinderClass", "Category:", 0));
        label_3->setText(QApplication::translate("StuffFinderClass", "Description:", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("StuffFinderClass", "Add Item", 0));
        Search_button->setText(QApplication::translate("StuffFinderClass", "Search", 0));
        menuFile->setTitle(QApplication::translate("StuffFinderClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class StuffFinderClass: public Ui_StuffFinderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUFFFINDER_H
