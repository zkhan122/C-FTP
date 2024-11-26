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
    }
    return initializedResult;
}

int socketInitialization() {
    int active = 0;
    SOCKET serverSocket;
    // serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // checking if socket was created
    if (serverSocket == INVALID_SOCKET) {
        printf("\nSocket was not initialized -> ", WSAGetLastError());
        WSACleanup();
    }
    else {
        printf("\nSOCKET IS OK\n");
        active = 1;
    }

    if (active) {
        return serverSocket;
    }
    return 0;
}
