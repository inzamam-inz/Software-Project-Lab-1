
/*   ALLAH is Almighty.....  */

#include <bits/stdc++.h>
#include "Header.h"
using namespace std;


struct printCFile
{
      FILE *fp;
      string str, codeText;
      char ch;
      vector < string > codeLine;

      printCFile( ) {
            this->fp = fopen( "sourceCode.c", "r" );

            if ( fp == NULL ){
                  printf( "error while opening the file named 'sourceCode.c'\n" );
                  exit( 0 );
            }

            while ( ( ch = fgetc( fp ) ) != EOF ) {
                       codeText = codeText + ch;
            }
            codeLine.push_back( codeText ); //full code;

            stringstream X( codeText );
            while ( getline( X, str, '\n' ) ) {
                  codeLine.push_back( str );
            }
      }

      void printThisLine( int LN ) {
            cout << "\"" << codeLine[ LN ] << "\"\n";
      }

      void printTips( string str ) {
            cout << "  Tips : " << str << ".\n";
      }
};

void errorPrinting( int totalLine, set < string > errorsTips[] )
{
      printCFile CFILE;
      int errorsLineCount = 0;

      for ( int i = 0; i <= totalLine; ++i ) {
            if ( errorsTips[ i ].size() ) {
                  cout << "\nLine No - " << i << " : ";
                  CFILE.printThisLine( i );
                  errorsLineCount++;
                  for ( set < string > :: iterator it = errorsTips[ i ].begin(); it != errorsTips[ i ].end(); ++it )
                        CFILE.printTips( *it );
            }
      }

      cout << "\n\n[ Number of Error Line in Your C file = " << errorsLineCount << " ]\n";
}
