#define _OPEN_SYS_SOCK_EXT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>

int socketInitialization() {
    int socket_init = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    printf("Socket initialization status: (%d)", socket_init);
    // checking if socket was created
    if (socket_init < 0) {
      printf("\nSocket was not initialized -> Error code: %d\n");
      perror("Error");
      exit(2);
    } else {
    printf("\nSUCCESS: SOCKET IS OK -> SERVER SOCKET CREATED\n");
    }
    return socket_init;
}
