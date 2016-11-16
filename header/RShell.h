#ifndef RSHELL_H
#define  RSHELL_H
#include<iostream>
#include <string>
#include <vector>
#include <unistd.h>//Linux
#include <sys/types.h>
#include <sys/wait.h>//Missing on my system
#include <errno.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cstring>
using namespace std;
#include "Parser.h"

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
class Tester : public RShell{
	public:
		Tester( string setStr );
		~Tester(void);
		bool execute();
		void addCommand( RShell* newCmd );
		string getErrTxt();
	protected:
		Composite* composite;
		bool testing;
		bool parse1( string &in );
		bool parse2( string &in );
};
#endif
