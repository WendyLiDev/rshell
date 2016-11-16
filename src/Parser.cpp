#include "Parser.h"

string Parser::getErrTxt(){
	/* Returns text for parsing errors */
	switch( errNo ){
		case 2:
			return "Check syntax near '&& || ;'";
		default:
			return "";
	}
}
int Parser::getErrNo(){
	return errNo;
}
vector< string >* Parser::strToV( string in ){
	string list="&|;", pushMe="";
	vector< string >* t1=new vector< string >;
	bool skip=true, inSub=false;
	int n = in.length(), curr=0, i;
	for( i = 0; i<n; i++ ){
		if( UT::inStr( in[i], list ) && !inSub ){
			//cout << "yes..."  << i << " skip="  << skip << ": " << in[i]<<endl;
			if( !skip ){
				//cout << "dump "  << in.substr( curr, i-curr ) <<endl;
				pushMe=UT::trm( in.substr( curr, i-curr ) );
				if( pushMe.length() ){
					t1->push_back( pushMe );
				}
				t1->push_back( in.substr( i, 1 ) );
				skip=true;
			}
			curr=i+1;
		}
		else if( in[i]=='('){
			inSub=true;
			skip=false;
		}
		else if( in[i]==')'){
			inSub=false;
			skip=false;
		}
		else {
			//cout << "no..."  << i << " skip="  << skip << ": " << in[i]<<endl;
			skip=false;
		}
	}
	if( i-curr ){
		pushMe=UT::trm( in.substr( curr, i-curr ) );
		if( pushMe.length() ){
			t1->push_back( pushMe );
		}
	}
	if( t1->at( t1->size()-1 ) != ";" ){
		t1->push_back( ";" );
	}
	//cout << "Initial:" << endl;
	//UT::dispV( t1 );
	return t1;
}
void Parser::populate( RShell* composite ){
	/* Function populates composite object from string input */
	if( !str.length() ){
		errNo=1;//empty string, false, no message
		return;
	}
	UT::trunc( '#', str );
	vector< string >* t1=strToV( str );
	int n = t1->size();
	if( !n || n%2 != 0 ){
		//cout << "failed n%2" << endl;
		errNo=2;//syntax error
		return;
	}
	RShell* myConnector=NULL;
	RShell* myCommand=NULL;
	string curr="", prev=";", cmdTxt="";
	/* t1 length is multiples of 2 */
	for( int i = 1; i<n; i+=2 ){
		curr=t1->at( i );
		cmdTxt=t1->at( i-1 );
		/* &, | connectors have same behavior, accumulate or dump.
			Two ways to addCommand: in object constructor for initial cmd
			If multiple cmds, uses addCommand() to push them to the composite queue
		*/
		if( curr == "&" ){
			if( curr==prev ){
				if( cmdTxt.length()>2 && cmdTxt[0]=='(' ){
					myCommand=new Composite( cmdTxt.substr( 1, cmdTxt.length()-2 ) );
				}
				else{
					myCommand=new Cmd( cmdTxt );
				}
				myConnector->addCommand(  myCommand );
			}
			else{
				if( myConnector ){
					composite->addCommand( myConnector );
				}
				myConnector=new AND( new Cmd( t1->at( i-1 ) ) );
			}
		}
		else if( curr == "|" ){
			if( curr==prev ){
				if( cmdTxt.length()>2 && cmdTxt[0]=='(' ){
					myCommand=new Composite( cmdTxt.substr( 1, cmdTxt.length()-2 ) );
				}
				else{
					myCommand=new Cmd( cmdTxt );
				}
				myConnector->addCommand(  myCommand );
			}
			else{
				if( myConnector ){
					composite->addCommand( myConnector );
				}
				myConnector=new OR( new Cmd( t1->at( i-1 ) ) );
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
					myCommand=new Cmd( cmdTxt );
				}
				composite->addCommand(  myCommand );
			}
			else{
				if( myConnector ){
					if( cmdTxt.length()>2 && cmdTxt[0]=='(' ){
						myCommand=new Composite( cmdTxt.substr( 1, cmdTxt.length()-2 ) );
					}
					else{
						myCommand=new Cmd( cmdTxt );
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

