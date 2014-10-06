#ifndef QT_TEST_H
#define QT_TEST_H

#include <QtWidgets/QMainWindow>
#include "ui_qt_test.h"

class Qt_test : public QMainWindow
{
	Q_OBJECT

public:
	Qt_test(QWidget *parent = 0);
	~Qt_test();

private:
	Ui::Qt_testClass ui;
};

#endif // QT_TEST_H
