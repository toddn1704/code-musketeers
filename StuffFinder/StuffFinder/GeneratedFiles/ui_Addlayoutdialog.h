/********************************************************************************
** Form generated from reading UI file 'addlayoutdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDLAYOUTDIALOG_H
#define UI_ADDLAYOUTDIALOG_H

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

class Ui_Addlayoutdialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *layout_name;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *layout_description;

    void setupUi(QDialog *Addlayoutdialog)
    {
        if (Addlayoutdialog->objectName().isEmpty())
            Addlayoutdialog->setObjectName(QStringLiteral("Addlayoutdialog"));
        Addlayoutdialog->resize(389, 292);
        buttonBox = new QDialogButtonBox(Addlayoutdialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
        layout_name = new QLineEdit(Addlayoutdialog);
        layout_name->setObjectName(QStringLiteral("layout_name"));
        layout_name->setGeometry(QRect(130, 50, 141, 21));
        label = new QLabel(Addlayoutdialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 50, 53, 16));
        label_2 = new QLabel(Addlayoutdialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 80, 71, 20));
        layout_description = new QTextEdit(Addlayoutdialog);
        layout_description->setObjectName(QStringLiteral("layout_description"));
        layout_description->setGeometry(QRect(130, 80, 141, 87));

        retranslateUi(Addlayoutdialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Addlayoutdialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Addlayoutdialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Addlayoutdialog);
    } // setupUi

    void retranslateUi(QDialog *Addlayoutdialog)
    {
        Addlayoutdialog->setWindowTitle(QApplication::translate("Addlayoutdialog", "Add Layout", 0));
        label->setText(QApplication::translate("Addlayoutdialog", "Name", 0));
        label_2->setText(QApplication::translate("Addlayoutdialog", "Description", 0));
    } // retranslateUi

};

namespace Ui {
    class Addlayoutdialog: public Ui_Addlayoutdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDLAYOUTDIALOG_H
