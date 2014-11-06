/********************************************************************************
** Form generated from reading UI file 'addcontainerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCONTAINERDIALOG_H
#define UI_ADDCONTAINERDIALOG_H

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

class Ui_Addcontainerdialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *container_name;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *container_description;

    void setupUi(QDialog *Addcontainerdialog)
    {
        if (Addcontainerdialog->objectName().isEmpty())
            Addcontainerdialog->setObjectName(QStringLiteral("Addcontainerdialog"));
        Addcontainerdialog->resize(389, 292);
        buttonBox = new QDialogButtonBox(Addcontainerdialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
        container_name = new QLineEdit(Addcontainerdialog);
        container_name->setObjectName(QStringLiteral("container_name"));
        container_name->setGeometry(QRect(130, 50, 141, 21));
        label = new QLabel(Addcontainerdialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 50, 53, 16));
        label_2 = new QLabel(Addcontainerdialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 80, 71, 20));
        container_description = new QTextEdit(Addcontainerdialog);
        container_description->setObjectName(QStringLiteral("container_description"));
        container_description->setGeometry(QRect(130, 80, 141, 87));

        retranslateUi(Addcontainerdialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Addcontainerdialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Addcontainerdialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Addcontainerdialog);
    } // setupUi

    void retranslateUi(QDialog *Addcontainerdialog)
    {
        Addcontainerdialog->setWindowTitle(QApplication::translate("Addcontainerdialog", "Add Container", 0));
        label->setText(QApplication::translate("Addcontainerdialog", "Name", 0));
        label_2->setText(QApplication::translate("Addcontainerdialog", "Description", 0));
    } // retranslateUi

};

namespace Ui {
    class Addcontainerdialog: public Ui_Addcontainerdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCONTAINERDIALOG_H
