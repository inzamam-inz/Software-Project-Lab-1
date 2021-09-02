
/*   ALLAH is Almighty.....  */

#include <bits/stdc++.h>
#include "Header.h"
using namespace std;


perlinestruct perline[ 2000 ];


string getPrintString( string item, int l, int col )
{
      string toR;

      if ( isItInteger( item ) ) {
            toR = "integer\t" + item + "\t" + to_string( perline[ l ].line ) + "\t";
            toR += to_string( col - ( item.size() ) + 1 ) + "\n";
      }
      else if ( isItDouble( item ) ) {
            toR = "double\t" + item + "\t" + to_string( perline[ l ].line ) + "\t";
            toR +=  to_string( col - ( item.size() ) + 1 ) + "\n";
      }
      else {
            toR = "identifier\t" + item + "\t" + to_string( perline[ l ].line ) + "\t";
            toR += to_string( col - ( item.size() ) + 1 ) + "\n";
      }

      return toR;
}

string keyword_identifier_number_check( int l, int col, string &item )
{
      if ( item.size() == 0 ) {
            return "";
      }

      string keywords[ 32 ] = { "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
                          "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short",
                          "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while" };

      for ( int k = 0; k < 32; k++ ) {
            if ( item.compare( keywords[ k ] ) == 0 ) {
                  string toR = "keyword\t" + item + "\t" + to_string( perline[ l ].line ) + "\t";
                  toR += to_string( col - ( item.size() ) + 1 ) + "\n";
                  item = "";
                  return toR;
            }
      }

      string toR = getPrintString( item, l, col );

      item = "";
      return toR;
}

int inputCodeInLineByLine( string inputFile )
{
      int totalLine = 0;
      string part;

      stringstream X( inputFile );
      while ( getline( X, part, '\n' ) ) {
            perline[ totalLine ].text = part + " ";
            perline[ totalLine++ ].line = totalLine;
      }

      return totalLine;
}

void tokenization( int totalLine )
{
      ofstream take( "TokenFile.txt" );
      string item;

      for ( int i = 0; i < totalLine; i++ ) {
            int lenPerLine = perline[ i ].text.size();

            for ( int j = 0; j < lenPerLine; ) {
                  if ( operatorCheck( perline[ i ].text[ j ] ) && operatorCheckdup( perline[ i ].text[ j + 1 ] ) ) {
                        string toR = keyword_identifier_number_check( i, j, item );
                        take << toR;

                        take << "operator\t" << perline[ i ].text[ j ] << perline[ i ].text[ j + 1 ] << "\t";
                        take << perline[ i ].line << "\t" << j + 1 << "\n";
                        j += 2;
                  }
                  else if ( operatorCheck( perline[ i ].text[ j ] ) ) {
                        string toR = keyword_identifier_number_check( i, j, item );
                        take << toR;

                        take << "operator\t" << perline[ i ].text[ j ] << "\t";
                        take << perline[ i ].line << "\t" << j + 1 << "\n";
                        j += 1;
                  }
                  else if ( perline[ i ].text[ j ] == '\\' ) {
                        string toR = keyword_identifier_number_check( i, j, item );
                        take << toR;

                        take << "character\t" << perline[ i ].text[ j ] << perline[ i ].text[ j + 1 ] << "\t";
                        take << perline[ i ].line << "\t" << j + 1 << "\n";
                        j += 2;
                  }
                  else if ( perline[ i ].text[ j ] == '"' ) {
                        string toR = keyword_identifier_number_check( i, j, item );
                        take << toR;

                        j++;
                        int temp = j;
                        string strg;

                        while ( perline[ i ].text[ j ] != '"' ) {
                              strg = strg + perline[ i ].text[ j ];
                              j++;
                        }

                        j++;
                        take << "string\t" << strg  << "\t";
                        take << perline[ i ].line << "\t" << temp + 1 << "\n";
                  }
                  else if ( perline[ i ].text[ j ] == ' ' || perline[ i ].text[ j ] == '\n' ) {
                        string toR = keyword_identifier_number_check( i, j, item );
                        take << toR;

                        j++;
                  }
                  else {
                        item = item + perline[ i ].text[ j++ ];
                  }
            }
      }

      take.close();
}

string readInputCode()
{
      FILE *fp;
	string inputFile, orginal;
	char ch;

	fp = fopen( "sourceCode.c", "r" );

	if ( fp == NULL ){
		printf( "error while opening the input file\n" );
		exit( 0 );
	}

	while ( ( ch = fgetc( fp ) ) != EOF ) {
            inputFile = inputFile + ch;
      }

      orginal = inputFile;
      cout << "\n\n\t\t\tYour Input C Code:\n\n";
      cout <<  orginal << "\n\n";

      for ( int i = 0; i + 1 < (int) inputFile.size(); ++i ) {
            int starti = i;
            if ( inputFile[ i ] == '/' && inputFile[ i + 1 ] == '/' ) {
                  while ( i < (int) inputFile.size() && inputFile[ i ] != '\n' ) {
                        i++;
                  }

                  i--;
            }

            if ( inputFile[ i ] == '/' && inputFile[ i + 1 ] == '*' ) {
                  while ( i + 1 < (int) inputFile.size() && ( inputFile[ i ] != '*' || inputFile[ i + 1 ] != '/' ) ) {
                        i++;
                  }

                  if ( i + 1 == (int) inputFile.size() && ( inputFile[ i ] != '*' || inputFile[ i + 1 ] != '/' ) ) {
                        int lineNumberCount = 1;

                        for ( int j = 0; j < starti; ++j ) {
                              if ( orginal[ j ] == '\n' ) {
                                    lineNumberCount++;
                              }
                        }

                        cout << "\n\n*** Unterminated comment issue on Line Number - " << lineNumberCount << "\n";

                        exit( 0 );
                  }

                  i++;
            }

            if ( starti == i ) {
                  continue;
            }

            while ( starti <= i ) {
                  if ( inputFile[ starti ] != '\n' ) {
                        inputFile[ starti ] = ' ';
                  }

                  starti++;
            }
      }

      return inputFile;
}
