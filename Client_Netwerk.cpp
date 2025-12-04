#include<iostream>
#include<string>
#include<winsock2.h>
#include<ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 512

using namespace std;

int main() {
    // 1) Startup Winsock
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD(2, 2);
    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }
    else {
        printf("WSAStartup successful!\n");
    }

    // 2) Initialize Socket
    SOCKET ConnectSocket = INVALID_SOCKET;
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    else {
        printf("Socket created successfully!\n");
    }

    // 3) Specify Connection
    struct sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_port = htons(26000);

    // Verwende localhost für Test, oder die gewünschte IP
    if (inet_pton(AF_INET, "10.172.67.161", &clientService.sin_addr) <= 0) {
        // Alternative: if (inet_pton(AF_INET, "10.172.67.161", &clientService.sin_addr) <= 0) {
        printf("Invalid address or address not supported\n");
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // 4) Connect to server
    int iResult = connect(ConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService));
    if (iResult == SOCKET_ERROR) {
        printf("connect failed with error: %d\n", WSAGetLastError());
        printf("Make sure the server is running on the correct IP and port!\n");
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    else {
        printf("Connected to server successfully!\n");
    }

    // 5) Send data
    const char* rq_all = "HalloServer\n";
    iResult = send(ConnectSocket, rq_all, (int)strlen(rq_all), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
    }
    else {
        printf("Message sent successfully: %s", rq_all);
        printf("Bytes sent: %d\n", iResult);
    }

    // 6) Close the socket
    iResult = closesocket(ConnectSocket);
    if (iResult == SOCKET_ERROR) {
        printf("closesocket failed with error: %d\n", WSAGetLastError());
    }
    else {
        printf("Socket closed successfully\n");
    }

    WSACleanup();
    printf("Client shutdown complete. Press Enter to exit...\n");
    cin.get();  // Wartet auf Eingabe bevor das Programm beendet wird

    return 0;
}