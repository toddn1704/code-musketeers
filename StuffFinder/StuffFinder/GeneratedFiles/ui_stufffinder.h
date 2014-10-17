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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StuffFinderClass
{
public:
    QWidget *centralWidget;
    QPushButton *Create_db;
    QTabWidget *tabWidget;
    QWidget *tab;
    QListWidget *listWidget;
    QWidget *tab_2;
    QListView *listView;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *Item_name;
    QLabel *label_3;
    QTextEdit *itemDescription;
    QLabel *label_4;
    QLineEdit *itemQuantity;
    QComboBox *categoryCombo;
    QLabel *label_5;
    QCheckBox *trackCheck;
    QLabel *label_6;
    QLineEdit *minQuantity;
    QLabel *label_7;
    QLineEdit *itemCost;
    QPushButton *addCancel;
    QPushButton *Add_save;
    QGraphicsView *graphicsView;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
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
        listWidget = new QListWidget(tab);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 331, 531));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        listView = new QListView(tab_2);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(0, 0, 331, 531));
        label = new QLabel(tab_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 71, 16));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 40, 61, 16));
        Item_name = new QLineEdit(tab_2);
        Item_name->setObjectName(QStringLiteral("Item_name"));
        Item_name->setGeometry(QRect(100, 40, 113, 20));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 110, 61, 16));
        itemDescription = new QTextEdit(tab_2);
        itemDescription->setObjectName(QStringLiteral("itemDescription"));
        itemDescription->setGeometry(QRect(100, 110, 191, 71));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 200, 51, 16));
        itemQuantity = new QLineEdit(tab_2);
        itemQuantity->setObjectName(QStringLiteral("itemQuantity"));
        itemQuantity->setGeometry(QRect(90, 200, 41, 20));
        categoryCombo = new QComboBox(tab_2);
        categoryCombo->setObjectName(QStringLiteral("categoryCombo"));
        categoryCombo->setGeometry(QRect(100, 70, 131, 22));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 70, 51, 16));
        trackCheck = new QCheckBox(tab_2);
        trackCheck->setObjectName(QStringLiteral("trackCheck"));
        trackCheck->setGeometry(QRect(160, 200, 131, 17));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setEnabled(true);
        label_6->setGeometry(QRect(30, 230, 101, 16));
        label_6->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
        minQuantity = new QLineEdit(tab_2);
        minQuantity->setObjectName(QStringLiteral("minQuantity"));
        minQuantity->setGeometry(QRect(130, 230, 41, 20));
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(40, 260, 91, 16));
        itemCost = new QLineEdit(tab_2);
        itemCost->setObjectName(QStringLiteral("itemCost"));
        itemCost->setGeometry(QRect(120, 260, 71, 20));
        addCancel = new QPushButton(tab_2);
        addCancel->setObjectName(QStringLiteral("addCancel"));
        addCancel->setGeometry(QRect(150, 290, 75, 23));
        Add_save = new QPushButton(tab_2);
        Add_save->setObjectName(QStringLiteral("Add_save"));
        Add_save->setGeometry(QRect(230, 290, 75, 23));
        tabWidget->addTab(tab_2, QString());
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(390, 90, 671, 531));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(480, 40, 461, 20));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(960, 40, 75, 23));
        StuffFinderClass->setCentralWidget(centralWidget);
        tabWidget->raise();
        graphicsView->raise();
        Create_db->raise();
        lineEdit->raise();
        pushButton->raise();
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

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(StuffFinderClass);
    } // setupUi

    void retranslateUi(QMainWindow *StuffFinderClass)
    {
        StuffFinderClass->setWindowTitle(QApplication::translate("StuffFinderClass", "StuffFinder", 0));
        Create_db->setText(QApplication::translate("StuffFinderClass", "Create DB", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("StuffFinderClass", "List View", 0));
        label->setText(QApplication::translate("StuffFinderClass", "Add/Edit Item", 0));
        label_2->setText(QApplication::translate("StuffFinderClass", "Item Name:", 0));
        label_3->setText(QApplication::translate("StuffFinderClass", "Description:", 0));
        label_4->setText(QApplication::translate("StuffFinderClass", "Quantity:", 0));
        label_5->setText(QApplication::translate("StuffFinderClass", "Category:", 0));
        trackCheck->setText(QApplication::translate("StuffFinderClass", "Track for shopping list", 0));
        label_6->setText(QApplication::translate("StuffFinderClass", "Minimum Quantity:", 0));
        label_7->setText(QApplication::translate("StuffFinderClass", "Estimated Cost:", 0));
        addCancel->setText(QApplication::translate("StuffFinderClass", "Cancel", 0));
        Add_save->setText(QApplication::translate("StuffFinderClass", "Save", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("StuffFinderClass", "Add Item", 0));
        pushButton->setText(QApplication::translate("StuffFinderClass", "Search", 0));
        menuFile->setTitle(QApplication::translate("StuffFinderClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class StuffFinderClass: public Ui_StuffFinderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUFFFINDER_H
