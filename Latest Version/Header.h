
/*   ALLAH is Almighty.....  */

#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <bits/stdc++.h>
using namespace std;


#define thisLine_Done                     1
#define thisLine_Error                    2
#define thisLine_NotFinish                3
#define maximumLineCount                  2000
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


//For Debugging
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



//Structure
struct perlinestruct {
      int line;
      string text;
};

struct func {
      int startLine;
      int endLine;
      string returnType;
      vector < string > parameter;
      vector < string > parameterType;
      int statement_text_start;
      int statement_text_end;
      string fTokens;
};

struct for_struct {
      int startLine;
      int endLine;
      vector < string > condition;
      vector < string > conditionType;
      vector < string > change;
      vector < string > changeType;
      vector < string > initialize;
      vector < string > initializeType;
      int statement_text_start;
      int statement_text_end;
};

struct while_struct {
      int startLine;
      int endLine;
      vector < string > condition;
      vector < string > conditionType;
      int statement_text_start;
      int statement_text_end;
};

struct do_while_struct {
      int startLine;
      int endLine;
      vector < string > condition;
      vector < string > conditionType;
      int statement_text_start;
      int statement_text_end;
};

struct else_struct {
      int startLine;
      int endLine;
      int statement_text_start;
      int statement_text_end;
};

struct else_if_struct {
      int startLine;
      int endLine;
      int statement_text_start;
      int statement_text_end;
      vector < string > condition;
      vector < string > conditionType;
};

struct if_struct {
      int startLine;
      int endLine;
      int statement_text_start;
      int statement_text_end;
      vector < string > condition;
      vector < string > conditionType;
      vector < else_struct > elses;
      vector < else_if_struct > if_elses;
};


// ALL Function Prototype

//Supporter file's function prototype
string trim_left( string st, char ch );
string trim_right( string st, char ch );
string trim_both( string st, char ch );
bool isDigit( char ch );
bool isCapitalLetter( char ch );
bool isSmallLetter( char ch );
bool isLetter( char ch );
bool isNumber( string st );
string to_string( int number );
int strTint( string str );
bool validVariableName( string st );
bool operatorCheck( char ch );
bool operatorCheckdup( char ch );
bool isItInteger( string check );
bool isItDouble( string check );



//ReadTokenFile file's function prototype
int readTokenFile( vector < string > Tokens[], vector < string > TokenType[] );



//Grouping file's function prototype
void findGroup( int startLine, int endLine, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
int functionGroup( int i, vector < string > Tokens[], vector < string > TokenType[], int totalLine, bool isFinish[], set < string > errorsTips[], vector < func > &functions );
int forGroup( int i, vector < string > Tokens[], vector < string > TokenType[], int totalLine, bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors );
int whileGroup( int i, vector < string > Tokens[], vector < string > TokenType[], int totalLine, bool isFinish[], set < string > errorsTips[], vector < while_struct > &whiles );
int doWhileGroup( int i, vector < string > Tokens[], vector < string > TokenType[], int totalLine, bool isFinish[], set < string > errorsTips[], vector < do_while_struct > &do_whiles );
int ifGroup( int i, vector < string > Tokens[], vector < string > TokenType[], int totalLine, bool isFinish[], set < string > errorsTips[], vector < if_struct > &ifs,
                            vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
else_struct elseGroup( int i, vector < string > Tokens[], vector < string > TokenType[], int totalLine, bool isFinish[], set < string > errorsTips[], vector < if_struct > &ifs,
                            vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
else_if_struct elseIfGroup( int i, vector < string > Tokens[], vector < string > TokenType[], int totalLine, bool isFinish[], set < string > errorsTips[], vector < if_struct > &ifs,
                            vector < else_if_struct > &else_ifs, vector < else_struct > &elses );



//LineByLineSyntaxErrorChecking file's function prototype
void lineByLineSyntaxErrorChecking( int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void initialize_Checking( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void find_MAIN_function( int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void sameFunctionNameDetection( int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
int headerFiles_check( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void headerFile_check( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void check_THIS_Line( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
bool isFunction( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
bool isFor( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
bool isWhile( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
bool isDOWhile( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void isIFELSE( else_if_struct &elseIf, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void isELSE( else_struct &els, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
bool isIF( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void checking_statement( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
string addSemiColonTipsModify( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
int isDeclareVariableLine( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
int isReturnLine( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
int isBreakContinue( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
bool isSpecialoperator( int lineNumber, int columnNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses  );
int checking_Equation( int lineNumber, vector < int > checkList, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses  );
bool validoperator( int lineNumber, int columnNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );



//VariableHandling file's function prototype
int variableHandling( int startLine, int endLine, set < string > takenVarible, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void tryToGetVariableFromThisDeclarationLine( int startLine, int endLine, set < string > &takenVarible, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void tryToGetVariableFromThisLineAllType( int startLine, int endLine, set < string > &takenVarible, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void identifierCheckingOfThisLine( int LN, set < string > &takenVarible, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
bool isItDeclarationLine( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void addThisInScope( string token, set < string > &takenVarible, int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void getVariableFromThisLine( int lineNumber, set < string > &takenVarible, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
bool availableVariable( string var, set < string > &inScope, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
int isFunctionScope( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
int isForScope( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
int isWhileScope( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
int isDoWhileScope( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
int isIfScope( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
int isElseIfScope( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
int isElseScope( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );



//SpecialChecking file's function prototype
void specialChecking( int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void partIncreaseDecrease( int lineNumber, vector < int > segment, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void increaseDecrease( int lineNumber, vector < int > segment, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void checking_condition( int lineNumber, vector < int > checkList, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
bool initializeDeclaration( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );



//FunctionCallingLineCheck file's function prototype
void functionCallingLine( int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void checkThisFunctionCallingLine( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void checkingAsCustomFunction( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void checkingAsScanfFunction( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
void checkingAsPrintfFunction( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
int whichFunctionCalling( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );
bool isCallingFunction( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses );



//ErrorPrinting file's function prototype
void errorPrinting( int totalLine, set < string > errorsTips[] );



// Tokenization file's function prototype
bool isDigit( char ch );
bool operatorCheck( char ch );
bool operatorCheckdup(char ch);
bool isItInteger( string check );
bool isItDouble( string check );
string keyword_identifier_number_check( int l, int col, string &check );
void tokenization( int totalLine );
string readInputCode( );
int inputCodeInLineByLine( string codeText );


// Mini C Compiler file's function prototype
void miniCCompiler();

#endif
