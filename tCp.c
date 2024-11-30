#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
#endif
#include <ws2def.h>


#pragma comment(lib,"ws2_32.lib")


int winSockInitialization() {
    WSADATA myWindowsSocketData;
    // WSAStartup(0x0202, &myWindowsSocketData);
    // return myWindowsSocketData;
    WORD windowsVersionRequested = MAKEWORD(2, 2);
    int initializedResult = WSAStartup(windowsVersionRequested, &myWindowsSocketData);
    if (initializedResult != 0) {
      printf("winsock initialization failed: %d\n", initializedResult);
      return initializedResult;
    }
    printf("Winsock Initialization state: SUCCESS");
    return 0;
}

SOCKET socketInitialization() {
    int active = 0;
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // checking if socket was created
    if (serverSocket == INVALID_SOCKET) {
      int errorCode = WSAGetLastError();
      printf("\nSocket was not initialized -> Error code: %d\n", errorCode);
      WSACleanup();
      return INVALID_SOCKET;
    }
    printf("\nSOCKET IS OK\n");
    return serverSocket;
}
