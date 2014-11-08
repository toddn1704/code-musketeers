/*addlayoutdialog.h

This file holds the AddLayoutDialog class, which defines
a dialog window allowing the user to create a new layout.

*/

#ifndef ADDLAYOUTDIALOG_H
#define ADDLAYOUTDIALOG_H

#include <qdialog.h>
#include <layout.h>
#include <ui_addlayoutdialog.h>

class Addlayoutdialog : public QDialog {
	Q_OBJECT
public:
	Addlayoutdialog(QWidget *parent, Layout *lay);
	~Addlayoutdialog(){}

private:
	Ui::Addlayoutdialog ui;

	Layout *new_layout;

	public slots:
	void SaveLayout();

};
#endif