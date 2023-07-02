#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <chrono>

using namespace std::chrono;

#define BUFLEN 8192

int main() {
    // Инициализируем библиотеку Windows Sockets
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "Ошибка инициализации сокетов" << std::endl;
        return 1;
    }

    // Создаем сокет для сервера
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Задаем параметры адреса сервера
    sockaddr_in server_address;
    server_address.sin_family = AF_INET; // тип адреса IPv4
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // адрес локального узла
    server_address.sin_port = htons(8888); // номер порта

    // Связываем сокет сервера с адресом и портом
    bind(server_socket, (SOCKADDR*)&server_address, sizeof(server_address));

    // Начинаем прослушивание входящих соединений
    listen(server_socket, SOMAXCONN);

    std::cout << "Waiting for clients..." << std::endl;

    // Принимаем первого клиента
    SOCKET client_socket1 = accept(server_socket, NULL, NULL);
    std::cout << "Client 1 connected!" << std::endl;
    struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&client_socket1;

    // Создаем буфер для получения и отправки сообщений
    char buffer[BUFLEN];
    int bytes_received;
    int bytes_count;
    int bytes_sent;
    int i = 0;

    long resultTime = 0;
    long resultBytes = 0;
    setlocale(LC_ALL, "Russian");
    while (1)
    {
        // Получаем пакет от первого клиента
            //bytes_received = recv(client_socket1, buffer, BUFLEN, 0);
        // Отправляем пакет второму клиенту
           // bytes_sent = send(client_socket1, buffer, bytes_received, 0);
        //printf("Waiting for data...");
        fflush(stdout);

        //clear the buffer by filling null, it might have previously received data
        memset(buffer, '\0', BUFLEN);

        //try to receive some data, this is a blocking call
        if ((bytes_received = recv(client_socket1, buffer, BUFLEN, 0)) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code : %d", WSAGetLastError());
            exit(EXIT_FAILURE);
        }
       
        //print details of the client/peer and the data received
        //printf("Received packet from %s:%d\n", inet_ntoa(pV4Addr->sin_addr), ntohs(pV4Addr->sin_port));

        //now reply the client with the same data
        if ((bytes_sent = send(client_socket1, buffer, bytes_received, 0)) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code : %d", WSAGetLastError());
            exit(EXIT_FAILURE);
        }
    }
    Sleep(50000);

    // Закрываем сокеты и освобождаем ресурсы Windows Sockets
    closesocket(client_socket1);
    closesocket(server_socket);

    WSACleanup();

    return 0;
}
