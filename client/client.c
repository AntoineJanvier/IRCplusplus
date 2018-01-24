#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <zconf.h>

int main(int argc , char *argv[]) {
    int sock;
    struct sockaddr_in server;

    char message[1000], server_reply[2000];

    char * server_address = "127.0.0.1";
    uint16_t server_port = 8890;

    char * custom_response = "";
    char tmp[5];

    sock = socket(AF_INET , SOCK_STREAM , 0); // Create a Socket
    if (sock == -1) {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr(server_address);
    server.sin_port = htons(server_port);
    server.sin_family = AF_INET;

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected to 127.0.0.1:8890");

    while(1) {
        printf("Send message : ");
        scanf("%s", message);
        if(send(sock, message, strlen(message), 0) < 0) {
            puts("Send failed");
            return 1;
        }
        fflush(stdout);
        if( recv(sock , server_reply , 2000 , 0) < 0) {
            puts("recv failed");
            break;
        }
        puts(server_reply);
    }
    close(sock);
    return 0;
}