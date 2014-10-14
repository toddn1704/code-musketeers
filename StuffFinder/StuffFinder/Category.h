#ifndef __category_h_
#define __category_h_
#include <string>
#include <vector>
#include "Item.h"

class Category {
public:
	Category();
	void set_name(std::string n) { name = n; }
	void set_description(std::string d) { description = d; }
	std::string get_name() { return name; }
	std::string get_description() { return description; }
	

private:
	std::string name;
	std::string description;
	std::vector<Item*> items;
}
#endif