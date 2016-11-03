#include "Operator.h"
#include "Semicolon.h"

using namespace std;

Semicolon::Semicolon() { }

Semicolon::Semicolon(Base*) {
    this->left = left;
}

bool Semicolon::execute(){
    return left->execute();
}

void Semicolon::setRight(Base *r){
    right = r;
    return;
}
