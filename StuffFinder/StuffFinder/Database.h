#ifndef DATABASE_H
#define DATABASE_H
#include "sqlite3.h"
#include <vector>
#include <string>

class Database
{
	public:
		Database();
		~Database();

		// Two dimensional vector to store latest query results
		// Not sure this is the best way to do this
		std::vector<std::vector<std::string>> qry_result;
	private:
		void Create_Database();	// Creates Tables for Database
		sqlite3 *db;
		
};

#endif