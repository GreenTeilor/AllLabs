#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <sstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ctime>

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
        std::cerr << "Error: failed to create a socket. Error code: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Get server address information
    struct addrinfo hints, * server_addr;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    //time.nist.gov
    if (getaddrinfo("time.nist.gov", "daytime", &hints, &server_addr) != 0) {
        std::cerr << "Error: invalid server domain." << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Connect to server
    if (connect(sockfd, server_addr->ai_addr, (int)server_addr->ai_addrlen) == SOCKET_ERROR) {
        std::cerr << "Error: failed to connect to server. Error code: " << WSAGetLastError() << std::endl;
        freeaddrinfo(server_addr);
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Receive data from server
    char buffer[MAX_BUFFER_SIZE];
    int bytes_received = recv(sockfd, buffer, MAX_BUFFER_SIZE - 1, 0);
    if (bytes_received == SOCKET_ERROR) {
        std::cerr << "Error: failed to receive data from server. Error code: " << WSAGetLastError() << std::endl;
        freeaddrinfo(server_addr);
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Add null terminator to received data
    buffer[bytes_received] = '\0';

    // Convert received data to time string
    time_t time_seconds = std::stoi(buffer);
    struct tm* time_info = gmtime(&time_seconds);
    char time_string[80];
    strftime(time_string, 80, "%Y-%m-%d %H:%M:%S", time_info);

    // Print time string
    //std::cout << "Time received from server: " << time_string << std::endl;
    puts(buffer);

    // Close socket
    freeaddrinfo(server_addr);
    closesocket(sockfd);

    // Clean up Winsock
    WSACleanup();
    char a;
    std::cin >> a;

    return 0;
}
