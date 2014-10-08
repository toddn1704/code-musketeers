#include "stufffinder.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	StuffFinder w;
	w.show();
	return a.exec();
}
