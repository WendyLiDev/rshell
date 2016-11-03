#include "Operator.h"

using namespace std;

Operator::Operator(){
    left = 0;
    right = 0;
}

Operator::Operator(Base* left, Base* right){
    this->left = left;
    this->right = right;
}

