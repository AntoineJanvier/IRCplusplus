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
    puts("Listening on 8890...");
    c = sizeof(struct sockaddr_in);

    initSocketArray();
    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))) {
        puts("Connection accepted ! ");
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = client_sock;
        sockets[counter++] = client_sock;
        if (pthread_create(&sniffer_thread, NULL, connection_handler, (void*) new_sock) < 0) {
            perror("could not create thread");
            return 1;
        }
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
    char client_message[1024];

    int i;
    while((read_size = recv(sock, client_message, 1024, 0)) > 0) {
        client_message[read_size+1] = '\0';
        for (i = 0; i < counter; i++) {
            if (sockets[i] > 0) {
                send(sockets[i], client_message , strlen(client_message), 0);
                send(sockets[i], "\n" , strlen("\n"), 0);
            }
        }
        puts(client_message);
        client_message[0] = '\0';
    }
    if(read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else if(read_size == -1) {
        perror("recv failed");
        free(socket_desc);
    }
    return 0;
}