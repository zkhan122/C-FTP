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
    char *ip_address = "127.0.0.c.1";
    int port = 1024;
    char messageBuffer[1024];
    struct sockaddr_in server_socket_addr; // initializing the server socket
    struct sockaddr_in client_socket_addr; // initializing the client socket
    server_socket_addr.sin_family = AF_INET;
    server_socket_addr.sin_port = htons(port); // htons used for endianess to store in big endian format
    server_socket_addr.sin_addr.s_addr = inet_addr(ip_address); // RUN THE SERVER ON THIS IP ADDRESS
    int server_socket = socketInitialization();
    int client_socket = socketInitialization();

    // connecting to the remote server_socket_addr
    int connectionStatus = bind(server_socket, (struct sockaddr *)&server_socket_addr, sizeof(server_socket_addr));
    if (connectionStatus < 0) {
      perror("\nBIND ERROR");
      exit(1);
    } else {
      printf("SUCCESS: BIND TO PORT NUMBER AT: (%d) COMPLETE\n", port);
    }

    listen(server_socket, 5);
    printf("Listening..\n");

    // client connection
    while (1) {
      socklen_t client_len = sizeof(client_socket_addr);
      int connection = accept(server_socket, (struct sockaddr *)&client_socket_addr, &client_len);

      printf("Connection Status: %d\n", connectionStatus);
      if (connectionStatus == -1) {
        perror("Error");
        return 1;
      }
      else {
        puts("Connection successful");
      }
      bzero(messageBuffer, 1024); // places nbyte null bytes in string s
      recv(client_socket, messageBuffer, sizeof(messageBuffer), 0);
      printf("Client: (%s)\n", messageBuffer);

      bzero(messageBuffer, 1024);
      strcpy(messageBuffer, "Hi! This is a response from the server");
      printf("Server: %s\n", messageBuffer);
      send(client_socket, messageBuffer, strlen(messageBuffer), 0);


      close(socket);
      printf("\n --> Client has disconnected\n\n");
    }

    return 0;
}
