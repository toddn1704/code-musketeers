/*Addlayoutdialog.h

This file holds the Addlayoutdialog class, which defines
a seperate window allowing the user to create a new layout.

*/

#ifndef ADDLAYOUTDIALOG_H
#define ADDLAYOUTDIALOG_H

#include <qdialog.h>
#include <Layout.h>
#include <ui_Addlayoutdialog.h>


class Addlayoutdialog : public QDialog {
	Q_OBJECT
public:
	Addlayoutdialog(QWidget *parent, Layout *lay);
	~Addlayoutdialog(){}

private:
	Ui::Addlayoutdialog ui;

	Layout *new_layout;

	public slots:
	void savelayout();

};
#endif