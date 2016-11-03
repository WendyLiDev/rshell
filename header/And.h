#ifndef __AND_H__
#define __AND_H__

#include"Operator.h"

using namespace std;

class And: public Operator{
    public:
    And();
    And(Base* right);
    And(Base* right, Base* left);
    bool execute();
    void setRight(Base*);
};

#endif