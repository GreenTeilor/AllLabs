#pragma once
#include <Windows.h>

#ifdef FUNCTION_EXPORTS
#define FUNCTION_API __declspec(dllexport)
#else
#define FUNCTION_API __declspec(dllimport)
#endif

struct Params {
	DWORD pid;
	char toReplace[256];
	char replaceStr[256];
};

extern "C" FUNCTION_API void replaceStringInMemory(Params* params);