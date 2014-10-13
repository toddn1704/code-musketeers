#include "Database.h"
#include "qdebug.h"

int Select_callback(void *param, int argc, char **argv, char **azColName);
int Table_callback(void *param, int argc, char **argv, char **azColName);

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
		Create_Database();
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

void Database::Create_Database()
{
	int rc;
	char *sql;
	char *zErrMsg = 0;

	/* Create SQL Table String
	   This is just a test item table
	*/
	sql = "CREATE TABLE ITEM("  \
		"ITEM_ID INT PRIMARY KEY     NOT NULL," \
		"CONTAINER      INT          NOT NULL," \
		"NAME           TEXT         NOT NULL," \
		"DESCRIPTION    TEXT," \
		"CATAGORY    TEXT            NOT NULL," \
		"QUANTITY        INT         NOT NULL," \
		"TRACKER         INT );";
	qDebug() << sql;
	rc = sqlite3_exec(db, sql, Table_callback, 0,&zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Table wasn't created";
		//sqlite3_free(zErrMsg);
	}
	else
	{
		//fprintf(stdout, "Table created successfully\n");
		qDebug() << "Table created successfully";
	}
}

int Table_callback(void *param, int argc, char **argv, char **azColName){
	int i;
	qDebug() << "Table callback function called";
	// Loop through columns
	for (i = 0; i < argc; i++){
		qDebug() << azColName[i] << (argv[i] ? argv[i] : "NULL");
	}
	return 0;
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