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
    server.sin_addr.s_addr = inet_addr("10.0.0.0");
    server.sin_family = AF_INET;
    server.sin_port = htons(80); // htons used for endianess to store in big endian format

    // connecting to the remote server
    int connectionStatus = connect(socket, (struct sockaddr*)&server, sizeof(server));
    if (connectionStatus < 0) {
      puts("Connection Error");
    }
    else {
      puts ("Connection successful");
    }

    return 0;
}
