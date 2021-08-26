
/*   ALLAH is Almighty.....  */

#include <bits/stdc++.h>
#include "Header.h"
using namespace std;


perlinestruct perline[ 2000 ];


string keyword_identifier_number_check( int l, int col, string &check )
{
      string keywords[ 32 ] = { "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
                          "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short",
                          "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while" };

      if ( check.size() == 0 ) {
            return "";
      }

      for ( int k = 0; k < 32; k++ ) {
            if ( check.compare( keywords[ k ] ) == 0 ) {
                  string toR = "keyword\t" + check + "\t" + to_string( perline[ l ].line ) + "\t" + to_string( col - ( check.size() ) + 1 ) + "\n";
                  //file << "keyword\t" << check << "\t" << perline[ l ].line << "\t" << col - ( check.size() ) + 1 << "\n";
                  check = "";
                  return toR;
            }
      }

      string toR;
      if ( isItInteger( check ) ) {
            toR = "integer\t" + check + "\t" + to_string( perline[ l ].line ) + "\t" + to_string( col - ( check.size() ) + 1 ) + "\n";
            //file << "integer\t" << check << "\t" << perline[ l ].line << "\t" << col - ( check.size() ) + 1 << "\n";
      }
      else if ( isItDouble( check ) ) {
            toR = "double\t" + check + "\t" + to_string( perline[ l ].line ) + "\t" + to_string( col - ( check.size() ) + 1 ) + "\n";
            //file << "double\t" << check << "\t" << perline[ l ].line << "\t" << col - ( check.size() ) + 1 << "\n";
      }
      else {
            toR = "identifier\t" + check + "\t" + to_string( perline[ l ].line ) + "\t" + to_string( col - ( check.size() ) + 1 ) + "\n";
            //file << "identifier\t" << check << "\t" << perline[ l ].line << "\t" << col - ( check.size() ) + 1 << "\n";
      }

      check = "";
      return toR;
}

void tokenization( int totalLine )
{
      ofstream file( "TokenFile.txt" );
      string keywords[ 32 ] = { "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
                                "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short",
                                "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while" };
      string check;

      for ( int i = 0; i < totalLine; i++ ) {
            int lenPerLine = perline[ i ].text.size();

            for ( int j = 0; j < lenPerLine; ) {
                  if ( operatorCheck( perline[ i ].text[ j ] ) && operatorCheckdup( perline[ i ].text[ j + 1 ] ) ) {   //operatorChecking
                        file << keyword_identifier_number_check( i, j, check );

                        file << "operator\t" << perline[ i ].text[ j ] << perline[ i ].text[ j + 1 ] << "\t" << perline[ i ].line << "\t" << j + 1 << "\n";
                        j += 2;
                  }
                  else if ( operatorCheck( perline[ i ].text[ j ] ) ) {   //operatorChecking
                        file << keyword_identifier_number_check( i, j, check );

                        file << "operator\t" << perline[ i ].text[ j ] << "\t" << perline[ i ].line << "\t" << j + 1 << "\n";
                        j += 1;
                  }
                  else if ( perline[ i ].text[ j ] == '\\' ) {   //charChecking
                        file << keyword_identifier_number_check( i, j, check );

                        file << "character\t" << perline[ i ].text[ j ] << perline[ i ].text[ j + 1 ] << "\t" << perline[ i ].line << "\t" << j + 1 << "\n";    //check which character
                        j += 2;
                  }
                  else if ( perline[ i ].text[ j ] == '"' ) {    //stringChecking
                        file << keyword_identifier_number_check( i, j, check );

                        j++;
                        int temp = j;
                        string strg;

                        while ( perline[ i ].text[ j ] != '"' ) {
                              strg = strg + perline[ i ].text[ j ];
                              j++;
                        }

                        j++;
                        file << "string\t" << strg  << "\t" << perline[ i ].line << "\t" << temp + 1 << "\n";       //char check in string
                  }
                  else if ( perline[ i ].text[ j ] == ' ' || perline[ i ].text[ j ] == '\n' ) {      //keyword_identifier_number_checking
                        file << keyword_identifier_number_check( i, j, check );

                        j++;
                  }
                  else {
                        check = check + perline[ i ].text[ j++ ];
                  }
            }
      }

      file.close();
}

int inputCodeInLineByLine( string codeText )
{
      int totalLine = 0;
      string part;

      stringstream X( codeText );
      while ( getline( X, part, '\n' ) ) {
            perline[ totalLine ].text = part + " ";
            perline[ totalLine++ ].line = totalLine;
      }

      return totalLine;
}

string readInputCode()
{
      FILE *fp;
	string codeText, mainCodeText;
	char ch;

	fp = fopen( "sourceCode.c", "r" );

	if ( fp == NULL ){
		printf( "error while opening the file is named \'sourceCode.c\'\n" );
		exit( 0 );
	}

	while ( ( ch = fgetc( fp ) ) != EOF ) {
            codeText = codeText + ch;
      }

      mainCodeText = codeText;
      cout << "\n\n\t\t\tYour Input C Code:\n\n";
      cout <<  mainCodeText << "\n\n";

      for ( int i = 0; i + 1 < (int) codeText.size(); ++i ) {
            int starti = i;
            if ( codeText[ i ] == '/' && codeText[ i + 1 ] == '/' ) {
                  while ( i < (int) codeText.size() && codeText[ i ] != '\n' ) {
                        i++;
                  }

                  i--;
            }

            if ( codeText[ i ] == '/' && codeText[ i + 1 ] == '*' ) {
                  while ( i + 1 < (int) codeText.size() && ( codeText[ i ] != '*' || codeText[ i + 1 ] != '/' ) ) {
                        i++;
                  }

                  if ( i + 1 == (int) codeText.size() && ( codeText[ i ] != '*' || codeText[ i + 1 ] != '/' ) ) {
                        int lineNumberCount = 1;

                        for ( int j = 0; j < starti; ++j ) {
                              if ( mainCodeText[ j ] == '\n' ) {
                                    lineNumberCount++;
                              }
                        }

                        //cout << mainCodeText;
                        cout << "\n\n*** Unterminated comment issue on Line Number - " << lineNumberCount << "\n";

                        exit( 0 );
                  }

                  i++;
            }

            if ( starti == i ) {
                  continue;
            }

            while ( starti <= i ) {
                  if ( codeText[ starti ] != '\n' ) {
                        codeText[ starti ] = ' ';
                  }

                  starti++;
            }
      }

      //cout << mainCodeText;
      return codeText;
}
