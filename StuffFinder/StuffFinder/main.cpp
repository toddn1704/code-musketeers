#include "stufffinder.h"
#include <QtWidgets/QApplication>
#include "Database.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	StuffFinder w;
	w.show();
	Database db;
	return a.exec();
}
