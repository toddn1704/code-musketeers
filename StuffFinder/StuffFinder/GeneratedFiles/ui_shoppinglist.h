/********************************************************************************
** Form generated from reading UI file 'shoppinglist.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOPPINGLIST_H
#define UI_SHOPPINGLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Shoppinglist
{
public:
    QPushButton *export_button;
    QTextEdit *items_textedit;

    void setupUi(QDialog *Shoppinglist)
    {
        if (Shoppinglist->objectName().isEmpty())
            Shoppinglist->setObjectName(QStringLiteral("Shoppinglist"));
        Shoppinglist->resize(389, 523);
        export_button = new QPushButton(Shoppinglist);
        export_button->setObjectName(QStringLiteral("export_button"));
        export_button->setGeometry(QRect(280, 490, 71, 23));
        items_textedit = new QTextEdit(Shoppinglist);
        items_textedit->setObjectName(QStringLiteral("items_textedit"));
        items_textedit->setGeometry(QRect(33, 30, 321, 441));
        items_textedit->setReadOnly(true);

        retranslateUi(Shoppinglist);

        QMetaObject::connectSlotsByName(Shoppinglist);
    } // setupUi

    void retranslateUi(QDialog *Shoppinglist)
    {
        Shoppinglist->setWindowTitle(QApplication::translate("Shoppinglist", "Shopping List", 0));
        export_button->setText(QApplication::translate("Shoppinglist", "Export", 0));
    } // retranslateUi

};

namespace Ui {
    class Shoppinglist: public Ui_Shoppinglist {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOPPINGLIST_H
