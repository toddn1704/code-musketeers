#ifndef STUFFFINDER_H
#define STUFFFINDER_H

#include <QtWidgets/QMainWindow>
#include "ui_stufffinder.h"

class StuffFinder : public QMainWindow
{
	Q_OBJECT

public:
	StuffFinder(QWidget *parent = 0);
	~StuffFinder();

private:
	Ui::StuffFinderClass ui;
};

#endif // STUFFFINDER_H
