#include "Layout.h"

void Layout::delete_room(Container * room) {
	for (unsigned int x = 0; x < rooms.size(); x++) {
		if (rooms[x] == room) {
			rooms.erase(rooms.begin() + x);
			//output message here
			break;
		}
	}
}
Item* Layout::search(int id) {
	Item* found;
	for (unsigned int x = 0; x < rooms.size(); x++) {
		found = rooms[x]->search(id);
		if (found != NULL) {
			break;
		}
	}
	if (found != NULL) {
		//output found
		return found;
	}
	else {
		//output not found
		return NULL;
	}
}
Item* Layout::search(std::string name) {
	Item* found;
	for (unsigned int x = 0; x < rooms.size(); x++) {
		found = rooms[x]->search(name);
		if (found != NULL) {
			break;
		}
	}
	if (found != NULL) {
		//output found
		return found;
	}
	else {
		//output not found
		return NULL;
	}
}
