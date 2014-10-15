#include "stufffinder.h"
#include <QtWidgets/QApplication>
#include "Database.h"
#include "qdebug.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	StuffFinder w;
	w.show();
	Database db;

	// Test create item
	Item* test_item = new Item;
	int id;
	test_item->set_description("hit stuff");
	test_item->set_name("Hammer");
	id = db.Create_Item(test_item);
	test_item->set_item_id(id);

	db.Delete_Item(test_item);

	Container * test_cont = new Container;
	db.Load_Items(test_cont);
	std::vector<Container*> test_containers = db.Load_Containers(test_cont);
	for (int i = 0; i < test_containers.size(); i++)
	{
		qDebug() << test_containers[i]->get_container_id() << "," << test_containers[i]->get_name().c_str() <<
			"," << test_containers[i]->get_description().c_str();
	}
	return a.exec();
}
