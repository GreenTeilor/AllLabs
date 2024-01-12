#include "Task.h"

Task::Task(void(*func)(void*), void* params) : m_function{ func }, m_params{ params }
{

}