#ifndef __OR_H__
#define __OR_H__

#include"Operator.h"

using namespace std;

class Or: public Operator {
    public:
    Or();
    Or(Base*);
    Or(Base*, Base*);
    bool execute();
    void setRight(Base*);
};

#endif