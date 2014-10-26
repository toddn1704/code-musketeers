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

	void Output_item_tree();
	void setItems(QTreeWidgetItem * room, Container * cont, int level);

	QMenu* containerContextMenu;
	QMenu* itemContextMenu;

private slots:
void addContainerClicked();
void addItemClicked();
void editItemClicked();

public slots:
void on_Search_button_clicked();
void on_search_returnPressed();
void on_Add_save_clicked();
void on_Add_cancel_clicked();
void onCustomContextMenu(const QPoint &point);


};

#endif // STUFFFINDER_H
