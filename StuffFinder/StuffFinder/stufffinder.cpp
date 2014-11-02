#include "stufffinder.h"
#include "sqlite3.h"
#include "Database.h"
#include <string>
#include "Addcontainerdialog.h"
#include "Addlayoutdialog.h"
#include "Addcategorydialog.h"
#include "Edititemdialog.h"
#include <vector>
#include <Layout.h>
//included for testing only
#include<iostream>
#include<fstream>
#include<qdebug.h>

// Constructo sets up ui and outputs whatever is currently in the database
StuffFinder::StuffFinder(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.layoutComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleLayoutChange(int)));

	// Add layouts to comboBox
	layouts = db.Load_Layouts();
	if (layouts.size())
	{
		for (int i = 0; i < layouts.size(); i++)
		{
			ui.layoutComboBox->addItem(QString::fromStdString(layouts[i]->get_name()),
				layouts[i]->get_layout_id());
		}
	}
	// Set the list views
	Output_item_tree();

	// Create context menus
	containerContextMenu = new QMenu(ui.itemsTreeWidget);
	itemContextMenu = new QMenu(ui.itemsTreeWidget);
	topLevelContainerMenu = new QMenu(ui.itemsTreeWidget);
	ui.itemsTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

	categoryContextMenu = new QMenu(ui.categoryTreeWidget);
	nocategoryContextMenu = new QMenu(ui.categoryTreeWidget);
	ui.categoryTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	
	// Connect the tree widget to the onCustomContextMenu slot function
	connect(ui.itemsTreeWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));
	// Add actions to the menus and connect them to their slots
	containerContextMenu->addAction("Add Container", this, SLOT(addContainerClicked()));
	containerContextMenu->addAction("Add Item", this, SLOT(addItemClicked()));
	containerContextMenu->addSeparator();
	containerContextMenu->addAction("Delete Container", this, SLOT(deleteContainerClicked()));
	itemContextMenu->addAction("Edit Item", this, SLOT(editItemClicked()));
	itemContextMenu->addSeparator();
	itemContextMenu->addAction("Delete Item",this, SLOT(deleteItemClicked()));
	topLevelContainerMenu->addAction("Add Container", this, SLOT(addTopContainerClicked()));

	// Setup category context menus and actions
	connect(ui.categoryTreeWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCatCustomContextMenu(const QPoint &)));
	nocategoryContextMenu->addAction("Add Category", this, SLOT(addCategoryClicked()));
	categoryContextMenu->addAction("Delete Category", this, SLOT(deleteCategoryClicked()));

	
	
}

StuffFinder::~StuffFinder()
{

}

// Function loads data from the database and outputs it to the GUI(list views and comboboxes)
void StuffFinder::Output_item_tree()
{
	// Clear and setup tree widget
	ui.itemsTreeWidget->clear();
	ui.itemsTreeWidget->header()->close();
	ui.itemsTreeWidget->setColumnCount(1);

	ui.categoryTreeWidget->clear();
	ui.categoryTreeWidget->header()->close();
	ui.categoryTreeWidget->setColumnCount(1);
	
	// Get all the layouts and their items
	layouts = db.Load_Layouts();
	ui.containerComboBox->clear();

	ui.Category_menu->clear();
	
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
	
	// Load Categories and add them to the category view with their items
	// and set the combobox for user to choose from
	std::vector<Category*> categories = db.Load_Categories();
	for (int k = 0; k < categories.size(); k++)
	{
		ui.Category_menu->addItem(QString::fromStdString(categories[k]->get_name()), categories[k]->get_category_id());
		QTreeWidgetItem * category = new QTreeWidgetItem(ui.categoryTreeWidget);
		category->setText(0, QString::fromStdString(categories[k]->get_name()));
		category->setData(0, Qt::UserRole, categories[k]->get_category_id());

		ui.categoryTreeWidget->addTopLevelItem(category);
		for (std::map<std::string, Item*>::iterator it = categories[k]->get_items().begin();
			it != categories[k]->get_items().end(); it++)
		{
			QTreeWidgetItem * item = new QTreeWidgetItem(category);
			item->setText(0, QString::fromStdString(it->first));
		}
	}
	ui.Category_menu->setCurrentIndex(-1);
	ui.containerComboBox->setCurrentIndex(-1);

}

// Adds children of containers to the QTreeWidget
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
		//set column "1" to item id.
		item->setData(1,Qt::UserRole,cont->get_items()[i]->get_item_id());
		//set column "2" to cont id
		item->setData(2, Qt::UserRole, cont->get_container_id());
	}

	return;
}

// Search button SLOT
void StuffFinder::on_search_returnPressed()
{
	//binds return key to on_Search_button_clicked
	//function, essentially
	//
	on_Search_button_clicked();
}

// Searches layouts for user entered item by name and outputs result to messagebox
void StuffFinder::on_Search_button_clicked()
{
	//get value from search entry field & convert 
	//to string.
	//
	std::string query = ui.search->text().toStdString();

	//Search all layouts
	Item * find_item = NULL;
	for (int i = 0; i < layouts.size(); i++)
	{
		find_item = layouts[i]->search(query);
		if (find_item != NULL)
		{
			break;
		}
	}
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

// Saves User entered item if data is valid
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
	int category_id = ui.Category_menu->itemData(ui.Category_menu->currentIndex(), Qt::UserRole).toInt();

	//send values to an add/edit item function
	//  which is connected to the database
	// Check if the fields are populated
	if (name.empty() || descript.empty() || quant.empty() || minquant.empty()
		|| cost.empty() || ui.containerComboBox->currentIndex() == -1
		|| ui.Category_menu->currentIndex() == -1)
	{
		QMessageBox msgBox;
		msgBox.setText("You didnt fill in all the boxees silly!");
		msgBox.exec();
		return;
	}
	// Add item and update list
	Item * add_me = new Item(name, descript, std::stoi(quant.c_str()), "temp");
	db.Create_Item(add_me, container_id, category_id);
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

// Clears data
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

// Handles right click within List View tab
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

// When user clicks "Add Container" creates dialog box to enter information
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

// When user clicks "Add Layout" button creates dialog box to enter information
void StuffFinder::on_addLayout_clicked()
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

// Handles when "Add Container" is clicked with no parent 
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

// Deletes container from database then reloads lists
void StuffFinder::deleteContainerClicked()
{
	db.Delete_Container(ui.itemsTreeWidget->currentItem()->data(0, Qt::UserRole).toInt());
	Output_item_tree();
}

// Doesn't do anything yet
void StuffFinder::addItemClicked()
{
	// Temp code
	QMessageBox msgBox;
	msgBox.setText("Eventually I'll do something(like adding an item)!");
	msgBox.exec();
}

// Deletes item from database and reloads list
void StuffFinder::deleteItemClicked()
{
	//Get current item name you want to delete
	std::string str = ui.itemsTreeWidget->currentItem()->text(0).toStdString();
	//Delete item from database
	db.Delete_Item(str);
	//Reload tree
	Output_item_tree();
}

// Doesn't do anything yet
void StuffFinder::editItemClicked()
{
	int item_id = ui.itemsTreeWidget->currentItem()->data(1, Qt::UserRole).toInt();
	// Create a Item
	Item *new_item = new Item;
	for (int i = 0; i < layouts.size(); i++)
	{
		new_item = layouts[i]->search(item_id);
		if (new_item != NULL)
		{
			break;
		}
	}
	if (new_item == NULL)
	{
		QMessageBox msgBox;
		msgBox.setText("Error: could not find item.(INTERNAL ERROR)");
		msgBox.exec();
		return;
	}
	else
	{
		// Get combobox info
		int cont_id;
		std::vector<QString> contcombo;
		std::vector<QString> categorycombo;
		//loop through container combobox to get info
		//Im saving container name, then id
		for(int i = 0; i < ui.containerComboBox->count(); i++)
		{
			contcombo.push_back(ui.containerComboBox->itemText(i));
			contcombo.push_back(ui.containerComboBox->itemData(i,Qt::UserRole).toString());
		}
		//loop through categories
		for (int i = 0; i < ui.Category_menu->count(); i++)
		{
			categorycombo.push_back(ui.Category_menu->itemText(i));
			categorycombo.push_back(ui.Category_menu->itemData(i, Qt::UserRole).toString());
		}
		//set container id for item
		cont_id = ui.itemsTreeWidget->currentItem()->data(2, Qt::UserRole).toInt();
		// Popup dialog for user to enter
		Edititemdialog *new_item_window = new Edititemdialog(this, new_item,cont_id,contcombo,categorycombo);
		new_item_window->exec();

		//update database item
		db.Update_Item(new_item);
		Output_item_tree();
	}
}
// Handles when user right clicks within category tab
void StuffFinder::onCatCustomContextMenu(const QPoint &point)
{
	// No category selected
	if (!ui.categoryTreeWidget->itemAt(point))
	{
		nocategoryContextMenu->exec(ui.categoryTreeWidget->mapToGlobal(point));
		return;
	}
	
	else
	{
		categoryContextMenu->exec(ui.categoryTreeWidget->mapToGlobal(point));
	}
	
}

// Creates dialog window and creates a container from entered information
void StuffFinder::addCategoryClicked()
{
	// Create a category
	Category *new_category = new Category;

	// Popup dialog for user to enter
	Addcategorydialog *new_category_window = new Addcategorydialog(this, new_category);
	new_category_window->exec();
	if (new_category->get_name().empty() || new_category->get_description().empty())
	{
		QMessageBox msgBox;
		msgBox.setText("You didnt fill in all the boxees silly!");
		msgBox.exec();
		return;
	}
	//Add category to db
	db.Create_Category(new_category);
	//Reload trees
	Output_item_tree();
}

// Deletes selected category
void StuffFinder::deleteCategoryClicked()
{

	db.Delete_Category(ui.categoryTreeWidget->currentItem()->data(0, Qt::UserRole).toInt());
	Output_item_tree();
}