//
// Created by antoine on 12/01/18.
//

#ifndef CHAT_USER_H
#define CHAT_USER_H

#include <string>
#include <utility>

using namespace std;

class User {
private:
    int id;
public:
    string name;
    User *next;
    User(int id, string name) {
        this->id = id;
        this->name = move(name);
        this->next = nullptr;
    }
    string getName() {
        return this->name;
    }
};

#endif //CHAT_USER_H
