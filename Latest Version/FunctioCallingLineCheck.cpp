
/*   ALLAH is Almighty.....  */

#include <bits/stdc++.h>
#include "Header.h"
using namespace std;


bool isCallingFunction( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      bool isHere = false;

      for ( int i = 0; i + 1 < (int) Tokens[ lineNumber ].size(); ++i ) {
            if ( ( TokenType[ lineNumber ][ i ] != "identifier" && Tokens[ lineNumber ][ i ] != "prinft" && Tokens[ lineNumber ][ i ] != "scanf" ) || Tokens[ lineNumber ][ i + 1 ] != "(" ) {
                  continue;
            }

            bool isFunc = false;
            for ( int j = 0; j < (int) functions.size(); ++j ) {
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

      return isHere;  // return false;
}

int whichFunctionCalling( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      for ( int i = 0; i + 1 < (int) Tokens[ lineNumber ].size(); ++i ) {
            if ( ( TokenType[ lineNumber ][ i ] != "identifier" && Tokens[ lineNumber ][ i ] != "prinft" && Tokens[ lineNumber ][ i ] != "scanf" ) || Tokens[ lineNumber ][ i + 1 ] != "(" ) {
                  continue;
            }

            bool isFunc = false;
            for ( int j = 0; j < (int) functions.size(); ++j ) {
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

void checkingAsPrintfFunction( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      //printf( "%d", var );
      if ( whichFunctionCalling( lineNumber, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) != 0 ) {
            errorsTips[ lineNumber + 1 ].insert( "Don\'t expect any token before \'printf\' function" );
            return;
      }

      // basic structure ->
      // 1. printf + ( + string + ) + ;
      // 2. printf + ( + string + , + variables + ) + ;
      int cvar1 = 0, cvar2 = 0;
      if ( Tokens[ lineNumber ].size() >= 5 && Tokens[ lineNumber ][ 0 ] == "printf" && Tokens[ lineNumber ][ 1 ] == "(" && TokenType[ lineNumber ][ 2 ] == "string" && Tokens[ lineNumber ][ (int)Tokens[ lineNumber ].size() - 2 ] == ")" && Tokens[ lineNumber ].back() == ";" ) {
            for ( int i = 0; i + 1 < (int) Tokens[ lineNumber ][ 2 ].size(); ++i ) {
                  if ( Tokens[ lineNumber ][ 2 ][ i ] == '%' && ( Tokens[ lineNumber ][ 2 ][ i + 1 ] == 'd' || Tokens[ lineNumber ][ 2 ][ i + 1 ] == 'c' || Tokens[ lineNumber ][ 2 ][ i + 1 ] == 'f' ) ) {
                        cvar1++;
                  }
            }

            for ( int i = 3; i + 3 < (int) Tokens[ lineNumber ].size(); ++i ) {
                  if ( Tokens[ lineNumber ][ i ] == "," && TokenType[ lineNumber ][ i + 1 ] == "identifier" ) {
                        cvar2++;
                        ++i;
                  }
                  else {
                        errorsTips[ lineNumber + 1 ].insert( "Format specifier and variable don\'t match" );
                  }
            }

            if ( cvar1 != cvar2 ) {
                  errorsTips[ lineNumber + 1 ].insert( "Format specifier and variable count not same" );
            }
      }
      else {
            errorsTips[ lineNumber + 1 ].insert( "\'printf\' structure violated" );
      }
}

void checkingAsScanfFunction( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      //scanf( "%d", &var );
      if ( whichFunctionCalling( lineNumber, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) != 0 ) {
            errorsTips[ lineNumber + 1 ].insert( "Don\'t expect any token before \'scanf\' function" );
            return;
      }

      // basic structure ->
      // 1. scanf + ( + string + , + & + variables + ) + ;
      int cvar1 = 0, cvar2 = 0;
      if ( (int) Tokens[ lineNumber ].size() >= 8 && Tokens[ lineNumber ][ 0 ] == "scanf" && Tokens[ lineNumber ][ 1 ] == "(" && TokenType[ lineNumber ][ 2 ] == "string" && Tokens[ lineNumber ][ 3 ] == "," && Tokens[ lineNumber ][ (int)Tokens[ lineNumber ].size() - 2 ] == ")" && Tokens[ lineNumber ].back() == ";" ) {
            for ( int i = 0; i < (int) Tokens[ lineNumber ][ 2 ].size(); ++i ) {
                  if ( i + 1 < (int) Tokens[ lineNumber ][ 2 ].size() && Tokens[ lineNumber ][ 2 ][ i ] == '%' && ( Tokens[ lineNumber ][ 2 ][ i + 1 ] == 'd' || Tokens[ lineNumber ][ 2 ][ i + 1 ] == 'c' || Tokens[ lineNumber ][ 2 ][ i + 1 ] == 'f' ) ) {
                        cvar1++;
                        ++i;
                  }
                  else if ( Tokens[ lineNumber ][ 2 ][ i ] != ' ' ) {
                        errorsTips[ lineNumber + 1 ].insert( "Invalid Format specifying" );
                  }
            }

            for ( int i = 3; i + 4 < (int) Tokens[ lineNumber ].size(); ++i ) {
                  if ( Tokens[ lineNumber ][ i ] == "," && Tokens[ lineNumber ][ i + 1 ] == "&" && TokenType[ lineNumber ][ i + 2 ] == "identifier" ) {
                        cvar2++;
                        i += 2;
                  }
                  else {
                        errorsTips[ lineNumber + 1 ].insert( "Invalid formation of variable" );
                  }
            }

            if ( cvar1 != cvar2 ) {
                  errorsTips[ lineNumber + 1 ].insert( "Format specifier and variable count not same" );
            }
      }
      else {
            errorsTips[ lineNumber + 1 ].insert( "\'scanf\' structure violated" );
      }
}

void checkingAsCustomFunction( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      int posOfFunction = whichFunctionCalling( lineNumber, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
      string functionName = Tokens[ lineNumber ][ posOfFunction ];

      // is known function
      bool isKnown = false;
      int idOfFunction = -1;
      for ( int i = 0; i < (int) functions.size(); ++i ) {
            if ( functions[ i ].fTokens == functionName ) {
                  isKnown |= true;
                  idOfFunction = i;
                  break;
            }
      }

      if ( !isKnown ) {
            // unknown function
            errorsTips[ lineNumber + 1 ].insert( "\'" + functionName + "\'" + " is undefined" );
            return;
      }

      // function parameter
      int numberOfParameterInThisLineFunction = 0;
      int numberOfParameterOfThisFunction = functions[ idOfFunction ].parameter.size();
      vector < int > checkList;
      for ( int i = posOfFunction + 2; i < (int) Tokens[ lineNumber ].size(); ++i ) {
            if ( Tokens[ lineNumber ][ i ] == ")" ) {
                  break;
            }

            checkList.push_back( i );
      }

      if ( checkList.empty() ) {
            if ( numberOfParameterOfThisFunction ) {
                  errorsTips[ lineNumber + 1 ].insert( "Expected parameter but none was passed" );
            }
      }
      else if ( (int)checkList.size() % 2 == 0 ) {
            errorsTips[ lineNumber + 1 ].insert( "Structure violated while passing parameter" );
      }
      else {
            for ( int i = 0; i < (int) checkList.size(); ++i ) {
                  if ( i % 2 && Tokens[ lineNumber ][ checkList[ i ] ] == "," ) {
                        continue;
                  }
                  else if ( i % 2 == 0 && ( TokenType[ lineNumber ][ checkList[ i ] ] == "identifier" || TokenType[ lineNumber ][ checkList[ i ] ] == "integer" ) ) {
                        numberOfParameterInThisLineFunction++;
                  }
                  else {
                        errorsTips[ lineNumber + 1 ].insert( "Structure violated while passing parameter" );
                  }
            }

            if ( numberOfParameterInThisLineFunction != numberOfParameterOfThisFunction ) {
                  errorsTips[ lineNumber + 1 ].insert( "Fewer or more parameter than Expected" );
            }
      }

      // treat as a statement
      // make a fake Line
      // line number is 1990
      int ln = 1990;
      for ( int i = 0; i <= posOfFunction; ++i ) {
            Tokens[ ln ].push_back( Tokens[ lineNumber ][ i ] );
            TokenType[ ln ].push_back( TokenType[ lineNumber ][ i ] );
      }

      int next = posOfFunction;
      for ( int i = posOfFunction; i < (int) Tokens[ lineNumber ].size(); ++i ) {
            if ( Tokens[ lineNumber ][ i ] == ")" ) {
                  next = i + 1;
                  break;
            }
      }

      for ( int i = next; i < (int) Tokens[ lineNumber ].size(); ++i ) {
            Tokens[ ln ].push_back( Tokens[ lineNumber ][ i ] );
            TokenType[ ln ].push_back( TokenType[ lineNumber ][ i ] );
      }

      checking_statement( ln, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );

      for ( set < string > :: iterator it = errorsTips[ ln + 1 ].begin(); it != errorsTips[ ln + 1 ].end(); ++it ) {
            errorsTips[ lineNumber + 1 ].insert( *it );
      }

      Tokens[ ln ].clear();
      TokenType[ ln ].clear();
      errorsTips[ ln + 1 ].clear();

      // return type
      bool haveReturnLine = false;
      for ( int i = 0; i < (int) Tokens[ lineNumber ].size(); ++i ) {
            if ( Tokens[ lineNumber ][ i ] == "=" || Tokens[ lineNumber ][ i ] == "==" ) {
                  haveReturnLine = true;
                  break;
            }
      }

      bool haveReturnFunction = ( functions[ idOfFunction ].returnType != "void" );

      if ( haveReturnFunction && !haveReturnLine ) {
            errorsTips[ lineNumber + 1 ].insert( "\'" + functionName + "\'" + " have return type but no container to contain" );
      }
      else if ( !haveReturnFunction && haveReturnLine ) {
            errorsTips[ lineNumber + 1 ].insert( "\'" + functionName + "\'" + " have no return type");
      }
}

void checkThisFunctionCallingLine( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      int posOfFunction = whichFunctionCalling( lineNumber, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
      if ( posOfFunction == -1 ) {
            assert( false );
            return;
      }

      string functionName = Tokens[ lineNumber ][ posOfFunction ];
      string deleteThisError = "\'" + functionName + "\'" + " is undeclared here";
      errorsTips[ lineNumber + 1 ].erase( deleteThisError );

      // printf
      if ( functionName == "printf" ) {
            checkingAsPrintfFunction( lineNumber, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
      }
      else if ( functionName == "scanf" ) {
            checkingAsScanfFunction( lineNumber, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
      }
      else {
            checkingAsCustomFunction( lineNumber, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
      }
}

void functionCallingLine( int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      for ( int i = 0; i < totalLine; ++i ) {
            if ( isCallingFunction( i, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) ) {
                  errorsTips[ i + 1 ].erase( "Fix this Line");
                  checkThisFunctionCallingLine( i, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
            }
      }
}


