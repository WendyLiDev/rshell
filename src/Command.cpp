#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

#include "Command.h"

using namespace std;


Command::Command(){ }

Command::Command(string& s){
    input = s;
}

bool Command::execute(){
    //execvp here
    // pid_t pid = fork();
    return false;
}