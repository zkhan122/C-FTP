#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "./tCp.h"

int main(void) {
  int client_to_server_socket =  socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (client_to_server_socket == -1) {
    perror("Socket creation failed..");
    return 1;
  }
  char *ip_client_address = "127.0.0.1";
  int port = 8080;

  struct sockaddr_in client_addr;
  socklen_t client_addr_size;
  char messageBuffer[1024];

  memset(&client_addr, '\0', sizeof(client_addr));
  client_addr.sin_family = AF_INET;
  client_addr.sin_port = htons(port);
  client_addr.sin_addr.s_addr = inet_addr(ip_client_address);

  while (1) {
    int connectionStatus = connect(client_to_server_socket, (struct sockaddr*)&client_addr, sizeof(client_addr));
    if (connectionStatus == -1) {
      perror("Connection failed");
      close(client_to_server_socket);
      return 1;
    }

    printf("SUCCESS: CONNECTED TO SERVER\n");

    // sending message to server
    bzero(messageBuffer, 1024);
    strcpy(messageBuffer, "Hi! This is a response from the client");
    printf("Client: %s\n", messageBuffer);

    int sendStatus = send(client_to_server_socket, messageBuffer, strlen(messageBuffer), 0);
    printf("Client-end send Status: %d\n", sendStatus);
    if (sendStatus == -1) {
      perror("Error whilst sending message");
      close(client_to_server_socket);
      return 1;
    }

    // receiving message from server
    bzero(messageBuffer, 1024);
    int clientBytesReceived = recv(client_to_server_socket, messageBuffer, sizeof(messageBuffer), 0);

    if (clientBytesReceived == -1) {
      perror("Error whilst receiving message");
      close(client_to_server_socket);
      return 1;

    } else if (clientBytesReceived == 0) {
      printf("Server closed the connection\n");
      close(client_to_server_socket);
      return 1;
    }
    printf("Server: %s\n", messageBuffer);

    close(client_to_server_socket); // closing socket to disconnect
    printf("Disconnected from the server\n");

    sleep(1);

  }
  return 0;
}
