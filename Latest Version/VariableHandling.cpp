
/*   ALLAH is Almighty.....  */

#include <bits/stdc++.h>
#include "Header.h"
using namespace std;


int variableHandling( int startLine, int endLine, set < string > takenVarible, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      if ( !startLine ) {
            while ( Tokens[ startLine ].empty() || Tokens[ startLine ][ 0 ] == "#" ) {
                  startLine++;
            }
            startLine--;
      }
      tryToGetVariableFromThisLineAllType( startLine, startLine, takenVarible, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
      identifierCheckingOfThisLine( startLine, takenVarible, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );

      for ( int i = startLine + 1; i <= endLine; ++i ) {  // 0 based
            if ( Tokens[ i ].empty() || Tokens[ i ][ 0 ] == "#" ) {
                  continue;
            }

            // function
            int nexti = isFunctionScope( i, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
            if ( nexti != -1 ) {
                  variableHandling( i, nexti, takenVarible, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                  i = nexti;
                  continue;
            }

            // for
            nexti = isForScope( i, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
            if ( nexti != -1 ) {
                  variableHandling( i, nexti, takenVarible, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                  i = nexti;
                  continue;
            }

            // while
            nexti = isWhileScope( i, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
            if ( nexti != -1 ) {
                  variableHandling( i, nexti, takenVarible, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                  i = nexti;
                  continue;
            }

            // do while
            nexti = isDoWhileScope( i, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
            if ( nexti != -1 ) {
                  variableHandling( i, nexti, takenVarible, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                  i = nexti;
                  continue;
            }

            // if
            nexti = isIfScope( i, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
            if ( nexti != -1 ) {
                  variableHandling( i, nexti, takenVarible, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                  i = nexti;
                  continue;
            }

            // else if
            nexti = isElseIfScope( i, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
            if ( nexti != -1 ) {
                  variableHandling( i, nexti, takenVarible, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                  i = nexti;
                  continue;
            }

            // else
            nexti = isElseScope( i, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
            if ( nexti != -1 ) {
                  variableHandling( i, nexti, takenVarible, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                  i = nexti;
                  continue;
            }

            tryToGetVariableFromThisDeclarationLine( i, i, takenVarible, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
            identifierCheckingOfThisLine( i, takenVarible, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
      }

      return 0;
}

void tryToGetVariableFromThisDeclarationLine( int startLine, int endLine, set < string > &takenVarible, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      for ( int i = startLine; i <= endLine; ++i ) {  // 0 based
            // declaration line
            if ( errorsTips[ i + 1 ].empty() && isItDeclarationLine( i, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) ) {
                  getVariableFromThisLine( i, takenVarible, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
            }

      }
}

void tryToGetVariableFromThisLineAllType( int startLine, int endLine, set < string > &takenVarible, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      for ( int i = startLine; i <= endLine; ++i ) {  // 0 based
            // function
            for ( int j = 0; j < (int) functions.size(); ++j ) {
                  if ( functions[ j ].startLine - 1 == i ) {
                        addThisInScope( functions[ j ].fTokens, takenVarible, functions[ j ].startLine - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                        for ( int k = 0; k < (int) functions[ j ].parameter.size(); ++k ) {
                              addThisInScope( functions[ j ].parameter[ k ], takenVarible, functions[ j ].startLine - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                        }
                  }
            }

            // for
            for ( int j = 0; j < (int) fors.size(); ++j ) {
                  if ( fors[ j ].startLine - 1 == i ) {
                        addThisInScope( fors[ j ].initialize[ 1 ], takenVarible, fors[ j ].startLine - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                        for ( int k = 2; k < (int) fors[ j ].initialize.size(); ++k ) {
                              if ( fors[ j ].initialize[ k ] == "," ) {
                                    addThisInScope( fors[ j ].initialize[ k + 1 ], takenVarible, fors[ j ].startLine - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                              }
                        }
                  }
            }
      }
}

void identifierCheckingOfThisLine( int LN, set < string > &takenVarible, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      for ( int j = 0; j < (int) Tokens[ LN ].size(); ++j ) {
            if ( TokenType[ LN ][ j ] == "identifier" ) {
                  if ( !validVariableName( Tokens[ LN ][ j ] ) ) {
                        errorsTips[ LN + 1 ].insert( "'" + Tokens[ LN ][ j ] + "' is not valid variable" );
                  }

                  if( !availableVariable( Tokens[ LN ][ j ], takenVarible, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) ) {
                        errorsTips[ LN + 1 ].insert( "'" + Tokens[ LN ][ j ] + "' is undeclared here" );
                  }
            }
      }
}

bool isItDeclarationLine( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      set < string > rightType;
      rightType.insert( "char" );
      rightType.insert( "int" );
      rightType.insert( "double" );

      return ( !Tokens[ lineNumber ].empty() && rightType.find( Tokens[ lineNumber ][ 0 ] ) != rightType.end() );
}

void addThisInScope( string token, set < string > &takenVarible, int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      if ( !validVariableName( token ) ) {
            errorsTips[ lineNumber + 1 ].insert( "'" + token + "' is not valid variable" );
      }
      else if( availableVariable( token, takenVarible, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) ) {
            errorsTips[ lineNumber + 1 ].insert( "'" + token + "' is already used" );
      }
      else {
            takenVarible.insert( token );
      }
}

void getVariableFromThisLine( int lineNumber, set < string > &takenVarible, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      addThisInScope( Tokens[ lineNumber ][ 1 ], takenVarible, lineNumber, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );

      for ( int i = 2; i < (int) Tokens[ lineNumber ].size(); ++i ) {
            if ( Tokens[ lineNumber ][ i ] == "," ) {
                  addThisInScope( Tokens[ lineNumber ][ i + 1 ], takenVarible, lineNumber, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
            }
      }
}

bool availableVariable( string var, set < string > &inScope, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      return inScope.find( var ) != inScope.end();
}

int isFunctionScope( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      for ( int i = 0; i < (int) functions.size(); ++i ) {
            if ( LN + 1 == functions[ i ].startLine ) {
                  return functions[ i ].endLine - 1;
            }
      }

      return -1;
}

int isForScope( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      for ( int i = 0; i < (int) fors.size(); ++i ) {
            if ( LN + 1 == fors[ i ].startLine ) {
                  return fors[ i ].endLine - 1;
            }
      }

      return -1;
}

int isWhileScope( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      for ( int i = 0; i < (int) whiles.size(); ++i ) {
            if ( LN + 1 == whiles[ i ].startLine ) {
                  return whiles[ i ].endLine - 1;
            }
      }

      return -1;
}

int isDoWhileScope( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      for ( int i = 0; i < (int) do_whiles.size(); ++i ) {
            if ( LN + 1 == do_whiles[ i ].startLine ) {
                  return do_whiles[ i ].endLine - 1;
            }
      }

      return -1;
}

int isIfScope( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      for ( int i = 0; i < (int) ifs.size(); ++i ) {
            if ( LN + 1 == ifs[ i ].startLine ) {
                  return ifs[ i ].endLine - 1;
            }
      }

      return -1;
}

int isElseIfScope( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      for ( int i = 0; i < (int) else_ifs.size(); ++i ) {
            if ( LN + 1 == else_ifs[ i ].startLine ) {
                  return else_ifs[ i ].endLine - 1;
            }
      }

      return -1;
}

int isElseScope( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      for ( int i = 0; i < (int) elses.size(); ++i ) {
            if ( LN + 1 == elses[ i ].startLine ) {
                  return elses[ i ].endLine - 1;
            }
      }

      return -1;
}
