#include <stdlib.h>
#include<iostream>
#include<vector>
#include<sstream>
#include <string.h>

using namespace std;


int main() {

    const char* name = "PROC_TO_KILL";
    char* value = "firefox";
    const char* deletevalue = "";


    setenv(name,value,0);

    //system("g++ ~/CLionProjects/LabProcessL/Killer.cpp -o killer && ./killer n firefox");
    system("g++ ~/CLionProjects/LabProcessL/Killer.cpp -o killer && ./killer i 7613");

    setenv(name, deletevalue, 0);



    return 0;
}
