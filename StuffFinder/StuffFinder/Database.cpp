#include "Database.h"
#include "qdebug.h"

int Select_callback(void *param, int argc, char **argv, char **azColName);

Database::Database()
{
	char *zErrMsg = 0;
	int rc;

	// Open database and check if successful
	rc = sqlite3_open("test2.db", &db);

	if (rc)
	{
		qDebug() << "Can't open database";
	}
	else
	{
		qDebug() << "Opened database successfully.";
	}

	// Check if databse is empty
	char * sql = "SELECT COUNT(*) from sqlite_master where type = \"table\";";
	const char* data = 0;

	// Initiate vector to size of one
	qry_result.push_back(std::vector<std::string>());
	// Use sqlite3_exec might be better to use prepare/step/finalize
	// so we don't have to deal with callbacks
	rc = sqlite3_exec(db, sql, Select_callback, this, &zErrMsg);
	
	// If database is empty create tables
	if (qry_result[0][0] == "0")
	{
		qDebug() << "Database is empty";
	}


	// Else do nothing
	else
	{
		qDebug() << "Database has something in it";
	}

	qry_result.clear();
}

Database::~Database()
{
	sqlite3_close(db);
	qDebug() << "Closed database successfully.";

}

// Callback function puts the results in the qry_result of the class passed to param argument
int Select_callback(void *param, int argc, char **argv, char **azColName){
	// Get the database object
	Database* database = reinterpret_cast<Database*>(param);
	int i;
	qDebug() << "Callback function called";
	// Loop through columns
	for (i = 0; i<argc; i++){
		qDebug() << azColName[i] << (argv[i] ? argv[i] : "NULL");
		// Set the column result
		database->qry_result[i].push_back(std::string(argv[i]));
	}
	qDebug() << endl;
	return 0;
}