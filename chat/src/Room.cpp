//
// Created by antoine on 12/01/18.
//

#include <string>
#include <iostream>
#include "Message.h"
#include "Room.h"

using namespace std;

void Room::listMessages() {
    Message *current = this->listOfMessages;
    while (current != nullptr) {
        cout << current->getContent() << endl;
        current = current->next;
    }
}

void Room::listUsers() {
    User *current = this->listOfUsers;
    while (current != nullptr) {
        if (current->next == nullptr) {
            cout << current->getName() << "." << endl;
        } else {
            cout << current->getName() << ", ";
        }
        current = current->next;
    }
}