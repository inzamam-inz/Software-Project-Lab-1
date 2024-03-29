
/*   ALLAH is Almighty.....  */

#include <bits/stdc++.h>
#include "Header.h"
using namespace std;


void syntaxErrorChecking()
{
      vector < for_struct > fors;
      vector < func > functions;
      vector < while_struct > whiles;
      vector < do_while_struct > do_whiles;
      vector < if_struct > ifs;
      vector < else_if_struct > else_ifs;
      vector < else_struct > elses;
      vector < string > TokenType[ maximumLineCount ];
      vector < string > Tokens[ maximumLineCount ];
      set < string > takenVariable;
      set < string > errorsTips[ maximumLineCount ];             // 1 based
      bool isFinish[ maximumLineCount ];


      int TL = readTokenFile( Tokens, TokenType );
      functionPrototypeLine( TL, parameterCalling );
      findGroup( 0, TL, TL, parameterCalling );
      lineByLineSyntaxErrorChecking( TL, parameterCalling );
      variableHandling( 0, TL, takenVariable, TL, parameterCalling );
      specialChecking( TL, parameterCalling );
      functionCallingLine( TL, parameterCalling );
      errorPrinting( TL, errorsTips );

      E -> E * E
      E -> E + E

      num = S + B;

      cout << "[ Number of Line in Your C file = " << TL << " ]\n";
}

void sourceCodeMakeToken()
{
      string codeText;

	codeText = readInputCode();
	int TL = inputCodeInLineByLine( codeText );
      tokenization( TL );
}

void sampleCFile()
{
      FILE *ff;
      string codeText;
	char ch;

      ff = fopen( "sampleCode.c", "r" );

	if ( ff == NULL ){
		printf( "error while opening the file is named \'simpleCode.c\'\n" );
		exit( 0 );
	}

	while ( ( ch = fgetc( ff ) ) != EOF ) {
            codeText = codeText + ch;
      }

      fclose( ff );
      ofstream take( "sourceCode.c" );
      take << codeText;
}

void codeEditor()
{
      string codeText;
      cout << "Instruction - write \"Done\" to finish\n";

      string lineText;
      int lineNo = 1;

      getline( cin, lineText );
      while ( 1 ) {
            if ( lineNo < 10 ) {
                  cout << " ";
            }
            if ( lineNo < 100 ) {
                  cout << " ";
            }
            cout << lineNo << "|";
            lineNo++;
            getline( cin, lineText );
            if ( lineText == "Done") {
                  break;
            }
            lineText += "\n";
            codeText += lineText;
      }

      ofstream take( "sourceCode.c" );
      take << codeText;
}

void filesPath()
{
      FILE *ff;
	char ch;
      string codeText, path;
      char input[ 100 ];

      cout << "Instruction - Write File\'s Path\n";
      gets( input );
      gets( input );

      for ( int i = 0; i < strlen( input ); ++i ) {
            path += input[ i ];
      }


      ff = fopen( input, "r" );

	if ( ff == NULL ){
		printf( "error while opening the file is named \'simpleCode.c\'\n" );
		exit( 0 );
	}

	while ( ( ch = fgetc( ff ) ) != EOF ) {
            codeText = codeText + ch;
      }

      fclose( ff );
      ofstream take( "sourceCode.c" );
      take << codeText;
}

void userManual()
{
      cout << "\t\t\tMini C Compiler\n\n\n\t\t    1. Sample C file\n\t\t    2. Code Editor\n\t\t    3. C File\'s Path\n\t\t    4. Exit\n\nOption:";
      int option;
      cin >> option;

      if ( option == 1 ) {
            sampleCFile();
      }
      else if ( option == 2 ) {
            codeEditor();
      }
      else if ( option == 3 ) {
            filesPath();
      }
      else if ( option == 4 ) {
            exit( 0 );
      }
      else {
            cout << "Something Wrong!\n";
            userManual();
      }
}

void miniCCompiler()
{
      userManual();
      sourceCodeMakeToken();
      cout << "\n\n";
      cout << "\t\t\tErrors of Your C Code:\n\n";
      syntaxErrorChecking();
}

