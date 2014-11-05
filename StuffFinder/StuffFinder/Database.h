/*Database.h

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
#include "Item.h"
#include "Container.h"
#include "Layout.h"
#include "Category.h"

class Database
{
	public:
		Database();
		~Database();
		void Create_Item(Item* newItem, int parent_id, int category);
		void Delete_Item(Item* delItem);
		void Delete_Item(std::string name);
		void Create_Container(Container* new_cont, int parent_id, bool top);
		void Delete_Container(int id) { Delete_Container(Load_Container(id)); }
		void Delete_Container(Container* del_cont);
		void Create_Layout(Layout* new_layout);
		void Delete_Layout(Layout* del_layout);
		void Create_Category(Category* new_cat);
		void Delete_Category(int id);

		void Update_Item(Item* up_item);
		void UpdateContainer(Container* container, int parent_id);

		void Load_Items(Container * cont);
		void Load_Items(Category * categ);
		void Load_Containers(Container * cont);

		void Load_Layout_Containers(Layout * lay);
		std::vector<Category*> Load_Categories();
		std::vector<Layout*> Load_Layouts();

		// Two dimensional vector to store latest query results
		// Not sure this is the best way to do this
		std::vector<std::vector<std::string>> qry_result;
	private:
		void Create_Database();	// Creates Tables for Database
		void Delete_Database(){ remove("test2.db"); };

		Container* Load_Container(int id);
		sqlite3 *db;
};

#endif