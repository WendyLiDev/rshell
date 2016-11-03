#ifndef __SEMICOLON_H__
#define __SEMICOLON_H__

#include "Base.h"
#include "Operator.h"

using namespace std;

class Semicolon: public Operator{
    public:
    //Default constructor
    Semicolon();
    //Semicolon's will always call execute on left pointer, 
    //right pointer should point to 0
    Semicolon(Base* left); 
    bool execute();
    void setRight(Base*);
};

#endif