#include "Container.h"

void Container::delete_item(Item* item) {
	for (unsigned int x = 0; x < items.size(); x++) {
		if (items[x] == item) {
			delete items[x];
			items.erase(items.begin() + x);
			//output message here
			break;
		}
	}
}
void Container::delete_container(Container* container) {
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
Item* Container::search(int id) {
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
		found = containers[x]->search(id);
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
Item* Container::search(std::string name) {
	Item* found = NULL;
	for (unsigned int x = 0; x < items.size(); x++) {
		if (items[x]->get_name() == name) {
			found = items[x];
			break;
		}
	}

	if (found != NULL) {
		return found;
	}

	for (unsigned int x = 0; x < containers.size(); x++) {
		found = containers[x]->search(name);
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