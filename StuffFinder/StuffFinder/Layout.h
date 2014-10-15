#ifndef __layout_h_
#define __layout_h_
#include <string>
#include "Container.h"
class Layout {
	public:
		Layout();
		void set_layout_name(std::string ln){ name = ln; }
		void set_description(std::string d){ desription = d; }
		std::string get_name(){ return name; }
		std::string get_description(){ return desription; }

		void add_room(Container * room);
		void delete_room(Container * room);
	private:
		int layout_id;
		std::string name;
		std::string desription;
		std::vector<Container *> rooms;
};
#endif