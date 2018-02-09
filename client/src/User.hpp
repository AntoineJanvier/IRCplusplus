#ifndef USER_H
#define USER_H

#include <cstdlib>
#include <errno.h>
#include <iostream>

using namespace std;

class User {

	private:
		int id;
		string username;
		string color;

	public:
		User(string username);
		User(string username, string color);
		int getId();
		string getUsername();
		string getColor();
		void setUsername(string username);
		void setColor(string color);
		
};

#endif
