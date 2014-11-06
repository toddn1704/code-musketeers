/*Addcontainerdialog.h

This file holds the Addcontainerdialog class which defines
a separate window that allows the user to add a new
container.

*/

#ifndef ADDCONTAINERDIALOG_H
#define ADDCONTAINERDIALOG_H

#include <qdialog.h>
#include <container.h>
#include <ui_addcontainerdialog.h>
//#include <ui_Addcontainerdialog.h>


class Addcontainerdialog : public QDialog {
	Q_OBJECT
public:
	Addcontainerdialog(QWidget *parent, Container *cont);
	~Addcontainerdialog(){}

private:
	Ui::Addcontainerdialog ui;
	
	Container *new_container;

public slots:
void saveContainer();

};
#endif