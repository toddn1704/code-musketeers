/*additemdialog.cpp

This file will implement the functions declared in the
additemdialog.h file.

*/

#include "additemdialog.h"
#include "qmessagebox.h"

Additemdialog::Additemdialog(QWidget *parent, Item *item, int cont_id,std::string cont_name, std::vector<QString> combocategory)
	: QDialog(parent)
{
	new_item = item;
	container_id = cont_id;
	ui.setupUi(this);
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(SaveItem()));

	ui.Item_container->setText(QString::fromStdString(cont_name));
	//load categories and preSelect category if it exists
	for (unsigned int i = 0; i < combocategory.size(); i = i + 2)
	{
		ui.Add_category_menu->addItem(combocategory[i], combocategory[i + 1]);
	}
	ui.Add_category_menu->setCurrentIndex(-1);
}

void Additemdialog::SaveItem()
{
	// Get user input and validate
	std::string name = ui.Item_name->text().toStdString();
	std::string description = ui.Item_descript->toPlainText().toStdString();
	int quant = ui.Item_quant->value();
	int category_id = ui.Add_category_menu->itemData(ui.Add_category_menu->currentIndex(), Qt::UserRole).toInt();

	if (name.empty() || description.empty())
	{
		QMessageBox msgBox;
		msgBox.setText("Sorry you didn't fill out all info.");
		msgBox.exec();
		new_item->set_min_quantity(-1);
		return;
	}
	else
	{
		// Set Item attributes
		new_item->set_name(name);
		new_item->set_description(description);
		new_item->set_quantity(quant);
		new_item->set_category(category_id);
		new_item->set_container_id(container_id);
	}
}