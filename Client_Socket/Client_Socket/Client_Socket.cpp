// Author: Jeff Ngeama
// Course: CIS 687
//Syracuse University
//Project 4
//Start Date: 05/22/22
//Last Updated Date: 06/19/22

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <sys/types.h>
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <WS2tcpip.h>
#include <chrono>
#include <thread>


//Need to link with Ws2_32.lib,Mswsock.lib,and Advapi32.lib
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"Mswsock.lib")
#pragma comment(lib,"Advapi32.lib")

#define DEFAULT_BUFLEN 512
//define the default port
#define DEFAULT_PORT "88888"
//define the default server
#define DEFAULT_SERVER "192.168.1.208"

int __cdecl main(int argc, char** argv)
{
    WSADATA wasData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    //define the msg to send to the server
    const char* sendbuf = "Ready to process files. Start MAP.";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    //initialize winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wasData);
    //if the initialization fails print a msg and stop
    if (iResult != 0)
    {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    //resolve the server address and port
    iResult = getaddrinfo(DEFAULT_SERVER, DEFAULT_PORT, &hints, &result);
    if (iResult != 0)
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
    {
        //create a socket for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        // if creating the socket was not successful,print the msg and stop
        if (ConnectSocket == INVALID_SOCKET)
        {
            printf("Socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        //connect to the server
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        //if the connection was not successful print the msg and stop
        if (iResult == SOCKET_ERROR)
        {
            printf("connect was not successful\n");
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    //free up address info space
    freeaddrinfo(result);
    //if the connect socket is an error print the msg and stop
    if (ConnectSocket == INVALID_SOCKET)
    {
       printf("unable to connect to server\n");
       WSACleanup();
        return 1;
    }

    do {
        //this is the heart beat code.
        //send the msg
        iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
        // if send was unsuccessful,print the msg and stop
        if (iResult == SOCKET_ERROR)
        {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(ConnectSocket);
            WSACleanup();
            return 1;
        }
        //if send was successful,print the bytes sent
        printf("Bytes sent: %ld\n", iResult);

        //receive until the peer closes the connection  
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        //if successfully received the msg,print the number of bytes recieved
        if (iResult > 0)
            printf("Bytes received: %d\n", iResult);
        else if (iResult == 0) //if the connection was closed,print the msg
            printf("connection closed\n");
        else // if there is an error ,print the error msg
            printf("recv failed with error: %d\n", WSAGetLastError());

        //wait for 1 minute
        std::this_thread::sleep_for(std::chrono::milliseconds(60000));
    } while (iResult > 0); // continue as long as there is no error

    //cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}