/*container.h

This file contains the Container class, which describes a 
container (eg. room, box, dresser, etc.). A container can hold
multiple containers (as a vector of container pointers), and
multiple items (as a vector of item pointers).

*/

#ifndef __container_h_
#define __container_h_
#include <string>
#include <vector>
#include "item.h"

class Container {
public:
	Container() {};
	Container(int id, std::string n, std::string d) { container_id = id; name = n; description = d; }
	~Container();
	void set_name(std::string n) { name = n; }
	void set_description(std::string d) { description = d; }
	void set_container_id(int id) { container_id = id; }
	std::string get_name() { return name; }
	std::string get_description() { return description; }
	std::vector<Item*> get_items() { return items; }
	std::vector<Container*> get_container() { return containers; }
	int get_container_id() { return container_id; }

	void AddItem(Item* item) { items.push_back(item); };
	void AddContainer(Container* container) { containers.push_back(container); };
	void DeleteItem(Item* item);
	void DeleteContainer(Container* container);
	void set_coords(int x1, int y1, int x2, int y2);
	void set_containers(std::vector<Container*> loaded_containers) { containers = loaded_containers; }
	
	Item* Search(int id);
	Item* Search(std::string name);
	Container* SearchContainer(int id);
private:
	int container_id;
	std::string name;
	std::string description;
	std::vector<Item*> items;
	std::vector<Container*> containers;
	std::pair<int, int> coord1;
	std::pair<int, int> coord2;

};
#endif