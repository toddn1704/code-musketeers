/********************************************************************************
** Form generated from reading UI file 'editcontainerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITCONTAINERDIALOG_H
#define UI_EDITCONTAINERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_editcontainerdialog
{
public:
    QDialogButtonBox *button_box;
    QLineEdit *container_name;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *container_description;
    QLabel *label_3;
    QComboBox *container_combobox;

    void setupUi(QDialog *editcontainerdialog)
    {
        if (editcontainerdialog->objectName().isEmpty())
            editcontainerdialog->setObjectName(QStringLiteral("editcontainerdialog"));
        editcontainerdialog->resize(389, 292);
        button_box = new QDialogButtonBox(editcontainerdialog);
        button_box->setObjectName(QStringLiteral("button_box"));
        button_box->setGeometry(QRect(30, 240, 341, 32));
        button_box->setOrientation(Qt::Horizontal);
        button_box->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
        container_name = new QLineEdit(editcontainerdialog);
        container_name->setObjectName(QStringLiteral("container_name"));
        container_name->setGeometry(QRect(130, 50, 141, 21));
        label = new QLabel(editcontainerdialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 50, 53, 16));
        label_2 = new QLabel(editcontainerdialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 110, 71, 20));
        container_description = new QTextEdit(editcontainerdialog);
        container_description->setObjectName(QStringLiteral("container_description"));
        container_description->setGeometry(QRect(130, 110, 141, 87));
        label_3 = new QLabel(editcontainerdialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 80, 61, 16));
        container_combobox = new QComboBox(editcontainerdialog);
        container_combobox->setObjectName(QStringLiteral("container_combobox"));
        container_combobox->setGeometry(QRect(130, 80, 121, 22));

        retranslateUi(editcontainerdialog);
        QObject::connect(button_box, SIGNAL(accepted()), editcontainerdialog, SLOT(accept()));
        QObject::connect(button_box, SIGNAL(rejected()), editcontainerdialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(editcontainerdialog);
    } // setupUi

    void retranslateUi(QDialog *editcontainerdialog)
    {
        editcontainerdialog->setWindowTitle(QApplication::translate("editcontainerdialog", "Edit Container", 0));
        label->setText(QApplication::translate("editcontainerdialog", "Name:", 0));
        label_2->setText(QApplication::translate("editcontainerdialog", "Description:", 0));
        label_3->setText(QApplication::translate("editcontainerdialog", "Container:", 0));
    } // retranslateUi

};

namespace Ui {
    class editcontainerdialog: public Ui_editcontainerdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITCONTAINERDIALOG_H
