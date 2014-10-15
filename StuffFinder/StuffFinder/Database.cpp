#include "Database.h"
#include "qdebug.h"

int Select_callback(void *param, int argc, char **argv, char **azColName);
int Table_callback(void *param, int argc, char **argv, char **azColName);
int Insert_callback(void *param, int argc, char **argv, char **azColName);

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
	Delete_Database();
	qDebug() << "Deleted database";

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
		"ITEM_ID INTEGER PRIMARY KEY," \
		"CONTAINER_ID      INT          NOT NULL," \
		"ITEM_NAME           TEXT         NOT NULL," \
		"ITEM_DESCRIPTION    TEXT," \
		"CATAGORY    TEXT            NOT NULL," \
		"QUANTITY        INT         NOT NULL," \
		"TRACKER         INT );"\

		"CREATE TABLE CONTAINER("  \
		"CONTAINER_ID INTEGER PRIMARY KEY," \
		"CONTAINER_NAME      TEXT         NOT NULL," \
		"CONTAINER_DESCRIPTION    TEXT," \
		"PARENT_CONTAINER_ID INT);"\

		"CREATE TABLE LAYOUT("  \
		"LAYOUT_ID INT PRIMARY KEY     NOT NULL," \
		"LAYOUT_NAME           TEXT         NOT NULL," \
		"LAYOUT_DESCRIPTION    TEXT);";
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

int Database::Create_Item(Item *newItem)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "INSERT INTO ITEM (CONTAINER_ID, CATAGORY, QUANTITY, ITEM_NAME, ITEM_DESCRIPTION) " \
		"VALUES(1,'test_cat',1,'"+ newItem->get_name() + "','" + newItem->get_description() + "');";
	qDebug() << sql.c_str();

	rc = sqlite3_exec(db, sql.c_str(), Insert_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Item wasn't created";
	}
	else
	{
		qDebug() << "Item created successfully";
	}
	qDebug() << "new item id: " << sqlite3_last_insert_rowid(db);
	return sqlite3_last_insert_rowid(db);
}

void Database::Delete_Item(Item* delItem)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;
	
	sql = "DELETE FROM ITEM WHERE ITEM_ID = " + std::to_string(delItem->get_item_id()) + ";";

	qDebug() << sql.c_str();
	rc = sqlite3_exec(db, sql.c_str(), Select_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Item wasn't deleted";
	}
	else
	{
		qDebug() << "Item deleted successfully";
	}

}
void Database::Load_Items(Container * cont)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "SELECT * FROM ITEM WHERE CONTAINER_ID = 1;" /*+ std::to_string(cont->get_container_id())*/;

	rc = sqlite3_exec(db, sql.c_str(), Select_callback, this, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Items werent loaded";
	}
	else
	{
		qDebug() << "Item loaded successfully";
	}
	qDebug() << qry_result.size();
	
	for (int i = 0; i < qry_result.size(); i++)
	{
		for (int j = 0; j < qry_result[i].size(); j++)
		{
			qDebug() << qry_result[i][j].c_str() << " , ";
		}
		
	}

	qry_result.clear();
	return;
}

std::vector <Container *> Database::Load_Containers(Container * cont)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "SELECT * FROM CONTAINER WHERE PARENT_CONTAINER_ID = 0;" /*+ std::to_string(cont->get_container_id())*/;

	rc = sqlite3_exec(db, sql.c_str(), Select_callback, this, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Containers werent loaded";
	}
	else
	{
		qDebug() << "Containers loaded successfully";
	}
	qDebug() << qry_result.size();
	std::vector <Container *> return_containers;
	for (int i = 0; i < qry_result.size(); i++)
	{
		Container * temp = new Container(atoi(qry_result[i][0].c_str()), qry_result[i][1], qry_result[i][2]);
		return_containers.push_back(temp);

	}

	qry_result.clear();
	return return_containers;
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
	// Get current index
	database->qry_result.push_back(std::vector<std::string>());
	int j = database->qry_result.size();
	// Add another row
	
	//qDebug() << "Callback function called" << endl;
	// Loop through columns
	for (i = 0; i<argc; i++){
		//qDebug() << azColName[i] << (argv[i] ? argv[i] : "NULL");
		// Set the column result
		database->qry_result[j-1].push_back(argv[i] ? std::string(argv[i]) : "NULL");
	}
	//qDebug() << endl;
	return 0;
}

int Insert_callback(void *param, int argc, char **argv, char **azColName){
	int i;
	qDebug() << "Insert Callback function called";
	return 0;
}