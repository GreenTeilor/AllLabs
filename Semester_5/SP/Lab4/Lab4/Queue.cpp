#include "Queue.h"

Queue::Queue() : m_tasks{}
{
	InitializeCriticalSection(&m_mutex); //May fail only in Windows XP or Windows server 2003 in low memory situations (msdn)
	//Default spin count - 0, and it's good: (c) You can improve performance significantly by choosing a small spin count for a critical section of short duration. (stackoverflow.com)
}

Task* Queue::retrieve()
{
	EnterCriticalSection(&m_mutex);

	if (isEmpty())
	{
		LeaveCriticalSection(&m_mutex);
		return NULL;
	}

	Task* task = m_tasks.back();
	m_tasks.pop_back();

	LeaveCriticalSection(&m_mutex);

	return task;
}

void Queue::add(Task* task)
{
	EnterCriticalSection(&m_mutex);

	m_tasks.push_back(task);

	LeaveCriticalSection(&m_mutex);
}

bool Queue::isEmpty()
{
	return m_tasks.empty();
}

Queue::~Queue()
{
	DeleteCriticalSection(&m_mutex);
}