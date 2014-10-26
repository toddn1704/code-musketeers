#include "Addcontainerdialog.h"
#include "qmessagebox.h"

Addcontainerdialog::Addcontainerdialog(QWidget *parent, Container *cont)
	: QDialog(parent)
{
	new_container = cont;
	ui.setupUi(this);
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(saveContainer()));

}

void Addcontainerdialog::saveContainer()
{
	// Get user input and validate
	std::string name = ui.container_name->text().toStdString();
	std::string description = ui.container_description->toPlainText().toStdString();
	if (name.empty() || description.empty())
	{
		QMessageBox msgBox;
		msgBox.setText("You didnt fill in all the boxees silly!");
		msgBox.exec();
		return;
	}
	// Set Containers attributes
	new_container->set_name(name);
	new_container->set_description(description);
}
