#ifndef __container_h_
#define __container_h_
#include <string>
#include <vector>
#include "Item.h"

class Container {
public:
	Container();
	void set_name(std::string n) { name = n; }
	void set_description(std::string d) { description = d; }
	std::string get_name() { return name; }
	std::string get_description() { return description; }
	std::vector<Item*> get_items() { return items; }
	std::vector<Container*> get_container() { return containers; }

	void add_item(Item* item);
	void add_container(Container* container);
	void delete_item(Item* item);
	void delete_container(Container* container);
	void set_coords(int x1, int y1, int x2, int y2);
private:
	std::string name;
	std::string description;
	std::vector<Item*> items;
	std::vector<Container*> containers;
	std::pair<int, int> coord1;
	std::pair<int, int> coord2;

};
#endif