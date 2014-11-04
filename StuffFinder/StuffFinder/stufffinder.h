/*stufffinder.h

This file contains the StuffFinder class. StuffFinder is 
a giant class that allows the interface to interact with
the database functions. 

*/

#ifndef STUFFFINDER_H
#define STUFFFINDER_H

#include <QtWidgets/QMainWindow>
#include "ui_stufffinder.h"
#include <QMessageBox>
#include "Database.h"

class StuffFinder : public QMainWindow
{
	Q_OBJECT

public:
	StuffFinder(QWidget *parent = 0);
	~StuffFinder();

private:
	Ui::StuffFinderClass ui;
	Database db;
	std::vector<Layout *> layouts;
	std::vector<QString> contcombo;//holds container name then id ie[container1,conatainer1 id,container2,container2 id]
	std::vector<QString> categorycombo;//holds category name and id

	void Output_item_tree();
	void setItems(QTreeWidgetItem * room, Container * cont, int level);

	QMenu* containerContextMenu;
	QMenu* itemContextMenu;
	QMenu* topLevelContainerMenu;
	QMenu* categoryContextMenu;
	QMenu* nocategoryContextMenu;

private slots:
void addContainerClicked();
void addItemClicked();
void editItemClicked();
void deleteItemClicked();
void addTopContainerClicked();
void deleteContainerClicked();
void handleLayoutChange(int index) { Output_item_tree(); }
void addCategoryClicked();
void deleteCategoryClicked();

public slots:
void on_Search_button_clicked();
void on_search_returnPressed();
void on_addLayout_clicked();
void onCustomContextMenu(const QPoint &point);
void onCatCustomContextMenu(const QPoint &point);


};

#endif // STUFFFINDER_H
