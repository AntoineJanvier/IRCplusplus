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
using namespace std;

int client_max = 50;
int clients[50];
int nb_clients = 0;

void *messages_thread(void *ptr) {
            
    int i = (int)(size_t) ptr;
    int newClient = clients[i];
    //buffer to send messages with
    char msg[1500];
    char fnl_msg[1505];

    while(1) {

        // catch client message
        memset(&msg, 0, sizeof(msg)); //clear the buffer
        recv(newClient, (char*)&msg, sizeof(msg), 0);
        if(!strcmp(msg, "/exit")) {
            cout << "A client has quit the session" << endl;
            close(newClient);
            break;
        }
        cout << msg << endl;

        memset(&fnl_msg, 0, sizeof(fnl_msg)); //clear the buffer
        strcpy(fnl_msg , "\n");
        strcat(fnl_msg , msg);
        strcat(fnl_msg , "\n\n");

        // redirstribute message to all other clients
        for (int j = 0; j < nb_clients; j++) {
            if (clients[j] != newClient) {
                send(clients[j], (char*)&fnl_msg, strlen(fnl_msg), 0);
            }
        }

    }

}

int main(int argc, char *argv[]) {

    //for the server, we only need to specify a port number
    if (argc != 2) {
        cerr << "Usage: port" << endl;
        exit(0);
    }
    //grab the port number
    int port = atoi(argv[1]);

    //setup a socket and connection tools
    sockaddr_in servAddr;
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    //open stream oriented socket with internet address
    //also keep track of the socket descriptor
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }
    //bind the socket to its local address
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr, sizeof(servAddr));
    if(bindStatus < 0)
    {
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }
    cout << "Waiting for a client to connect..." << endl;
    // listen for up to client_max requests at a time
    listen(serverSd, client_max);
    pthread_t t[client_max];

    for (int i = 0; i < client_max; i++) {

        // wait for a client to accept socker connection
        sockaddr_in from = { 0 };
        socklen_t addrlen = sizeof(servAddr);
        int newClient = accept(serverSd, (sockaddr *)&from, &addrlen);
        if (newClient >= 0) {
            char buff[INET6_ADDRSTRLEN] = { 0 };
            std::string clientAddress = inet_ntop(servAddr.sin_family, (void*)&(servAddr.sin_addr), buff, INET6_ADDRSTRLEN);
            std::cout << "Connection of " << clientAddress << ":" << servAddr.sin_port << std::endl;
        } else
            break;

        // launch new thread to catch and redistribute client message
        clients[i] = newClient;
        nb_clients++;
        int res = pthread_create( &t[i], NULL, messages_thread, (void*) i);
        if (res) {
            std::cout << "Error creating message thread number : " << i;
        }

    }

    for (int i = 0; i < client_max; ++i) {
        pthread_join(t[i], NULL);
    }

    close(serverSd);
    cout << "Connection closed..." << endl;

    return 0;
}