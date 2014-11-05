#include "editcontainerdialog.h"
#include "qmessagebox.h"

EditContainerDialog::EditContainerDialog(QWidget *parent, Container *container,int &parent_container_id,std::vector<QString> container_combo)
	: QDialog(parent)
{
	int count = 0;
	container_ = container;
	parent_container_id_ = &parent_container_id;
	ui.setupUi(this);
	connect(ui.button_box, SIGNAL(accepted()), this, SLOT(SaveContainer()));
	ui.container_combobox->clear();
	// load the container combo box
	// also save when we find the container the item is in so that we can pre select it from the combo box
	for (unsigned int i = 0; i < container_combo.size(); i = i + 2)
	{
		//make sure not to add the container ur moving/editing b/c
		//you would beable to but the same container in its self.
		if (container_combo[i + 1].toInt() != container_->get_container_id()) 
		{
			// text               id
			ui.container_combobox->addItem(container_combo[i], container_combo[i + 1]);
			//save combo index for preselect
			if (parent_container_id == container_combo[i + 1].toInt())
			{
				// preSelect the container that the item is in
				ui.container_combobox->setCurrentIndex(count);
			}
			count++;
		}
	}
	ui.container_name->setText(QString::fromStdString(container->get_name()));
	ui.container_description->setText(QString::fromStdString(container->get_description()));
}

void EditContainerDialog::SaveContainer()
{
	// Get user input and validate
	std::string name = ui.container_name->text().toStdString();
	std::string description = ui.container_description->toPlainText().toStdString();
	// Set Containers attributes
	if (!name.empty() && !description.empty())
	{
		container_->set_name(name);
		container_->set_description(description);
		*parent_container_id_ = ui.container_combobox->itemData(ui.container_combobox->currentIndex(), Qt::UserRole).toInt();
	}
	
}