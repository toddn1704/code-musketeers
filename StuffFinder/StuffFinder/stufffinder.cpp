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
	//get values from entry fields
	QString name = ui.Item_name->text();
	QString descript = ui.Item_descript->text();
	QString quant = ui.Item_quant->text();
	QString minquant = ui.Min_quant->text();
	QString cost = ui.Item_cost->text();

	//send values to an add/edit item function
	//  which is connected to the database

	QMessageBox msgBox;
	msgBox.setText(name);
	msgBox.exec();

}

void StuffFinder::on_Add_cancel_clicked()
{
	//does something when the Add_cancel
	//   button is clicked.

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
