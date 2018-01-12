//
// Created by antoine on 08/01/18.
//

#ifndef CLIENT_SOCKETEXCEPTION_H
#define CLIENT_SOCKETEXCEPTION_H

#include <string>

using namespace std;

class SocketException
{
public:
    SocketException ( string s ) : m_s ( s ) {};
    ~SocketException (){};

    string description() { return m_s; }

private:

    string m_s;

};

#endif //CLIENT_SOCKETEXCEPTION_H
