#pragma once

#include "Queue.h"

class ThreadPool
{
private:
	HANDLE* m_threads;
	int m_threadsAmount;
	static DWORD WINAPI doWork(LPVOID queue);

public:
	ThreadPool(int threadsAmount, Queue* queue);
	void waitAll();

};
