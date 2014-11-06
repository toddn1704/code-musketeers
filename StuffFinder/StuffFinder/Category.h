/*Category.h

This file contains the Category class, which simply defines
a category. A category can have many items, which are stored
in a map of item names and item pointers.

*/

#ifndef __category_h_
#define __category_h_
#include <string>
#include <vector>
#include <map>
#include "item.h"

class Category {
public:
	Category(){}
	Category(int i,std::string n,std::string d) : category_id(i),name(n),description(d) {}

	void set_name(std::string n) { name = n; }
	void set_description(std::string d) { description = d; }
	void set_category_id(int i) { category_id = i; }
	void add_item(Item* i) { items.insert(std::make_pair(i->get_name(),i)); }

	int get_category_id() { return category_id; }
	std::string get_name() { return name; }
	std::string get_description() { return description; }
	std::map<std::string, Item*> &get_items() { return items; }
	

private:
	int category_id;
	std::string name;
	std::string description;
	std::map<std::string, Item*> items;
};
#endif