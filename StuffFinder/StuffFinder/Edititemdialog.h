/*edititemdialog.h

This file holds the EditItemDialog class which defines
a separate window that allows the user to add a new
item.

*/

#ifndef EDITITEMDIALOG_H
#define EDITITEMDIALOG_H

#include <qdialog.h>
#include <item.h>
#include <ui_edititemdialog.h>

class Edititemdialog : public QDialog {Q_OBJECT
	
public:
	Edititemdialog(QWidget *parent, Item *item, int cont_id, std::vector<QString> combocontainers, std::vector<QString> combocategory);
	~Edititemdialog(){}

private:
	Ui::Edititemdialog ui;

	Item *new_item;

	public slots:
	void SaveItem();

};
#endif