#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define MAX_BUFFER_SIZE 1024

int main() {
    // Initialize Winsock
    WSADATA wsa_data;
    int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != 0) {
        std::cerr << "Error: failed to initialize Winsock." << std::endl;
        return 1;
    }

    // Create a socket
    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        std::cerr << "Error: failed to create a socket." << std::endl;
        WSACleanup();
        return 1;
    }

    // Bind socket to port
    struct sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(13);
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Error: failed to bind to port." << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Listen for connections
    if (listen(sockfd, 5) == SOCKET_ERROR) {
        std::cerr << "Error: failed to listen for connections." << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Accept connection
    SOCKET connfd = accept(sockfd, NULL, NULL);
    if (connfd == INVALID_SOCKET) {
        std::cerr << "Error: failed to accept connection." << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Get current time as string
    time_t current_time = std::time(nullptr);
    char time_string[80];
    std::strftime(time_string, 80, "%Y-%m-%d %H:%M:%S", std::gmtime(&current_time));

    // Send time string to client
    if (send(connfd, time_string, std::strlen(time_string), 0) == SOCKET_ERROR) {
        std::cerr << "Error: failed to send data to client." << std::endl;
        closesocket(connfd);
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Close connection and socket
    closesocket(connfd);
    closesocket(sockfd);
    WSACleanup();

    return 0;
}
