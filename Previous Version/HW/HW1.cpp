
/*   ALLAH is Almighty.....  */
/*   https://www.cs.uic.edu/~troy/spring01/eecs473/mp1.html   */

#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define pi                                acos( -1.0 )
#define rep( i, a, n )                    for ( Long i = a; i < n; i++ )
#define per( i, a, n )                    for ( Long i = n - 1; i >= a; i-- )
#define all( x )                          ( x ).begin(), ( x ).end()
#define Long                              long long

#ifndef ONLINE_JUDGE
#define Debug( x )                        cerr << "#[ " << #x << " = "; PrintForDebug( x ); cerr << " ]\n";
#else
#define Debug( x )
#endif


template < class Type > void PrintForDebug( Type Var ) {
      cerr << setprecision( 15 ) << Var;
}

template < class Type1, class Type2 > void PrintForDebug( pair < Type1, Type2 > Var ) {
      cerr << "(";  PrintForDebug( Var.first );  cerr << ",";  PrintForDebug( Var.second );  cerr << ")";
}

template < class Type > void PrintForDebug( vector < Type > Var ) {
      cerr << "{ ";
      for ( int i = 0; i < Var.size(); ++i ) {
            if ( i ) cerr << ", "; PrintForDebug( Var[ i ] );
      } cerr << " } Size = " << Var.size();
}

template < class Type > void PrintForDebug( set < Type > Var ) {
      cerr << "{ "; int Size = Var.size();
      while ( !Var.empty() ) {
             PrintForDebug( *Var.begin() ); Var.erase( Var.begin() ); if ( !Var.empty() )  cerr << ", ";
      } cerr << " } Size = " << Size;
}


typedef tree < Long, null_type, less < Long >, rb_tree_tag, tree_order_statistics_node_update > Ordered_set;


struct perlinestruct {
      int line;
      string text;
};

perlinestruct perline[ 2000 ];
string keywords[ 32 ] = { "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
                          "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short",
                          "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while" };
int totalLine = 0;
string check;
ofstream file( "output.txt" );


bool isDigit( char ch )
{
      if ( ch >= '0' && ch <= '9' )
            return true;
      else
            return false;
}

bool operatorCheck( char ch )
{
      if ( ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '(' || ch == ')' || ch == '#' || ch == ';' || ch == ':' || ch == '?' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '&' ||ch ==  '|' || ch == '!' || ch == '=' || ch == '<' || ch == '>' || ch == ',' )
            return true;
      else
            return false;
}

bool operatorCheckdup(char ch)
{
      if ( ch == '+' || ch == '-' || ch == '&' || ch == '|' || ch == '=' || ch == '>' || ch == '<' )
            return true;
      else
            return false;
}

bool isItInteger( string check )
{
      for ( int i = 0; i < check.size(); ++i ) {
            if ( !isDigit( check[ i ] ) )
                  return false;
      }

      return true;
}

bool isItDouble( string check )
{
      int dotCount = 0;
      for ( int i = 0; i < check.size(); ++i ) {
            if ( isDigit( check[ i ] ) )
                  continue;
            if ( check[ i ] == '.' )
                  dotCount++;
            else
                  return false;
      }

      return dotCount <= 1;
}

void keyword_identifier_number_check( int l, int col )
{
      if ( check.size() == 0 )
            return;

      for ( int k = 0; k < 32; k++ ) {
            if ( check.compare( keywords[ k ] ) == 0 ) {
                  file << "keyword\t" << check << "\t" << perline[ l ].line << "\t" << col - ( check.size() ) + 1 << "\n";
                  check = "";
                  return;
            }
      }
      if ( isItInteger( check ) )
            file << "integer\t" << check << "\t" << perline[ l ].line << "\t" << col - ( check.size() ) + 1 << "\n";
      else if ( isItDouble( check ) )
            file << "double\t" << check << "\t" << perline[ l ].line << "\t" << col - ( check.size() ) + 1 << "\n";
      else
            file << "identifier\t" << check << "\t" << perline[ l ].line << "\t" << col - ( check.size() ) + 1 << "\n";

      check = "";
}

void lexing()
{
      for ( int i = 0; i < totalLine; i++ ) {
            int lenPerLine = perline[ i ].text.size();
            for ( int j = 0; j < lenPerLine; ) {
                  if ( operatorCheck( perline[ i ].text[ j ] ) && operatorCheckdup( perline[ i ].text[ j + 1 ] ) ) {//operatorChecking(done)
                        keyword_identifier_number_check( i, j );
                        file << "operator\t" << perline[ i ].text[ j ] << perline[ i ].text[ j + 1 ] << "\t" << perline[ i ].line << "\t" << j + 1 << "\n";
                        j += 2;
                  }
                  else if ( operatorCheck( perline[ i ].text[ j ] ) ) { //operatorChecking(done)
                        keyword_identifier_number_check( i, j );
                        file << "operator\t" << perline[ i ].text[ j ] << "\t" << perline[ i ].line << "\t" << j + 1 << "\n";
                        j += 1;
                  }
                  /*bad
                  else if(otherCheck(perline[i].text[j])){
                        file << "other\t" << perline[i].text[j] << "\t" << perline[i].line << "\t" << j+1 << "\n";
                        j += 1;
                  }*/
                  else if ( perline[ i ].text[ j ] == '\\' ) { //charChecking(done)
                        keyword_identifier_number_check( i, j );
                        file << "character\t" << perline[ i ].text[ j ] << perline[ i ].text[ j + 1 ] << "\t" << perline[ i ].line << "\t" << j + 1 << "\n";//check which character
                        j += 2;
                  }
                  /*else if ( check == "" && isDigit( perline[ i ].text[ j ] ) ) { //isDigiting(done)
                        keyword_identifier_number_check( i, j );
                        int f = 0, a = perline[ i ].text[ j ] - '0';
                        j++;
                        int temp = j;
                        while ( isDigit( perline[ i ].text[ j ] ) || perline[ i ].text[ j ] == '.' ) {
                              if ( perline[ i ].text[ j ] == '.' ) {
                                    f = 1;
                                    file << "float\t" << a << ".";
                                          a = 0;
                              }
                              else
                                    a = a * 10 + ( perline[ i ].text[ j ] - '0' );
                              j++;
                        }
                        if( f == 0 )
                              file << "integer\t" << a << "\t" << perline[ i ].line << "\t" << temp << "\n";
                        else
                              file << a << "\t" << perline[ i ].line << "\t" << temp << "\n";
                  }*/
                  else if ( perline[ i ].text[ j ] == '"' ) { //stringChecking(done)
                        keyword_identifier_number_check( i, j );
                        j++;
                        int temp = j;
                        string strg;
                        while ( perline[ i ].text[ j ] != '"' ) {
                              strg = strg + perline[ i ].text[ j ];
                              j++;
                        }
                        j++;
                        file << "string\t" << strg  << "\t" << perline[ i ].line << "\t" << temp + 1 << "\n"; //char check in string
                  }
                  else if ( perline[ i ].text[ j ] == ' ' || perline[ i ].text[ j ] == '\n' ) { //keyword_identifier_number_checking(done)
                        //cout << check << i << " " << j <<"\n";
                        keyword_identifier_number_check( i, j );

                        j++;
                  }
                  else {
                        check = check + perline[ i ].text[ j++ ];
                  }
            }
      }
}

int main()
{
      FILE *fp;
	string str, codeText, mainCodeText;
	char ch;

	#ifndef ONLINE_JUDGE
            //freopen( "Error.txt", "w", stderr );
      #endif

	fp = fopen( "program.c", "r" );

	if ( fp == NULL ){
		printf( "error while opening the file\n" );
		exit( 0 );
	}

	while ( ( ch = fgetc( fp ) ) != EOF ) {
            codeText = codeText + ch;
      }

      mainCodeText = codeText;

      for ( int i = 0; i + 1 < codeText.size(); ++i ) {
            int starti = i;
            if ( codeText[ i ] == '/' && codeText[ i + 1 ] == '/' ) {
                  while ( i < codeText.size() && codeText[ i ] != '\n' )
                        i++;

                  i--;
            }
            if ( codeText[ i ] == '/' && codeText[ i + 1 ] == '*' ) {
                  while ( i + 1 < codeText.size() && ( codeText[ i ] != '*' || codeText[ i + 1 ] != '/' ) )
                        i++;

                  if ( i + 1 == codeText.size() && ( codeText[ i ] != '*' || codeText[ i + 1 ] != '/' ) ) {
                        int lineNumberCount = 1;
                        for ( int j = 0; j < starti; ++j ) {
                              if ( mainCodeText[ j ] == '\n' )
                                    lineNumberCount++;
                        }
                        cout << "*** Unterminated comment issue on Line Number - " << lineNumberCount << "\n";
                  }


                  i++;
            }

            if ( starti == i )
                  continue;

            while ( starti <= i ) {
                  if ( codeText[ starti ] != '\n' )
                        codeText[ starti ] = ' ';
                  starti++;
            }

      }

      //Debug( codeText );

      stringstream X( codeText );
      while ( getline( X, str, '\n' ) ) {
            perline[ totalLine ].text = str + " ";
            perline[ totalLine++ ].line = totalLine;
      }

      lexing();

      return 0;
}
