/*shoppinglist.h

This file holds the shoppinglist class which defines a dialog
window that displays a shopping list.

*/

#ifndef SHOPPINGLIST_H
#define SHOPPINGLIST_H

#include <qdialog.h>
#include <qdebug>
#include <ui_shoppinglist.h>

class Shoppinglist : public QDialog {
	Q_OBJECT

public:
	Shoppinglist(QWidget *parent, std::vector<std::string> output);
	~Shoppinglist(){}

private:
	Ui::Shoppinglist ui;
	std::string output_;
	public slots:
	void on_export_button_clicked();

};
#endif