#ifndef tCp_h
#define tCp_h

#ifdef __cplusplus
  extern "C" {
#endif

#if defined(_WIN32) || defined(_WIN64)
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
#endif

int winSockInitialization();
SOCKET socketInitialization();


#ifdef __cplusplus
}
#endif
#endif
