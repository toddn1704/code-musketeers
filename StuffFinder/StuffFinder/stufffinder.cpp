#include "stufffinder.h"
#include "sqlite3.h"
#include "Database.h"
#include <string>

#include <vector>
#include <Layout.h>
//included for testing only
#include<iostream>
#include<fstream>


StuffFinder::StuffFinder(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Output_item_tree();

	// Create context menus
	containerContextMenu = new QMenu(ui.itemsTreeWidget);
	itemContextMenu = new QMenu(ui.itemsTreeWidget);
	ui.itemsTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	
	// Connect the tree widget to the onCustomContextMenu slot function
	connect(ui.itemsTreeWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));
	// Add actions to the menus and connect them to their slots
	containerContextMenu->addAction("Add Container", this, SLOT(addContainerClicked()));
	containerContextMenu->addAction("Add Item", this, SLOT(addItemClicked()));
	itemContextMenu->addAction("Edit Item", this, SLOT(editItemClicked()));


	
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


	if (layouts.size())
	{
		// Iterate over all rooms in layout.   Currently by default does only first layout.
		for (int i = 0; i < layouts[0]->get_rooms().size(); i++)
		{
			// Create top level item and set text
			QTreeWidgetItem *room = new QTreeWidgetItem(ui.itemsTreeWidget);
			room->setText(0, QString::fromStdString(layouts[0]->get_rooms()[i]->get_name()));
			// Add the container id to the tree widget item
			room->setData(0, Qt::UserRole, layouts[0]->get_rooms()[i]->get_container_id());


			ui.containerComboBox->addItem(QString::fromStdString(layouts[0]->get_rooms()[i]->get_name()), 
				layouts[0]->get_rooms()[i]->get_container_id());
			// Get all of its children with recursive function
			setItems(room, layouts[0]->get_rooms()[i], 1);
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

void StuffFinder::on_Create_db_clicked()
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	
	rc = sqlite3_open("test.db", &db);

	if (rc)
	{
		QMessageBox msgBox;
		msgBox.setText("Can't open database: %s.");
		msgBox.exec();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText("Opened database successfully.");
		msgBox.exec();
	}
	sqlite3_close(db);
}

void StuffFinder::onCustomContextMenu(const QPoint &point)
{
	// Check if its a container
	if (ui.itemsTreeWidget->itemAt(point)->data(0, Qt::UserRole).toInt())
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
	// Temp code
	QMessageBox msgBox;
	msgBox.setText("Eventually I'll do something!");
	msgBox.exec();
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