#include "Edititemdialog.h"
#include "qmessagebox.h"

Edititemdialog::Edititemdialog(QWidget *parent, Item *item,int cont_id,std::vector<QString> combocontainer)
	: QDialog(parent)
{
	new_item = item;
	int count = 0,combo_index = 0;

	ui.setupUi(this);
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(saveItem()));

	ui.EditcontainerComboBox->clear();
	// load the container combo box
	// also save when we find the container the item is in so that we can pre select it from the combo box
	for (unsigned int i = 0; i < combocontainer.size(); i=i+2)
	{
		ui.EditcontainerComboBox->addItem(combocontainer[i],combocontainer[i+1]);
		//save combo index for preselect
		if (cont_id == combocontainer[i + 1].toInt())
		{
			combo_index = count;
		}
		count++;
	}
	// preSelect the container that the item is in
	ui.EditcontainerComboBox->setCurrentIndex(combo_index);

}

void Edititemdialog::saveItem()
{
	// Get user input and validate
	//std::string name = ui.container_name->text().toStdString();
	//std::string description = ui.container_description->toPlainText().toStdString();

	// Set Item attributes
	//new_container->set_name(name);
	//new_container->set_description(description);
}