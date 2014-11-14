/*edititemdialog.cpp

This file will implement the functions declared in the
edititemdialog.h file.

*/



#include "edititemdialog.h"
#include "qmessagebox.h"

Edititemdialog::Edititemdialog(QWidget *parent, Item *item,int cont_id,std::vector<QString> combocontainer,std::vector<QString> combocategory)
	: QDialog(parent)
{
	new_item = item;
	int count = 0;

	ui.setupUi(this);
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(SaveItem()));

	ui.EditcontainerComboBox->clear();
	// load the container combo box
	// also save when we find the container the item is in so that we can pre select it from the combo box
	for (unsigned int i = 0; i < combocontainer.size(); i=i+2)
	{									// text               id
		ui.EditcontainerComboBox->addItem(combocontainer[i],combocontainer[i+1]);
		//save combo index for preselect
		if (cont_id == combocontainer[i + 1].toInt())
		{
			// preSelect the container that the item is in
			ui.EditcontainerComboBox->setCurrentIndex(count);
		}
		count++;
	}
	count = 0;
	//load categories and preSelect category if it exists
	for (unsigned int i = 0; i < combocategory.size(); i= i+2)
	{
		ui.Edit_category_menu->addItem(combocategory[i],combocategory[i+1]);
		//save combo index for preselect
		if (item->get_category() == combocategory[i+1].toInt())
		{
			// preSelect the container that the item is in
			ui.Edit_category_menu->setCurrentIndex(count);
		}
		count++;
	}
	//prefill name description and quantity
	ui.Item_name->setText(QString::fromStdString(item->get_name()));
	ui.Item_descript->setText(QString::fromStdString(item->get_description()));
	ui.Item_quant->setValue(item->get_quantity());
	ui.min_quant->setValue(item->get_min_quantity());
	if (item->get_track() == 1)
	{
		ui.Track_box->setChecked(true);
	}
}

void Edititemdialog::SaveItem()
{
	// Get user input and validate
	std::string name = ui.Item_name->text().toStdString();
	std::string description = ui.Item_descript->toPlainText().toStdString();
	int quant = ui.Item_quant->value();
	int min_quant = ui.min_quant->value();
	int new_cont_id = ui.EditcontainerComboBox->itemData(ui.EditcontainerComboBox->currentIndex(),Qt::UserRole).toInt();
	int new_category_id = ui.Edit_category_menu->itemData(ui.Edit_category_menu->currentIndex(), Qt::UserRole).toInt();

	if (name.empty() || description.empty())
	{
		QMessageBox msgBox;
		msgBox.setText("You forgot to fill something out.");
		msgBox.exec();
		return;
	}
	else
	{
		// Set Item attributes
		new_item->set_name(name);
		new_item->set_description(description);
		new_item->set_quantity(quant);
		new_item->set_category(new_category_id);
		new_item->set_container_id(new_cont_id);
		new_item->set_min_quantity(min_quant);
		new_item->set_track(ui.Track_box->isChecked());
	}
}