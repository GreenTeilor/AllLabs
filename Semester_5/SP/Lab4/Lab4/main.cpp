#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include <fstream>
#include <thread>
#include <regex>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <string.h>
#include "ThreadPool.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>

std::vector<std::string> lines;
std::vector<std::vector<std::string>> fragments;
LPCSTR fileProjection;

std::vector<std::string> readFileLines()
{
	std::string filePath = "assets/Data.txt";
	OFSTRUCT fileInfo{};
	HFILE file = OpenFile(filePath.c_str(), &fileInfo, OF_READWRITE); //Open file for read/write and get file descriptor

	DWORD fileSize = GetFileSize((HANDLE)file, NULL);

	HANDLE hFileObject = CreateFileMapping((HANDLE)file, NULL, PAGE_READWRITE, 0, fileSize, NULL); //Get descriptor of projected file object
	if (hFileObject == NULL) throw "Can't get descriptor of projected file object";

	fileProjection = (LPCSTR)MapViewOfFile(hFileObject, FILE_MAP_ALL_ACCESS, 0, 0, fileSize); //Maps a view of a file mapping into the address space of a calling process
	if (fileProjection == NULL) throw "Can't map file object to file";
	//From now on changing data in buffer will result in data change in file!!!

	char* fileData = (char*)calloc(fileSize + 1, sizeof(char));
	if (fileData == NULL) throw "Can't allocate memory for file data";
	strncpy_s(fileData, fileSize + 1, fileProjection, fileSize);

	//Get array of file lines(data)
	std::vector<std::string> fileLines{};
	char* line = strtok(fileData, "\r\n");
	while (line != NULL)
	{
		fileLines.push_back(std::string(line));
		line = strtok(NULL, "\r\n");
	}

	CloseHandle((HANDLE)file);
	CloseHandle(hFileObject);

	return fileLines;
}

short inputThreadsNumber()
{
	std::cout << "Input number of threads: ";
	std::string threadsNumber;
	std::cin >> threadsNumber;
	std::cout << "\n";
	std::regex numberRegex("^([0-9]+)$");
	if (!std::regex_match(threadsNumber, numberRegex) || stoi(threadsNumber) > lines.size() || stoi(threadsNumber) <= 0) throw "Incorrect data";
	return stoi(threadsNumber);
}

void sortFragment(void* fragment)
{
	std::vector<std::string>* lines = (std::vector<std::string>*)fragment;
	std::sort(lines->begin(), lines->end());
}

template<typename T>
struct Sort
{
	static void mergeSort(std::vector<T>& left, std::vector<T>& right, std::vector<T>& bars)
	{
		int nL = left.size();
		int nR = right.size();
		int i = 0, j = 0, k = 0;

		while (j < nL && k < nR)
		{
			if (left[j] < right[k]) {
				bars[i] = left[j];
				j++;
			}
			else {
				bars[i] = right[k];
				k++;
			}
			i++;
		}
		while (j < nL) {
			bars[i] = left[j];
			j++; i++;
		}
		while (k < nR) {
			bars[i] = right[k];
			k++; i++;
		}
	}

	static void sort(std::vector<T>& bar) 
	{
		if (bar.size() <= 1) return;

		int mid = bar.size() / 2;
		std::vector<T> left;
		std::vector<T> right;

		for (size_t j = 0; j < mid; j++)
			left.push_back(bar[j]);
		for (size_t j = 0; j < (bar.size()) - mid; j++)
			right.push_back(bar[mid + j]);

		sort(left);
		sort(right);
		mergeSort(left, right, bar);
	}
};

void createTasks(std::vector<std::string> lines, short threadsAmount, Queue* queue)
{
	bool isEven = lines.size() % threadsAmount == 0;
	int standardStringCapacity = lines.size() / threadsAmount;
	if (!isEven)
		standardStringCapacity = lines.size() / threadsAmount + 1;
	int globalCounter = 0;
	for (int i = 0; i < threadsAmount; i++)
	{
		fragments[i].clear();
		int tmpCounter = 0;
		while (standardStringCapacity != tmpCounter)
		{
			if (globalCounter == lines.size())
				break;
			std::string str = lines[globalCounter];
			if (str != "") {
				fragments[i].push_back(str);
			}
			globalCounter++;
			tmpCounter++;
		}
		Task* newtask = new Task(&sortFragment, (void*)&fragments[i]);
		queue->add(newtask);
	}
}

int main()
{
	try
	{
		lines = readFileLines();
		short threadsCount = inputThreadsNumber();
		fragments.resize(threadsCount);
		Queue* queue = new Queue();
		createTasks(lines, threadsCount, queue);
		lines.clear();
		ThreadPool* threads = new ThreadPool(threadsCount, queue);
		threads->waitAll();
		delete(threads);
		delete(queue);

		for (const auto& fragment : fragments)
		{
			lines.insert(lines.begin(), fragment.begin(), fragment.end());
		}
		Sort<std::string>::sort(lines);

		std::string joinedStr = "";
		for (const auto& str : lines)
		{
			joinedStr += str + "\r\n";
		}
		joinedStr.pop_back();
		joinedStr.pop_back();

		CopyMemory((PVOID)fileProjection, joinedStr.c_str(), strlen(joinedStr.c_str()) * sizeof(char));
		UnmapViewOfFile(fileProjection);
		return 0;
	}
	catch (const char* message)
	{
		std::cout << message << std::endl;
	}
}
