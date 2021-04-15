#!/bin/sh
gcc -c Number.cpp -o Number.o
ar rcs Number.a Number.o
g++ -g -fPIC -Wall -Werror -Wextra -pedantic Vectored.cpp Number.a -shared -o Vectored.so
gcc -c MyMain.cpp -o MyMain.o
g++ -o MyMain MyMain.o -L Number.a Vector.so
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. 
./MyMain
