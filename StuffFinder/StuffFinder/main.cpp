#include "stufffinder.h"
#include <QtWidgets/QApplication>
#include "Database.h"
#include "qdebug.h"
#include <iostream>
#include <fstream>

using namespace std;

void testprint()
{
	ofstream myfile;
	myfile.open("sfexample.txt");
	myfile << "Hullo, World!" << endl;
	myfile.close();
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//creates a test button & connects it to a test function
	QPushButton *button = new QPushButton("Hullo World");
	button->setGeometry(20, 20, 20, 20);
	QObject::connect(button, &QPushButton::clicked, testprint);
	button->show();

	StuffFinder w;
	w.show();
	Database db;



	/*
	// Test create item
	Item* test_item = new Item;
	int id;
	test_item->set_description("hit stuff");
	test_item->set_name("Hammer");
	db.Create_Item(test_item);
	db.Delete_Item(test_item);

	Container * test_cont = new Container;
	db.Load_Items(test_cont);
	std::vector<Container*> test_containers = db.Load_Containers(test_cont);
	for (int i = 0; i < test_containers.size(); i++)
	{
		qDebug() << test_containers[i]->get_container_id() << "," << test_containers[i]->get_name().c_str() <<
			"," << test_containers[i]->get_description().c_str();
	}
	*/

	/*
	std::vector<Layout*> all_layouts = db.Load_Layouts();
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

	}*/

	return a.exec();
}
