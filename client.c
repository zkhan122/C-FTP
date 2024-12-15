#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ip_address = "127.0.0.1";
int port 1024;

int client_to_server_socket;
struct sockaddr_in client_addr;
socklen_t client_addr_size;
char buffer[1024];
int n;

client_to_server_socket = socket(AF_INET, SOCK_STREAM, 0); // AF_INET is an address family that your socket can communicate with
if (client_to_server_socket < 0) {
  perror("Error");
} else {
  printf("good");
}
