#ifndef UT_H
#define UT_H
#include<string>
#include<vector>
#include<iostream>
#include<cstring>
using namespace std;

/*	This is the c++ equivalent to PHP static classes
	If there's a function that's general enough to be used in several
	different classes, just give it global scope (protected by a namespace)
*/
namespace UT{//Utility
	/*	Converts vector to array of char arrays to comply with execvp.
		Adds NULL element at end
		These are heap pointers: need to delete
		Use deleteNullTermArray()
		Note: this function sucked to write; hope it works
	*/
	char* const* toNullTermArray( vector< string > &v );

	/* Deallocates the above array by iterating and deleting */
	void deleteNullTermArray( char* const* &argv );
	void printNullTermArray( char* const* argv );
	/* Tokenize string to the referenced vector on 'at' char
		Assume empty vector to start 
	*/
	void tok( char at, string in, vector< string > &t1 );

	/* Truncates referenced string on 'at' char */
	void trunc( char at, string &in );

	/* Kills whitespace before and after text; returns altered string */
	string trm( string in );

	/* Like find, but returns bool */
	bool inStr( char needle, string haystack );

	/* Returns length of longest string in the vector */
	int maxStrLen( vector< string >* v );

	/* Dev tool; Quick display of vector contents */
	void dispV( vector< string >* v );
};

#endif

