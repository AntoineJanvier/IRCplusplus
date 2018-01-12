//
// Created by antoine on 08/01/18.
//

#ifndef CLIENT_SERVERSOCKET_H
#define CLIENT_SERVERSOCKET_H

#include "Socket.h"


class ServerSocket : private Socket
{
public:

    ServerSocket ( int port );
    ServerSocket (){};
    virtual ~ServerSocket();

    const ServerSocket& operator << ( const std::string& ) const;
    const ServerSocket& operator >> ( std::string& ) const;

    void accept ( ServerSocket& );

};


#endif //CLIENT_SERVERSOCKET_H
