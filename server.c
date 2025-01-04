#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "tCp.h"


// only for visual c++ compiler -> #pragma comment(lib,"ws2_32.lib

#define MAX_MESSAGE_SIZE 256

int main(void) {
    char *ip_address = "127.0.0.1";
    int port = 8080;
    char messageBuffer[1024];
    struct sockaddr_in server_socket_addr; // initializing the server socket
    struct sockaddr_in client_socket_addr; // initializing the client socket
    server_socket_addr.sin_family = AF_INET;
    server_socket_addr.sin_port = htons(port); // htons used for endianess to store in big endian format
    server_socket_addr.sin_addr.s_addr = inet_addr(ip_address); // RUN THE SERVER ON THIS IP ADDRESS
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // int client_socket = socketInitialization();

    // connecting to the remote server_socket_addr
    int connectionStatus = bind(server_socket, (struct sockaddr *)&server_socket_addr, sizeof(server_socket_addr));
    if (connectionStatus < 0) {
      perror("\nBIND ERROR");
      exit(1);
    } else {
      printf("SUCCESS: BIND TO PORT NUMBER AT: (%d) COMPLETE\n", port);
    }

    listen(server_socket, 5);
    printf("Server is listening..\n");

    int connected = 0;

    // client connection
    while (1) {
      socklen_t client_len = sizeof(client_socket_addr);
      int client_socket = accept(server_socket, (struct sockaddr *)&client_socket_addr, &client_len);

      printf("Connection Status: %d\n", client_socket);
      if (client_socket == -1) {
        perror("Error");
        return 1;
      }
      else {
        puts("Connection successful");
        connected = 1;
      }
      if (connected == 1) {
        // receive message from client
        bzero(messageBuffer, 1024); // places nbyte null bytes in string s
        int serverBytesReceived = recv(client_socket, messageBuffer, sizeof(messageBuffer), 0);

        if (serverBytesReceived == -1) {
          perror("Error whilst receiving message");
          close(client_socket);
          return 1;

        } else if (serverBytesReceived == 0) {
          printf("Server closed the connection\n");
          close(client_socket);
          return 1;
        }

        printf("Client: (%s)\n", messageBuffer);

        // send message to client
        bzero(messageBuffer, 1024);
        strcpy(messageBuffer, "Hi! This is a response from the server");
        printf("Server: %s\n", messageBuffer);

        int sendStatus = send(client_socket, messageBuffer, strlen(messageBuffer), 0);

        printf("Server-end send Status: %d", sendStatus, "\n");
        if (sendStatus == -1) {
          perror("Error whilst sending message");
          close(client_socket);
          return 1;
        }


        close(client_socket); // closing the current client socket to allow server to accept new connections
        printf("\n --> Client has disconnected\n\n");
      }
    }

    return 0;
}
