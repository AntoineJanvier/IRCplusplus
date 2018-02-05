#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <zconf.h>
#include <pthread.h>

#define BUF_SIZE 1024
int msock;
char *musername;
int needToRePrintCursor;

void * receiveMessage(void * socket) {
    int sockfd, ret;
    char buffer[BUF_SIZE];
    sockfd = msock;
    memset(buffer, 0, BUF_SIZE);

    char *myBan = "";
    strcpy(myBan, "/ban ");
    strcat(myBan, musername);

    while (1) {
        ret = (int) recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);
        needToRePrintCursor = 1;
        if (strcmp(buffer, myBan) == 0) {
            break;
        } else if (ret < 0) {
            printf("Error receiving data!\n");
        } else {

            fputs(buffer, stdout);
            //printf("\n");
        }
    }
}

int main(int argc , char *argv[]) {

    int sock;
    struct sockaddr_in server;

    char username[100], message[BUF_SIZE], final_message[1102];

    char * server_address = "127.0.0.1";
    uint16_t server_port = 8890;

    pthread_t rThread;

    sock = socket(AF_INET , SOCK_STREAM , 0); // Create a Socket
    if (sock == -1) {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr(server_address);
    server.sin_port = htons(server_port);
    server.sin_family = AF_INET;

    printf("Username : ");
    scanf("%s", username);
    strcpy(musername, username);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected to 127.0.0.1:8890");

    msock = sock;
    int ret = pthread_create(&rThread, NULL, receiveMessage, NULL);
    if (ret) {
        printf("ERROR: Return Code from pthread_create() is %d\n", ret);
        exit(1);
    }

    while(1) {
        if (needToRePrintCursor == 1) {
            printf("> ");
            needToRePrintCursor = 0;
        }
        scanf("%s", message);
        if (strcmp(message, (const char *) "/exit") == 0) break;

        // Format : "<User> Hello !"
        strcpy(final_message, "<");
        strcat(final_message, username);
        strcat(final_message, "> ");
        strcat(final_message, message);

        if(send(sock, final_message, strlen(final_message), 0) < 0) {
            puts("Send failed");
            return 1;
        }
        fflush(stdout);
    }
    close(sock);
    return 0;
}