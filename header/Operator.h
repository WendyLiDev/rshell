#ifndef __OPERATOR_H__
#define __OPERATOR_H__

#include "Base.h"

using namespace std;

class Operator: public Base{
    protected:
    Base* left;
    Base* right;
    
    public:
    Operator(); //default sets left and right to point to 0
    Operator(Base*, Base*);
    bool execute();
    virtual void setRight(Base*) = 0;
};

#endif