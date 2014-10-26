#include "stufffinder.h"
#include "sqlite3.h"
#include "Database.h"
#include <string>
#include "Addcontainerdialog.h"
#include "Addlayoutdialog.h"
#include <vector>
#include <Layout.h>
//included for testing only
#include<iostream>
#include<fstream>
#include<qdebug.h>

StuffFinder::StuffFinder(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.layoutComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleLayoutChange(int)));
	layouts = db.Load_Layouts();
	if (layouts.size())
	{
		for (int i = 0; i < layouts.size(); i++)
		{
			ui.layoutComboBox->addItem(QString::fromStdString(layouts[i]->get_name()),
				layouts[i]->get_layout_id());
		}
	}
	
	Output_item_tree();

	// Create context menus
	containerContextMenu = new QMenu(ui.itemsTreeWidget);
	itemContextMenu = new QMenu(ui.itemsTreeWidget);
	topLevelContainerMenu = new QMenu(ui.itemsTreeWidget);
	ui.itemsTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	
	// Connect the tree widget to the onCustomContextMenu slot function
	connect(ui.itemsTreeWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));
	// Add actions to the menus and connect them to their slots
	containerContextMenu->addAction("Add Container", this, SLOT(addContainerClicked()));
	containerContextMenu->addAction("Add Item", this, SLOT(addItemClicked()));
	containerContextMenu->addSeparator();
	containerContextMenu->addAction("Delete Container", this, SLOT(deleteContainerClicked()));
	itemContextMenu->addAction("Edit Item", this, SLOT(editItemClicked()));
	topLevelContainerMenu->addAction("Add Container", this, SLOT(addTopContainerClicked()));

	
	
}

StuffFinder::~StuffFinder()
{

}

void StuffFinder::Output_item_tree()
{
	// Clear and setup tree widget
	ui.itemsTreeWidget->clear();
	ui.itemsTreeWidget->header()->close();
	ui.itemsTreeWidget->setColumnCount(1);
	
	// Get all the layouts and their items
	layouts = db.Load_Layouts();
	ui.containerComboBox->clear();


	
	if (layouts.size())
	{
		int j = ui.layoutComboBox->currentIndex();
		// Iterate over all rooms in layout.   Currently by default does only first layout.
		for (int i = 0; i < layouts[ui.layoutComboBox->currentIndex()]->get_rooms().size(); i++)
		{
			// Create top level item and set text
			QTreeWidgetItem *room = new QTreeWidgetItem(ui.itemsTreeWidget);
			room->setText(0, QString::fromStdString(layouts[j]->get_rooms()[i]->get_name()));
			// Add the container id to the tree widget item
			room->setData(0, Qt::UserRole, layouts[j]->get_rooms()[i]->get_container_id());


			ui.containerComboBox->addItem(QString::fromStdString(layouts[j]->get_rooms()[i]->get_name()), 
				layouts[j]->get_rooms()[i]->get_container_id());
			// Get all of its children with recursive function
			setItems(room, layouts[j]->get_rooms()[i], 1);
			ui.itemsTreeWidget->addTopLevelItem(room);
		}
	}
	
	ui.containerComboBox->setCurrentIndex(-1);

}

void StuffFinder::setItems(QTreeWidgetItem * room, Container * cont, int level)
{
	// Recursively go through all subcontainers
	for (int j = 0; j < cont->get_container().size(); j++)
	{
		QTreeWidgetItem * subcontainer = new QTreeWidgetItem(room);
		subcontainer->setText(0, QString::fromStdString(cont->get_container()[j]->get_name()));
		// Add the container id to the tree widget item
		subcontainer->setData(0, Qt::UserRole, cont->get_container()[j]->get_container_id());

		// Get container name and add "-" for each level its at
		QString container_name = QString::fromStdString(cont->get_container()[j]->get_name());
		for (int k = 0; k < level; k++)
		{
			container_name = "-" + container_name;
		}
		// Add container to combo box
		ui.containerComboBox->addItem(container_name,
			cont->get_container()[j]->get_container_id());
		setItems(subcontainer, cont->get_container()[j], ++level);
	}
	// Add owned items to the tree
	for (int i = 0; i < cont->get_items().size(); i++)
	{
		QTreeWidgetItem *item = new QTreeWidgetItem(room);
		item->setText(0, QString::fromStdString(cont->get_items()[i]->get_name()));
		// Set "container id" to 0 so we know its an item
		item->setData(0, Qt::UserRole, 0);
	}

	return;
}

void StuffFinder::on_search_returnPressed()
{
	//binds return key to on_Search_button_clicked
	//function, essentially
	//
	on_Search_button_clicked();
}

void StuffFinder::on_Search_button_clicked()
{
	//get value from search entry field & convert 
	//to string.
	//
	std::string query = ui.search->text().toStdString();

	Item * find_item = layouts[0]->search(query);
	//send value to db search function
	if (find_item == NULL)
	{
		QMessageBox msgBox;
		msgBox.setText("Your search found no items with that name.");
		msgBox.exec();
		return;
	}
	else
	{
		QMessageBox msgBox;
		std::string output = "Found your item!!!!\nName: " + find_item->get_name() + "\nDescription: " + find_item->get_description() + "\nCategory: " 
			+ find_item->get_category() + "\nQuantity: " + std::to_string(find_item->get_quantity());
		QString qstr = QString::fromStdString(output);
		msgBox.setText(qstr);
		msgBox.exec();
		return;
	}
}

void StuffFinder::on_Add_save_clicked()
{
	//gets values from entry fields and
	//converts to string so can be saved in database
	//
	
	std::string name = ui.Item_name->text().toStdString();
	std::string descript = ui.Item_descript->toPlainText().toStdString();
	std::string quant = ui.Item_quant->text().toStdString();
	std::string minquant = ui.Min_quant->text().toStdString();
	std::string cost = ui.Item_cost->text().toStdString(); 
	int container_id = ui.containerComboBox->itemData(ui.containerComboBox->currentIndex(), Qt::UserRole).toInt();

	//send values to an add/edit item function
	//  which is connected to the database
	// Check if the fields are populated
	if (name.empty() || descript.empty() || quant.empty() || minquant.empty()
		|| cost.empty() || ui.containerComboBox->currentIndex() == -1)
	{
		QMessageBox msgBox;
		msgBox.setText("You didnt fill in all the boxees silly!");
		msgBox.exec();
		return;
	}
	// Add item and update list
	Item * add_me = new Item(name, descript, std::stoi(quant.c_str()), "temp");
	db.Create_Item(add_me, container_id);
	Output_item_tree();

	ui.Item_name->clear();
	ui.Item_descript->clear();
	ui.Item_quant->clear();
	ui.Min_quant->clear();
	ui.Item_cost->clear();
	ui.containerComboBox->setCurrentIndex(-1);
	/*test print
	using namespace std;
	ofstream file;
	file.open("testoutput.txt");
	file << name << endl;
	file << iquant << endl;
	file.close();
	*/
}

void StuffFinder::on_Add_cancel_clicked()
{
	/*clears entry fields when cancel button is
	clicked (in add/edit item tab).
	*/
	ui.Item_name->clear();
	ui.Item_descript->clear();
	ui.Item_quant->clear();
	ui.Min_quant->clear();
	ui.Item_cost->clear();
}

void StuffFinder::onCustomContextMenu(const QPoint &point)
{
	qDebug() << ui.itemsTreeWidget->itemAt(point);
	// Check if user is clicking outside any items
	if (!ui.itemsTreeWidget->itemAt(point))
	{
		topLevelContainerMenu->exec(ui.itemsTreeWidget->mapToGlobal(point));
		return;
	}
	// Check if its a container
	else if (ui.itemsTreeWidget->itemAt(point)->data(0, Qt::UserRole).toInt())
	{
		containerContextMenu->exec(ui.itemsTreeWidget->mapToGlobal(point));
	}
	// Its an item
	else
	{
		itemContextMenu->exec(ui.itemsTreeWidget->mapToGlobal(point));
	}
}

void StuffFinder::addContainerClicked()
{
	// Create a container
	Container *new_container = new Container;

	// Popup dialog for user to enter
	Addcontainerdialog *new_container_window = new Addcontainerdialog(this, new_container);
	new_container_window->exec();
	if (new_container->get_name().empty() || new_container->get_description().empty())
	{
		QMessageBox msgBox;
		msgBox.setText("You didnt fill in all the boxees silly!");
		msgBox.exec();
		return;
	}
	// Create the container and reload list
	db.Create_Container(new_container, ui.itemsTreeWidget->currentItem()->data(0, Qt::UserRole).toInt(), false);
	Output_item_tree();
}

void StuffFinder::on_AddLayout_clicked()
{
	// Create a layout
	Layout *new_layout = new Layout;

	// Popup dialog for user to enter
	Addlayoutdialog *new_layout_window = new Addlayoutdialog(this, new_layout);
	new_layout_window->exec();
	if (new_layout->get_name().empty() || new_layout->get_description().empty())
	{
		QMessageBox msgBox;
		msgBox.setText("You didnt fill in all the boxees silly!");
		msgBox.exec();
		return;
	}
	//Add layout to db
	db.Create_Layout(new_layout);
	//Add layout to loaded layouts
	layouts.push_back(new_layout);
	//Add layout name and id to layout combo box
	ui.layoutComboBox->addItem(QString::fromStdString(new_layout->get_name()),
		new_layout->get_layout_id());
}

void StuffFinder::addTopContainerClicked()
{
	// Create a container
	Container *new_container = new Container;

	// Popup dialog for user to enter
	Addcontainerdialog *new_container_window = new Addcontainerdialog(this, new_container);
	new_container_window->exec();

	// Create the container and reload list  ***Currently defaults to layout 1****
	if (new_container->get_name().empty() || new_container->get_description().empty())
	{
		QMessageBox msgBox;
		msgBox.setText("You didnt fill in all the boxees silly!");
		msgBox.exec();
		return;
	}
	db.Create_Container(new_container, ui.layoutComboBox->currentData().toInt(), true);
	Output_item_tree();
}

void StuffFinder::deleteContainerClicked()
{
	db.Delete_Container(ui.itemsTreeWidget->currentItem()->data(0, Qt::UserRole).toInt());
	Output_item_tree();
}
void StuffFinder::addItemClicked()
{
	// Temp code
	QMessageBox msgBox;
	msgBox.setText("Eventually I'll do something(like adding an item)!");
	msgBox.exec();
}

void StuffFinder::editItemClicked()
{
	// Temp code
	QMessageBox msgBox;
	msgBox.setText("Eventually I'll do something to an item!");
	msgBox.exec();
}