#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdio.h>
#include<winsock2.h>
#include<string.h>
#include<chrono>
#include<iostream>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 8192	//Max length of buffer
#define PORT 8888	//The port on which to listen for incoming data

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

int main(void)
{
	setlocale(LC_ALL, "Russian");
	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];
	WSADATA wsa;

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char*)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	steady_clock::time_point start = high_resolution_clock::now();
	steady_clock::time_point stop = high_resolution_clock::now();
	long transferTime;
	int bytes_received;

	//start communication
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
			generate(message, BUFLEN, i);
			//message[0] += 1;
			start = high_resolution_clock::now();
			//send the message
			if (sendto(s, message, strlen(message), 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
			{
				printf("sendto() failed with error code : %d", WSAGetLastError());
				exit(EXIT_FAILURE);
			}
			//receive a reply and print it
			//clear the buffer by filling null, it might have previously received data
			memset(buf, '\0', BUFLEN);
			//try to receive some data, this is a blocking call
			if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen) == SOCKET_ERROR)
			{
				printf("recvfrom() failed with error code : %d", WSAGetLastError());
				exit(EXIT_FAILURE);
			}
			stop = high_resolution_clock::now();
			transferTime = duration_cast<microseconds>(stop - start).count();
			resultTime += transferTime;

			if (areEqual(message, buf, strlen(message)))
			{
				printf("Пакет принят. Время передачи(мкс): %d. Размер пакета: %d. Скорость передачи: %lf\n", transferTime, BUFLEN, (((double)BUFLEN / transferTime) * 1000000) / (1024 * 1024));
				totalBytesReceived += BUFLEN;
				++totalPacketsReceived;
			}
			else
				++totalPacketsLost;
			//puts(buf);
		}
		// Выводим статистику о передаче данных
		std::cout << "Принято " << totalBytesReceived << " байт в " << totalPacketsReceived << " пакетах" << std::endl;

		// Считаем количество потерянных пакетов
		std::cout << "Потеряно или повреждено " << totalPacketsLost << " пакетов" << std::endl;

		std::cout << "Общее время: " << resultTime << "мкс\n";
		std::cout << "Средняя скорость: " << (((double)totalBytesReceived / resultTime) * 1000000) / (1024 * 1024) << "Мб/с\n";
	}

	closesocket(s);
	WSACleanup();

	return 0;
}