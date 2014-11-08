/*main.cpp

This function opens the main window of the application
and creates a database object.

*/


#include "stufffinder.h"
#include <QtWidgets/QApplication>
#include "database.h"
#include "qdebug.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	StuffFinder w;
	w.show();
	Database db;

	/*
	// Test create item
	Item* test_item = new Item;
	int id;
	test_item->set_description("hit stuff");
	test_item->set_name("Hammer");
	db.CreateItem(test_item);
	db.DeleteItem(test_item);

	Container * test_cont = new Container;
	db.LoadItems(test_cont);
	std::vector<Container*> test_containers = db.LoadContainers(test_cont);
	for (int i = 0; i < test_containers.size(); i++)
	{
		qDebug() << test_containers[i]->get_container_id() << "," << test_containers[i]->get_name().c_str() <<
			"," << test_containers[i]->get_description().c_str();
	}
	

	Category * C1 = new Category;
	Layout * L1 = new Layout;
	Item * I1 = new Item;
	I1->set_name("Hammer");
	I1->set_description("Hits things");
	I1->set_quantity(1);
	I1->set_category("Tool");
	C1->set_name("Tool");
	C1->set_description("General Tools");
	L1->set_layout_name("Floor1");
	L1->set_description("First floor of home");
	db.CreateCategory(C1);
	db.CreateLayout(L1);
	db.CreateItem(I1,0);
	db.DeleteLayout(L1);
	
	std::vector<Layout*> all_layouts = db.LoadLayouts();
	for (int i = 0; i < all_layouts.size(); i++)
	{
		qDebug() << all_layouts[i]->get_name().c_str();
		std::vector<Container *> layout_cont = all_layouts[i]->get_rooms();
		for (int j = 0; j < layout_cont.size(); j++)
		{
			qDebug() << layout_cont[j]->get_name().c_str();
			std::vector<Item *> cont_items = layout_cont[j]->get_items();
			for (int k = 0; k < cont_items.size(); k++)
			{
				qDebug() << cont_items[k]->get_name().c_str();
			}
		}

	}
	*/
	return a.exec();
}
