#ifndef DATABASE_H
#define DATABASE_H
#include "sqlite3.h"
#include <vector>
#include <string>
#include <stdio.h>
#include "Item.h"

class Database
{
	public:
		Database();
		~Database();
		int Create_Item(Item* newItem);
		void Delete_Item(Item* delItem);
		//Create_Container();
		//Delete_Container();
		//Create_Layout();
		//Delete_Layout();


		// Two dimensional vector to store latest query results
		// Not sure this is the best way to do this
		std::vector<std::vector<std::string>> qry_result;
	private:
		void Create_Database();	// Creates Tables for Database
		void Delete_Database(){ remove("test2.db"); };

		sqlite3 *db;
		
};

#endif