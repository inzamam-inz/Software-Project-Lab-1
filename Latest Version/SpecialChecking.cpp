
/*   ALLAH is Almighty.....  */

#include <bits/stdc++.h>
#include "Header.h"
using namespace std;


void specialChecking( int totalLine, parameterStruct )
{
      vector < int > checkList;
      // for
      for ( int i = 0; i < (int) fors.size(); ++i ) {
            bool ok = initializeDeclaration( fors[ i ].startLine - 1, totalLine, parameterCalling );
            if ( !ok ) {
                  checkList.clear();
                  for ( int j = 2; Tokens[ fors[ i ].startLine - 1 ][ j ] != ";"; ++j ) {
                        checkList.push_back( j );
                  }

                  checking_condition( fors[ i ].startLine - 1, checkList, totalLine, parameterCalling );
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
            checking_condition( fors[ i ].startLine - 1, checkList, totalLine, parameterCalling );

            ++j;
            checkList.clear();
            for ( ; Tokens[ fors[ i ].startLine - 1 ][ j ] != ")"; ++j ) {
                  checkList.push_back( j );
            }
            increaseDecrease( fors[ i ].startLine - 1, checkList, totalLine, parameterCalling );
      }
      // if
      for ( int i = 0; i < (int) ifs.size(); ++i ) {
            checkList.clear();
            for ( int j = 2; Tokens[ ifs[ i ].startLine - 1 ][ j ] != ")"; ++j ) {
                  checkList.push_back( j );
            }

            checking_condition( ifs[ i ].startLine - 1, checkList, totalLine, parameterCalling );
      }
      // else if
      for ( int i = 0; i < (int) else_ifs.size(); ++i ) {
            checkList.clear();
            for ( int j = 3; Tokens[ else_ifs[ i ].startLine - 1 ][ j ] != ")"; ++j ) {
                  checkList.push_back( j );
            }

            checking_condition( else_ifs[ i ].startLine - 1, checkList, totalLine, parameterCalling );
      }
      // while
      for ( int i = 0; i < (int) whiles.size(); ++i ) {
            checkList.clear();
            for ( int j = 2; Tokens[ whiles[ i ].startLine - 1 ][ j ] != ")"; ++j ) {
                  checkList.push_back( j );
            }
            checking_condition( whiles[ i ].startLine - 1, checkList, totalLine, parameterCalling );
      }
      // do while
      for ( int i = 0; i < (int) do_whiles.size(); ++i ) {
            checkList.clear();
            for ( int j = 2; Tokens[ do_whiles[ i ].endLine - 1 ][ j ] != ")"; ++j ) {
                  checkList.push_back( j );
            }
            checking_condition( do_whiles[ i ].endLine - 1, checkList, totalLine, parameterCalling );

            if ( Tokens[ do_whiles[ i ].endLine - 1 ].back() != ";" ) {
                  errorsTips[ do_whiles[ i ].endLine ].insert( "Expected ';' in this line" );
            }
      }
}

void partIncreaseDecrease( int lineNumber, vector < int > segment, int totalLine, parameterStruct ) {
      vector < int > checkList;

      for ( int i = 0; i < (int) segment.size(); ++i ) {
            if ( i + 1 < (int) segment.size() && isSpecialoperator( lineNumber, segment[ i ], totalLine, parameterCalling ) && TokenType[ lineNumber ][ segment[ i ] + 1 ] == "identifier" ) {
                  ++i;
                  checkList.push_back( segment[ i ] );
            }
            else if ( isSpecialoperator( lineNumber, segment[ i ], totalLine, parameterCalling ) ) {
                  errorsTips[ lineNumber + 1 ].insert( "Fix this Line" );
                  return;
            }
            else if ( TokenType[ lineNumber ][ segment[ i ] ] == "identifier" && isSpecialoperator( lineNumber, segment[ i ] + 1, totalLine, parameterCalling ) ) {
                  checkList.push_back( segment[ i ] );
                  ++i;
            }
            else {
                  checkList.push_back( segment[ i ] );
            }
      }

      int useless = checking_Equation( lineNumber, checkList, totalLine, parameterCalling );
}

void increaseDecrease( int lineNumber, vector < int > segment, int totalLine, parameterStruct ) {
      vector < int > part;

      for ( int i = 0; i < (int) segment.size(); ++i ) {
            if ( Tokens[ lineNumber ][ segment[ i ] ] == "," ) {
                  partIncreaseDecrease( lineNumber, part, totalLine, parameterCalling );
                  part.clear();
            }
            else {
                  part.push_back( segment[ i ] );
            }
      }
}

void checking_condition( int lineNumber, vector < int > checkList, int totalLine, parameterStruct )
{
      vector < int > segment;

      while ( !checkList.empty() && Tokens[ lineNumber ][ checkList.back() ] != "||" && Tokens[ lineNumber ][ checkList.back() ] != "&&" ) {
            segment.push_back( checkList.back() );
            checkList.pop_back();
      }

      if (  segment.size() % 2 == 0 || !segment.size() ) {
            errorsTips[ lineNumber + 1 ].insert( "Not valid expression" );
            return;
      }

      for ( int i = 0; i < (int) segment.size(); ++i ) {
            if ( i % 2 == 0 && ( TokenType[ lineNumber ][ segment[ i ] ] != "identifier" && TokenType[ lineNumber ][ segment[ i ] ] != "integer" && TokenType[ lineNumber ][ segment[ i ] ] != "double") ) {
                  errorsTips[ lineNumber + 1 ].insert( "Not valid expression" );
                  return;
            }

            if ( i % 2 == 1 && !validoperator( lineNumber, segment[ i ], totalLine, parameterCalling ) ) {
                  errorsTips[ lineNumber + 1 ].insert( "Not valid expression" );
                  return;
            }
      }

      if ( !checkList.empty() ) {
            checkList.pop_back();
            checking_condition( lineNumber, checkList, totalLine, parameterCalling );
      }

      return;
}

bool initializeDeclaration( int lineNumber, int totalLine, parameterStruct ) {
      if ( Tokens[ lineNumber ][ 2 ] != "int" ) {
            return false;
      }

      if ( (int) Tokens[ lineNumber ].size() > 3 && TokenType[ lineNumber ][ 3 ] != "identifier" ) {
            errorsTips[ lineNumber + 1 ].insert( "Need variable name" );
            return true;
      }

      vector < int > checkList;
      for ( int i = 3; i < (int) Tokens[ lineNumber ].size(); ++i ) {
            if ( Tokens[ lineNumber ][ i ] == "," || Tokens[ lineNumber ][ i ] == ";" ) {
                  checking_condition( lineNumber, checkList, totalLine, parameterCalling );
                  checkList.clear();
            }
            else {
                  if ( isSpecialoperator( lineNumber, i, totalLine, parameterCalling ) && TokenType[ lineNumber ][ i + 1 ] == "identifier" ) {
                        ++i;
                        checkList.push_back( i );
                  }
                  else if ( isSpecialoperator( lineNumber, i, totalLine, parameterCalling ) ) {
                        errorsTips[ lineNumber + 1 ].insert( "Fix this Line" );
                        return true;
                  }
                  else if ( TokenType[ lineNumber ][ i ] == "identifier" && isSpecialoperator( lineNumber, i + 1, totalLine, parameterCalling ) ) {
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
