#ifndef __BASE_H__
#define __BASE_H__

using namespace std;

class Base{
    public:
    //Default Constructor
    Base() { };
    //Pure virtual function
    virtual bool execute() = 0;
};

#endif