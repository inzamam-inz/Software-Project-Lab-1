
/*   ALLAH is Almighty.....  */

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


#define thisLine_Done           1
#define thisLine_Error          2
#define thisLine_NotFinish      3
#define maximumLineCount        2000



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
bool availableVariable( string var, set < string > &inScope );
bool validoperator( int lineNumber, int columnNumber );
bool isSpecialoperator( int lineNumber, int columnNumber );
int checking_Equation( int lineNumber, vector < int > checkList );
int isDeclareVariableLine( int lineNumber );
int isBreakContinue( int lineNumber );
int isReturnLine( int lineNumber );
string addSemiColonTipsModify( int lineNumber );
void checking_statement( int lineNumber );
int forGroup( int i );
int functionGroup( int i );
int whileGroup( int i );
int doWhileGroup( int i );
else_if_struct elseIfGroup( int i );
else_struct elseGroup( int i );
int ifGroup( int i );
void findGroup( int startLine, int endLine );
void headerFile_check( int LN );
int headerFiles_check( int LN );
void find_MAIN_function();
void sameFunctionNameDetection();
void initialize_Checking( int LN );
bool isFunction( int LN );
bool isFor( int LN );
bool isWhile( int LN );
bool isDOWhile( int LN );
void isIFELSE( else_if_struct &elseIf );
void isELSE( else_struct &els );
bool isIF( int LN );
void check_THIS_Line ( int LN );
void syntaxChecking();
void errorPrinting();
bool isItDeclarationLine( int lineNumber );
void addThisInScope( string token, set < string > &takenVarible, int lineNumber );
void getVariableFromThisLine( int lineNumber, set < string > &takenVarible );
void tryToGetVariableFromThisDeclarationLine( int startLine, int endLine, set < string > &takenVarible );
void tryToGetVariableFromThisLineAllType( int startLine, int endLine, set < string > &takenVarible );
int isFunctionScope( int LN );
int isForScope( int LN );
int isWhileScope( int LN );
int isDoWhileScope( int LN );
int isIfScope( int LN );
int isElseIfScope( int LN );
int isElseScope( int LN );
void identifierCheckingOfThisLine( int LN, set < string > &takenVarible );
int variableHandling( int startLine, int endLine, set < string > takenVarible );
void finalChecking();



vector < for_struct > fors;
vector < func > functions;
vector < while_struct > whiles;
vector < do_while_struct > do_whiles;
vector < if_struct > ifs;
vector < else_if_struct > else_ifs;
vector < else_struct > elses;
int totalLine = 0;
vector < string > TokenType[ maximumLineCount ];
vector < string > Tokens[ maximumLineCount ];
bool isFinish[ maximumLineCount ], haveERROR[ maximumLineCount ];
vector < vector < string > > allVariable;
set < string > errorsTips[ maximumLineCount ];             // 1 based



struct printCFile
{
      FILE *fp;
      string str, codeText;
      char ch;
      vector < string > codeLine;

      printCFile() {
            this->fp = fopen( "program.c", "r" );
            if ( fp == NULL ){
                  printf( "error while opening the file 'program.c'\n" );
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
            //Debug( codeText );
      }

      void printThisLine( int LN ) {
            cout << "\"" << codeLine[ LN ] << "\"\n";
      }

      void printTips( string str ) {
            cout << "  Tips : " << str << ".\n";
      }
};

struct finalKEYChecking
{
      void partIncreaseDecrease( int lineNumber, vector < int > segment ) {
            vector < int > checkList;

            for ( int i = 0; i < segment.size(); ++i ) {
                  if ( i + 1 < segment.size() && isSpecialoperator( lineNumber, segment[ i ] ) && TokenType[ lineNumber ][ segment[ i ] + 1 ] == "identifier" ) {
                        ++i;
                        checkList.push_back( segment[ i ] );
                  }
                  else if ( isSpecialoperator( lineNumber, segment[ i ] ) ) {
                        errorsTips[ lineNumber + 1 ].insert( "Fix this Line" );
                        return;
                  }
                  else if ( TokenType[ lineNumber ][ segment[ i ] ] == "identifier" && isSpecialoperator( lineNumber, segment[ i ] + 1 ) ) {
                        checkList.push_back( segment[ i ] );
                        ++i;
                  }
                  else {
                        checkList.push_back( segment[ i ] );
                  }
            }

            int useless = checking_Equation( lineNumber, checkList );
      }

      void increaseDecrease( int lineNumber, vector < int > segment ) {
            vector < int > part;

            for ( int i = 0; i < segment.size(); ++i ) {
                  if ( Tokens[ lineNumber ][ segment[ i ] ] == "," ) {
                        partIncreaseDecrease( lineNumber, part );
                        part.clear();
                  }
                  else {
                        part.push_back( segment[ i ] );
                  }
            }
      }

      void checking_condition( int lineNumber, vector < int > checkList ) {
            vector < int > segment;

            if ( lineNumber == 92 ) {
                  for ( int i = 0; i < checkList.size(); ++i ) {
                        cout <<  Tokens[ lineNumber ][ checkList[ i ] ] << " ";
                  }
                  cout << "\n";
                  //Debug( checkList );
            }

            while ( !checkList.empty() && Tokens[ lineNumber ][ checkList.back() ] != "||" && Tokens[ lineNumber ][ checkList.back() ] != "&&" ) {
                  segment.push_back( checkList.back() );
                  checkList.pop_back();
            }

            if ( segment.size() % 2 == 0 || !segment.size() ) {
                  errorsTips[ lineNumber + 1 ].insert( "Not valid expression" );
                  return;
            }

            for ( int i = 0; i < segment.size(); ++i ) {
                  if ( i % 2 == 0 && ( TokenType[ lineNumber ][ segment[ i ] ] != "identifier" && TokenType[ lineNumber ][ segment[ i ] ] != "integer" && TokenType[ lineNumber ][ segment[ i ] ] != "double") ) {
                        errorsTips[ lineNumber + 1 ].insert( "Not valid expression" );
                        return;
                  }

                  if ( i % 2 == 1 && !validoperator( lineNumber, segment[ i ] ) ) {
                        errorsTips[ lineNumber + 1 ].insert( "Not valid expression" );
                        return;
                  }
            }

            if ( !checkList.empty() ) {
                  checkList.pop_back();
                  checking_condition( lineNumber, checkList );
            }

            return;
      }

      bool initializeDeclaration( int lineNumber ) {
            if ( Tokens[ lineNumber ][ 2 ] != "int" ) {
                  return false;
            }

            if ( Tokens[ lineNumber ].size() > 3 && TokenType[ lineNumber ][ 3 ] != "identifier" ) {
                  errorsTips[ lineNumber + 1 ].insert( "Need variable name" );
                  return true;
            }

            vector < int > checkList;
            for ( int i = 3; i < Tokens[ lineNumber ].size(); ++i ) {
                  if ( Tokens[ lineNumber ][ i ] == "," || Tokens[ lineNumber ][ i ] == ";" ) {
                        checking_condition( lineNumber, checkList );
                        checkList.clear();
                  }
                  else {
                        if ( isSpecialoperator( lineNumber, i ) && TokenType[ lineNumber ][ i + 1 ] == "identifier" ) {
                              ++i;
                              checkList.push_back( i );
                        }
                        else if ( isSpecialoperator( lineNumber, i ) ) {
                              errorsTips[ lineNumber + 1 ].insert( "Fix this Line" );
                              return true;
                        }
                        else if ( TokenType[ lineNumber ][ i ] == "identifier" && isSpecialoperator( lineNumber, i + 1 ) ) {
                              checkList.push_back( i );
                              ++i;
                        }
                        else {
                              checkList.push_back( i );
                        }
                  }

                  if ( Tokens[ lineNumber ][ i ] == ";" ) {
                        break;
                  }
            }

            return true;
      }
};

string trim_left( string st, char ch )
{
      while ( st.size() && st[ 0 ] == ch ) {
            st.erase( 0, 1 );
      }

      return st;
}

string trim_right( string st, char ch )
{
      while ( st.size() && st[ st.size() - 1 ] == ch ) {
            st.erase( st.size() - 1, 1 );
      }

      return st;
}

string trim_both( string st, char ch )
{
      st = trim_right( st, ch );
      st = trim_left( st, ch );

      return st;
}

bool isDigit( char ch )
{
      return ch >= '0' && ch <= '9';
}

bool isCapitalLetter( char ch )
{
      return ch >= 'A' && ch <= 'Z';
}

bool isSmallLetter( char ch )
{
      return ch >= 'a' && ch <= 'z';
}

bool isLetter( char ch )
{
      return ( isCapitalLetter( ch ) || isSmallLetter( ch ) );
}

bool isNumber( string st )
{
      for ( int i = 0; i < st.size(); ++i ) {
            if ( !isDigit( st[ i ] ) ) {
                  return false;
            }
      }

      return true;
}

string to_string( int number )
{
      string str;

      while ( number ) {
            str += '0' + ( number % 10 );
            number /= 10;
      }

      reverse( str.begin(), str.end() );

      return str;
}

int strTint( string str )
{
      int n = 0;
      for ( int i = 0; i < str.size(); i++ ) {
            n *= 10;
            n += str[ i ] - '0';
      }

      return n;
}

bool validVariableName( string st )
{
      if ( !( isLetter( st[ 0 ] ) || st[ 0 ] == '_' ) ) {
            return false;
      }

      for ( int i = 1; i < st.size(); ++i ) {
            if ( !( isLetter( st[ i ] ) || isDigit( st[ i ] ) || st[ i ] == '_' ) ) {
                  return false;
            }
      }

      return true;
}

bool availableVariable( string var, set < string > &inScope )
{
      return inScope.find( var ) != inScope.end();
}

bool validoperator( int lineNumber, int columnNumber )
{
      if ( TokenType[ lineNumber ].size() <= columnNumber || TokenType[ lineNumber ][ columnNumber ] != "operator" || Tokens[ lineNumber ][ columnNumber ].size() > 2 ) {
            return false;
      }

      set < char > goodoperator;
      goodoperator.insert( '+' );
      goodoperator.insert( '-' );
      goodoperator.insert( '&' );
      goodoperator.insert( '|' );
      goodoperator.insert( '=' );
      goodoperator.insert( '>' );
      goodoperator.insert( '<' );
      goodoperator.insert( '*' );
      goodoperator.insert( '/' );

      string currentToken = Tokens[ lineNumber ][ columnNumber ];
      if ( currentToken.size() == 1 && goodoperator.count( currentToken[ 0 ] ) ) {
            return true;
      }
      else if ( currentToken.size() == 2 && goodoperator.count( currentToken[ 0 ] ) && goodoperator.count( currentToken[ 1 ] ) ) {
            return true;
      }
      else {
            return false;
      }
}

bool isSpecialoperator( int lineNumber, int columnNumber )
{
      if ( TokenType[ lineNumber ].size() <= columnNumber || TokenType[ lineNumber ][ columnNumber ] != "operator" || Tokens[ lineNumber ][ columnNumber ].size() > 2 ) {
            return false;
      }

      if ( Tokens[ lineNumber ][ columnNumber ] == "++"  || Tokens[ lineNumber ][ columnNumber ] == "--" ) {
            return true;
      }
}

int checking_Equation( int lineNumber, vector < int > checkList )
{
      if ( checkList.size() % 2 == 0 || !checkList.size() ) {
            errorsTips[ lineNumber + 1 ].insert( "Fix this Line" );
            return thisLine_Done;
      }

      for ( int i = 0; i < checkList.size(); ++i ) {
            if ( i % 2 == 0 && ( TokenType[ lineNumber ][ checkList[ i ] ] != "identifier" && TokenType[ lineNumber ][ checkList[ i ] ] != "integer" && TokenType[ lineNumber ][ checkList[ i ] ] != "double") ) {
                  errorsTips[ lineNumber + 1 ].insert( "Fix this Line" );
                  return thisLine_Done;
            }

            if ( i % 2 == 1 && !validoperator( lineNumber, checkList[ i ] ) ) {
                  errorsTips[ lineNumber + 1 ].insert( "Fix this Line" );
                  return thisLine_Done;
            }
      }

      return thisLine_NotFinish;
}

int isDeclareVariableLine( int lineNumber )
{
      set < string > rightType;
      rightType.insert( "char" );
      rightType.insert( "int" );
      rightType.insert( "double" );

      if ( !rightType.count( Tokens[ lineNumber ][ 0 ] ) ) {
            return thisLine_NotFinish;
      }

      if ( Tokens[ lineNumber ].size() <= 2 ) {
            errorsTips[ lineNumber + 1 ].insert( "Need variable name" );
            return thisLine_Done;
      }

      vector < int > checkList;
      for ( int i = 1; i < Tokens[ lineNumber ].size(); ++i ) {
            if ( Tokens[ lineNumber ][ i ] == "," || Tokens[ lineNumber ][ i ] == ";" ) {
                  if( checking_Equation( lineNumber, checkList ) == thisLine_Done ) {
                        return thisLine_Done;
                  }
                  checkList.clear();
            }
            else {
                  if ( isSpecialoperator( lineNumber, i ) && TokenType[ lineNumber ][ i + 1 ] == "identifier" ) {
                        ++i;
                        checkList.push_back( i );
                  }
                  else if ( isSpecialoperator( lineNumber, i ) ) {
                        errorsTips[ lineNumber + 1 ].insert( "Fix this Line" );
                        return thisLine_Done;
                  }
                  else if ( TokenType[ lineNumber ][ i ] == "identifier" && isSpecialoperator( lineNumber, i + 1 ) ) {
                        checkList.push_back( i );
                        ++i;
                  }
                  else {
                        checkList.push_back( i );
                  }
            }
      }

      return thisLine_Done;
}

int isBreakContinue( int lineNumber )
{
      if ( Tokens[ lineNumber ][ 0 ] != "break" && Tokens[ lineNumber ][ 0 ] != "continue" ) {
            return thisLine_NotFinish;
      }

      if ( Tokens[ lineNumber ].size() != 2 ) {
            if ( Tokens[ lineNumber ][ 0 ] == "break" ) {
                  errorsTips[ lineNumber + 1 ].insert( "Replace with \"break;\"" );
            }

            if ( Tokens[ lineNumber ][ 0 ] == "continue" ) {
                  errorsTips[ lineNumber + 1 ].insert( "Replace with \"continue;\"" );
            }
      }

      return thisLine_Done;
}

int isReturnLine( int lineNumber )
{
      if ( Tokens[ lineNumber ][ 0 ] != "return" ) {
            return thisLine_NotFinish;
      }

      for ( int i = 0; i < functions.size(); ++i ) {
            if ( lineNumber >= functions[ i ].startLine && lineNumber <= functions[ i ].endLine ) {
                  if ( functions[ i ].returnType == "void" && Tokens[ lineNumber ].size() > 2 ) {
                        errorsTips[ lineNumber + 1 ].insert( "Function name '" + functions[ i ].fTokens + "' have void return type" );
                        return thisLine_Done;
                  }
                  else if ( functions[ i ].returnType != "void" && Tokens[ lineNumber ].size() <= 2 ) {
                        errorsTips[ lineNumber + 1 ].insert( "Function name '" + functions[ i ].fTokens + "' have return type, but return value not Found" );
                        return thisLine_Done;
                  }
                  else {
                        vector < int > checkList;
                        for ( int i = 1; i + 1 < Tokens[ lineNumber ].size(); ++i ) {
                              checkList.push_back( i );
                        }

                        checking_Equation( lineNumber, checkList );
                        return thisLine_Done;
                  }
            }
      }

      errorsTips[ lineNumber + 1 ].insert( "This Line is Out of any Function" );
      return thisLine_Done;
}

bool isCallingFunction( int lineNumber )
{
      bool isHere = false;

      for ( int i = 0; i + 1 < Tokens[ lineNumber ].size(); ++i ) {
            if ( ( TokenType[ lineNumber ][ i ] != "identifier" && Tokens[ lineNumber ][ i ] != "prinft" && Tokens[ lineNumber ][ i ] != "scanf" ) || Tokens[ lineNumber ][ i + 1 ] != "(" ) {
                  continue;
            }

            bool isFunc = false;
            for ( int j = 0; j < functions.size(); ++j ) {
                  if ( lineNumber + 1 == functions[ j ].startLine ) {
                        isFunc = true;
                        break;
                  }
            }

            isHere |= !isFunc;

            if ( isHere ) {
                  break;
            }
      }

//      if ( isHere ) {
//            cout << lineNumber << " ";
//      }

      return isHere;  // return false;
}

int whichFunctionCalling( int lineNumber )
{
      for ( int i = 0; i + 1 < Tokens[ lineNumber ].size(); ++i ) {
            if ( ( TokenType[ lineNumber ][ i ] != "identifier" && Tokens[ lineNumber ][ i ] != "prinft" && Tokens[ lineNumber ][ i ] != "scanf" ) || Tokens[ lineNumber ][ i + 1 ] != "(" ) {
                  continue;
            }

            bool isFunc = false;
            for ( int j = 0; j < functions.size(); ++j ) {
                  if ( lineNumber + 1 == functions[ j ].startLine ) {
                        isFunc = true;
                        break;
                  }
            }

            if ( !isFunc ) {
                  return i;  // i -> column position of function
            }
      }

      return -1;  // return false;
}

void checkingAsPrintfFunction( int lineNumber )
{
      //printf( "%d", var );
      if ( whichFunctionCalling( lineNumber ) != 0 ) {
            errorsTips[ lineNumber + 1 ].insert( "Don\'t expect any token before \'printf\' function" );
            return;
      }

      // basic structure ->
      // 1. printf + ( + string + ) + ;
      // 2. printf + ( + string + , + variables + ) + ;

      int cvar1 = 0, cvar2 = 0;
      if ( Tokens[ lineNumber ].size() >= 5 && Tokens[ lineNumber ][ 0 ] == "printf" && Tokens[ lineNumber ][ 1 ] == "(" && TokenType[ lineNumber ][ 2 ] == "string" && Tokens[ lineNumber ][ (int)Tokens[ lineNumber ].size() - 2 ] == ")" && Tokens[ lineNumber ].back() == ";" ) {
            for ( int i = 0; i + 1 < Tokens[ lineNumber ][ 2 ].size(); ++i ) {
                  if ( Tokens[ lineNumber ][ 2 ][ i ] == '%' && ( Tokens[ lineNumber ][ 2 ][ i + 1 ] == 'd' || Tokens[ lineNumber ][ 2 ][ i + 1 ] == 'c' || Tokens[ lineNumber ][ 2 ][ i + 1 ] == 'f' ) ) {
                        cvar1++;
                  }
            }

            for ( int i = 3; i + 3 < Tokens[ lineNumber ].size(); ++i ) {
                  if ( Tokens[ lineNumber ][ i ] == "," && TokenType[ lineNumber ][ i + 1 ] == "identifier" ) {
                        cvar2++;
                  }
            }

            if ( cvar1 != cvar2 ) {
                  Debug( lineNumber );
                  Debug( cvar1 );
                  Debug( cvar2 );
                  //  TODO
                  //  error
            }
            else {
                  Debug( lineNumber + 1 );
            }
      }
      else {
            cout << lineNumber + 1 << "\n";
      }
}

void checkThisFunctionCallingLine( int lineNumber )
{
      int posOfFunction = whichFunctionCalling( lineNumber );
      if ( posOfFunction == -1 ) {
            assert( false );
            return;
      }

      string functionName = Tokens[ lineNumber ][ posOfFunction ];
      string deleteThisError = "\'" + functionName + "\'" + " is undeclared here";
      //cout << functionName << "|->    " << deleteThisError << "\n";
      errorsTips[ lineNumber + 1 ].erase( deleteThisError );

      // printf
      if ( functionName == "printf" ) {
            Debug( functionName );
            checkingAsPrintfFunction( lineNumber );
      }

}

void functionCallingLine()
{
      for ( int i = 0; i < totalLine; ++i ) {
            if ( isCallingFunction( i ) ) {
                  errorsTips[ i + 1 ].erase( "Fix this Line");
                  checkThisFunctionCallingLine( i );
            }
      }
}

string addSemiColonTipsModify( int lineNumber )
{
      // keyword
      if ( Tokens[ lineNumber ].size() > 1 && Tokens[ lineNumber ][ 0 ] == "else" && Tokens[ lineNumber ][ 1 ] == "if" ) {
            return "This 'else if' has no previous 'if'";
      }
      else if ( Tokens[ lineNumber ][ 0 ] == "else" ) {
            return "This 'else' has no previous 'if'";
      }
      else if ( Tokens[ lineNumber ][ 0 ] == "for" ) {
            return "Wrong 'for loop' formation";
      }
      else if ( Tokens[ lineNumber ][ 0 ] == "while" || Tokens[ lineNumber ][ 0 ] == "do" ) {
            return "Wrong 'while/do-while loop' formation";
      }
      else if ( Tokens[ lineNumber ].back() == "{" || Tokens[ lineNumber ].back() == "}" ) {
            return "Expected valid identifier or valid formation before";
      }
      else  {
            return "Expected ';' in this line";
      }
}

void checking_statement( int lineNumber )
{
      if ( Tokens[ lineNumber ].size() && Tokens[ lineNumber ].back() != ";" ) {
            errorsTips[ lineNumber + 1 ].insert( addSemiColonTipsModify( lineNumber ) );
            return;
      }

      if ( Tokens[ lineNumber ].empty() ) {
            return;
      }

      if ( isDeclareVariableLine( lineNumber ) == thisLine_Done ) {
            return;
      }

      if ( isReturnLine( lineNumber ) == thisLine_Done ) {
            return;
      }

      if ( isBreakContinue( lineNumber ) == thisLine_Done ) {
            return;
      }

      //printf, scanf function -> TODO

      /*if ( isCallingFunction( lineNumber ) ) {
            return;
      }*/

      vector < int > checkList;
      for ( int i = 0; i < Tokens[ lineNumber ].size() - 1; ++i ) {
            if ( isSpecialoperator( lineNumber, i ) && TokenType[ lineNumber ][ i + 1 ] == "identifier" ) {
                  ++i;
                  checkList.push_back( i );
            }
            else if ( isSpecialoperator( lineNumber, i ) ) {
                  errorsTips[ lineNumber + 1 ].insert( "Fix this Line" );
                  return;
            }
            else if ( TokenType[ lineNumber ][ i ] == "identifier" && isSpecialoperator( lineNumber, i + 1 ) ) {
                  checkList.push_back( i );
                  ++i;
            }
            else {
                  checkList.push_back( i );
            }
      }

      int useless = checking_Equation( lineNumber, checkList );

      return;
}

int forGroup( int i )
{
      int semi = 0, f = 2;
      for_struct fa;
      fa.startLine = i + 1;
      fa.statement_text_start = i + 3;

      if ( Tokens[ i ][ TokenType[ i ].size() - 1 ].compare( "{" ) == 0 ) {
            fa.statement_text_start = i + 2;
      }

      while ( Tokens[ i ][ f ].compare( ")" ) != 0 ) {
            if ( Tokens[ i ][ f ].compare( ";" ) == 0 ) {
                  semi++;
                  f++;
                  continue;;
            }

            if ( semi == 0 ) {
                  fa.initialize.push_back( Tokens[ i ][ f ] );
                  fa.initializeType.push_back( TokenType[ i ][ f ] );
            }

            if ( semi == 1 )  {
                  fa.condition.push_back( Tokens[ i ][ f ] );
                  fa.conditionType.push_back( TokenType[ i ][ f ] );
            }

            if ( semi == 2 ) {
                  fa.change.push_back( Tokens[ i ][ f ] );
                  fa.changeType.push_back( TokenType[ i ][ f ] );
            }

            f++;
      }

      if ( semi != 2 ) {
            errorsTips[ fa.startLine ].insert( "Expected ';' before ')' token" );
            return i;
      }

      stack < int > temp;
      int h = fa.statement_text_start - 1;
      temp.push( h - 1 );

      while( !temp.empty() ) {
            for ( int k = 0; k < TokenType[ h ].size(); k++ ) {
                  if ( Tokens[ h ][ k ].compare( "{" ) == 0 ) {
                        temp.push( h );
                  }

                  if ( Tokens[ h ][ k ].compare( "}" ) == 0 ) {
                        temp.pop();
                  }
            }

            h++;
            if ( h == totalLine )
                  break;
      }

      while ( !temp.empty() ) {
            errorsTips[ temp.top() + 1 ].insert( "Expected identifier or '('" );
            temp.pop();
      }

      fa.statement_text_end = h - 1;
      fa.endLine = h;
      fors.push_back( fa );
      i = fa.endLine - 1;

      return i;
}

int functionGroup( int i )
{
      if ( Tokens[ i ][ TokenType[ i ].size() - 2 ].compare( ")" ) == 0 && Tokens[ i ][ TokenType[ i ].size() - 1 ].compare( ";" ) == 0 ) {
            cout << "function protoType\n";
            isFinish[ i ] = true;
      }
      else {
            func f;

            f.startLine = i + 1;
            f.returnType = Tokens[ i ][ 0 ];
            f.fTokens = Tokens[ i ][ 1 ];

            if ( Tokens[ i ][ 3 ].compare( ")" ) == 0 || Tokens[ i ][ 3 ].compare( "void" ) == 0 ) {
                  f.parameter.push_back( "None" );
                  f.parameterType.push_back( "void" );
            }
            else {
                  int j = 2;
                  while ( 1 )  {
                        if ( j >= Tokens[ i ].size() || ( Tokens[ i ][ j ] != "(" && Tokens[ i ][ j ] != "," && Tokens[ i ][ j ] != ")" ) ) {
                              Debug( j );
                              return i;
                        }

                        if ( Tokens[ i ][ j ].compare( ")" ) == 0 ) {
                              break;
                        }

                        f.parameter.push_back( Tokens[ i ][ j + 2 ] );
                        f.parameterType.push_back( Tokens[ i ][ j + 1 ] );
                        j += 3;
                  }
            }

            f.statement_text_start = i + 3;
            if ( Tokens[ i ][ TokenType[ i ].size() - 1 ].compare( "{" ) == 0 ) {
                  f.statement_text_start = i + 2;
            }

            int h = f.statement_text_start - 1;
            stack < int > temp;
            temp.push( h - 1 );

            while ( !temp.empty() ) {
                  for ( int k = 0; k < TokenType[ h ].size(); k++ ) {
                        if ( Tokens[ h ][ k ].compare( "{" ) == 0 ) {
                              temp.push( h );
                        }

                        if ( Tokens[ h ][ k ].compare( "}" ) == 0 ) {
                              temp.pop();
                        }
                  }

                  h++;
                  if ( h == totalLine )
                        break;
            }

            while ( !temp.empty() ) {
                  errorsTips[ temp.top() + 1 ].insert( "Expected identifier or '('" );
                  temp.pop();
            }

            f.statement_text_end = h - 1;
            f.endLine = h;
            functions.push_back( f );

            i = h - 1;
      }

      return i;
}

int whileGroup( int i )
{
      int f = 2;
      while_struct fa;
      fa.startLine = i + 1;
      fa.statement_text_start = i + 3;
      if ( Tokens[ i ][ TokenType[ i ].size() - 1 ].compare( "{" ) == 0 ) {
            fa.statement_text_start = i + 2;
      }

      while ( Tokens[ i ][ f ].compare( ")" ) != 0 ) {
            fa.condition.push_back( Tokens[ i ][ f ] );
            fa.conditionType.push_back( TokenType[ i ][ f ] );
            f++;
      }

      stack < int > temp;
      int h = fa.statement_text_start - 1;
      temp.push( h - 1 );

      while ( !temp.empty() ) {
            for ( int k  =0; k < TokenType[ h ].size(); k++ ) {
                  if ( Tokens[ h ][ k ].compare( "{" ) == 0 ) {
                        temp.push( h );
                  }

                  if ( Tokens[ h ][ k ].compare( "}" ) == 0 ) {
                        temp.pop();
                  }
            }

            h++;
            if ( h == totalLine )
                  break;
      }

      while ( !temp.empty() ) {
            errorsTips[ temp.top() + 1 ].insert( "Expected identifier or '('" );
            temp.pop();
      }

      fa.statement_text_end = h - 1;
      fa.endLine = h;
      whiles.push_back( fa );
      i = fa.endLine - 1;

      return i;
}

int doWhileGroup( int i )
{
      int f = 2;
      do_while_struct fa;
      fa.startLine = i + 1;
      fa.statement_text_start = i + 3;

      if ( Tokens[ i ][ TokenType[ i ].size() - 1 ].compare( "{" ) == 0 ) {
            fa.statement_text_start = i + 2;
      }

      stack < int > temp;
      int h = fa.statement_text_start - 1;
      temp.push( h - 1 );

      while ( !temp.empty() ) {
            for ( int k = 0; k < TokenType[ h ].size(); k++ ) {
                  if( Tokens[ h ][ k ].compare( "{" ) == 0 ) {
                        temp.push( h );
                  }

                  if ( Tokens[ h ][ k ].compare( "}" ) == 0 ) {
                        temp.pop();
                  }
            }

            h++;
            if ( h == totalLine )
                  break;
      }
      while ( !temp.empty() ) {
            errorsTips[ temp.top() + 1 ].insert( "Expected identifier or '('" );
            temp.pop();
      }

      fa.statement_text_end = h - 1;
      fa.endLine = h + 1;
      if ( Tokens[ h - 1].size() > 1 && Tokens[ h - 1 ][ 1 ].compare( "while" ) == 0 ) {
            fa.endLine = h;
            f = 3;
      }

      while ( Tokens[ fa.endLine - 1 ][ f ].compare( ")" ) != 0 ) {
            fa.condition.push_back( Tokens[ fa.endLine - 1 ][ f ] );
            fa.conditionType.push_back( TokenType[ fa.endLine - 1 ][ f ] );
            f++;
      }

      do_whiles.push_back( fa );
      i = fa.endLine - 1;

      return i;
}

else_if_struct elseIfGroup( int i )
{
      int f = 3;
      else_if_struct fa;
      fa.startLine = i + 1;
      fa.statement_text_start = i + 3;

      while ( Tokens[ i ][ f ].compare( ")" ) != 0 ) {
            fa.condition.push_back( Tokens[ i ][ f ] );
            fa.conditionType.push_back( TokenType[ i ][ f ] );
            f++;
      }

      if ( Tokens[ i ][ TokenType[ i ].size() - 1 ].compare( "{" ) == 0 ) {
            fa.statement_text_start = i + 2;
      }

      if ( Tokens[ i ][ TokenType[ i ].size() - 1 ].compare( "{" ) != 0 && ( Tokens[ i + 1 ].size() > 0 && Tokens[ i + 1 ][ 0 ].compare( "{" ) != 0 ) ) {
            fa.statement_text_start = i + 2;
            fa.statement_text_end = i + 2;
            fa.endLine = i + 2;
            i = i + 1;
      }
      else {
            stack < int > temp;
            int h = fa.statement_text_start - 1;
            temp.push( h - 1 );

            while ( !temp.empty() ) {
                  for ( int k = 0; k < TokenType[ h ].size(); k++ ) {
                        if ( Tokens[ h ][ k ].compare( "{" ) == 0 ) {
                              temp.push( h );
                        }

                        if ( Tokens[ h ][ k ].compare( "}" ) == 0 ) {
                              temp.pop();
                        }
                  }

                  h++;
                  if ( h == totalLine )
                        break;
            }

            while ( !temp.empty() ) {
                  errorsTips[ temp.top() + 1 ].insert( "Expected identifier or '('" );
                  temp.pop();
            }

            fa.statement_text_end = h - 1;
            fa.endLine = h;
      }

      else_ifs.push_back( fa );

      return fa;
}

else_struct elseGroup( int i )
{
      else_struct fa;
      fa.startLine = i + 1;
      fa.statement_text_start = i + 3;

      if ( Tokens[ i ][ TokenType[ i ].size() - 1 ].compare( "{" ) == 0 ) {
            fa.statement_text_start = i + 2;
      }

      if ( Tokens[ i ][ TokenType[ i ].size() - 1 ].compare( "{" ) != 0 && ( Tokens[ i + 1 ].size() > 0 && Tokens[ i + 1 ][ 0 ].compare( "{" ) != 0 ) ) {
            fa.statement_text_start = i + 2;
            fa.statement_text_end = i + 2;
            fa.endLine = i + 2;
            i = i + 1;
      }
      else {
            stack < int > temp;
            int h = fa.statement_text_start - 1;
            temp.push( h - 1 );

            while ( !temp.empty() ) {
                  for ( int k = 0; k < TokenType[ h ].size(); k++ ) {
                        if ( Tokens[ h ][ k ].compare( "{" ) == 0 ) {
                              temp.push( h );
                        }

                        if ( Tokens[ h ][ k ].compare( "}" ) == 0 ) {
                              temp.pop();
                        }
                  }

                  h++;
                  if ( h == totalLine )
                        break;
            }

            while ( !temp.empty() ) {
                  errorsTips[ temp.top() + 1 ].insert( "Expected identifier or '('" );
                  temp.pop();
            }

            fa.statement_text_end = h - 1;
            fa.endLine = h;
      }

      elses.push_back( fa );

      return fa;
}

int ifGroup( int i )
{
      int f = 2;
      if_struct fa;
      fa.startLine = i + 1;
      fa.statement_text_start = i + 3;

      while ( Tokens[ i ][ f ].compare( ")" ) != 0 ) {
            fa.condition.push_back( Tokens[ i ][ f ] );
            fa.conditionType.push_back( TokenType[ i ][ f ] );
            f++;
      }

      if ( Tokens[ i ][ TokenType[ i ].size() - 1 ].compare( "{" ) == 0 ) {
            fa.statement_text_start = i + 2;
      }

      if ( Tokens[ i ][ TokenType[ i ].size() - 1 ].compare( "{" ) == 0 || ( Tokens[ i + 1 ].size() > 0 && Tokens[ i + 1 ][ 0 ].compare( "{" ) == 0 ) ) {
            stack < int > temp;
            int h = fa.statement_text_start - 1;
            temp.push( h - 1 );

            while ( !temp.empty() ) {
                  for ( int k = 0; k < TokenType[ h ].size(); k++ ) {
                        if ( Tokens[ h ][ k ].compare( "{" ) == 0 ) {
                              temp.push( h );
                        }

                        if ( Tokens[ h ][ k ].compare( "}" ) == 0 ) {
                              temp.pop();
                        }
                  }

                  h++;
                  if ( h == totalLine )
                        break;
            }

            while ( !temp.empty() ) {
                  errorsTips[ temp.top() + 1 ].insert( "Expected identifier or '('" );
                  temp.pop();
            }

            fa.statement_text_end = h - 1;
            fa.endLine = h;
            i = fa.endLine - 1;
      }
      else {
            fa.statement_text_start = i + 2;
            fa.statement_text_end = i + 2;
            fa.endLine = i + 2;
            i = i + 1;
      }

      i++;
      while ( 1 ) {
            if ( TokenType[ i ].size() > 1 && Tokens[ i ][ 0 ].compare( "else" ) == 0  && Tokens[ i ][ 1 ].compare( "if" ) == 0 ) {
                  //
                  else_if_struct fi = elseIfGroup( i );
                  fa.if_elses.push_back( fi );
                  i = fi.endLine;
            }
            else if ( TokenType[ i ].size() > 0 && Tokens[ i ][ 0 ].compare( "else" ) == 0 ) {
                  else_struct fy = elseGroup( i );
                  fa.elses.push_back( fy );
                  i = fy.endLine;
                  break;
            }
            else {
                  break;
            }
      }

      ifs.push_back( fa );
      i--;

      return i;
}

void findGroup( int startLine, int endLine )
{
      for ( int i = startLine; i <= endLine; i++ ) {
            if ( TokenType[ i ].size() > 3 && TokenType[ i ][ 0 ].compare( "keyword" ) == 0  && TokenType[ i ][ 1 ].compare( "identifier" ) == 0  && Tokens[ i ][ 2 ].compare( "(" ) == 0  && ( Tokens[ i ][ 3 ] == ")" || TokenType[ i ][ 3 ] == "keyword" ) ) { //function
                  i = functionGroup( i );
            }
            else if ( Tokens[ i ].size() > 4 && Tokens[ i ][ 0 ].compare( "for" ) == 0 && Tokens[ i ][ 1 ].compare( "(" ) == 0 ) { //for
                  i = forGroup( i );
            }
            else if ( Tokens[ i ].size() > 3 && Tokens[ i ][ 0 ].compare( "while" ) == 0 && Tokens[ i ][ 1 ].compare( "(" ) == 0 && Tokens[ i ][ 2 ].compare( ")" ) != 0 ) { //while
                  i = whileGroup( i );
            }
            else if ( ( Tokens[ i ].size() <= 2 && Tokens[ i ].size() >= 1 ) && Tokens[ i ][ 0 ].compare( "do" ) == 0 ) { //do-while
                  i = doWhileGroup( i );
            }
            else if ( Tokens[ i ].size() > 3 && Tokens[ i ][ 0 ].compare( "if" ) == 0 ) {
                  i = ifGroup( i );
            }
            //
      }
}

void headerFile_check( int LN )
{
      vector < string > HEADER;
      HEADER.push_back( "#include<stdio.h>" );
      HEADER.push_back( "#include<conio.h>" );
      HEADER.push_back( "#include<stdlib.h>" );
      HEADER.push_back( "#include<math.h>" );
      HEADER.push_back( "#include<string.h>" );

      string H, afterRomoveSpace;

      for ( int i = 0; i < Tokens[ LN ].size(); ++i ) {
            H += Tokens[ LN ][ i ];
      }

      for ( int i = 0; i < H.size(); ++i ) {
            if ( H[ i ] != ' ' )
                  afterRomoveSpace += H[ i ];
      }

      for ( int i = 0; i < HEADER.size(); ++i ) {
            if ( H == HEADER[ i ] )
                  return;
      }

      errorsTips[ LN + 1 ].insert( "Fatal error: No such file or directory" );
}

int headerFiles_check( int LN )
{
      while ( LN < totalLine ) {
            if ( Tokens[ LN ].empty() ) {
                  // any empty line -> skip
                  isFinish[ LN ] = true;
                  ++LN;
                  continue;
            }
            else if ( Tokens[ LN ][ 0 ] == "#" ) {
                  // Maybe this line -> header file
                  headerFile_check( LN );
                  isFinish[ LN ] = true;
                  ++LN;
            }
            else {
                  break;
            }
      }

      return LN;
}

void find_MAIN_function()
{
      int C = 0;
      for ( int i = 0; i < functions.size(); ++i ) {
            if ( functions[ i ].fTokens == "main" ) {
                  C++;
            }
      }

      // TODO : same function name detection
      if ( C )  return;
      else      cout << "*** No MAIN function in your C file\n";

}

void sameFunctionNameDetection()
{
      map < string, vector < int > > functionInfo;
      for ( int i = 0; i < functions.size(); ++i ) {
            functionInfo[ functions[ i ].fTokens ].push_back( functions[ i ].startLine );
      }

      for ( map < string, vector < int > > :: iterator it = functionInfo.begin(); it != functionInfo.end(); ++it ) {
            vector < int > lineNumbers = it->second;
            string tips = "\"";

            if ( lineNumbers.size() > 1 ) {
                  tips += it->first;
                  tips += "\" is found more time as function name in Line number : ";

                  for ( int i = 0; i < lineNumbers.size(); ++i ) {
                        if ( i ) {
                              tips += ", ";
                        }

                        tips += to_string( lineNumbers[ i ] );
                  }

                  for ( int i = 0; i < lineNumbers.size(); ++i ) {
                        errorsTips[ lineNumbers[ i ] ].insert( tips );
                  }
            }
      }
}

void initialize_Checking( int LN )
{
      // find MAIN function
      find_MAIN_function();
      // TODO : same function name detection
      sameFunctionNameDetection();
      // header file check
      LN = headerFiles_check( LN );
}

bool isFunction( int LN )
{
      for ( int i = 0; i < functions.size(); ++i ) {
            if ( functions[ i ].startLine == LN + 1 ) {
                  for ( int j = functions[ i ].startLine; j < functions[ i ].statement_text_start; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  for ( int j = functions[ i ].statement_text_end + 1; j <= functions[ i ].endLine; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  findGroup( functions[ i ].statement_text_start - 1, functions[ i ].statement_text_end - 1 );

                  for ( int j = functions[ i ].statement_text_start; j <= functions[ i ].statement_text_end; ++j ) {
                        if ( !isFinish[ j - 1 ] ) {
                              check_THIS_Line( j - 1 );
                        }
                  }

                  return true;
            }
      }

      return false;
}

bool isFor( int LN )
{
      for ( int i = 0; i < fors.size(); ++i ) {
            if ( fors[ i ].startLine == LN + 1 ) {
                  for ( int j = fors[ i ].startLine; j < fors[ i ].statement_text_start; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  for ( int j = fors[ i ].statement_text_end + 1; j <= fors[ i ].endLine; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  findGroup( fors[ i ].statement_text_start - 1, fors[ i ].statement_text_end - 1 );

                  for ( int j = fors[ i ].statement_text_start; j <= fors[ i ].statement_text_end; ++j ) {
                        if ( !isFinish[ j - 1 ] ) {
                              check_THIS_Line( j - 1 );
                        }
                  }

                  return true;
            }
      }

      return false;
}

bool isWhile( int LN )
{
      for ( int i = 0; i < whiles.size(); ++i ) {
            if ( whiles[ i ].startLine == LN + 1 ) {
                  for ( int j = whiles[ i ].startLine; j < whiles[ i ].statement_text_start; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  for ( int j = whiles[ i ].statement_text_end + 1; j <= whiles[ i ].endLine; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  findGroup( whiles[ i ].statement_text_start - 1, whiles[ i ].statement_text_end - 1 );

                  for ( int j = whiles[ i ].statement_text_start; j <= whiles[ i ].statement_text_end; ++j ) {
                        if ( !isFinish[ j - 1 ] ) {
                              check_THIS_Line( j - 1 );
                        }
                  }

                  return true;
            }
      }

      return false;
}

bool isDOWhile( int LN )
{
      for ( int i = 0; i < do_whiles.size(); ++i ) {
            if ( do_whiles[ i ].startLine == LN + 1 ) {
                  for ( int j = do_whiles[ i ].startLine; j < do_whiles[ i ].statement_text_start; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  for ( int j = do_whiles[ i ].statement_text_end + 1; j <= do_whiles[ i ].endLine; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  findGroup( do_whiles[ i ].statement_text_start - 1, do_whiles[ i ].statement_text_end - 1 );

                  for ( int j = do_whiles[ i ].statement_text_start; j <= do_whiles[ i ].statement_text_end; ++j ) {
                        if ( !isFinish[ j - 1 ] ) {
                              check_THIS_Line( j - 1 );
                        }
                  }

                  return true;
            }
      }

      return false;
}

void isIFELSE( else_if_struct &elseIf )
{
      isFinish[ elseIf.startLine ] = true;

      for ( int j = elseIf.startLine; j < elseIf.statement_text_start; ++j ) {
            isFinish[ j - 1 ] = true;
      }

      for ( int j = elseIf.statement_text_end + 1; j <= elseIf.endLine; ++j ) {
            isFinish[ j - 1 ] = true;
      }

      findGroup( elseIf.statement_text_start - 1, elseIf.statement_text_end - 1 );

      for ( int j = elseIf.statement_text_start; j <= elseIf.statement_text_end; ++j ) {
            if ( !isFinish[ j - 1 ] ) {
                  check_THIS_Line( j - 1 );
            }
      }
}

void isELSE( else_struct &els )
{
      isFinish[ els.startLine ] = true;

      for ( int j = els.startLine; j < els.statement_text_start; ++j ) {
            isFinish[ j - 1 ] = true;
      }

      for ( int j = els.statement_text_end + 1; j <= els.endLine; ++j ) {
            isFinish[ j - 1 ] = true;
      }

      findGroup( els.statement_text_start - 1, els.statement_text_end - 1 );

      for ( int j = els.statement_text_start; j <= els.statement_text_end; ++j ) {
            if ( !isFinish[ j - 1 ] ) {
                  check_THIS_Line( j - 1 );
            }
      }
}

bool isIF( int LN )
{
      for ( int i = 0; i < ifs.size(); ++i ) {
            if ( ifs[ i ].startLine == LN + 1 ) {
                  for ( int j = ifs[ i ].startLine; j < ifs[ i ].statement_text_start; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  for ( int j = ifs[ i ].statement_text_end + 1; j <= ifs[ i ].endLine; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  findGroup( ifs[ i ].statement_text_start - 1, ifs[ i ].statement_text_end - 1 );

                  for ( int j = ifs[ i ].statement_text_start; j <= ifs[ i ].statement_text_end; ++j ) {
                        if ( !isFinish[ j - 1 ] ) {
                              check_THIS_Line( j - 1 );
                        }
                  }

                  for ( int j = 0; j < ifs[ i ].if_elses.size(); ++j ) {
                        isIFELSE( ifs[ i ].if_elses[ j ] );
                  }

                  for ( int j = 0; j < ifs[ i ].elses.size(); ++j ) {
                        isELSE( ifs[ i ].elses[ j ] );
                  }

                  return true;
            }
      }

      return false;
}

void check_THIS_Line( int LN )
{
      isFinish[ LN ] = true;

      if ( isFunction( LN ) ) {
            return;
      }
      else if ( isFor( LN ) ) {
            return;
      }
      else if ( isWhile( LN ) ) {
            return;
      }
      else if ( isDOWhile( LN ) ) {
            return;
      }
      else if ( isIF( LN ) ) {
            return;
      }
      else {
            //if ( LN == 43 )   cout << "--------------";
            checking_statement( LN );
      }
}

void syntaxChecking()
{
      int LN = 0;
      initialize_Checking( LN );

      for ( int i = 0; i < totalLine; ++i ) {
            if ( Tokens[ i ].empty() ) {
                  isFinish[ i ] = true;
            }
            else if ( !isFinish[ i ] ) {
                  check_THIS_Line( i );
            }
      }
}

void errorPrinting()
{
      printCFile CFILE;

      for ( int i = 0; i <= totalLine; ++i ) {
            if ( errorsTips[ i ].size() ) {
                  cout << "\nLine No - " << i << " : ";
                  CFILE.printThisLine( i );
                  for ( set < string > :: iterator it = errorsTips[ i ].begin(); it != errorsTips[ i ].end(); ++it )
                        CFILE.printTips( *it );
            }
      }
}

bool isItDeclarationLine( int lineNumber )
{
      set < string > rightType;
      rightType.insert( "char" );
      rightType.insert( "int" );
      rightType.insert( "double" );

      return ( !Tokens[ lineNumber ].empty() && rightType.find( Tokens[ lineNumber ][ 0 ] ) != rightType.end() );
}

void addThisInScope( string token, set < string > &takenVarible, int lineNumber )
{
      if ( !validVariableName( token ) ) {
            errorsTips[ lineNumber + 1 ].insert( "'" + token + "' is not valid variable" );
      }
      else if( availableVariable( token, takenVarible ) ) {
            errorsTips[ lineNumber + 1 ].insert( "'" + token + "' is already used" );
      }
      else {
            takenVarible.insert( token );
      }
}

void getVariableFromThisLine( int lineNumber, set < string > &takenVarible )
{
      addThisInScope( Tokens[ lineNumber ][ 1 ], takenVarible, lineNumber );

      for ( int i = 2; i < Tokens[ lineNumber ].size(); ++i ) {
            if ( Tokens[ lineNumber ][ i ] == "," ) {
                  addThisInScope( Tokens[ lineNumber ][ i + 1 ], takenVarible, lineNumber );
            }
      }
}

void tryToGetVariableFromThisDeclarationLine( int startLine, int endLine, set < string > &takenVarible )
{
      for ( int i = startLine; i <= endLine; ++i ) {  // 0 based
            // declaration line
            if ( errorsTips[ i + 1 ].empty() && isItDeclarationLine( i ) ) {
                  getVariableFromThisLine( i, takenVarible );
            }

      }
}

void tryToGetVariableFromThisLineAllType( int startLine, int endLine, set < string > &takenVarible )
{
      for ( int i = startLine; i <= endLine; ++i ) {  // 0 based
            // function
            for ( int j = 0; j < functions.size(); ++j ) {
                  if ( functions[ j ].startLine - 1 == i ) {
                        addThisInScope( functions[ j ].fTokens, takenVarible, functions[ j ].startLine - 1 );
                        for ( int k = 0; k < functions[ j ].parameter.size(); ++k ) {
                              addThisInScope( functions[ j ].parameter[ k ], takenVarible, functions[ j ].startLine - 1 );
                        }
                  }
            }

            // for
            for ( int j = 0; j < fors.size(); ++j ) {
                  if ( fors[ j ].startLine - 1 == i ) {
                        addThisInScope( fors[ j ].initialize[ 1 ], takenVarible, fors[ j ].startLine - 1 );
                        for ( int k = 2; k < fors[ j ].initialize.size(); ++k ) {
                              if ( fors[ j ].initialize[ k ] == "," ) {
                                    addThisInScope( fors[ j ].initialize[ k + 1 ], takenVarible, fors[ j ].startLine - 1 );
                              }
                        }
                  }
            }
      }
}

int isFunctionScope( int LN )
{
      for ( int i = 0; i < functions.size(); ++i ) {
            if ( LN + 1 == functions[ i ].startLine ) {
                  return functions[ i ].endLine - 1;
            }
      }

      return -1;
}

int isForScope( int LN )
{
      for ( int i = 0; i < fors.size(); ++i ) {
            if ( LN + 1 == fors[ i ].startLine ) {
                  return fors[ i ].endLine - 1;
            }
      }

      return -1;
}

int isWhileScope( int LN )
{
      for ( int i = 0; i < whiles.size(); ++i ) {
            if ( LN + 1 == whiles[ i ].startLine ) {
                  return whiles[ i ].endLine - 1;
            }
      }

      return -1;
}

int isDoWhileScope( int LN )
{
      for ( int i = 0; i < do_whiles.size(); ++i ) {
            if ( LN + 1 == do_whiles[ i ].startLine ) {
                  return do_whiles[ i ].endLine - 1;
            }
      }

      return -1;
}

int isIfScope( int LN )
{
      for ( int i = 0; i < ifs.size(); ++i ) {
            if ( LN + 1 == ifs[ i ].startLine ) {
                  return ifs[ i ].endLine - 1;
            }
      }

      return -1;
}

int isElseIfScope( int LN )
{
      for ( int i = 0; i < else_ifs.size(); ++i ) {
            if ( LN + 1 == else_ifs[ i ].startLine ) {
                  return else_ifs[ i ].endLine - 1;
            }
      }

      return -1;
}

int isElseScope( int LN )
{
      for ( int i = 0; i < elses.size(); ++i ) {
            if ( LN + 1 == elses[ i ].startLine ) {
                  return elses[ i ].endLine - 1;
            }
      }

      return -1;
}

void identifierCheckingOfThisLine( int LN, set < string > &takenVarible )
{
      for ( int j = 0; j < Tokens[ LN ].size(); ++j ) {
            if ( TokenType[ LN ][ j ] == "identifier" ) {
                  if ( !validVariableName( Tokens[ LN ][ j ] ) ) {
                        errorsTips[ LN + 1 ].insert( "'" + Tokens[ LN ][ j ] + "' is not valid variable" );
                  }

                  if( !availableVariable( Tokens[ LN ][ j ], takenVarible ) ) {
                        errorsTips[ LN + 1 ].insert( "'" + Tokens[ LN ][ j ] + "' is undeclared here" );
                  }
            }
      }
}

int variableHandling( int startLine, int endLine, set < string > takenVarible )
{
      tryToGetVariableFromThisLineAllType( startLine, startLine, takenVarible );
      identifierCheckingOfThisLine( startLine, takenVarible );

      for ( int i = startLine + 1; i <= endLine; ++i ) {  // 0 based
            if ( Tokens[ i ].empty() || Tokens[ i ][ 0 ] == "#" ) {
                  continue;
            }

            // function
            int nexti = isFunctionScope( i );
            if ( nexti != -1 ) {
                  variableHandling( i, nexti, takenVarible );
                  i = nexti;
                  continue;
            }

            // for
            nexti = isForScope( i );
            if ( nexti != -1 ) {
                  variableHandling( i, nexti, takenVarible );
                  i = nexti;
                  continue;
            }

            // while
            nexti = isWhileScope( i );
            if ( nexti != -1 ) {
                  variableHandling( i, nexti, takenVarible );
                  i = nexti;
                  continue;
            }

            // do while
            nexti = isDoWhileScope( i );
            if ( nexti != -1 ) {
                  variableHandling( i, nexti, takenVarible );
                  i = nexti;
                  continue;
            }

            // if
            nexti = isIfScope( i );
            if ( nexti != -1 ) {
                  variableHandling( i, nexti, takenVarible );
                  i = nexti;
                  continue;
            }

            // else if
            nexti = isElseIfScope( i );
            if ( nexti != -1 ) {
                  variableHandling( i, nexti, takenVarible );
                  i = nexti;
                  continue;
            }

            // else
            nexti = isElseScope( i );
            if ( nexti != -1 ) {
                  variableHandling( i, nexti, takenVarible );
                  i = nexti;
                  continue;
            }

            tryToGetVariableFromThisDeclarationLine( i, i, takenVarible );
            identifierCheckingOfThisLine( i, takenVarible );
      }

      return 0;
}

void finalChecking()
{
      finalKEYChecking FKC;
      vector < int > checkList;

      // for
      for ( int i = 0; i < fors.size(); ++i ) {
            bool ok = FKC.initializeDeclaration( fors[ i ].startLine - 1 );
            if ( !ok ) {
                  checkList.clear();
                  for ( int j = 2; Tokens[ fors[ i ].startLine - 1 ][ j ] != ";"; ++j ) {
                        checkList.push_back( j );
                  }

                  FKC.checking_condition( fors[ i ].startLine - 1, checkList );
            }

            int j = 2;
            for ( ; Tokens[ fors[ i ].startLine - 1 ][ j ] != ";"; ) {
                  ++j;
            }

            ++j;
            checkList.clear();
            for ( ; Tokens[ fors[ i ].startLine - 1 ][ j ] != ";"; ++j ) {
                  checkList.push_back( j );
            }
            FKC.checking_condition( fors[ i ].startLine - 1, checkList );

            ++j;
            checkList.clear();
            for ( ; Tokens[ fors[ i ].startLine - 1 ][ j ] != ")"; ++j ) {
                  checkList.push_back( j );
            }
            FKC.increaseDecrease( fors[ i ].startLine - 1, checkList );
      }

      // if
      for ( int i = 0; i < ifs.size(); ++i ) {
            checkList.clear();
            for ( int j = 2; Tokens[ ifs[ i ].startLine - 1 ][ j ] != ")"; ++j ) {
                  checkList.push_back( j );
            }

            FKC.checking_condition( ifs[ i ].startLine - 1, checkList );
      }

      // else if
      for ( int i = 0; i < else_ifs.size(); ++i ) {
            checkList.clear();
            for ( int j = 3; Tokens[ else_ifs[ i ].startLine - 1 ][ j ] != ")"; ++j ) {
                  checkList.push_back( j );
            }

            FKC.checking_condition( else_ifs[ i ].startLine - 1, checkList );
      }

      // while
      for ( int i = 0; i < whiles.size(); ++i ) {
            checkList.clear();
            for ( int j = 2; Tokens[ whiles[ i ].startLine - 1 ][ j ] != ")"; ++j ) {
                  checkList.push_back( j );
            }
            FKC.checking_condition( whiles[ i ].startLine - 1, checkList );
      }

      // do while
      for ( int i = 0; i < do_whiles.size(); ++i ) {
            checkList.clear();
            for ( int j = 2; Tokens[ do_whiles[ i ].endLine - 1 ][ j ] != ")"; ++j ) {
                  checkList.push_back( j );
            }
            FKC.checking_condition( do_whiles[ i ].endLine - 1, checkList );

            if ( Tokens[ do_whiles[ i ].endLine - 1 ].back() != ";" ) {
                  errorsTips[ do_whiles[ i ].endLine ].insert( "Expected ';' in this line" );
            }
      }
}

int main()
{
      system( "g++ Tokenization.cpp -o Tokenization" );
      system( "Tokenization" );

      FILE *fp;
      string str, Text, strg1, strg2, strg3, strg4;
      char ch;

	#ifndef ONLINE_JUDGE
            //freopen( "Error.txt", "w", stderr );
      #endif

      fp = fopen( "output.txt", "r" );

      if ( fp == NULL ) {
            printf( "error while opening the file\n" );
            exit( 0 );
      }

      while ( ( ch = fgetc( fp ) ) != EOF ) {
            Text = Text + ch;
      }

      stringstream X( Text );
      while ( getline(X, str, '\n' ) ) {
            stringstream Y( str );
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


      findGroup( 0, totalLine );
      syntaxChecking();
      set < string > takenVariable;
      variableHandling( 0, totalLine, takenVariable );
      finalChecking();
      functionCallingLine();
      errorPrinting();

      cout << '\n';
      Debug( totalLine );

      return 0;
}

/*
TODO : final check of main function;
TODO : function calling;
*/
