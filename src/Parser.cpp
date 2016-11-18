/* David Swanson CS100 Fall 2016 */

#include "Parser.h"

string Parser::getErrTxt(){
	/* Returns text for parsing errors */
	switch( errNo ){
		/* 0=no error; 1=empty string, not reported */
		case 2:
			return "Check syntax near '&& || ;'\n";
		default:
			return "";
	}
}
int Parser::getErrNo(){
	return errNo;
}
/* Tokenizes input string on connector chars, ignoring 
	second occurrence of same char; trims whitespace.
	Creates vector* t1 which needs to be deleted
	For the input string: cmd1 arg1 && cmd2; Vector will hold:
		cmd1 arg1
		&
		cmd2
		;
*/
vector< string >* Parser::strToV( string in ){/**/
	/* variables:
		list is what to split on
		t1 is target
		curr is index for start of current substr
		skip allows skipping of second char occurrence
		inSub allows grouping of all text within parentheses
		i is needed outside the for loop
	*/
	string list="&|;", pushMe="";
	vector< string >* t1=new vector< string >;
	bool skip=true;
	int n = in.length(), curr=0, stackLevel=0, i;
	/* Parse input string one char at a time */
	for( i = 0; i<n; i++ ){
		if( UT::inStr( in[i], list ) && !stackLevel ){
			/* If here, found a &|; char and not inside parentheses */
			if( !skip ){
				/* If here, it's the first &|; char. So dump the 
					previous part of the string into the vector 
				*/
				pushMe=UT::trm( in.substr( curr, i-curr ) );
				if( pushMe.length() ){//if nothing is there, don't push it
					t1->push_back( pushMe );
				}
				t1->push_back( in.substr( i, 1 ) );//push the current &|; char
				skip=true;//skip the next one
			}
			curr=i+1;//set current so the next dump starts here
		}
		/* All of the below cases set skip to false */
		else if( in[i]=='(' ){//parenthes beginning; ignore &|; chars
			stackLevel++;
			skip=false;
		}
		else if( in[i]==')' ){//parenthes end; stop ignoring &|; chars
			stackLevel--;
			skip=false;
		}
		else {//a regular character; just count and keep parsing
			skip=false;
		}
	}
	/* On loop finish, dump the rest of the string into the vector */
	if( i-curr ){
		pushMe=UT::trm( in.substr( curr, i-curr ) );
		if( pushMe.length() ){//Couple of steps to avoid pushing empty string
			t1->push_back( pushMe );
		}
	}
	/* ; is optional in bash, so add it if not there */
	if( t1->at( t1->size()-1 ) != ";" ){
		t1->push_back( ";" );
	}
	return t1;
}
/* Function populates composite object from string input */
void Parser::populate( RShell* composite ){
	/* First, parse the string and deal with parse errors */
	if( !str.length() ){
		errNo=1;//empty string, false, no message
		return;
	}
	UT::trunc( '#', str );//Get rid of comments
	vector< string >* t1=strToV( str );//tokenize string to vector
	int n = t1->size();
	if( !n || n%2 != 0 ){
		/* If here, user typed something like & & */
		errNo=2;//syntax error
		return;
	}
	/* Variables:
		RShell pointers are local vars to hold commands to be added to composite
		curr is more readable than: t1->at( i )  It's the current &|; char
		cmdTxt is more readable than: t1->at( i-1 )  It's the current command and args
		prev holds curr from previous round
	*/
	RShell* myConnector=NULL;
	RShell* myCommand=NULL;
	string curr="", cmdTxt="", prev=";";
	/* t1 length is multiples of 2 */
	for( int i = 1; i<n; i+=2 ){
		curr=t1->at( i );
		cmdTxt=t1->at( i-1 );
		/* &, | connectors have same behavior, accumulate or dump.
			Two ways to addCommand: 
			1. In object constructor for initial cmd; pushes to first of composite queue
			2. If multiple cmds, uses addCommand() to push them to the composite queue
		*/
		/* First 2 cases are identical except for AND or OR object being created */
		if( curr == "&" ){
			if( curr==prev ){
				if( cmdTxt.length()>2 && cmdTxt[0]=='(' ){
					myCommand=new Composite( cmdTxt.substr( 1, cmdTxt.length()-2 ) );
				}
				else{
					myCommand=new Tester( cmdTxt );
				}
				myConnector->addCommand(  myCommand );
			}
			else{
				if( myConnector ){
					composite->addCommand( myConnector );
				}
				if( cmdTxt.length()>2 && cmdTxt[0]=='(' ){
					myConnector=new AND( new Composite( cmdTxt.substr( 1, cmdTxt.length()-2 ) ) );
				}
				else{
					myConnector=new AND( new Tester( cmdTxt ) );
				}
				
			}
		}
		else if( curr == "|" ){
			if( curr==prev ){
				if( cmdTxt.length()>2 && cmdTxt[0]=='(' ){
					myCommand=new Composite( cmdTxt.substr( 1, cmdTxt.length()-2 ) );
				}
				else{
					myCommand=new Tester( cmdTxt );
				}
				myConnector->addCommand(  myCommand );
			}
			else{
				if( myConnector ){
					composite->addCommand( myConnector );
				}
				if( cmdTxt.length()>2 && cmdTxt[0]=='(' ){
					myConnector=new OR( new Composite( cmdTxt.substr( 1, cmdTxt.length()-2 ) ) );
				}
				else{
					myConnector=new OR( new Tester( cmdTxt ) );
				}
			}
		}
		
		else if( curr == ";" ){
			/* Semicolon behavior different because of input like: cmd && cmd;
				Skip adding new if preceded by a different connector, as that connector
				needs to finish out. If input is like this: "cmd;" then cmd is 
				pushed directly to the composite queue. There is no semicolon class
			*/
			if( curr==prev ){
				if( cmdTxt.length()>2 && cmdTxt[0]=='(' ){
					myCommand=new Composite( cmdTxt.substr( 1, cmdTxt.length()-2 ) );
				}
				else{
					myCommand=new Tester( cmdTxt );
				}
				composite->addCommand(  myCommand );
			}
			else{
				if( myConnector ){
					if( cmdTxt.length()>2 && cmdTxt[0]=='(' ){
						myCommand=new Composite( cmdTxt.substr( 1, cmdTxt.length()-2 ) );
					}
					else{
						myCommand=new Tester( cmdTxt );
					}
					myConnector->addCommand(  myCommand );
					composite->addCommand( myConnector );
					myConnector=NULL;
				}
			}
		}
		prev=curr;
	}
	/* final dump after loop */
	if( myConnector ){
		composite->addCommand( myConnector );
	}
	delete t1;
}
/*
*/