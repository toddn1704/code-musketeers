/*stufffinder.cpp

This file will implement the functions declared in the stufffinder.h
file.

This file is also responsible for handling user input and communicating
with the database accordingly.

*/

#include "stufffinder.h"
#include "sqlite3.h"
#include "database.h"
#include <string>
#include "addcontainerdialog.h"
#include "addlayoutdialog.h"
#include "addcategorydialog.h"
#include "edititemdialog.h"
#include "additemdialog.h"
#include "editcontainerdialog.h"
#include <vector>
#include <layout.h>
#include <layoutscene.h>
//included for testing only
#include<iostream>
#include<fstream>
#include<qdebug.h>
#include<QGraphicsRectItem>
#include<QGraphicsScene>
#include<QGraphicsView>

// Constructo sets up ui and outputs whatever is currently in the database
StuffFinder::StuffFinder(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//lock the window size to current size
	this->setFixedSize(geometry().width(),geometry().height());
	//set current tab to changelog
	ui.tabWidget_2->setCurrentIndex(0);


	connect(ui.layoutComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(HandleLayoutChange(int)));

	//connect search_result_tree to double and single clicked
	ui.search_result_treewidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.search_result_treewidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem *,int)), this, SLOT(SearchResultDoubleClicked(QTreeWidgetItem *,int)));
	connect(ui.search_result_treewidget,SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(SearchResultRightClicked(const QPoint &)));
	

	scene_ = new LayoutScene;
	scene_->setSceneRect(0,0,665,525);
	ui.graphics_view->setScene(scene_);

	connect(ui.itemsTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem * , int)), this, SLOT(TreeItemClicked(QTreeWidgetItem * , int)));

	// Add layouts to comboBox
	//iterates through layouts and adds them to a combo box
	layouts = db.LoadLayouts();
	if (layouts.size())
	{
		for (int i = 0; i < layouts.size(); i++)
		{
			ui.layoutComboBox->addItem(QString::fromStdString(layouts[i]->get_name()),
				layouts[i]->get_layout_id());
		}
	}
	// Set the list views
	//updates list
	OutputItemTree();

	// Create context menus
	//things that pop-up when you right-click
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
	containerContextMenu->addAction("Add Container", this, SLOT(AddContainerClicked()));
	containerContextMenu->addAction("Add Item", this, SLOT(AddItemClicked()));
	containerContextMenu->addSeparator(); //visual line
	containerContextMenu->addAction("Edit Container", this, SLOT(EditContainerClicked()));
	containerContextMenu->addAction("Delete Container", this, SLOT(DeleteContainerClicked()));
	itemContextMenu->addAction("Edit Item", this, SLOT(EditItemClicked()));
	itemContextMenu->addSeparator();
	itemContextMenu->addAction("Delete Item",this, SLOT(DeleteItemClicked()));
	topLevelContainerMenu->addAction("Add Container", this, SLOT(AddTopContainerClicked()));

	// Setup category context menus and actions
	connect(ui.categoryTreeWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCatCustomContextMenu(const QPoint &)));
	nocategoryContextMenu->addAction("Add Category", this, SLOT(AddCategoryClicked()));
	categoryContextMenu->addAction("Delete Category", this, SLOT(DeleteCategoryClicked()));

	
	//set current tab to list view
	ui.tabWidget->setCurrentIndex(0);
	//set graphic view status text to locked and background color red
	ui.graphic_view_status_text->setText("Locked");
	ui.graphic_view_status_text->setStyleSheet("QLineEdit{background: red;}");
	//lock the graphic view window so that you can't draw
	ui.graphics_view->setInteractive(false);
}

StuffFinder::~StuffFinder()
{

}

// Function loads data from the database and outputs it to the GUI(list views and comboboxes)
//reloads list view
void StuffFinder::OutputItemTree()
{
	// Clear and setup tree widget
	ui.itemsTreeWidget->clear();
	ui.itemsTreeWidget->header()->close();
	ui.itemsTreeWidget->setColumnCount(1);

	ui.categoryTreeWidget->clear();
	ui.categoryTreeWidget->header()->close();
	ui.categoryTreeWidget->setColumnCount(1);
	
	ui.search_result_treewidget->clear();
	ui.search_result_treewidget->header()->close();
	ui.search_result_treewidget->setColumnCount(1);
	// Get all the layouts and their items
	layouts = db.LoadLayouts();
	//ui.containerComboBox->clear();
	contcombo.clear();
	categorycombo.clear();
	//ui.Category_menu->clear();

	//clear scene
	scene_->clear();
	scene_->update();
	
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


			//ui.containerComboBox->addItem(QString::fromStdString(layouts[j]->get_rooms()[i]->get_name()), 
				//layouts[j]->get_rooms()[i]->get_container_id());
			contcombo.push_back(QString::fromStdString(layouts[j]->get_rooms()[i]->get_name()));
			contcombo.push_back(QString::number(layouts[j]->get_rooms()[i]->get_container_id()));

			scene_->NewContainer(layouts[j]->get_rooms()[i]->get_container_id(),
				db.LoadCoords(layouts[j]->get_rooms()[i]->get_container_id()),-1);
			// Get all of its children with recursive function
			SetItems(room, layouts[j]->get_rooms()[i], 1);
			ui.itemsTreeWidget->addTopLevelItem(room);

		}
	}
	
	// Load Categories and add them to the category view with their items
	// and set the combobox for user to choose from
	std::vector<Category*> categories = db.LoadCategories();
	for (int k = 0; k < categories.size(); k++)
	{
		//ui.Category_menu->addItem(QString::fromStdString(categories[k]->get_name()), categories[k]->get_category_id());
		categorycombo.push_back(QString::fromStdString(categories[k]->get_name()));
		categorycombo.push_back(QString::number(categories[k]->get_category_id()));
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
	//ui.Category_menu->setCurrentIndex(-1);
	//ui.containerComboBox->setCurrentIndex(-1);
	scene_->update();
}

// Adds children of containers to the QTreeWidget
void StuffFinder::SetItems(QTreeWidgetItem * room, Container * cont, int level)
{
	// Recursively go through all subcontainers
	for (int j = 0; j < cont->get_container().size(); j++)
	{
		QTreeWidgetItem * subcontainer = new QTreeWidgetItem(room);
		subcontainer->setText(0, QString::fromStdString(cont->get_container()[j]->get_name()));
		// Add the container id to the tree widget item column "0"
		subcontainer->setData(0, Qt::UserRole, cont->get_container()[j]->get_container_id());
		// Add the conainer id that the sub container is in to column "1"
		subcontainer->setData(1, Qt::UserRole, cont->get_container_id());
		// Get container name and add "-" for each level its at
		QString container_name = QString::fromStdString(cont->get_container()[j]->get_name());
		for (int k = 0; k < level; k++)
		{
			container_name = "-" + container_name;
		}
		// Add container to combo box
		//ui.containerComboBox->addItem(container_name,
			//cont->get_container()[j]->get_container_id());
		contcombo.push_back(container_name);
		contcombo.push_back(QString::number(cont->get_container()[j]->get_container_id()));
		if (level == 1)
		{
			scene_->NewContainer(cont->get_container()[j]->get_container_id(),
				db.LoadCoords(cont->get_container()[j]->get_container_id()),cont->get_container_id());
		}
		int lvl = level + 1;
		SetItems(subcontainer, cont->get_container()[j], lvl);
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
void StuffFinder::on_Search_returnPressed()
{
	//binds return key to on_Search_button_clicked
	//function, essentially
	//
	on_Search_button_clicked();
}

// Searches layouts for user entered item by name and outputs result to messagebox
void StuffFinder::on_Search_button_clicked()
{
	//get value from Search entry field & convert 
	//to string.
	std::string name = ui.Search->text().toStdString();
	//create search_result container to hold all items that were found
	std::vector<Item> search_results;

	//set current tab to search results and clear last results
	ui.tabWidget->setCurrentIndex(2);
	ui.search_result_treewidget->clear();
	//Search all layouts
	for (int i = 0; i < layouts.size(); i++)
	{
		layouts[i]->SearchName(name,search_results);
	}
	//send value to db Search function
	if (search_results.empty())
	{
		QTreeWidgetItem *item = new QTreeWidgetItem(ui.search_result_treewidget);
		item->setText(0, "Sorry could not find the item you searched.");
		return;
	}
	else
	{
		for (int i = 0; i < search_results.size(); i++)
		{
			QTreeWidgetItem *item = new QTreeWidgetItem(ui.search_result_treewidget);
			item->setText(0, QString::fromStdString(search_results[i].get_name()));
			item->setData(0, Qt::UserRole, search_results[i].get_item_id());
			ui.search_result_treewidget->addTopLevelItem(item);
		}
	}
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

/*
	When a search_item is double clicked run this function.
	This function will display item information in a messagebox.
	*item is the item clicked in the treewidget.
*/
void StuffFinder::SearchResultDoubleClicked(QTreeWidgetItem *item, int col)
{
	QMessageBox msgBox;
	std::string results,category = "None";
	Item * return_item = new Item;
	for (int i = 0; i < layouts.size(); i++)
	{
		return_item = layouts[i]->Search(item->data(0,Qt::UserRole).toInt());
		if (return_item != NULL)
		{
			break;
		}
	}
	if (return_item != NULL)
	{
		for (int i = 0; i < categorycombo.size(); i=i+2)
		{
			if (categorycombo[i + 1].toInt() == return_item->get_category())
			{
				category = categorycombo[i].toStdString();
				break;
			}
		}
		results = "Name: " + return_item->get_name() + "\nDescription: " + return_item->get_description() + "\nCategory: " + category +
			"\nQantity: " + std::to_string(return_item->get_quantity());
		msgBox.setText(QString::fromStdString(results));
		msgBox.exec();
		return;
	}
}

void StuffFinder::SearchResultRightClicked(const QPoint &point)
{
	qDebug() << "rightclicked";
	QMessageBox msgBox;
	msgBox.setText("Temporary");
	msgBox.exec();
	return;
}

// When user clicks "Add Container" creates dialog box to enter information
void StuffFinder::AddContainerClicked()
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
	db.CreateContainer(new_container, ui.itemsTreeWidget->currentItem()->data(0, Qt::UserRole).toInt(), false);
	if (!ui.itemsTreeWidget->currentItem()->parent())
	{
		qDebug() << new_container->get_container_id();
		GraphicViewSwitch();
		scene_->NewContainer(new_container->get_container_id(), ui.itemsTreeWidget->currentItem()->data(0, Qt::UserRole).toInt());
	}

	QTreeWidgetItem * subcontainer = new QTreeWidgetItem(ui.itemsTreeWidget->currentItem());
	subcontainer->setText(0, QString::fromStdString(new_container->get_name()));
	// Add the container id to the tree widget item column "0"
	subcontainer->setData(0, Qt::UserRole, new_container->get_container_id());
	// Add the conainer id that the sub container is in to column "1"
	subcontainer->setData(1, Qt::UserRole, ui.itemsTreeWidget->currentItem()->data(0, Qt::UserRole).toInt());
	// Get container name and add "-" for each level its at
	QString container_name = QString::fromStdString(new_container->get_name());
	QTreeWidgetItem * parent = ui.itemsTreeWidget->currentItem();
	while (parent->parent() != NULL)
	{
		container_name = "-" + container_name;
		parent = parent->parent();
	}
	contcombo.push_back(container_name);
	contcombo.push_back(QString::number(new_container->get_container_id()));

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
	db.CreateLayout(new_layout);
	//Add layout to loaded layouts
	layouts.push_back(new_layout);
	//Add layout name and id to layout combo box
	ui.layoutComboBox->addItem(QString::fromStdString(new_layout->get_name()),
		new_layout->get_layout_id());
}

// Handles when "Add Container" is clicked with no parent 
void StuffFinder::AddTopContainerClicked()
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
	db.CreateContainer(new_container, ui.layoutComboBox->currentData().toInt(), true);
	OutputItemTree();
	GraphicViewSwitch();
	scene_->NewContainer(new_container->get_container_id(),-1);
}

// Deletes container from database then reloads lists
void StuffFinder::DeleteContainerClicked()
{
	db.DeleteContainer(ui.itemsTreeWidget->currentItem()->data(0, Qt::UserRole).toInt());
	scene_->DeleteContainer(ui.itemsTreeWidget->currentItem()->data(0, Qt::UserRole).toInt());
	delete ui.itemsTreeWidget->currentItem();
	scene_->update();
}

// Doesn't do anything yet
void StuffFinder::AddItemClicked()
{
	Item * new_item = new Item;
	//get container id and name to add item to
	int container_id = ui.itemsTreeWidget->currentItem()->data(0,Qt::UserRole).toInt();
	std::string container_name = ui.itemsTreeWidget->currentItem()->text(0).toStdString();
	
	Additemdialog *new_item_window = new Additemdialog(this, new_item, container_id,container_name, categorycombo);
	new_item_window->exec();
	
	if (new_item->get_min_quantity() != -1)
	{
		db.CreateItem(new_item,new_item->get_container_id(),new_item->get_category());
		OutputItemTree();
	}
}

// Deletes item from database and reloads list
void StuffFinder::DeleteItemClicked()
{
	//Get current item name you want to delete
	std::string str = ui.itemsTreeWidget->currentItem()->text(0).toStdString();
	//Delete item from database
	db.DeleteItem(str);
	//Reload tree
	OutputItemTree();
}

// Doesn't do anything yet
void StuffFinder::EditItemClicked()
{
	int item_id = ui.itemsTreeWidget->currentItem()->data(1, Qt::UserRole).toInt();
	// Create a Item
	Item *new_item = new Item;
	for (int i = 0; i < layouts.size(); i++)
	{
		new_item = layouts[i]->Search(item_id);
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

		//set container id for item
		cont_id = ui.itemsTreeWidget->currentItem()->data(2, Qt::UserRole).toInt();
		// Popup dialog for user to enter
		Edititemdialog *new_item_window = new Edititemdialog(this, new_item,cont_id,contcombo,categorycombo);
		new_item_window->exec();

		//update database item
		db.UpdateItem(new_item);
		OutputItemTree();
	}
}

void StuffFinder::EditContainerClicked()
{
	int container_id = ui.itemsTreeWidget->currentItem()->data(0, Qt::UserRole).toInt();
	int parent_container_id = ui.itemsTreeWidget->currentItem()->data(1, Qt::UserRole).toInt();
	Container *new_container = new Container;
	for (int i = 0; i < layouts.size(); i++)
	{
		new_container = layouts[i]->SearchContainer(container_id);
		if (new_container != NULL)
		{
			break;
		}
	}
	if (new_container == NULL)
	{
		QMessageBox msgBox;
		msgBox.setText("Error: could not find container.(INTERNAL ERROR)");
		msgBox.exec();
		return;
	}
	else
	{
		// Popup dialog for user to enter
		EditContainerDialog *new_container_window = new EditContainerDialog(this, new_container, parent_container_id, contcombo);
		new_container_window->exec();

		//update database container
		db.UpdateContainer(new_container,parent_container_id);
		OutputItemTree();
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
void StuffFinder::AddCategoryClicked()
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
	db.CreateCategory(new_category);
	//Reload trees
	OutputItemTree();
}

// Deletes selected category
void StuffFinder::DeleteCategoryClicked()
{

	db.DeleteCategory(ui.categoryTreeWidget->currentItem()->data(0, Qt::UserRole).toInt(), ui.categoryTreeWidget->currentItem()->text(0).toStdString());
	OutputItemTree();
}

//lock/unlock graphic view
void StuffFinder::GraphicViewSwitch()
{
	if (ui.graphic_view_status_text->text() == "Locked")
	{
		ui.graphics_view->setInteractive(true);
		ui.graphic_view_status_text->setText("Unlocked");
		ui.graphic_view_status_text->setStyleSheet("QLineEdit{background: green;}");
	}
	else
	{
		ui.graphics_view->setInteractive(false);
		ui.graphic_view_status_text->setText("Locked");
		ui.graphic_view_status_text->setStyleSheet("QLineEdit{background: red;}");
	}
}

void StuffFinder::on_expand_button_clicked()
{
	if (geometry().height() > 700)
	{
		this->setFixedSize(1206,700);
	}
	else
	{
		this->setFixedSize(1206, 800);
	}
}

void StuffFinder::keyPressEvent(QKeyEvent * e)
{
	if (e->key() == Qt::Key_Return)
	{
		QVector<QPointF> points = scene_->StopDrawing();
		if (points.size() > 0)
		{
			db.InsertCoords(scene_->CurrentContainerId(), points);
		}
		GraphicViewSwitch();
	}
}

void StuffFinder::TreeItemClicked(QTreeWidgetItem * item, int column)
{
	qDebug() << "CLICKED";
	scene_->HighlightItem(item->data(0, Qt::UserRole).toInt());
	
}