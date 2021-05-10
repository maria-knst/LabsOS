#include "signal.h"
#include<iostream>
#include<sstream>
#include <string.h>

using namespace std;

void killUsingName(char* name){

    string str = "killall "+ (string)name;
    system(const_cast<char *>(str.c_str()));
}

int main(int argc, char* argv[]) {

    const char* name = "PROC_TO_KILL";

    cout << "Killing process started\n";


    if (argc < 1) {
        return 0;
    }

    if (strcmp(argv[1], "i") == 0) {
        cout <<"Hurray ID!!!!\n";
        kill(atoi(argv[2]),SIGKILL);
    }
    if (strcmp(argv[1], "n") == 0) {
        cout << "Hurray NAME!!!!\n";
        killUsingName(argv[2]);
    }
    
    return 0;
}
