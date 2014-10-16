#ifndef DATABASE_H
#define DATABASE_H
#include "sqlite3.h"
#include <vector>
#include <string>
#include <stdio.h>
#include "Item.h"
#include "Container.h"
#include "Layout.h"

class Database
{
	public:
		Database();
		~Database();
		void Create_Item(Item* newItem);
		void Delete_Item(Item* delItem);
		void Create_Container(Container* new_cont, int parent_id);
		void Delete_Container(Container* del_cont);
		void Create_Layout(Layout* new_layout);
		void Delete_Layout(Layout* del_layout);
		
		void Load_Items(Container * cont);
		void Load_Containers(Container * cont);
		void Load_Layout_Containers(Layout * lay);
		std::vector<Layout*> Load_Layouts();

		// Two dimensional vector to store latest query results
		// Not sure this is the best way to do this
		std::vector<std::vector<std::string>> qry_result;
	private:
		void Create_Database();	// Creates Tables for Database
		void Delete_Database(){ remove("test2.db"); };

		sqlite3 *db;
		
};

#endif