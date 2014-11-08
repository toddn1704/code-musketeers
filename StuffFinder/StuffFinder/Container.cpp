/*container.cpp

This file will implement the functions declared in the
container.h file.

*/

#include "container.h"

void Container::DeleteItem(Item* item) {
	for (unsigned int x = 0; x < items.size(); x++) {
		if (items[x] == item) {
			delete items[x];
			items.erase(items.begin() + x);
			//output message here
			break;
		}
	}
}

void Container::DeleteContainer(Container* container) {
	for (unsigned int x = 0; x < containers.size(); x++) {
		if (containers[x] == container) {
			delete containers[x];
			containers.erase(containers.begin() + x);
			//output message here
			break;
		}
	}
}
Container::~Container() {
	//need to delete from database somehow
	//requires database reference as a parameter
	for (unsigned int x = 0; x < containers.size(); x++) {
		delete containers[x];
	}
	for (unsigned int x = 0; x < items.size(); ++x) {
		delete items[x];
	}
}
void Container::set_coords(int x1, int y1, int x2, int y2) {
	coord1 = std::make_pair(x1, y1);
	coord2 = std::make_pair(x2, y2);
	//update qt
}
Item* Container::Search(int id) {
	Item* found = NULL;
	for (unsigned int x = 0; x < items.size(); x++) {
		if (items[x]->get_item_id() == id) {
			found = items[x];
			break;
		}
	}

	if (found != NULL) {
		return found;
	}

	for (unsigned int x = 0; x < containers.size(); x++) {
		found = containers[x]->Search(id);
		if (found != NULL) {
			break;
		}
	}

	if (found != NULL) {
		return found;
	}
	else {
		return NULL;
	}
}
/*
	Search through the items in the given container, if name is = to item name save it.
	then search through any containers in within this container.
*/
void Container::SearchName(std::string name,std::vector<Item> &search_results) {
	for (unsigned int x = 0; x < items.size(); x++) {
		if (stricmp(items[x]->get_name().c_str(),name.c_str()) == 0) {
			//make a copy of the item
			search_results.push_back(*items[x]);
		}
	}

	for (unsigned int x = 0; x < containers.size(); x++) {
		containers[x]->SearchName(name,search_results);
	}
}

Container* Container::SearchContainer(int id) {
	Container* found = NULL;

	for (unsigned int x = 0; x < containers.size(); x++) {
		if (containers[x]->get_container_id() == id)
		{
			found = containers[x];
		}
		else
		{
			found = containers[x]->SearchContainer(id);
		}
		if (found != NULL) {
			break;
		}
	}

	if (found != NULL) {
		return found;
	}
	else {
		return NULL;
	}
}