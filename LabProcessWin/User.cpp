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
#include <stdlib.h>

using namespace std;

int setenv(const char* name, const char* value, int overwrite)
{
    int errcode = 0;
    if (!overwrite) {
        size_t envsize = 0;
        errcode = getenv_s(&envsize, NULL, 0, name);
        if (errcode || envsize) return errcode;
    }
    return _putenv_s(name, value);
}

int main() {

    const CHAR* name = "PROC_TO_KILL";
    const CHAR* value = "notepad";
    const CHAR* deletevalue = "";

    cout << "notepad ID is: \n";
    system("tasklist | find \"notepad.exe\"");

    setenv(name,deletevalue,0);
    string str = "D:\\OC\\LabProccesW\\Debug\\Killer.exe n notepad";
    system(str.c_str());

    //string str1 = "D:\\OC\\LabProccesW\\Debug\\Killer.exe i чиселко";
    //system(str1.c_str());
    
    setenv(name, deletevalue, 0);

    cout << "notepad ID is: \n";
    system("tasklist | find \"notepad.exe\"");


	return 0;
}