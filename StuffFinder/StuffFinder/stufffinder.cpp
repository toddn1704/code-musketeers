#include "stufffinder.h"
#include "sqlite3.h"



StuffFinder::StuffFinder(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);


}

StuffFinder::~StuffFinder()
{

}

void StuffFinder::on_Add_save_clicked()
{
	//get value from Item_name field
	QString name = ui.Item_name->text();
	QMessageBox msgBox;
	
	msgBox.setText(name);
	msgBox.exec();

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
