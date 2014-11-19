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
	return a.exec();
}
