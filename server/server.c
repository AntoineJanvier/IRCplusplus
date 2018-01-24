#include "server.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc , char *argv[]) {
    int socket_desc , client_sock , c , *new_sock;
    struct sockaddr_in server , client;
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1) printf("Could not create socket");
    puts("Socket created");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8890 );

    if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("bind failed. Error");
        return 1;
    }
    listen(socket_desc , 3);
    puts("Listening...");
    c = sizeof(struct sockaddr_in);

    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))) {
        puts("Connection accepted ! ");
        initSocketArray();
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = client_sock;
        if (pthread_create(&sniffer_thread, NULL, connection_handler, (void*) new_sock) < 0) {
            perror("could not create thread");
            return 1;
        }
        sockets[counter++] = *new_sock;
    }
    if (client_sock < 0) {
        perror("accept failed");
        return 1;
    }
    return 0;
}

void *connection_handler(void *socket_desc) {
    int sock = *(int*) socket_desc; // Socket descriptor
    ssize_t read_size;
    char *message = "", client_message[2000];
    write(sock, message, strlen(message));
    while((read_size = recv(sock, client_message, 2000, 0)) > 0)
        for (int i = 0; i <= counter; i++) write(sockets[i], client_message , strlen(client_message));
    if(read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else if(read_size == -1)
        perror("recv failed");
    free(socket_desc);
    return 0;
}