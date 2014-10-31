/********************************************************************************
** Form generated from reading UI file 'Addcategorydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCATEGORYDIALOG_H
#define UI_ADDCATEGORYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Addcategorydialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *category_name;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *category_description;

    void setupUi(QDialog *Addcategorydialog)
    {
        if (Addcategorydialog->objectName().isEmpty())
            Addcategorydialog->setObjectName(QStringLiteral("Addcategorydialog"));
        Addcategorydialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(Addcategorydialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        category_name = new QLineEdit(Addcategorydialog);
        category_name->setObjectName(QStringLiteral("category_name"));
        category_name->setGeometry(QRect(150, 50, 141, 21));
        label = new QLabel(Addcategorydialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 50, 53, 16));
        label_2 = new QLabel(Addcategorydialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 80, 71, 20));
        category_description = new QTextEdit(Addcategorydialog);
        category_description->setObjectName(QStringLiteral("category_description"));
        category_description->setGeometry(QRect(150, 80, 141, 87));

        retranslateUi(Addcategorydialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Addcategorydialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Addcategorydialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Addcategorydialog);
    } // setupUi

    void retranslateUi(QDialog *Addcategorydialog)
    {
        Addcategorydialog->setWindowTitle(QApplication::translate("Addcategorydialog", "Dialog", 0));
        label->setText(QApplication::translate("Addcategorydialog", "Name", 0));
        label_2->setText(QApplication::translate("Addcategorydialog", "Description", 0));
    } // retranslateUi

};

namespace Ui {
    class Addcategorydialog: public Ui_Addcategorydialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCATEGORYDIALOG_H
