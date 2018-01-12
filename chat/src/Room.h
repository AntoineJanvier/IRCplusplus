//
// Created by antoine on 12/01/18.
//

#ifndef CHAT_ROOM_H
#define CHAT_ROOM_H

#include <string>
#include "User.h"
#include "Message.h"

using namespace std;

class Room {
private:
    int id;
    string name;
    User *listOfUsers;
    Message *listOfMessages;
public:
    Room(int id, string name) {
        this->id = id;
        this->name = move(name);
        this->listOfUsers = nullptr;
        this->listOfMessages = nullptr;
    }
    void listMessages();
    void listUsers();
};

#endif //CHAT_ROOM_H
