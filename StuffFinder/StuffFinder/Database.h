/*database.h

This file contains the Database class, which is responsible 
for creating and deleting the database; and creating, editing,
and deleting items, containers, layouts, and categories.

*/

#ifndef DATABASE_H
#define DATABASE_H
#include "sqlite3.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <ctime>
#include "item.h"
#include "container.h"
#include "layout.h"
#include "category.h"
#include "qvector.h"

class Database
{
	public:
		Database();
		~Database();
		void CreateItem(Item* newItem, int parent_id, int category);
		void DeleteItem(Item* delItem);
		void DeleteItem(std::string name);
		void CreateContainer(Container* new_cont, int parent_id, bool top);
		void DeleteContainer(int id) { DeleteContainer(LoadContainer(id)); }
		void DeleteContainer(Container* del_cont);
		void CreateLayout(Layout* new_layout);
		void DeleteLayout(Layout* del_layout);
		void CreateCategory(Category* new_cat);
		void DeleteCategory(int id, std::string del_cat);

		void UpdateItem(Item* up_item);
		void UpdateContainer(Container* container, int parent_id);
		void UpdateChangeLog(std::string change);

		void LoadItems(Container * cont);
		void LoadItems(Category * categ);
		void LoadContainers(Container * cont);

		void LoadLayoutContainers(Layout * lay);
		std::vector<Category*> LoadCategories();
		std::vector<Layout*> LoadLayouts();

		void InsertCoords(int container_id, QVector<QPointF> points);
		QVector<QPointF> LoadCoords(int container_id);
		void DeleteCoords(int container_id);


		// Two dimensional vector to store latest query results
		// Not sure this is the best way to do this
		std::vector<std::vector<std::string>> qry_result;
private:
	void CreateDatabase();	// Creates Tables for Database
	void DeleteDatabase(){ remove("test2.db"); };

	Container* LoadContainer(int id);
	sqlite3 *db;
};

#endif

