#ifndef QTDEMO_H
#define QTDEMO_H

#include <QtWidgets/QMainWindow>
#include "ui_qtdemo.h"

class qtdemo : public QMainWindow
{
	Q_OBJECT

public:
	qtdemo(QWidget *parent = 0);
	~qtdemo();

private:
	Ui::qtdemoClass ui;
};

#endif // QTDEMO_H
