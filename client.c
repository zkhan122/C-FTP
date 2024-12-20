#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "./tCp.h"

int main(void) {
  int client_to_server_socket =  socketInitialization();
  char *ip_client_address = "127.0.0.1";
  int port = 1024;

  struct sockaddr_in client_addr;
  socklen_t client_addr_size;
  char messageBuffer[1024];

  memset(&client_addr, '\0', sizeof(client_addr));
  client_addr.sin_family = AF_INET;
  client_addr.sin_port = port;
  client_addr.sin_addr.s_addr = inet_addr(ip_client_address);

  while (1) {
    connect(client_to_server_socket, (struct sockclient_addr*)&client_addr, sizeof(client_addr));
    printf("SUCCESS: CONNECTED TO SERVER\n");

    bzero(messageBuffer, 1024);
    strcpy(messageBuffer, "Hi! This is a response from the client");
    printf("Client: %s\n", messageBuffer);
    send(client_to_server_socket, messageBuffer, strlen(messageBuffer), 0);

    bzero(messageBuffer, 1024);
    recv(client_to_server_socket, messageBuffer, sizeof(messageBuffer), 0);
    printf("Server: %s\n", messageBuffer);

    close(client_to_server_socket);
    printf("Disconnected from the server");

  }
  return 0;
}
