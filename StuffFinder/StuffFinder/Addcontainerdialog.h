#ifndef ADDCONTAINERDIALOG_H
#define ADDCONTAINERDIALOG_H

#include <qdialog.h>
#include <Container.h>
#include <ui_Addcontainerdialog.h>


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