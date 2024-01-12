#include "pch.h"
#include <Windows.h>
#include <cstdlib>
#include <iostream>
#include "function.h"

void replaceStringInMemory(Params* params)
{
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, params->pid);
	if (process)
	{
		size_t toReplaceStrLen = strlen(params->toReplace);
		SYSTEM_INFO systemInfo;
		MEMORY_BASIC_INFORMATION memoryInfo;
		GetSystemInfo(&systemInfo);
		char* ptr = 0;
		SIZE_T bytesRead = 0;
		while (ptr < systemInfo.lpMaximumApplicationAddress) //lpMaximumApplicationAddress - pointer to the highest memory address accessible to applications and DLLs
		{
			int size = VirtualQueryEx(process, ptr, &memoryInfo, sizeof(MEMORY_BASIC_INFORMATION));
			if (size == sizeof(MEMORY_BASIC_INFORMATION)) //memoryInfo shell contain MEMORY_BASIC_INFORMATION structure with info about the specified page range
			{
				if ((memoryInfo.State == MEM_COMMIT) && memoryInfo.AllocationProtect == PAGE_READWRITE)
				{
					ptr = (char*)memoryInfo.BaseAddress;
					BYTE* buffer = (BYTE*)malloc(memoryInfo.RegionSize);
					if (ReadProcessMemory(process, ptr, buffer, memoryInfo.RegionSize, &bytesRead)) //Here read memory(ptr - pointer to the base address in the specified process from which to read, 
					//buffer - pointer to a buffer that receives the contents from the address space of the specified process, bytesRead - number of bytes read)
					{
						for (size_t i = 0; i < (bytesRead - toReplaceStrLen); ++i) //Cycle trough all bytes
						{
							if (memcmp(params->toReplace, &buffer[i], toReplaceStrLen) == 0) //If str is found
							{
								char* replaceMemory = ptr + i; //Add to base address position, where strToReplace was found
								for (int j = 0; (j < (strlen(params->replaceStr)) && j < (strlen(params->toReplace))); j++)
								{
									replaceMemory[j] = params->replaceStr[j];
								}
								replaceMemory[strlen(params->replaceStr)] = 0;
							}
						}
					}
					free(buffer);
				}
			}
			ptr += memoryInfo.RegionSize;
		}

		CloseHandle(process);
	}
}