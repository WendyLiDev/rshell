/* David Swanson CS100 Fall 2016 */
#ifndef PARSER_H
#define PARSER_H
#include "../header/RShell.h"
#include "../header/UT.h"

class RShell;

class Parser{
	public:
		Parser( string setStr ) : str( setStr ), errNo( 0 ) {}
		void populate( RShell* composite );
		int getErrNo();
		string getErrTxt();
	protected:
		string str;
		int errNo;		//integer error code
		vector< string >* strToV( string in );
};

#endif