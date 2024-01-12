#include <Windows.h>
#include <iostream>

int main()
{
	DWORD pid = GetCurrentProcessId();
	std::cout << "pid: " << pid << std::endl;

	char testStr[] = "Elephant";
	std::cout << "Initial string: " << testStr << std::endl;

	system("pause");
	std::cout << "Result: " << testStr << std::endl;
}