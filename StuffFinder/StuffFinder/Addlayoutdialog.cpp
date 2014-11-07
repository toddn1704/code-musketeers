#include "addlayoutdialog.h"
#include "qmessagebox.h"

Addlayoutdialog::Addlayoutdialog(QWidget *parent, Layout *lay)
	: QDialog(parent)
{
	new_layout = lay;
	ui.setupUi(this);
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(SaveLayout()));

}

void Addlayoutdialog::SaveLayout()
{
	// Get user input and validate
	std::string name = ui.layout_name->text().toStdString();
	std::string description = ui.layout_description->toPlainText().toStdString();

	// Set layouts attributes
	new_layout->set_layout_name(name);
	new_layout->set_description(description);
}