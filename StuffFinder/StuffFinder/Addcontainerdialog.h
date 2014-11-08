/*addcontainerdialog.h

This header file holds the AddContainerDialog class, which defines
a simple dialog window which allowing the user to add a new container.

*/

#ifndef ADDCONTAINERDIALOG_H
#define ADDCONTAINERDIALOG_H

#include <qdialog.h>
#include <container.h>
#include <ui_addcontainerdialog.h>



class Addcontainerdialog : public QDialog {
	Q_OBJECT
public:
	Addcontainerdialog(QWidget *parent, Container *cont);
	~Addcontainerdialog(){}

private:
	Ui::Addcontainerdialog ui;
	
	Container *new_container;

public slots:
void SaveContainer();

};
#endif