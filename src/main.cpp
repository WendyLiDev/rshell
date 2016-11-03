// main.cpp 
// Assignment 2 cs100 
// November 2, 2016

#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <iterator>

using namespace std;
using namespace boost;

#include "Base.h"
#include "Command.h"
#include "Operator.h"
#include "Semicolon.h"
#include "Or.h"
#include "And.h"

void buildTree(vector<string> parsed);

int main(){
    
    //parses the input into seperate strings stored in s
    string input = "ls -a; echo hello && mkdir test || echo world; git status";
    vector<string> s;
    typedef tokenizer<char_separator<char> > tokenizer;
    char_separator<char> sep("", ";#&|");
    tokenizer tokens(input, sep);
    for (tokenizer::iterator tok_iter = tokens.begin();tok_iter != tokens.end(); ++tok_iter){
        s.push_back(*tok_iter);
    }
    
    //rewriting the vector of strings to have "||"" and "&&"" 
    vector<string> parsed;
    for(unsigned i = 0; i < s.size()-1; i++){ 
        if( (s.at(i).compare(s.at(i+1))==0) && (s.at(i).compare("|") || s.at(i).compare("&")) ){
            string temp = s.at(i)+s.at(i);
            parsed.push_back(temp);
            i=i+1;
        }
        else{
            parsed.push_back(s.at(i));
        }
    }
    parsed.push_back(s.at(s.size()-1));
    
    //prints out the contents of parsed
    for(unsigned i = 0; i < parsed.size(); i ++){
        cout << parsed.at(i) << endl;
    }
    
    buildTree(parsed);
    
    return 0;
}

void buildTree(vector<string> parsed){
    //-------------------------BUILD THE TREE---------------------------
    
    bool reachedHash = false;
    Base* prev = 0; //Base pointer holds the address of the previous object created for next obj to point to the previous
    Operator* prevOp = 0;
    for(unsigned i = 0; (i < parsed.size())&&!reachedHash; i++){
        if(parsed.at(i).compare("#")){ //checks if parsed at some index i is a comment
            reachedHash = true;
            return;
        }
        //deals with case of last string in parsed
        if(i == parsed.size()-1){
            prev->execute();
            return;
        }
        if(parsed.at(i).compare(";")){
            //create semicolon
            Operator* s = new Semicolon(prev);
            s->execute();
            prev = 0;
        }
        else if(parsed.at(i).compare("||")){
            //create Or
            Operator* o = new Or(prev);
            prev = o;
            prevOp = o;
        }
        else if(parsed.at(i).compare("&&")){
            //create And
            Operator* a = new And(prev); //set a's Base* left to prev
            prev = a;
            prevOp = a;
        }
        else{
            //create Command and set member input to parsed.at(i)
            if(prev==0){
                Base* c = new Command(parsed.at(i));
                prev = c;
            }
            else{
                Base* c = new Command(parsed.at(i));
                prevOp->setRight(c);
            }
        }
    }
    return;
}