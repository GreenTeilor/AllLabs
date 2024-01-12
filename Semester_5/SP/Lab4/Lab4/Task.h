#pragma once

class Task
{
public:
	void(*m_function)(void*);
	void* m_params;

	Task(void(*func)(void*), void* params);
};

