#ifndef __item_h_
#define __item_h_
#include <string>

class Item {
public:
	Item() {}
	Item(std::string iname,std::string d,int q,std::string c) : name(iname),description(d),quantity(q),category(c) {}
	void set_name(std::string n) { name = n; }
	void set_description(std::string d) { description = d; }
	void set_quantity(int q) { quantity = q; }
	void set_track(bool t) { track = t; }
	void set_min_quantity(int min) { min_quantity = min; }
	void set_item_id(int id){ item_id = id; };
	void set_category(std::string c) { category = c; }
	std::string get_name() { return name; }
	std::string get_description() { return description; }
	std::string get_category() { return category; }
	int get_quantity() { return quantity; }
	int get_min_quantity() { return min_quantity; }
	int get_item_id(){ return item_id;}
	void increment(int n = 1) { quantity += n; }
	void decrement(int n = 1) { quantity -= n; }
private:
	int item_id;
	std::string category;
	std::string name;
	std::string description;
	//Date exp_date;
	int quantity;
	bool track;
	int min_quantity;
};
#endif