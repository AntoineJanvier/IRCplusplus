fndef VECTOR_H
#define VECTOR_H

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
		User(int id, string username) {
			this->id = id;
			this->username = username;
			this->color = "#ff0000";
		}
		User(int id, string username, string color) {
			this->id = id;
                        this->username = username;
                        this->color = color;
		}
		int getId() { return this->id; }
		string getUsername() { return this->username; }
		string getColor() { return this->color; }
		void setUsername(string username) {
			this->username = username;
		}
		void setColor(string color) {
			this->color = color;
		}
};

#endif
