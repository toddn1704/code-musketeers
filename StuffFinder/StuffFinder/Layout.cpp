/*layout.cpp

This file will implement the functions declared in the
layout.h file.

*/

#include "layout.h"

void Layout::DeleteRoom(Container * room) {
	for (unsigned int x = 0; x < rooms.size(); x++) {
		if (rooms[x] == room) {
			rooms.erase(rooms.begin() + x);
			//output message here
			break;
		}
	}
}
Item* Layout::Search(int id) {
	Item* found;
	for (unsigned int x = 0; x < rooms.size(); x++) {
		found = rooms[x]->Search(id);
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
Item* Layout::Search(std::string name) {
	Item* found;
	for (unsigned int x = 0; x < rooms.size(); x++) {
		found = rooms[x]->Search(name);
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

Container* Layout::SearchContainer(int id) {
	Container* found;
	for (unsigned int x = 0; x < rooms.size(); x++) {
		found = rooms[x]->SearchContainer(id);
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