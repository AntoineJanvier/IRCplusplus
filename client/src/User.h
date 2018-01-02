#ifndef CLIENT_USER_H
#define CLIENT_USER_H

#include <iostream>
#include <utility>

using namespace std;

class User {
    public:
        int id;
        string name;
        User *next;

        User(int id, string name) {
            this->id = id;
            this->name = move(name);
            this->next = nullptr;
        }
};

#endif //CLIENT_USER_H
