#include "ThreadPool.h"

ThreadPool::ThreadPool(int threadsAmount, Queue* queue) : m_threadsAmount{ threadsAmount }
{

	m_threads = (HANDLE*)malloc(sizeof(HANDLE) * threadsAmount);
	if (m_threads == NULL) throw "Can't allocate memory for threads";
	for (int i = 0; i < threadsAmount; i++)
		m_threads[i] = CreateThread(NULL, 0, &ThreadPool::doWork, (LPVOID)queue, NULL, NULL);
}

void ThreadPool::waitAll()
{
	WaitForMultipleObjects(m_threadsAmount, m_threads, TRUE, INFINITE);
}

DWORD WINAPI ThreadPool::doWork(LPVOID queue)
{
	Queue* tasks = (Queue*)queue;
	while (true) //Not necessary as all lines from file divided the way number of partitions equals number of threads, so each thread will take only one task
	{
		Task* task = tasks->retrieve();
		if (task == NULL)
			ExitThread(0);
		task->m_function(task->m_params); //Calls function sortFragment
	}
	return 0;

}