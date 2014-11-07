/*editcontainerdialog.h

This file holds the EditContainerDialog class which defines
a separate window that allows the user to edit an existing 
container.

*/

#ifndef EDITCONTAINERDIALOG_H
#define EDITCONTAINERDIALOG_H

#include <qdialog.h>
#include <container.h>
#include <ui_editcontainerdialog.h>


class EditContainerDialog : public QDialog {
	Q_OBJECT
public:
	EditContainerDialog(QWidget *parent, Container * container,int &parent_container_id,std::vector<QString> container_combo);
	~EditContainerDialog(){}

private:
	Ui::editcontainerdialog ui;

	int *parent_container_id_;
	Container * container_;

	public slots:
	void SaveContainer();

};
#endif