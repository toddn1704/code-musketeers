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

void StuffFinder::on_search_returnPressed()
{
	//binds return key to on_Search_button_clicked
	//function, essentially
	//
	on_Search_button_clicked();
}

void StuffFinder::on_Search_button_clicked()
{
	//get value from search entry field
	QString query = ui.search->text();

	//send value to db search function

	//test print
	QMessageBox msgBox;
	msgBox.setText(query);
	msgBox.exec();
}

void StuffFinder::on_Add_save_clicked()
{
	//get values from entry fields
	QString name = ui.Item_name->text();
	QString descript = ui.Item_descript->toPlainText();
	QString quant = ui.Item_quant->text();
	QString minquant = ui.Min_quant->text();
	QString cost = ui.Item_cost->text();

	//send values to an add/edit item function
	//  which is connected to the database

	//test print
	QMessageBox msgBox;
	msgBox.setText(name);
	msgBox.exec();

}

void StuffFinder::on_Add_cancel_clicked()
{
	/*clears entry fields when cancel button is
	clicked (in add/edit item tab).
	*/
	ui.Item_name->clear();
	ui.Item_descript->clear();
	ui.Item_quant->clear();
	ui.Min_quant->clear();
	ui.Item_cost->clear();
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
