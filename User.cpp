#include <cstdlib>
#include <errno.h>
#include <iostream>

#include "User.hpp"

using namespace std;

int index = 0;

User::User(string username)
	: id(index++), username(username), color("#ff0000")
{}

User::User(string username, string color)
	: id(index++), username(username), color(color)
{}

int User::getId() { return id; }

string User::getUsername() { return username; }

string User::getColor() { return color; }

void User::setUsername(string username) {
	username = username;
}

void User::setColor(string color) {
	color = color;
}
