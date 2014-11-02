#include "Edititemdialog.h"
#include "qmessagebox.h"

Edititemdialog::Edititemdialog(QWidget *parent, Item *item)
	: QDialog(parent)
{
	new_item = item;
	ui.setupUi(this);
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(saveItem()));

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