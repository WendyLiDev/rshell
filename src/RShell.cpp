#include "RShell.h"
#include "Parser.h"

Composite::Composite( string setStr ){
	P=new Parser( setStr );
	P->populate( this );
}
Composite::~Composite(void){
	int n = q.size();
	for( int i = 0; i<n; i++ ){
		delete q[i];
	}
	delete P;
}
bool Composite::execute(){
	/* Returns false on parse error */
	if( P->getErrNo()>1 ){
		return false;
	}
	/* q may hold objects of AND, OR, and Cmd */
	int n = q.size();
	//cout << "Composite numCmds=" << n << endl;
	for( int i = 0; i<n; i++ ){
		q.at( i )->execute();
	}
	return true;
}
void Composite::addCommand( RShell* newConnector ){
	q.push_back( newConnector );
}
string Composite::getErrTxt(){
	return P->getErrTxt();
}

Connector::~Connector(void){
	int n = q.size();
	for( int i = 0; i<n; i++ ){
		delete q[i];
	}
}
void Connector::addCommand( RShell* newCommand ){
	q.push_back( newCommand );
}
/* Connectors may be initialized with a command,
or may add commands later using addCommand() 
*/
AND::AND( RShell* newCmd ){
	q.push_back( newCmd );
}
OR::OR( RShell* newCmd ){
	q.push_back( newCmd );
}
bool AND::execute(){
	/* Follows 'short circuit rules for evaluation' 
		Any false quits loop and returns false
	*/
	//cout << "AND execute" << endl;
	int n = q.size();
	for( int i = 0; i<n; i++ ){
		if( !q.at( i )->execute() ){
			return false;
		}
	}
	//cout << "end AND execute" << endl;
	return true;
}
bool OR::execute(){
	/* Follows 'short circuit rules for evaluation' 
		Any true quits loop and returns true
	*/
	//cout << "OR execute" << endl;
	int n = q.size();
	for( int i = 0; i<n; i++ ){
		if( q.at( i )->execute() ){
			//cout << "end OR execute: true result" << endl;
			return true;
		}
	}
	//cout << "end OR execute" << endl;
	return false;
}

Cmd::Cmd( string setCmd ) : cmd( setCmd ){}
void Cmd::addCommand( RShell* newCommand ){}
bool Cmd::execute(){
	//cout << "Cmd execute: cmd=" << cmd << endl;
	if( cmd=="exit" || cmd=="quit" ){
		exit( 0 );
	}
	int status=0;
	vector< string > t1;
	UT::tok( ' ', cmd, t1 );
	char* const* argv=UT::toNullTermArray( t1 );
	//UT::printNullTermArray( argv );
	
	///*
	pid_t pid = fork();
	
	if (pid == -1){
		perror( "Could not start child process" );
	}
	//If here, the process has split in two, with parent and child both running this code.
	//Check id to see which is which
	else if (pid == 0){//This is the child process; run the child task
		vector< string > t1;
		UT::tok( ' ', cmd, t1 );
		char* const* argv=UT::toNullTermArray( t1 );
		//UT::printNullTermArray( argv );
		execvp( *argv, argv );//execvp lets you specify just the file name; execv wants the whole path
		UT::deleteNullTermArray( argv );
		_exit( 1 );
		// exec only returns on error; else when the called program finishes, the child is terminated
		//automatically and the called program's exit status shows up in the parent's waitpid
	}
	else {//This is the parent process; wait for child
		waitpid( pid, &status, 0 );
		if( status ){
			perror( "Command exited with status > 0" );
		}
		//cout << "Parent process: status=" << cmd << ", " << arg << " exited with status " << status << endl;
	}
	//*/
	return ( status == 0 );
}

Tester::Tester( string setStr ){
	testing=false;
	composite=new Composite( setStr );
}
Tester::~Tester(void){
	delete composite;
}
bool Tester::parse1( string &in ){
	string trimmed=UT::trm( in );
	if( trimmed.length() > 4 && trimmed.substr( 0,4 )=="test" ){
		in=UT::trm( trimmed.substr( 4 ) );
		return true;
	}
	return false;
}
bool Tester::parse2( string &in ){
	string trimmed=UT::trm( in );
	if( trimmed.length() > 1 && trimmed[1]=='[' ){
		in=UT::trm( trimmed.substr( 4 ) );
		return true;
	}
	return false;
}
bool Tester::execute(){
	if( !testing ){
		return composite->execute();
	}
	/* Returns false on parse error */
	string err=composite->getErrTxt();
	if( err.length() || !composite->execute() ){
		cout << "(False)" << endl;
		return false;
	}
	cout << "(True)" << endl;
	return true;
}
void Tester::addCommand( RShell* newConnector ){
	composite->addCommand( newConnector );
}
string Tester::getErrTxt(){
	return composite->getErrTxt();
}
