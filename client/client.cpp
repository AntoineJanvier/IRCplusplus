#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <pthread.h>

#include "src/User.hpp"

using namespace std;

void *receive_messages_thread(void *ptr) {
            
    auto clientSd = (int)(size_t) ptr;
    //buffer to receive messages with
    char msg[1500];

    while(true) {
        // catch server messages
        memset(&msg, 0, sizeof(msg)); //clear the buffer
        recv(clientSd, (char*)&msg, sizeof(msg), 0);
        cout << msg;

    }

}

int main(int argc, char *argv[]) {

    //we need 2 things: ip address and port number, in that order
    if(argc != 3) {
        cerr << "Usage: ip_address port" << endl; exit(0);
    } //grab the IP address and port number
    char *serverIp = argv[1]; int port = atoi(argv[2]);
    
    string username;
    cout << "Username : ";
    getline(cin, username);

    User *uClient = new User(username);

    //setup a socket and connection tools
    struct hostent* host = gethostbyname(serverIp);
    sockaddr_in sendSockAddr{};
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(static_cast<uint16_t>(port));
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);
    //try to connect...
    int status = connect(clientSd, (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
    if(status < 0) {
        cout<<"Error connecting to socket!"<<endl;
    }
    cout << "Connected to the server!" << endl << endl;

    pthread_t receivThread;
    int res = pthread_create( &receivThread, nullptr, receive_messages_thread, (void*) clientSd);
    if (res) {
        std::cout << "Error creating receive message thread";
    }
    char msg[1500];
    while(true) {
        string data;
        getline(cin, data);
        memset(&msg, 0, sizeof(msg)); //clear the buffer
        strcpy(msg, uClient->getUsername().c_str());
        strcat(msg, " : ");
        strcat(msg, data.c_str());
        if(data == "/exit") {
            send(clientSd, (char*)&msg, strlen(msg), 0);
            close(clientSd);
            break;
        }
        send(clientSd, (char*)&msg, strlen(msg), 0);

    }
    cout << "Connection closed" << endl;
    
    return 0;

}