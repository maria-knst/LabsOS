#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
  int fd[2];
  
  string* elements = new string[4];
  elements[0] = "./M";
  elements[1] = "./A";
  elements[2] = "./P";
  elements[3] = "./S";
  pid_t pid;
  
  for(int i = 0; i < 3; i++) {
    
    if(pipe(fd) < 0){
      return 1;
    }
    
    pid = fork();
    if(pid == 0) {
      dup2(fd[1], 1);
      execlp(elements[i].c_str(), elements[i].c_str(), NULL);
     exit(0);
    }

    dup2(fd[0], 0);
    close(fd[1]);
  }

  execlp("./S", "./S", NULL);
  exit(0);
  return 0;
}
