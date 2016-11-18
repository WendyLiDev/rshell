/* David Swanson CS100 Fall 2016 */

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
	/* q may hold objects of AND, OR, Cmd or Composite */
	int n = q.size();
	bool good=true;
	for( int i = 0; i<n; i++ ){
		good &= q.at( i )->execute();
	}
	return good;
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
			// cout << "end OR execute: true result" << endl;
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
	//vector< string > t1;
	//UT::tok( ' ', cmd, t1 );
	//char* const* argv=UT::toNullTermArray( t1 );
	//UT::printNullTermArray( argv );
	
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
			// perror( "Command exited with status > 0" );
		}
		//cout << "Parent process: status=" << cmd << ", " << arg << " exited with status " << status << endl;
	}
	//UT::deleteNullTermArray( argv );
	return ( status == 0 );
}

Tester::Tester( string setStr ){
	/* Tester parses command text looking for [] or 'test' 
		
	*/
	vector< string > t1;
	if( 
		( prepTest1( setStr, t1 ) || prepTest2( setStr, t1 ) ) &&
			prepTest3( t1 )
		){
		testing= true;
		//cout << "testType=" << testType << endl;
		//cout << "fileName=" << fileName << endl;
		C=NULL;
	}
	else{
		/* If here, no test; instantiate Cmd object and pass execution to that 
			based on bool testing var
		*/
		C=new Cmd( setStr );
		testing=false;
	}
}
Tester::~Tester(void){
	if( C ){
		delete C;
	}
}
bool Tester::prepTest1( string &in, vector< string > &t1 ){
	/* Checks for test brackets; if so, tokenizes string to vector */
	string trimmed=UT::trm( in, '[', ']' );
	if( trimmed.length() != in.length() ){
		in=trimmed;
		UT::tok( ' ', '"', '"', trimmed, t1 );
		return true;
	}
	return false;
}
bool Tester::prepTest2( string &in, vector< string > &t1 ){
	/* Tokenizes string to vector and checks for keyword 'test' */
	UT::tok( ' ', '"', '"', in, t1 );
	int n=t1.size();
	for( int i = 0; i<n; i++ ){
		if( t1.at( i ) == "test" ){
			t1.erase( t1.begin() + i );
			return true;
		}
	}
	return false;
}
bool Tester::prepTest3( vector<string> &t1 ){
	/* Checks for args -e -f -d. Sets test type and filename */
	int n=t1.size();
	testType=' ';
	fileName="";
	for( int i = 0; i<n; i++ ){
		if( t1.at( i ) == "-e" ){
			testType='e';
		}
		else if( t1.at( i ) == "-f" ){
			testType='f';
		}
		else if( t1.at( i ) == "-d" ){
			testType='d';
		}
		else{
			fileName=UT::trm( t1.at( i ), '"', '"' );
		}
	}
	return testType && fileName.length();
}
/* d, e, f execute based on testType, if any */
bool Tester::d() {
	const char *path=fileName.c_str();
 	struct stat s;
	return !stat( path,&s ) && ( s.st_mode & S_IFDIR );
}
bool Tester::e() {
	const char *path=fileName.c_str();
   	 struct stat s;
	return !stat( path,&s );
}
bool Tester::f(){
	const char* path=fileName.c_str();
	struct stat s;
	return !stat( path, &s ) && ( s.st_mode & S_IFREG );
}
bool Tester::execute(){
	if( !testing ){
		//cout << "not testing" << endl;
		return C->execute();
	}
	bool result=( testType=='d' && d() ) ||
				( testType=='e' && e() ) ||
				( testType=='f' && f() );
	if( result){
		cout << "(True)" << endl;
		return true;
	}
	else{
		cout << "(False)" << endl;
		return false;
	}
}
void Tester::addCommand( RShell* newConnector ){
	C->addCommand( newConnector );
}