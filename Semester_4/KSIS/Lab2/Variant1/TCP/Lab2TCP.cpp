#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include <chrono>
#include <string.h>

#pragma comment(lib, "ws2_32.lib") // добавляем библиотеку ws2_32.lib

#define BUFLEN 8192

using namespace std::chrono;

void generate(char* buffer, int size, int base)
{
    for (int i = 0; i < size; ++i)
        buffer[i] = base + i;
}

bool areEqual(char* buffer1, char* buffer2, int size)
{
    for (int i = 0; i < size; ++i)
        if (buffer1[i] != buffer2[i])
            return false;
    return true;
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");
    // Инициализируем сокеты
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "Ошибка инициализации сокетов" << std::endl;
        return 1;
    }

    // Создаем сокет для отправки данных
    SOCKET sendSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sendSocket == INVALID_SOCKET)
    {
        std::cerr << "Ошибка создания сокета" << std::endl;
        return 1;
    }

    // Устанавливаем параметры сокета для отправки данных
    SOCKADDR_IN sendAddr;
    sendAddr.sin_family = AF_INET;
    sendAddr.sin_port = htons(8888); // номер порта для отправки данных
    sendAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // адрес получателя
    
    // Соединяемся с получателем
    if (connect(sendSocket, (SOCKADDR*)&sendAddr, sizeof(sendAddr)) == SOCKET_ERROR)
    {
        std::cerr << "Ошибка соединения" << std::endl;
        closesocket(sendSocket);
        WSACleanup();
        return 1;
    }

    // Генерируем случайные данные для отправки
    const int dataSize = BUFLEN; // размер данных для отправки
    char data[BUFLEN];
    char message[BUFLEN];
    steady_clock::time_point start = high_resolution_clock::now();
    steady_clock::time_point stop = high_resolution_clock::now();
    long transferTime;
    int bytes_received;
    int bytesCount;

    while (1)
    {
        printf("Enter message : ");
        gets_s(message);
        int totalPacketsLost = 0;
        int totalBytesReceived = 0;
        int totalPacketsReceived = 0;
        long resultTime = 0;
        for (int i = 0; i < 100; ++i)
        {
            bytesCount = 0;
            generate(message, BUFLEN, i);
            start = high_resolution_clock::now();
            //send the message
                //int bytesSent = send(sendSocket, message, dataSize, 0);
            if (send(sendSocket, message, dataSize, 0) == SOCKET_ERROR)
            {
                printf("sendto() failed with error code : %d", WSAGetLastError());
                exit(EXIT_FAILURE);
            }
            //receive a reply and print it
            //clear the buffer by filling null, it might have previously received data
            memset(data, '\0', BUFLEN);
            //try to receive some data, this is a blocking call
                //int bytesReceived = recv(sendSocket, data, sizeof(data), 0);
            if (recv(sendSocket, data, sizeof(data), 0) == SOCKET_ERROR)
            {
                printf("recvfrom() failed with error code : %d", WSAGetLastError());
                exit(EXIT_FAILURE);
            }
            stop = high_resolution_clock::now();
            transferTime = duration_cast<microseconds>(stop - start).count();
            resultTime += transferTime;

            if (areEqual(message, data, BUFLEN))
            {
                printf("Пакет принят. Время передачи(мкс): %d. Размер пакета: %d. Скорость передачи: %lf\n", transferTime, BUFLEN, (((double)BUFLEN / transferTime) * 1000000) / (1024 * 1024));
                totalBytesReceived += BUFLEN;
                ++totalPacketsReceived;
            }
            else
                ++totalPacketsLost;
        }
        // Выводим статистику о передаче данных
        std::cout << "Принято " << totalBytesReceived << " байт в " << totalPacketsReceived << " пакетах" << std::endl;

        // Считаем количество потерянных пакетов
        std::cout << "Потеряно или повреждено " << totalPacketsLost << " пакетов" << std::endl;

        std::cout << "Общее время: " << resultTime << "мкс\n";
        std::cout << "Средняя скорость: " << (((double)totalBytesReceived / resultTime) * 1000000) / (1024 * 1024) << "Мб/с\n";
    }


    // Освобождаем ресурсы
    closesocket(sendSocket);
    delete[] data;
    WSACleanup();
    Sleep(100000);

    return 0;
}