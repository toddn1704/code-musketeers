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
	std::string db_file_path = SetupStufffinderFolder();
	// Open database and check if successful
	rc = sqlite3_open(db_file_path.c_str(), &db);

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
		"DATE                  TEXT," \
		"TIME                  TEXT," \
		"OBJECT_NAME           TEXT," \
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
	qry_result.clear();
	//return sqlite3_last_insert_rowid(db);
	if (new_item->get_track())
	{
		CreateItemData(new_item->get_item_id());
	}

	UpdateChangeLog(new_item->get_name(),"Created Item");
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
	qry_result.clear();
	UpdateChangeLog(del_item->get_name(),"Deleted Item");
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
	qry_result.clear();
	UpdateChangeLog(name,"Deleted Item");
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
	//gets the old data from the database and compares to the new ones
	//sees if quanity or track tag has changed
	sql = "SELECT * FROM ITEM WHERE ITEM_ID = " + std::to_string(up_item->get_item_id()) + ";";
	rc = sqlite3_exec(db, sql.c_str(), Select_callback, this, &zErrMsg);
	std::vector<std::vector<std::string>> old_data = qry_result;
	qry_result.clear();
	if ((old_data[0][7] == "1") && (atoi(old_data[0][5].c_str()) > up_item->get_quantity()))
	{
		UpdateItemData(up_item->get_item_id(), atoi(old_data[0][5].c_str()) - up_item->get_quantity());
	}
	if (atoi(old_data[0][7].c_str()) != track)
	{
		if (up_item->get_track())
		{
			CreateItemData(up_item->get_item_id());
		}
		else
		{
			DeleteItemData(up_item->get_item_id());
		}
	}
	qry_result.clear();
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
	qry_result.clear();
	UpdateChangeLog(up_item->get_name(),"Updated Item");
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
	qry_result.clear();
	UpdateChangeLog(container->get_name(),"Updated Container");
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
	qry_result.clear();
	UpdateChangeLog(new_cont->get_name(),"Created Container");
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
	qry_result.clear();
	UpdateChangeLog(del_cont->get_name(),"Deleted Container");
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
	qry_result.clear();
	UpdateChangeLog(new_layout->get_name(),"Created Layout:");
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
	qry_result.clear();
	UpdateChangeLog(del_layout->get_name(),"Deleted Layout");
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
	qry_result.clear();
	UpdateChangeLog(new_cat->get_name(),"Category Created");
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
	qry_result.clear();
	UpdateChangeLog(del_cat, "Category Deleted");
}

void Database::CreateItemData(int id) 
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;
	//table name includes item id
	sql = "CREATE TABLE ITEMDATA" + std::to_string(id) + "("  \
		"ITEM_ID INTEGER PRIMARY KEY," \
		"YEAR      INT     NOT NULL," \
		"MONTH     INT     NOT NULL," \
		"DAY       INT     NOT NULL," \
		"AMOUNT    INT     NOT NULL," \
		"TIME      INT     NOT NULL);";

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
	qry_result.clear();
	time_t now_time = time(0);
	struct tm *now = localtime(&now_time);
	//first point (0,0)
	sql = "INSERT INTO ITEMDATA" + std::to_string(id) + "(YEAR, MONTH, DAY, AMOUNT, TIME) " \
		"VALUES(" + std::to_string(now->tm_year + 1900) + "," + std::to_string(now->tm_mon + 1) + "," + std::to_string(now->tm_mday) +
		",0,0);";
	rc = sqlite3_exec(db, sql.c_str(), Insert_callback, 0, &zErrMsg);
	qry_result.clear();
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
	qry_result.clear();
}

void Database::UpdateChangeLog(std::string name,std::string change) 
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;
	
	time_t t = time(0);
	struct tm *now = localtime(&t);
	std::string date;
	std::string time;
	//format date MM/DD/YYYY
	if (now->tm_mon < 9)
	{
		date = "0";
	}
	date += std::to_string(now->tm_mon + 1) + "/";
	if (now->tm_mday < 10)
	{
		date += "0";
	}
	date += std::to_string(now->tm_mday) + "/" + std::to_string(now->tm_year + 1900);
	//format time HH:MM:SS
	if (now->tm_hour < 10)
	{
		time = "0";
	}
	time += std::to_string(now->tm_hour) + ":";
	if (now->tm_min < 10)
	{
		time += "0";
	}
	time += std::to_string(now->tm_min) + ":";
	if (now->tm_sec < 10)
	{
		time += "0";
	}
	time += std::to_string(now->tm_sec);
	//format name to be of size 15(assumes name is less than 16 characters normally)
	if (name.size() < 15)
	{
		for (int x = name.size(); x < 15; x++)
		{
			name += " ";
		}
	}

	sql = "INSERT INTO CHANGELOG(DATE,TIME,OBJECT_NAME,CHANGE_DESCRIPTION) " \
		"VALUES('" + date + "','" + time + "','" + name + "','" + change + "');";
	rc = sqlite3_exec(db, sql.c_str(), Insert_callback, 0, &zErrMsg);
	qry_result.clear();
}

void Database::UpdateItemData(int id, int amount) 
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "SELECT * FROM ITEMDATA" + std::to_string(id) + " LIMIT 1;";
	rc = sqlite3_exec(db, sql.c_str(), Select_callback, this, &zErrMsg);
	int old_time = atoi(qry_result[0][5].c_str());
	//calculate date difference to determine the new time since the beginning
	time_t now_time = time(0);
	struct tm *before = new tm;
	before->tm_year = atoi(qry_result[0][1].c_str()) - 1900;
	before->tm_mon = atoi(qry_result[0][2].c_str()) - 1;
	before->tm_mday = atoi(qry_result[0][3].c_str());
	qry_result.clear();

	
	struct tm *now = localtime(&now_time);
	now->tm_hour = 0;
	now->tm_min = 0;
	now->tm_sec = 0;
	int x_diff = (int)(difftime(mktime(now), mktime(before))/(60*60*24));
	sql = "INSERT INTO ITEMDATA" + std::to_string(id) + "(YEAR, MONTH, DAY, AMOUNT, TIME) " \
		"VALUES(" + std::to_string(now->tm_year + 1900) + "," + std::to_string(now->tm_mon + 1) + "," + std::to_string(now->tm_mday) +
		"," + std::to_string(amount) + "," + std::to_string(x_diff + old_time) + ");";
	rc = sqlite3_exec(db, sql.c_str(), Insert_callback, 0, &zErrMsg);
	qry_result.clear();
}

std::vector<std::string> Database::GenerateShoppingList(int days_until_next_shopping_trip)
{
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "SELECT * FROM ITEM WHERE TRACKER = 1;";
	rc = sqlite3_exec(db, sql.c_str(), Select_callback, this, &zErrMsg);

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
	//for each item that has a track tag, check to see if they need to be put on the shopping list
	std::vector<std::string> shopping_list;
	for (int x = 0; x < item_ids.size(); x++)
	{
		std::vector<std::pair<int, int>> data;
		sql = "SELECT * FROM ITEMDATA" + std::to_string(item_ids[x]) + ";";
		rc = sqlite3_exec(db, sql.c_str(), Select_callback, this, &zErrMsg);
		//turn data into points
		int x_point = 0;
		int y_point = 0;
		for (int y = 0; y < qry_result.size(); y++)
		{
			if (atoi(qry_result[y][5].c_str()) != x_point)
			{
				data.push_back(std::make_pair(x_point,y_point));

			}
			x_point = atoi(qry_result[y][5].c_str());
			y_point += atoi(qry_result[y][4].c_str());
		}
		data.push_back(std::make_pair(x_point, y_point));

		//apply best fit algorithm
		int sum_x = 0;
		int sum_y = 0;
		int sum_x_squared = 0;
		int sum_x_y = 0;
		for (int z = 0; z < data.size(); z++)
		{
			sum_x += data[z].first;
			sum_y += data[z].second;
			sum_x_squared += data[z].first * data[z].first;
			sum_x_y += data[z].first * data[z].second;
		}
		double slope = (sum_x_y - (sum_x * (sum_y / data.size()))) / (sum_x_squared - (sum_x * (sum_x / data.size())));
		//check if slope*days > surplus
		if ((slope * days_until_next_shopping_trip) > (double)item_surplus[x])
		{
			shopping_list.push_back(item_names[x]);
		}

		qry_result.clear();
	}
	return shopping_list;
}

std::vector<std::string> Database::GetNotifications()
{
	std::vector<std::string> notifications;
	std::string sql;
	char *zErrMsg = 0;
	int rc;
	//finds items that have quanities below their minimum
	sql = "SELECT * FROM ITEM;";
	rc = sqlite3_exec(db, sql.c_str(), Select_callback, this, &zErrMsg);
	for (int x = 0; x < qry_result.size(); x++)
	{
		if (atoi(qry_result[x][5].c_str()) < atoi(qry_result[x][6].c_str()))
		{
			notifications.push_back(qry_result[x][2]);
		}
	}
	qry_result.clear();
	return notifications;
}

std::vector<std::string> Database::GetChangelog()
{
	std::vector<std::string> changelog;
	std::string sql;
	char *zErrMsg = 0;
	int rc;

	sql = "SELECT * FROM CHANGELOG;";
	rc = sqlite3_exec(db, sql.c_str(), Select_callback, this, &zErrMsg);
	for (int x = 0; x < qry_result.size(); x++)
	{
		changelog.push_back(qry_result[x][1] + "   " + qry_result[x][2] + "   " + qry_result[x][3] + "   " + qry_result[x][4]);

	}
	qry_result.clear();
	return changelog;
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
	qry_result.clear();
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
	qDebug() << "Layout size is";
	qDebug() << return_layouts.size();
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
	qry_result.clear();
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
	qry_result.clear();
}
std::string Database::SetupStufffinderFolder()
{
	//char stufffinder_folder[] = "\\StuffFinder";
	char *sys_drive = getenv("SystemDrive");
	std::string system_drive(sys_drive);
	system_drive.append("\\StuffFinder");
	qDebug() << system_drive.c_str();

	//try to create stufffinder folder, if it already exists it would create again
	if (_mkdir(system_drive.c_str()) < 0)
	{
		qDebug() << "Error couldnt make folder, or folder exists";
	}
	system_drive.append("\\stufffinder_db.db");
	return system_drive;
}

/*
	SQL callback functions
*/
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