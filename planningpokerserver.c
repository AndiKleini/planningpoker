#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "./headers/handler.h"

int main(int argc, char **argv)
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        printf("Socket creation failed with error %d . \n", errno);
        exit(EXIT_FAILURE);
    }
    printf("Socket was created with file descriptor id %d \n", sfd);

    // create server addresspeersoc
    struct sockaddr_in serveraddr = {
            .sin_family = AF_INET,
            .sin_port = htons(1234),
            .sin_addr.s_addr = INADDR_ANY
    };
    // overwrite socket address here
    inet_aton("127.0.0.3", &serveraddr.sin_addr);

    // make the socket immediately reusable by modification of the socket options
    int enable = 1;
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1) {
        printf("Unable to set socket options due to %d \n", errno);
        exit(EXIT_FAILURE);
    }

    // bind the name (servadress) to the socket
    if (bind(sfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1) {
        printf("Binding failed with error %d ", errno);
        exit(EXIT_FAILURE);
    }

    // start listening
    int constat = listen(sfd, 6);
    if (constat == -1) {
        printf("Connection could not be established. Socket is unable to accept new connections. %d", errno);
        exit(EXIT_FAILURE);
    }

    // accept incoming connectionstalktoclient(peersoc);
    struct sockaddr client;
    socklen_t addrlen = sizeof(client);

    int peersoc;
    int buflen = 50;
    char buffer[buflen];
    while(1) {
        if ((peersoc = accept(sfd, &client, &addrlen)) == -1) {
            printf("Unable to accept client connection. \n");
            exit(EXIT_FAILURE);
        }
        printf("Accepted with filedesiptor of requesting socket %d \n", peersoc);
        int nrbytes = recv(peersoc, buffer, buflen, 0); 
        if (nrbytes < 0) {
            printf("Error by reading from file descriptor %d \n", errno);
        } else {
            printf("Received %d bytes \n", nrbytes);
        }
        const char *response = process_request(buffer)->msg;
        int btsnd = send(peersoc, response, 2, 0);
        if (btsnd < 0) {
            printf("Unable to send byts \n");
        }
    }
}