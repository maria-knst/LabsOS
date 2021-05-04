#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include<iostream>
#include<vector>
#include<sstream>
#include <string.h>
#include <windows.h>
#include <winbase.h>
#include <process.h>
#include <Tlhelp32.h>

using namespace std;

void killUsingID(int id){
	HANDLE handle = OpenProcess(PROCESS_TERMINATE, FALSE, id);
	if (NULL != handle) {
		TerminateProcess(handle, 0);
		CloseHandle(handle);
	}
}


BOOL TerminateMyProcess(DWORD dwProcessId, UINT uExitCode)
{
    DWORD dwDesiredAccess = PROCESS_TERMINATE;
    BOOL  bInheritHandle = FALSE;
    HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
    if (hProcess == NULL)
        return FALSE;

    BOOL result = TerminateProcess(hProcess, uExitCode);

    CloseHandle(hProcess);

    return result;
}
BOOL GetProcessList(const string name)
{
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        return(FALSE);
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);  
        return(FALSE);
    }

    do
    {
        string str(pe32.szExeFile);

        if (str == (name + ".exe"))
        {
            TerminateMyProcess(pe32.th32ProcessID, 1);
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return(TRUE);
}


int main(int argc, char* argv[]) {

    const CHAR* name = "PROC_TO_KILL";
    const CHAR* value = "notepad";

    const DWORD buffSize = 65535;   
    char buffer[buffSize];
    cout << "Killing process started\n";

   /* GetEnvironmentVariable(name, buffer, buffSize);
    std::stringstream ss(buffer);
    while (ss.getline(reinterpret_cast<char*>(&buffer), buffSize, ',')) {
        GetProcessList(buffer);
    }*/

    if (argc < 1) {
        return 0;
    }

    if (strcmp(argv[1], "i") == 0) {
        cout <<"Hurray ID!!!!\n";
        killUsingID(atoi(argv[2]));
    }
    if (strcmp(argv[1], "n") == 0) {
        cout << "Hurray NAME!!!!\n";
        GetProcessList(argv[2]);
    }


   return 0;
}