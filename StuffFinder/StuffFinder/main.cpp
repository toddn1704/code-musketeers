#include "stufffinder.h"
#include <QtWidgets/QApplication>
#include "Database.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	StuffFinder w;
	w.show();
	Database db;

	// Test create item
	Item* test_item = new Item;
	test_item->set_description("hit stuff");
	test_item->set_name("Hammer");
	test_item->id = db.Create_Item(test_item);

	db.Delete_Item(test_item);



	return a.exec();
}
