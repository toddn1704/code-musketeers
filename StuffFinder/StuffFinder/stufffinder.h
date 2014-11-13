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
#include "database.h"
#include <layoutscene.h>


class StuffFinder : public QMainWindow
{
	Q_OBJECT

public:
	StuffFinder(QWidget *parent = 0);
	~StuffFinder();

private:
	Ui::StuffFinderClass ui;
	Database db;
	LayoutScene *scene_;
	std::vector<Layout *> layouts;
	std::vector<QString> contcombo;//holds container name then id ie[container1,conatainer1 id,container2,container2 id]
	std::vector<QString> categorycombo;//holds category name and id


	void OutputItemTree();
	void SetItems(QTreeWidgetItem * room, Container * cont, int level);
	void GraphicViewSwitch();

	QMenu* containerContextMenu;
	QMenu* itemContextMenu;
	QMenu* topLevelContainerMenu;
	QMenu* categoryContextMenu;
	QMenu* nocategoryContextMenu;

	void keyPressEvent(QKeyEvent * e);

private slots:
void AddContainerClicked();
void EditContainerClicked();
void AddItemClicked();
void EditItemClicked();
void DeleteItemClicked();
void AddTopContainerClicked();
void DeleteContainerClicked();
void HandleLayoutChange(int index) { OutputItemTree(); }
void AddCategoryClicked();
void DeleteCategoryClicked();


//These functions remain unedited
public slots:
void on_Search_button_clicked();
void on_Search_returnPressed();
void on_addLayout_clicked();
void onCustomContextMenu(const QPoint &point);
void onCatCustomContextMenu(const QPoint &point);
void SearchResultDoubleClicked(QTreeWidgetItem *item, int col);
void SearchResultRightClicked(const QPoint &point);
void on_expand_button_clicked();
//void onSearchResultContextMenu(const QPoint &point);
void TreeItemClicked(QTreeWidgetItem * item, int column);

};

#endif // STUFFFINDER_H
