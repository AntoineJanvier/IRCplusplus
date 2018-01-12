//
// Created by antoine on 12/01/18.
//

#ifndef CHAT_MESSAGE_H
#define CHAT_MESSAGE_H

#include <cstring>
#include <string>
#include <utility>

using namespace std;

class Message {
private:
    string content;
public:
    Message *next;
    Message(string content) {
        this->content = move(content);
        this->next = nullptr;
    }
    string getContent() {
        return this->content;
    }
};

#endif //CHAT_MESSAGE_H
