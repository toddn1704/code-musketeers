/*addcategorydialog.cpp

This file will implement the functions declared in the
addcategorydialog.h file.

*/

#include "addcategorydialog.h"
#include "qmessagebox.h"

Addcategorydialog::Addcategorydialog(QWidget *parent, Category *cat)
	: QDialog(parent)
{
	new_category = cat;
	ui.setupUi(this);
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(SaveCategory()));

}

void Addcategorydialog::SaveCategory()
{
	// Get user input and validate
	std::string name = ui.category_name->text().toStdString();
	std::string description = ui.category_description->toPlainText().toStdString();

	// Set Containers attributes
	new_category->set_name(name);
	new_category->set_description(description);
}
