//
// Created by antoine on 02/01/18.
//

#ifndef CLIENT_ROOM_H
#define CLIENT_ROOM_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "User.h"

using namespace std;

class Room {
    public:
        int id;
        string name;
        User *userlist{};

        void addUser(User *newUser) {
            User *tmp = userlist;
            while (tmp->next) {
                tmp = tmp->next;
            }
            tmp->next = newUser;
            cout << "+ " << newUser->name << " added." << endl;
        }
        void removeUser(int userID) {
            if (userlist->id == userID) {
                User *tmp = userlist;
                userlist = userlist->next;
                cout << "- " << tmp->name << " removed from " << this->name << "." << endl;
                free(tmp);
            } else {
                User *u = userlist;
                while (u) {
                    if (u->next->id == userID) {
                        User *tmp = u->next;
                        u->next = u->next->next;
                        cout << "- " << tmp->name << " removed from " << this->name << "." << endl;
                        free(tmp);
                    }
                }
            }
        }

        Room(int id, const string &name) {
            this->id = id;
            this->name = move(name);
            this->userlist = nullptr;
            cout << "Room #" << this->id << " : \"" << this->name << "\" created." << endl;
        }
        ~Room() {
            while (this->userlist != nullptr) {
                User *nn = this->userlist->next;
                free(this->userlist);
                this->userlist = nn;
            }
            cout << this->name << " closed." << endl;
        }

};

#endif //CLIENT_ROOM_H
