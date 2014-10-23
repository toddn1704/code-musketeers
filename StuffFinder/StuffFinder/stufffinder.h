#ifndef STUFFFINDER_H
#define STUFFFINDER_H

#include <QtWidgets/QMainWindow>
#include "ui_stufffinder.h"
#include <QMessageBox>
#include "Database.h"

class StuffFinder : public QMainWindow
{
	Q_OBJECT

public:
	StuffFinder(QWidget *parent = 0);
	~StuffFinder();

private:
	Ui::StuffFinderClass ui;
	Database db;

	void Output_item_tree();
	void setItems(QTreeWidgetItem * room, Container * cont);

public slots:
void on_Search_button_clicked();
void on_search_returnPressed();
void on_Create_db_clicked();
void on_Add_save_clicked();
void on_Add_cancel_clicked();


};

#endif // STUFFFINDER_H
