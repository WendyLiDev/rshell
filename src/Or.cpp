#include "Operator.h"
#include "Or.h"
#include "Base.h"

using namespace std;

Or::Or() {}

Or::Or(Base* l){
    left = l;
}

Or::Or(Base* l, Base* r) {
    left = l;
    right = r;
}

bool Or::execute(){
    if(!(left->execute())){
        right->execute();
        return true;
    }
    else{
        return false;
    }
}

void Or::setRight(Base* r) {
    right = r;
}