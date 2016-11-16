#include "UT.h"

char* const* UT::toNullTermArray( vector< string > &v ){
	int i, n=v.size();
	char** argv = new char*[ n+1 ];
	for ( i = 0; i<n; i++ ){
		//cout << "load: " << v.at(i).c_str() << endl;
        argv[i] = new char[ v.at(i).length() + 1];
		strcpy( argv[i], v.at(i).c_str() );
	}
	argv[i]=NULL;
	return argv;
}
void UT::printNullTermArray( char* const* argv ){
	cout << "printNullTermArray:" << endl;
	for ( int i = 0; true; i++ ){
		if( argv[i] == NULL ){
			cout << endl ;//<< "break on null" << endl;
			break;
		}
		for ( int j = 0; true; j++ ){
			if( argv[i][j] == 0 ){
				cout << endl;//": endline on null" << endl;
				break;
			}
			cout << argv[i][j];
		}
	}
	cout << "end printNullTermArray:" << endl;
}
void UT::deleteNullTermArray( char* const* &argv ){
	for ( int i = 0; true; i++ ){
		if( argv[i] == NULL ){
			break;
		}
		delete argv[i];
	}
	delete argv;
	argv=NULL;
}
void UT::trunc( char at, string &in ){
	int n=in.length();
	for( int i = 0; i<n; i++ ){
		if( in[i]==at ){
			in=in.substr( 0, i );
			return;
		}
	}
}
string UT::trm( string in ){
	int n=in.length(), top=-1, end=-1;
	for( int i = 0, j=n-1; i<n; i++, j-- ){
		if( in[i]!=' ' && top==-1 ){
			top=i;
		}
		if( in[j]!=' ' && in[i]!='\n' && end==-1 ){
			end=j+1;
		}
	}
	return ( top!=-1 && end!=-1 )? in.substr( top, end-top ) : "";
}
bool UT::inStr( char needle, string haystack ){
	//cout << "instring " << needle <<endl;
	int n=haystack.length();
	for( int i = 0; i<n; i++ ){
		if( haystack[i]==needle ){
			return true;
		}
	}
	return false;
}
void UT::tok( char at, string in, vector< string > &t1 ){
	string list="&|;", pushMe="";
	bool skip=true;
	int n = in.length(), curr=0, i;
	for( i = 0; i<n; i++ ){
		if( in[i]==at ){
			//cout << "yes..."  << i << " skip="  << skip << ": " << in[i] <<endl;
			if( !skip ){
				pushMe=trm( in.substr( curr, i-curr ) );
				//cout << "dump "  << pushMe << " or " << pushMe.c_str() <<endl;
				if( pushMe.length() ){
					t1.push_back( pushMe );
				}
				skip=true;
			}
			curr=i+1;
		}
		else {
			//cout << "no..."  << i << " skip="  << skip << ": " << in[i]<<endl;
			skip=false;
		}
	}
	if( !skip  && i-curr ){
		pushMe=trm( in.substr( curr, i-curr ) );
		//cout << "last dump "  << pushMe << endl;
		if( pushMe.length() ){
			t1.push_back( pushMe );
		}
	}
	//cout << "Initial:" << endl;
	//dispV( &t1 );
}
int UT::maxStrLen( vector< string >* v ){
	unsigned int n=v->size(), max=0;
	for( unsigned int i = 0; i<n; i++ ){
		if( v->at( i ).length() > max ){
			max=v->at( i ).length();
		}
	}
	return max;
}
void UT::dispV( vector< string >* v ){/* For dev */
	int n=v->size();
	for( int i = 0; i<n; i++ ){
		cout << ">>>" << v->at( i ) << "<<<" << endl;
	}
}
