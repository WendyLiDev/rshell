#include<iostream>
#include <string>
using namespace std;
#include "Parser.h"
#include "RShell.h"


void  toCharChar(char *line, char **argv){
	while (*line != '\0') {       /* if not the end of line ....... */ 
		while (*line == ' ' || *line == '\t' || *line == '\n'){
			*line = '\0';     /* replace white spaces with 0    */
			line++;
		}	
		*argv++ = line;          /* save the argument position     */
		while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n'){
			line++;             /* skip the argument until ...    */
		}	
	}
	*argv = '\0';                 /* mark the end of argument list  */
}
string prompt(){
	cout << "$ ";
	string str;
	getline(cin, str);
	return str;
}

int main(){
	//string input="";
	//Composite* C=NULL;
	do{
		//input=prompt();//Get command string from user
		//system( "cls" );
		Composite* C=new Composite( prompt() );//give the string to new composite
		if( !C->execute() ){
			cout << C->getErrTxt() << endl;
		}
		delete C;
	}
	while( true );//let exit command call exit( 0 );
	system("pause");
	return 0;
}

