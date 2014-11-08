/*item.h

This file contains the Item class, which holds all attributes
of an item, including the item's id, name, description, quantity,
and category. An item can also be marked for tracking, which will
allow that items quantity, cost, and consumption rate to be tracked
in order to generate a shopping list.

*/

#ifndef __item_h_
#define __item_h_
#include <string>

class Item {
public:
	Item() {}
	Item(std::string iname,std::string d,int q,int c) : name(iname),description(d),quantity(q),category_id(c) {}
	void set_name(std::string n) { name = n; }
	void set_description(std::string d) { description = d; }
	void set_quantity(int q) { quantity = q; }
	void set_track(bool t) { track = t; }
	void set_min_quantity(int min) { min_quantity = min; }
	void set_item_id(int id){ item_id = id; };
	void set_category(int c) { category_id = c; }
	void set_container_id(int cid){ container_id = cid; }
	std::string get_name() { return name; }
	std::string get_description() { return description; }
	int get_category() { return category_id; }
	int get_quantity() { return quantity; }
	int get_min_quantity() { return min_quantity; }
	int get_item_id(){ return item_id;}
	int get_container_id(){ return container_id; }
	void Increment(int n = 1) { quantity += n; }
	void Decrement(int n = 1) { quantity -= n; }

private:
	int item_id;
	int container_id;
	int category_id;
	std::string name;
	std::string description;
	//Date exp_date;
	int quantity;
	bool track;
	int min_quantity;
};
#endif