
/* David Swanson CS100 Fall 2016 */

#ifndef RSHELL_H
#define  RSHELL_H
#include<iostream>
#include <string>
#include <vector>
#include <unistd.h>//Linux
//#include <sys/types.h>//not needed?
#include <sys/wait.h>//Missing on my system
#include <errno.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;
#include "../header/Parser.h"

class Parser;
/* Abstract Base Class */
class RShell{
	public:
		virtual bool execute()=0;
		virtual void addCommand( RShell* newCmd )=0;
		virtual ~RShell(){}
};
/* Leaf class to implement commands */
class Cmd : public RShell{
	public:
		Cmd( string setCmd );
		~Cmd(){}
		bool execute();
		void addCommand( RShell* newCmd );
		string getErrTxt(){return "";}
	protected:
		string cmd;
};
/* Abract parent for AND, OR */
class Connector : public RShell{
	public:
		~Connector(void);
		virtual bool execute()=0;
		void addCommand( RShell* newCmd );
	protected:
		vector< RShell* > q;
};
/* Implementations of Connector */
class AND : public Connector{
	public:
		AND( RShell* newCmd );
		bool execute();
};
class OR : public Connector{
	public:
		OR( RShell* newCmd );
		bool execute();
};

/* Composite: concrete class that runs the shell */
class Composite : public RShell{
	public:
		//Composite();
		Composite( string setStr );
		~Composite(void);
		bool execute();
		void addCommand( RShell* newCmd );
		string getErrTxt();
	protected:
		vector< RShell* > q;
		Parser* P;
};
/* Tester: decorator pattern inserted just above any Cmd object */
class Tester : public RShell{
	public:
		Tester( string setStr );
		~Tester(void);
		bool execute();
		void addCommand( RShell* newCmd );
	protected:
		RShell* C;
		bool testing;
		char testType;
		string fileName;
		bool prepTest1( string &in, vector< string > &t1 );
		bool prepTest2( string &in, vector< string > &t1 );
		bool prepTest3( vector< string > &t1 );
		bool d();
		bool e();
		bool f();
};

/*
Is file and not directory:
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
bool f(){
	const char *path=fileName.c_str();
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG( path_stat.st_mode )>0;
}
*/

#endif
