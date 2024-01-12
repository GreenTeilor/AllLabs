#pragma once

#include <windows.h>
#include "Task.h"
#include <vector>

class Queue
{
private:
	std::vector<Task*> m_tasks;
	CRITICAL_SECTION m_mutex;

public:
	Queue();
	Task* retrieve();
	void add(Task* task);
	bool isEmpty();
	~Queue();

};

