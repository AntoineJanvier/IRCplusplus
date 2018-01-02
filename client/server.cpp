#include <iostream>
#include "src/Room.h"

#define SERVER_PORT 4896

using namespace std;

int main() {
    cout << "Server started at port " << SERVER_PORT << "..." << endl << endl;

    int cpt = 0;
    Room room1 = Room(++cpt, "General");

    auto *u = static_cast<User *>(malloc(sizeof(User)));
    u->id = 1;
    u->name = "Toto";

    auto *u2 = static_cast<User *>(malloc(sizeof(User)));
    u2->id = 2;
    u2->name = "Titi";

    room1.addUser(u);
    room1.addUser(u2);

    room1.removeUser(u->id);

    return 0;
}