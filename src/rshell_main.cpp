/* David Swanson CS100 Fall 2016 */

#include<iostream>
#include <string>
using namespace std;
#include "../header/Parser.h"
#include "../header/RShell.h"

string prompt(){
	// cout << "$ ";
	string str;
	getline(cin, str);
	return str;
}

int main( int argc, char* argv[] ){
	/* Accept command line args or console input:
		First check for args
	*/
	if ( argc > 1 ){
		//cout << UT::cmdLineToStr( argc, argv ) << endl;
		Composite* C=new Composite(  UT::cmdLineToStr( argc, argv ) );
		if( !C->execute() ){
			cout << C->getErrTxt();
		}
		delete C;
		//system( "pause" );
	}
	else{
		do{
			/* Get user input and send it to new Composite */
			Composite* C=new Composite( prompt() );
			if( !C->execute() ){
				cout << C->getErrTxt();
			}
			delete C;
		}
		while( true );//let exit command call exit( 0 );
	}
	return 0;
}
