
/*   ALLAH is Almighty.....  */

#include <bits/stdc++.h>
#include "Header.h"
using namespace std;


int readTokenFile( vector < string > Tokens[], vector < string > TokenType[] )
{
      FILE *ff;
      string str, Text, strg1, strg2, strg3, strg4;
      char ch;
      int totalLine;

      ff = fopen( "TokenFile.txt", "r" );

      if ( ff == NULL ) {
            printf( "error while opening the file\n" );
            exit( 0 );
      }

      while ( ( ch = fgetc( ff ) ) != EOF ) {
            Text = Text + ch;
            //cout << ch;
      }

      //Debug( Text );

      stringstream X( Text );
      while ( getline( X, str, '\n' ) ) {
            stringstream Y( str );
            //Debug( str );
            getline( Y, strg1, '\t' );
            getline( Y, strg2, '\t' );
            getline( Y, strg3, '\t' );
            getline( Y, strg4, '\t' );

            int h = strTint( strg3 );
            trim_both( strg1, ' ' );
            trim_both( strg2, ' ' );

            TokenType[ h - 1 ].push_back( strg1 );
            Tokens[ h - 1 ].push_back( strg2 );
            totalLine = max( totalLine, h );
      }

      //cout << totalLine << "--------------------------------------------";
      return totalLine;
}

