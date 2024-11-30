/*
Server

    Initialize Winsock.
    Create a socket.
    Bind the socket.
    Listen on the socket for a client.
    Accept a connection from a client.
    Receive and send data.
    Disconnect.

Client

    Initialize Winsock.
    Create a socket.
    Connect to the server.
    Send and receive data.
    Disconnect.


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <winsock2.h>

#include "./tCp.h"


// only for visual c++ compiler -> #pragma comment(lib,"ws2_32.lib")

/*
gcc main.c -o main.o -c
gcc module.c -o module.o -c
gcc -o program tCp.o server.o -lws2_32
program
*/


int main(void) {
    int socketDataInStatus;
    socketDataInStatus = winSockInitialization();
    SOCKET socket;
    socket = socketInitialization();
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(80); // htons used for endianess to store in big endian format
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // connecting to the remote server
    int connectionStatus = connect(socket, (struct sockaddr *)&server, sizeof(server));
    // int connectionStatus = connect(socket, sizeof(struct sockaddr_in), sizeof(server));
    printf("Connection Status: %d\n", connectionStatus);
    if (connectionStatus == -1) {
      perror("Error");
      return 1;
    }
    else {
      puts("Connection successful");
    }

    closesocket(socket);
    WSACleanup();

    return 0;
}
