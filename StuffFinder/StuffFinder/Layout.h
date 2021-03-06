/*layout.h

This file contains the Layout class, which represents a single 
floor of a house. Each layout has a vector of Container pointers
which represent rooms on the floor. 

*/

#ifndef __layout_h_
#define __layout_h_
#include <string>
#include "container.h"
#include "item.h"
class Layout {
	public:
		Layout(){}
		Layout(int id, std::string n, std::string d) { layout_id = id; name = n; desription = d; }
		void set_layout_name(std::string ln){ name = ln; }
		void set_description(std::string d){ desription = d; }
		std::string get_name(){ return name; }
		std::string get_description(){ return desription; }
		int get_layout_id(){ return layout_id; }
		std::vector<Container *> get_rooms() { return rooms; }
		void set_layout_id(int id) { layout_id = id; }

		void AddRoom(Container * room) { rooms.push_back(room); };
		void DeleteRoom(Container * room);
		Item* Search(int id);
		void SearchName(std::string name,std::vector<Item> &search_results);

		//SearchContainer(int id), Search the current layout for a container based on container id.
		//return a Container pointer if container found, else return NULL
		Container* SearchContainer(int id);
	private:
		int layout_id;
		std::string name;
		std::string desription;
		std::vector<Container *> rooms;
};
#endif