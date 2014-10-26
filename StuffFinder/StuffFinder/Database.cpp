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
	//Delete_Database();
	//qDebug() << "Deleted database";

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
		"CATEGORY    TEXT            NOT NULL," \
		"QUANTITY        INT         NOT NULL," \
		"TRACKER         INT );"\

		"CREATE TABLE CONTAINER("  \
		"CONTAINER_ID INTEGER PRIMARY KEY," \
		"CONTAINER_NAME      TEXT         NOT NULL," \
		"CONTAINER_DESCRIPTION    TEXT," \
		"PARENT_CONTAINER_ID INT,"
		"PARENT_LAYOUT_ID INT);"\

		"CREATE TABLE LAYOUT("  \
		"LAYOUT_ID INTEGER PRIMARY KEY     NOT NULL," \
		"LAYOUT_NAME           TEXT         NOT NULL," \
		"LAYOUT_DESCRIPTION    TEXT);" \

		"CREATE TABLE CATEGORY("  \
		"CATEGORY_ID INTEGER PRIMARY KEY     NOT NULL," \
		"CATEGORY_NAME           TEXT         NOT NULL," \
		"CATEGORY_DESCRIPTION    TEXT);";
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

void Database::Create_Item(Item *newItem, int parent_id)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "INSERT INTO ITEM (CONTAINER_ID, CATEGORY, QUANTITY, ITEM_NAME, ITEM_DESCRIPTION) " \
		"VALUES(" + std::to_string(parent_id) + ",'" +
		newItem ->get_category() +"'," + std::to_string(newItem->get_quantity()) + ",'" + 
		newItem->get_name() + "','" + newItem->get_description() + "');";
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
	newItem->set_item_id(sqlite3_last_insert_rowid(db));
	//return sqlite3_last_insert_rowid(db);
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
void Database::Update_Item(Item* up_item)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "UPDATE ITEM SET ITEM_NAME = '" + up_item->get_name() + "', ITEM_DESCRIPTION ='" +
		up_item->get_description() + "', CATEGORY = '" + up_item->get_category() + "', QUANTITY = " +
		std::to_string(up_item->get_quantity()) + " WHERE ITEM_ID = " + std::to_string(up_item->get_item_id()) +
		";";
	qDebug() << sql.c_str();

	rc = sqlite3_exec(db, sql.c_str(), Insert_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Item wasn't updated";
	}
	else
	{
		qDebug() << "Item updated successfully";
	}
}
void Database::Create_Container(Container* new_cont, int parent_id, bool top)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;
	// If it's a top level container use layout id
	if (top)
	{
		sql = "INSERT INTO CONTAINER (CONTAINER_NAME, CONTAINER_DESCRIPTION, PARENT_LAYOUT_ID) " \
			"VALUES('" + new_cont->get_name() + "','" + new_cont->get_description() + "'," + std::to_string(parent_id) + ");";
	}
	// If its a normal container use container id
	else
	{
		sql = "INSERT INTO CONTAINER (CONTAINER_NAME, CONTAINER_DESCRIPTION, PARENT_CONTAINER_ID) " \
			"VALUES('" + new_cont->get_name() + "','" + new_cont->get_description() + "'," + std::to_string(parent_id) + ");";
	}
	qDebug() << sql.c_str();

	rc = sqlite3_exec(db, sql.c_str(), Insert_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Container wasn't created";
	}
	else
	{
		qDebug() << "Container created successfully";
	}
	qDebug() << "new container id: " << sqlite3_last_insert_rowid(db);
	new_cont->set_container_id(sqlite3_last_insert_rowid(db));
}

void Database::Delete_Container(Container* del_cont)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	std::vector<Container *> sub_containers = del_cont->get_container();
	for (int i = 0; i < sub_containers.size(); i++)
	{
		Delete_Container(sub_containers[i]);
	}
	std::vector<Item *> items = del_cont->get_items();
	for (int j = 0; j < items.size(); j++)
	{
		Delete_Item(items[j]);
	}
	sql = "DELETE FROM CONTAINER WHERE CONTAINER_ID = " + std::to_string(del_cont->get_container_id()) + ";";

	qDebug() << sql.c_str();
	rc = sqlite3_exec(db, sql.c_str(), Select_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Container wasn't deleted";
	}
	else
	{
		qDebug() << "Container deleted successfully";
	}

}
void Database::Create_Layout(Layout* new_layout)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "INSERT INTO LAYOUT (LAYOUT_NAME, LAYOUT_DESCRIPTION) " \
		"VALUES('" + new_layout->get_name() + "','" + new_layout->get_description() +  "');";
	qDebug() << sql.c_str();

	rc = sqlite3_exec(db, sql.c_str(), Insert_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Layout wasn't created";
	}
	else
	{
		qDebug() << "Layout created successfully";
	}
	qDebug() << "new layout id: " << sqlite3_last_insert_rowid(db);
	new_layout->set_layout_id(sqlite3_last_insert_rowid(db));
}
void Database::Delete_Layout(Layout* del_layout)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;
	std::vector<Container*> rooms = del_layout->get_rooms();
	for (int i = 0; i < rooms.size(); i++)
	{
		Delete_Container(rooms[i]);
	}
	sql = "DELETE FROM LAYOUT WHERE LAYOUT_ID = " + std::to_string(del_layout->get_layout_id()) + ";";

	qDebug() << sql.c_str();
	rc = sqlite3_exec(db, sql.c_str(), Select_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Container wasn't deleted";
	}
	else
	{
		qDebug() << "Container deleted successfully";
	}
}

void Database::Create_Category(Category* new_cat)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "INSERT INTO CATEGORY (CATEGORY_NAME, CATEGORY_DESCRIPTION) " \
		"VALUES('" +	new_cat->get_name() + "','" + new_cat->get_description() + "');";
	qDebug() << sql.c_str();

	rc = sqlite3_exec(db, sql.c_str(), Insert_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Category wasn't created";
	}
	else
	{
		qDebug() << "Category created successfully";
	}
	qDebug() << "new category id: " << sqlite3_last_insert_rowid(db);
	new_cat->set_category_id(sqlite3_last_insert_rowid(db));
}

void Database::Load_Items(Container * cont)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "SELECT * FROM ITEM WHERE CONTAINER_ID = " + std::to_string(cont->get_container_id()) + ";";

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
	std::vector<std::vector<std::string>> c_qry_result = qry_result;
	qry_result.clear();
	for (int i = 0; i < c_qry_result.size(); i++)
	{
		Item * temp_item = new Item(c_qry_result[i][2], c_qry_result[i][3], atoi(c_qry_result[i][5].c_str()), c_qry_result[i][4]);
		temp_item->set_item_id(atoi(c_qry_result[i][0].c_str()));
		cont->add_item(temp_item);
	}
	return;
}

void Database::Load_Containers(Container * cont)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "SELECT * FROM CONTAINER WHERE PARENT_CONTAINER_ID = " + std::to_string(cont->get_container_id()) + ";";

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
	std::vector<std::vector<std::string>> c_qry_result = qry_result;
	qry_result.clear();
	for (int i = 0; i < c_qry_result.size(); i++)
	{
		Container * temp = new Container(atoi(c_qry_result[i][0].c_str()), c_qry_result[i][1], c_qry_result[i][2]);
		Load_Containers(temp);
		Load_Items(temp);
		cont->add_container(temp);

	}

}

Container* Database::Load_Container(int id)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "SELECT * FROM CONTAINER WHERE CONTAINER_ID = " + std::to_string(id) + ";";

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
	std::vector<std::vector<std::string>> c_qry_result = qry_result;
	qry_result.clear();
	Container * temp = new Container(atoi(c_qry_result[0][0].c_str()), c_qry_result[0][1], c_qry_result[0][2]);
	Load_Containers(temp);
	Load_Items(temp);
	return temp;
}

void Database::Load_Layout_Containers(Layout * lay)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "SELECT * FROM CONTAINER WHERE PARENT_LAYOUT_ID = " + std::to_string(lay->get_layout_id()) + ";";

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
	std::vector<std::vector<std::string>> c_qry_result = qry_result;
	qry_result.clear();
	for (int i = 0; i < c_qry_result.size(); i++)
	{
		Container * temp = new Container(atoi(c_qry_result[i][0].c_str()), c_qry_result[i][1], c_qry_result[i][2]);
		Load_Containers(temp);
		Load_Items(temp);
		lay->add_room(temp);

	}

}

std::vector<Layout*> Database::Load_Layouts()
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "SELECT * FROM LAYOUT;";

	rc = sqlite3_exec(db, sql.c_str(), Select_callback, this, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Layouts werent loaded";
	}
	else
	{
		qDebug() << "Layouts loaded successfully";
	}
	qDebug() << qry_result.size();
	std::vector <Layout *> return_layouts;
	std::vector<std::vector<std::string>> c_qry_result = qry_result;
	qry_result.clear();
	for (int i = 0; i < c_qry_result.size(); i++)
	{
		Layout * temp = new Layout(atoi(c_qry_result[i][0].c_str()), c_qry_result[i][1], c_qry_result[i][2]);
		Load_Layout_Containers(temp);
		return_layouts.push_back(temp);

	}

	return return_layouts;
}

std::vector<Category*> Database::Load_Categories()
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "SELECT * FROM CATEGORY;";

	rc = sqlite3_exec(db, sql.c_str(), Select_callback, this, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Categories werent loaded";
	}
	else
	{
		qDebug() << "Categories loaded successfully";
	}
	qDebug() << qry_result.size();
	std::vector <Category *> return_Categories;
	std::vector<std::vector<std::string>> c_qry_result = qry_result;
	qry_result.clear();
	for (int i = 0; i < c_qry_result.size(); i++)
	{
		Category * temp = new Category(atoi(c_qry_result[i][0].c_str()), c_qry_result[i][1], c_qry_result[i][2]);
		return_Categories.push_back(temp);
	}

	return return_Categories;
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