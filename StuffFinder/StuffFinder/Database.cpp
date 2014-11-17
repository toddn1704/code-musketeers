/*database.cpp

This file will implement the functions declared in the
database.h file.

*/

#include "database.h"
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
		CreateDatabase();
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
	//DeleteDatabase();
	//qDebug() << "Deleted database";

}

void Database::CreateDatabase()
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
		"CATEGORY_ID    INT            NOT NULL," \
		"QUANTITY        INT         NOT NULL," \
		"MIN_QUANTITY        INT     NOT NULL," \
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
		"CATEGORY_DESCRIPTION    TEXT);"

		"CREATE TABLE CHANGELOG("  \
		"ID INTEGER PRIMARY KEY     NOT NULL," \
		"Year            INT         NOT NULL," \
		"Month           INT         NOT NULL," \
		"Day             INT         NOT NULL," \
		"CHANGE_DESCRIPTION    TEXT);" \

		"CREATE TABLE COORDS(" \
		"ID INTEGER PRIMARY KEY NOT NULL," \
		"CONTAINER_ID    INT NOT NULL," \
		"xval            INT NOT NULL," \
		"yval            INT NOT NULL);";
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

void Database::CreateItem(Item *new_item, int parent_id, int category)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;
	int track = 0;
	if (new_item->get_track() == true)
	{
		track = 1;
	}
	sql = "INSERT INTO ITEM (CONTAINER_ID, CATEGORY_ID, QUANTITY, ITEM_NAME, ITEM_DESCRIPTION,TRACKER,MIN_QUANTITY) " \
		"VALUES(" + std::to_string(parent_id) + "," +
		std::to_string(category) +"," + std::to_string(new_item->get_quantity()) + ",'" + 
		new_item->get_name() + "','" + new_item->get_description() + "',"+ std::to_string(track) + "," + std::to_string(new_item->get_min_quantity()) + ");";
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
	new_item->set_item_id(sqlite3_last_insert_rowid(db));
	//return sqlite3_last_insert_rowid(db);

	UpdateChangeLog("Created Item: " + new_item->get_name());
}

void Database::DeleteItem(Item* del_item)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;
	
	sql = "DELETE FROM ITEM WHERE ITEM_ID = " + std::to_string(del_item->get_item_id()) + ";";

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

	UpdateChangeLog("Deleted Item: " + del_item->get_name());
}

void Database::DeleteItem(std::string name)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "DELETE FROM ITEM WHERE ITEM_NAME = '" + name + "';";

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

	UpdateChangeLog("Deleted Item: " + name);
}
void Database::UpdateItem(Item* up_item)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;
	int track = 0;
	if (up_item->get_track() == true)
	{
		track = 1;
	}
	sql = "UPDATE ITEM SET ITEM_NAME = '" + up_item->get_name() + "', ITEM_DESCRIPTION ='" +
		up_item->get_description() + "', CATEGORY_ID = " + std::to_string(up_item->get_category()) + ", QUANTITY = " +
		std::to_string(up_item->get_quantity()) + ", CONTAINER_ID = " + std::to_string(up_item->get_container_id()) + 
		", TRACKER = " + std::to_string(track) + ", MIN_QUANTITY = " + std::to_string(up_item->get_min_quantity()) + " WHERE ITEM_ID = " +
		std::to_string(up_item->get_item_id()) + ";";
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

	UpdateChangeLog("Updated Item: " + up_item->get_name());
}
void Database::UpdateContainer(Container* container,int parent_id)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "UPDATE CONTAINER SET CONTAINER_NAME = '" + container->get_name() + "', CONTAINER_DESCRIPTION ='" +
		container->get_description() + "', PARENT_CONTAINER_ID = " + std::to_string(parent_id) + " WHERE CONTAINER_ID = " + std::to_string(container->get_container_id()) +
		";";
	qDebug() << sql.c_str();

	rc = sqlite3_exec(db, sql.c_str(), Insert_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Container wasn't updated";
	}
	else
	{
		qDebug() << "Container updated successfully";
	}

	UpdateChangeLog("Updated Container: " + container->get_name());
}
void Database::CreateContainer(Container* new_cont, int parent_id, bool top)
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

	UpdateChangeLog("Created Container: " + new_cont->get_name());
}

void Database::DeleteContainer(Container* del_cont)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	DeleteCoords(del_cont->get_container_id());
	std::vector<Container *> sub_containers = del_cont->get_container();
	for (int i = 0; i < sub_containers.size(); i++)
	{
		DeleteContainer(sub_containers[i]);
	}
	std::vector<Item *> items = del_cont->get_items();
	for (int j = 0; j < items.size(); j++)
	{
		DeleteItem(items[j]);
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

	UpdateChangeLog("Deleted Container: " + del_cont->get_name());
}
void Database::CreateLayout(Layout* new_layout)
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

	UpdateChangeLog("Created Layout: " + new_layout->get_name());
}
void Database::DeleteLayout(Layout* del_layout)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;
	std::vector<Container*> rooms = del_layout->get_rooms();
	for (int i = 0; i < rooms.size(); i++)
	{
		DeleteContainer(rooms[i]);
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

	UpdateChangeLog("Deleted Layout: " + del_layout->get_name());
}

void Database::CreateCategory(Category* new_cat)
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

	UpdateChangeLog("Category Created: " + new_cat->get_name());
}

void Database::DeleteCategory(int id, std::string del_cat)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "DELETE FROM CATEGORY WHERE CATEGORY_NAME = " + del_cat + ";";

	qDebug() << sql.c_str();
	rc = sqlite3_exec(db, sql.c_str(), Select_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Category wasn't deleted";
	}
	else
	{
		qDebug() << "Category deleted successfully";
	}

	UpdateChangeLog("Category Deleted: " + del_cat);
}

void Database::CreateItemData(int id) 
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "CREATE TABLE ITEMDATA" + std::to_string(id) + "("  \
		"ITEM_ID INTEGER PRIMARY KEY," \
		"YEAR      INT     NOT NULL," \
		"MONTH     INT     NOT NULL," \
		"DAY       INT     NOT NULL," \
		"AMOUNT    INT     NOT NULL);";

	qDebug() << sql.c_str();
	rc = sqlite3_exec(db, sql.c_str(), Select_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Item Data wasn't Created";
	}
	else
	{
		qDebug() << "Item Data was created successfully";
	}
}

void Database::DeleteItemData(int id)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "DROP TABLE ITEMDATA" + std::to_string(id);

	qDebug() << sql.c_str();
	rc = sqlite3_exec(db, sql.c_str(), Select_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: ITEMDATA wasn't deleted";
	}
	else
	{
		qDebug() << "ITEMDATA deleted successfully";
	}
}

void Database::UpdateChangeLog(std::string change) 
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;
	
	time_t t = time(0);
	struct tm *now = localtime(&t);
	sql = "INSERT INTO CHANGELOG(YEAR, MONTH, DAY, DESCRIPTION) " \
		"VALUES(" + std::to_string(now->tm_year + 1900) + "," + std::to_string(now->tm_mon + 1) + "," + std::to_string(now->tm_mday) +
		",'" + change + "');";
	rc = sqlite3_exec(db, sql.c_str(), Insert_callback, 0, &zErrMsg);
}

void Database::UpdateItemData(int id, int amount) 
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	time_t t = time(0);
	struct tm *now = localtime(&t);
	sql = "INSERT INTO ITEMDATA" + std::to_string(id) + "(YEAR, MONTH, DAY, AMOUNT) " \
		"VALUES(" + std::to_string(now->tm_year + 1900) + "," + std::to_string(now->tm_mon + 1) + "," + std::to_string(now->tm_mday) +
		"," + std::to_string(amount) + ");";
	rc = sqlite3_exec(db, sql.c_str(), Insert_callback, 0, &zErrMsg);
}

std::vector<std::string> Database::GenerateShoppingList()
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "SELECT * FROM ITEM WHERE TRACKER = 1;";
	rc = sqlite3_exec(db, sql.c_str(), Insert_callback, 0, &zErrMsg);

	std::vector<int> item_ids;
	std::vector<int> item_surplus;
	std::vector<std::string> item_names;
	for (int i = 0; i < qry_result.size(); i++)
	{
		item_ids.push_back(atoi(qry_result[i][0].c_str()));
		item_surplus.push_back(atoi(qry_result[i][5].c_str()) - atoi(qry_result[i][6].c_str()));
		item_names.push_back(qry_result[i][2].c_str());
	}
	qry_result.clear();
	
	std::vector<std::string> shopping_list;
	for (int x = 0; x < item_ids.size(); x++)
	{
		sql = "SELECT * FROM ITEMDATA" + std::to_string(item_ids[x]) + ";";
		//TODO: turn data into points(include in database?)
		//apply best fit algorithm
		//check if slope > surplus

		qry_result.clear();
	}
}

void Database::LoadItems(Container * cont)
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
		Item * temp_item = new Item(c_qry_result[i][2], c_qry_result[i][3], atoi(c_qry_result[i][5].c_str()), atoi(c_qry_result[i][4].c_str()));
		temp_item->set_item_id(atoi(c_qry_result[i][0].c_str()));
		temp_item->set_container_id(atoi(c_qry_result[i][1].c_str()));
		temp_item->set_min_quantity(atoi(c_qry_result[i][6].c_str()));
		int tracker = atoi(c_qry_result[i][7].c_str());
		if (tracker == 1)
		{
			temp_item->set_track(true);
		}
		else
		{
			temp_item->set_track(false);
		}
		//cont->AddItem(temp_item);
		cont->AddItem(temp_item);
	}
	return;
}

void Database::LoadItems(Category * categ)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "SELECT * FROM ITEM WHERE CATEGORY_ID = " + std::to_string(categ->get_category_id()) + ";";

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
		Item * temp_item = new Item(c_qry_result[i][2], c_qry_result[i][3], atoi(c_qry_result[i][5].c_str()), atoi(c_qry_result[i][4].c_str()));
		temp_item->set_item_id(atoi(c_qry_result[i][0].c_str()));
		temp_item->set_container_id(atoi(c_qry_result[i][1].c_str()));
		temp_item->set_min_quantity(atoi(c_qry_result[i][6].c_str()));
		int tracker = atoi(c_qry_result[i][7].c_str());
		if (tracker == 1)
		{
			temp_item->set_track(true);
		}
		else
		{
			temp_item->set_track(false);
		}
		categ->AddItem(temp_item);
	}
	return;
}

void Database::LoadContainers(Container * cont)
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
		LoadContainers(temp);
		LoadItems(temp);
		//cont->AddContainer(temp);
		cont->AddContainer(temp);

	}

}

Container* Database::LoadContainer(int id)
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
	LoadContainers(temp);
	LoadItems(temp);
	return temp;
}
void Database::LoadLayoutContainers(Layout * lay)
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
		LoadContainers(temp);
		LoadItems(temp);
		lay->AddRoom(temp);

	}

}

std::vector<Layout*> Database::LoadLayouts()
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
		LoadLayoutContainers(temp);
		return_layouts.push_back(temp);

	}

	return return_layouts;
}

std::vector<Category*> Database::LoadCategories()
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
		LoadItems(temp);
		return_Categories.push_back(temp);
	}

	return return_Categories;
}

void Database::InsertCoords(int container_id, QVector<QPointF> points)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	for (int i = 0; i < points.size(); i++)
	{
		sql.append("INSERT INTO COORDS (CONTAINER_ID, xval, yval) VALUES ("
			+ std::to_string(container_id) + "," + std::to_string(points[i].x()) +
			"," + std::to_string(points[i].y()) + ");");
	}
	qDebug() << sql.c_str();

	rc = sqlite3_exec(db, sql.c_str(), Insert_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Coords wasn't inserted";
	}
	else
	{
		qDebug() << "Coords inserted successfully";
	}
}

QVector<QPointF> Database::LoadCoords(int container_id)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "SELECT * FROM COORDS WHERE CONTAINER_ID = " + std::to_string(container_id) + ";";

	rc = sqlite3_exec(db, sql.c_str(), Select_callback, this, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Coords werent loaded";
	}
	else
	{
		qDebug() << "Coords loaded successfully";
	}
	qDebug() << qry_result.size();
	QVector<QPointF> points;
	std::vector<std::vector<std::string>> c_qry_result = qry_result;
	qry_result.clear();
	for (int i = 0; i < c_qry_result.size(); i++)
	{
		Category * temp = new Category(atoi(c_qry_result[i][0].c_str()), c_qry_result[i][1], c_qry_result[i][2]);
		LoadItems(temp);
		points.push_back(QPointF(atof(c_qry_result[i][2].c_str()), atof(c_qry_result[i][3].c_str())));
	}

	return points;
}

void Database::DeleteCoords(int container_id)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "DELETE FROM COORDS WHERE CONTAINER_ID = " + std::to_string(container_id) + ";";

	qDebug() << sql.c_str();
	rc = sqlite3_exec(db, sql.c_str(), Select_callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		qDebug() << "SQL error: Coords wasn't deleted";
	}
	else
	{
		qDebug() << "Coords deleted successfully";
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