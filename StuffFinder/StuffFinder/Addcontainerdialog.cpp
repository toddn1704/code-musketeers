/*addcontainerdialog.cpp

This file will implement the functions declared in the
addcontainerdialog.h file.

*/

#include "addcontainerdialog.h"
#include "qmessagebox.h"

Addcontainerdialog::Addcontainerdialog(QWidget *parent, Container *cont)
	: QDialog(parent)
{
	new_container = cont;
	ui.setupUi(this);
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(SaveContainer()));

}

void Addcontainerdialog::SaveContainer()
{
	// Get user input and validate
	std::string name = ui.container_name->text().toStdString();
	std::string description = ui.container_description->toPlainText().toStdString();

	// Set Containers attributes
	new_container->set_name(name);
	new_container->set_description(description);
}