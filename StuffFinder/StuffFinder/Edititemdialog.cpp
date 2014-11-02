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
	for (unsigned int i = 0; i < combocontainer.size(); i=i+2)
	{
		ui.EditcontainerComboBox->addItem(combocontainer[i],combocontainer[i+1]);
		if (cont_id == combocontainer[i + 1].toInt())
		{
			combo_index = count;
		}
		count++;
	}
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