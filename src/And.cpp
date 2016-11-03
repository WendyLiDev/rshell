#include "Operator.h"
#include "And.h"

And::And(): Operator() {}

And::And(Base* left): Operator() {
    this->left = left;
}

And::And(Base* left, Base* right): Operator() {
    this->left = left;
    this->right = right;
}

bool And::execute(){
    if(left->execute()){
        right->execute();
        return true;
    }
    else{
        return false;
    }
}

void And::setRight(Base* r) {
    this->right = r;
}