/********************************************************************************
** Form generated from reading UI file 'additemdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDITEMDIALOG_H
#define UI_ADDITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Additemdialog
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox_2;
    QLineEdit *Item_name;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_3;
    QTextEdit *Item_descript;
    QComboBox *Add_category_menu;
    QLabel *label;
    QLineEdit *Item_container;
    QGroupBox *groupBox;
    QLabel *label_4;
    QCheckBox *Track_box;
    QLabel *label_6;
    QLineEdit *Min_quant;
    QLabel *label_7;
    QLineEdit *Item_cost;
    QSpinBox *Item_quant;

    void setupUi(QDialog *Additemdialog)
    {
        if (Additemdialog->objectName().isEmpty())
            Additemdialog->setObjectName(QStringLiteral("Additemdialog"));
        Additemdialog->resize(400, 524);
        buttonBox = new QDialogButtonBox(Additemdialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(40, 470, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
        groupBox_2 = new QGroupBox(Additemdialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 10, 291, 221));
        groupBox_2->setFlat(false);
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
        Add_category_menu = new QComboBox(groupBox_2);
        Add_category_menu->setObjectName(QStringLiteral("Add_category_menu"));
        Add_category_menu->setGeometry(QRect(90, 60, 131, 22));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 180, 61, 20));
        Item_container = new QLineEdit(groupBox_2);
        Item_container->setObjectName(QStringLiteral("Item_container"));
        Item_container->setGeometry(QRect(90, 180, 113, 20));
        Item_container->setReadOnly(true);
        groupBox = new QGroupBox(Additemdialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 260, 291, 131));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 30, 51, 16));
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
        Item_quant = new QSpinBox(groupBox);
        Item_quant->setObjectName(QStringLiteral("Item_quant"));
        Item_quant->setGeometry(QRect(70, 30, 42, 22));

        retranslateUi(Additemdialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Additemdialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Additemdialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Additemdialog);
    } // setupUi

    void retranslateUi(QDialog *Additemdialog)
    {
        Additemdialog->setWindowTitle(QApplication::translate("Additemdialog", "Add Item", 0));
        groupBox_2->setTitle(QApplication::translate("Additemdialog", "Edit Item", 0));
        Item_name->setText(QString());
        label_2->setText(QApplication::translate("Additemdialog", "Item Name:", 0));
        label_5->setText(QApplication::translate("Additemdialog", "Category:", 0));
        label_3->setText(QApplication::translate("Additemdialog", "Description:", 0));
        label->setText(QApplication::translate("Additemdialog", "Container:", 0));
        Item_container->setText(QString());
        groupBox->setTitle(QApplication::translate("Additemdialog", "Shopping List Options", 0));
        label_4->setText(QApplication::translate("Additemdialog", "Quantity:", 0));
        Track_box->setText(QApplication::translate("Additemdialog", "Track for shopping list", 0));
        label_6->setText(QApplication::translate("Additemdialog", "Minimum Quantity:", 0));
        label_7->setText(QApplication::translate("Additemdialog", "Estimated Cost:", 0));
    } // retranslateUi

};

namespace Ui {
    class Additemdialog: public Ui_Additemdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDITEMDIALOG_H
