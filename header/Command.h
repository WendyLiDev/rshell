#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <string>
#include "Base.h"

using namespace std;

class Command : public Base{
    private:
    string input;
    
    public:
    Command();
    Command(string&);
    bool execute();
};

#endif