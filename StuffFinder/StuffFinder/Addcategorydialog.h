#ifndef ADDCATEGORYDIALOG_H
#define ADDCATEGORYDIALOG_H

#include <qdialog.h>
#include <category.h>
#include <ui_addcategorydialog.h>
//#include <ui_Addcategorydialog.h>


class Addcategorydialog : public QDialog {
	Q_OBJECT
public:
	Addcategorydialog(QWidget *parent, Category * cat);
	~Addcategorydialog(){}

private:
	// Same ui as addlayout
	Ui::Addcategorydialog ui;

	Category * new_category;

	public slots:
	void SaveCategory();

};
#endif