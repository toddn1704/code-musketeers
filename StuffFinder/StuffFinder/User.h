/*user.h

This header file contains the User class, which defines
a user of the application. 

*/

#ifndef __user_h_
#define __user_h_
#include <string>

class User {
public:
	User();
	std::string get_name() { return name; }
	bool Login(std::string pw);

private:
	std::string name;
	std::string password;
}
#endif