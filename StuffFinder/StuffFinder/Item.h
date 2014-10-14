#ifndef __item_h_
#define __item_h_
#include <string>

class Item {
public:
	Item() {};
	void set_name(std::string n) { name = n; }
	void set_description(std::string d) { description = d; }
	void set_quantity(int q) { quantity = q; }
	void set_track(bool t) { track = t; }
	void set_min_quantity(int min) { min_quantity = min; }
	std::string get_name() { return name; }
	std::string get_description() { return description; }
	int get_quantity() { return quantity; }
	int get_min_quantity() { return min_quantity; }

	void increment(int n = 1) { quantity += n; }
	void decrement(int n = 1) { quantity -= n; }
private:
	std::string name;
	std::string description;
	//Date exp_date;
	int quantity;
	bool track;
	int min_quantity;
};
#endif