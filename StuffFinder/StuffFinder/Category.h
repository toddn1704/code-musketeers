#ifndef __category_h_
#define __category_h_
#include <string>
#include <vector>
#include "Item.h"

class Category {
public:
	Category();
	Category(std::string n,std::string d) : name(n),description(d) {}

	void set_name(std::string n) { name = n; }
	void set_description(std::string d) { description = d; }
	void add_item(Item* i) { items.push_back(i); }

	std::string get_name() { return name; }
	std::string get_description() { return description; }
	std::vector<Items*> get_items() { return items; }
	

private:
	std::string name;
	std::string description;
	std::vector<Item*> items;
}
#endif