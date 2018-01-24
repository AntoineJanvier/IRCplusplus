//
// Created by antoine on 24/01/18.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

int sockets[1000];
int counter = 0;

void *connection_handler(void *);
void initSocketArray() {
    int i;
    for (i = 0; i < 1000; i++) {
        sockets[i] = 0;
    }
}

#endif //SERVER_SERVER_H
