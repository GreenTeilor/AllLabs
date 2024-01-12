#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>

#pragma comment(lib, "..\\x64\\Debug\\Dll.lib") //For static import

void StaticImport(DWORD pid);
void DynamicImport(DWORD pid);
void Injection(DWORD pid);

const char* REPLACE_FUNC_NAME = "replaceStringInMemory";

#define TO_REPLACE "Elephant"
#define REPLACE_STR "Firewall"
#define DLL_PATH "Dll.dll"

struct Params {
    DWORD pid;
    char toReplace[256];
    char replaceStr[256];
};

extern "C" _declspec(dllimport) void __stdcall replaceStringInMemory(Params * params);
typedef void(__cdecl* TReplaceMemoryFunc)(Params* params); //Used as pointer on function replaceStringInMemory


int main()
{
    DWORD pid = GetCurrentProcessId();
    char data1[] = TO_REPLACE;
    std::cout << "pid: " << pid << "\n";

    std::cout << "Static Import" << "\n";
    StaticImport(pid);
    std::cout << "String to replace: " << TO_REPLACE << "; New string: " << data1 << "\n";

    std::cout << "Dynamic Import" << "\n";
    DynamicImport(pid);
    std::cout << "String to replace: " << REPLACE_STR << "; New string: " << data1 << "\n";

    std::cout << "Input another process pid: ";
    DWORD anotherProcessPid;
    std::cin >> anotherProcessPid;
    Injection(anotherProcessPid);
    return 0;
}

void StaticImport(DWORD pid)
{
    replaceStringInMemory(new Params{ pid, TO_REPLACE, REPLACE_STR });
}

void DynamicImport(DWORD pid)
{
    HMODULE dll = LoadLibraryA(DLL_PATH); //Load dll into address space of calling process
    TReplaceMemoryFunc func = (TReplaceMemoryFunc)GetProcAddress(dll, REPLACE_FUNC_NAME); //Get function address from dll and write into function pointer
    func(new Params{ pid, REPLACE_STR, TO_REPLACE });
    FreeLibrary(dll); //Free dll and decrease it's reference counter, if counter equals zero, dll is unloaded from address space of calling process
}

void Injection(DWORD pid) {

    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid); //Get access to process with given pid (get process object)
    LPVOID loadLibPtr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA"); //Get pointer at "LoadLibraryA" from "kernel32.dll"(GetModuleHandle - retrieves module handle)

    LPVOID dllPathPtr = VirtualAllocEx(process, NULL, strlen(DLL_PATH) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); //Allocate memory for library name
    WriteProcessMemory(process, dllPathPtr, DLL_PATH, strlen(DLL_PATH) + 1, NULL); //Write library name in process memory

    HANDLE thread = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibPtr/*Pointer at LoadLibraryA, which loads the dll*/, dllPathPtr, 0, NULL); //Create remote thread
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);

    LPVOID replaceFuncPointer = (LPVOID)GetProcAddress(GetModuleHandleA(DLL_PATH), REPLACE_FUNC_NAME); //Get replace function address

    Params params = { pid, TO_REPLACE, REPLACE_STR };
    LPVOID paramsPtr = VirtualAllocEx(process, NULL, sizeof(params), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); //Allocate memory for params
    WriteProcessMemory(process, paramsPtr, &params, sizeof(params), NULL); //Write params into memory

    thread = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE)replaceFuncPointer, paramsPtr, 0, NULL);
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);

    CloseHandle(process);
}

