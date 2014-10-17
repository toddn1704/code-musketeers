#ifndef STUFFFINDER_H
#define STUFFFINDER_H

#include <QtWidgets/QMainWindow>
#include "ui_stufffinder.h"
#include <QMessageBox>

class StuffFinder : public QMainWindow
{
	Q_OBJECT

public:
	StuffFinder(QWidget *parent = 0);
	~StuffFinder();

private:
	Ui::StuffFinderClass ui;

public slots:
void on_Create_db_clicked();
void on_Add_save_clicked();

};

#endif // STUFFFINDER_H
