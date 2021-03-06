/*additemdialog.h

This file holds the AddItemDialog class which defines a dialog
window that allows the user to add a new item.

*/

#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <qdialog.h>
#include <item.h>
#include <ui_additemdialog.h>

class Additemdialog : public QDialog {
	Q_OBJECT

public:
	Additemdialog(QWidget *parent, Item *new_item, int cont_id, std::string cont_name, std::vector<QString> combocategory);
	~Additemdialog(){}

private:
	Item * new_item;
	int container_id;
	Ui::Additemdialog ui;

	public slots:
	void SaveItem();

};
#endif