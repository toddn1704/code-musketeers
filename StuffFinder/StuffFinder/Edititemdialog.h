/*Edititemdialog.h

This file holds the Edititemdialog class which defines
a separate window that allows the user to add a new
item.

*/

#ifndef EDITITEMDIALOG_H
#define EDITITEMDIALOG_H

#include <qdialog.h>
#include <Item.h>
#include <ui_Edititemdialog.h>


class Edititemdialog : public QDialog {Q_OBJECT
	
public:
	Edititemdialog(QWidget *parent, Item *item);
	~Edititemdialog(){}

private:
	Ui::Edititemdialog ui;

	Item *new_item;

	public slots:
	void saveItem();

};
#endif