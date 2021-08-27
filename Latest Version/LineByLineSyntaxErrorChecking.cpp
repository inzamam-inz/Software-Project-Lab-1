
/*   ALLAH is Almighty.....  */

#include <bits/stdc++.h>
#include "Header.h"
using namespace std;


void lineByLineSyntaxErrorChecking( int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      int LN = 0;
      initialize_Checking( LN, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );

      for ( int i = 0; i < totalLine; ++i ) {
            if ( Tokens[ i ].empty() ) {
                  isFinish[ i ] = true;
            }
            else if ( !isFinish[ i ] ) {
                  check_THIS_Line( i, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
            }
      }
}

void initialize_Checking( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      // find MAIN function
      find_MAIN_function( totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );

      // TODO : same function name detection
      sameFunctionNameDetection( totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );

      // header file check
      LN = headerFiles_check( LN, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
}

void find_MAIN_function( int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      int C = 0;
      for ( int i = 0; i < (int) functions.size(); ++i ) {
            if ( functions[ i ].fTokens == "main" ) {
                  C++;
            }
      }

      if ( C ) {
           return;
      }
      else {
            cout << "*** No MAIN function in your C file\n";
      }
}

void sameFunctionNameDetection( int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      map < string, vector < int > > functionInfo;
      for ( int i = 0; i < (int) functions.size(); ++i ) {
            string key;
            key = functions[ i ].fTokens;
            key += " ";

            for ( int j = 0; j < functions[ i ].parameterType.size(); ++j ) {
                  key += functions[ i ].parameterType[ j ];
            }

            functionInfo[ key ].push_back( functions[ i ].startLine );
      }

      for ( map < string, vector < int > > :: iterator it = functionInfo.begin(); it != functionInfo.end(); ++it ) {
            vector < int > lineNumbers = it->second;
            string tips = "\"";

            if ( lineNumbers.size() > 1 ) {
                  string key =it->first;
                  for ( int i = 0; i < (int) key.size(); ++i ) {
                        if ( key[ i ] == ' ' ) {
                              break;
                        }

                        tips += key[ i ];
                  }
                  tips += "\" is found more time as function name in Line number : ";

                  for ( int i = 0; i < (int) lineNumbers.size(); ++i ) {
                        if ( i ) {
                              tips += ", ";
                        }

                        tips += to_string( lineNumbers[ i ] );
                  }

                  for ( int i = 0; i < (int) lineNumbers.size(); ++i ) {
                        errorsTips[ lineNumbers[ i ] ].insert( tips );
                  }
            }
      }
}

int headerFiles_check( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
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
                  //cout << LN << "<<<";
                  headerFile_check( LN, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                  isFinish[ LN ] = true;
                  ++LN;
            }
            else {
                  break;
            }
      }

      return LN;
}

void headerFile_check( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      vector < string > HEADER;
      HEADER.push_back( "#include<stdio.h>" );
      HEADER.push_back( "#include<conio.h>" );
      HEADER.push_back( "#include<stdlib.h>" );
      HEADER.push_back( "#include<math.h>" );
      HEADER.push_back( "#include<string.h>" );

      string H, afterRomoveSpace;

      for ( int i = 0; i < (int) Tokens[ LN ].size(); ++i ) {
            H += Tokens[ LN ][ i ];
      }

      for ( int i = 0; i < (int) H.size(); ++i ) {
            if ( H[ i ] != ' ' )
                  afterRomoveSpace += H[ i ];
      }

      for ( int i = 0; i < (int) HEADER.size(); ++i ) {
            if ( H == HEADER[ i ] )
                  return;
      }

      errorsTips[ LN + 1 ].insert( "Unknown Library or Header" );
}

void check_THIS_Line( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      isFinish[ LN ] = true;

      if ( isFunction( LN, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) ) {
            return;
      }
      else if ( isFor( LN, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) ) {
            return;
      }
      else if ( isWhile( LN, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) ) {
            return;
      }
      else if ( isDOWhile( LN, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) ) {
            return;
      }
      else if ( isIF( LN, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) ) {
            return;
      }
      else {
            checking_statement( LN, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
      }
}

bool isFunction( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      for ( int i = 0; i < (int) functions.size(); ++i ) {
            if ( functions[ i ].startLine == LN + 1 ) {
                  for ( int j = functions[ i ].startLine; j < functions[ i ].statement_text_start; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  for ( int j = functions[ i ].statement_text_end + 1; j <= functions[ i ].endLine; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  findGroup( functions[ i ].statement_text_start - 1, functions[ i ].statement_text_end - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );

                  for ( int j = functions[ i ].statement_text_start; j <= functions[ i ].statement_text_end; ++j ) {
                        if ( !isFinish[ j - 1 ] ) {
                              check_THIS_Line( j - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                        }
                  }

                  return true;
            }
      }

      return false;
}

bool isFor( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      for ( int i = 0; i < (int) fors.size(); ++i ) {
            if ( fors[ i ].startLine == LN + 1 ) {
                  for ( int j = fors[ i ].startLine; j < fors[ i ].statement_text_start; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  for ( int j = fors[ i ].statement_text_end + 1; j <= fors[ i ].endLine; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  findGroup( fors[ i ].statement_text_start - 1, fors[ i ].statement_text_end - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );

                  for ( int j = fors[ i ].statement_text_start; j <= fors[ i ].statement_text_end; ++j ) {
                        if ( !isFinish[ j - 1 ] ) {
                              check_THIS_Line( j - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                        }
                  }

                  return true;
            }
      }

      return false;
}

bool isWhile( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      for ( int i = 0; i < (int) whiles.size(); ++i ) {
            if ( whiles[ i ].startLine == LN + 1 ) {
                  for ( int j = whiles[ i ].startLine; j < whiles[ i ].statement_text_start; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  for ( int j = whiles[ i ].statement_text_end + 1; j <= whiles[ i ].endLine; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  findGroup( whiles[ i ].statement_text_start - 1, whiles[ i ].statement_text_end - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );

                  for ( int j = whiles[ i ].statement_text_start; j <= whiles[ i ].statement_text_end; ++j ) {
                        if ( !isFinish[ j - 1 ] ) {
                              check_THIS_Line( j - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                        }
                  }

                  return true;
            }
      }

      return false;
}

bool isDOWhile( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      for ( int i = 0; i < (int) do_whiles.size(); ++i ) {
            if ( do_whiles[ i ].startLine == LN + 1 ) {
                  for ( int j = do_whiles[ i ].startLine; j < do_whiles[ i ].statement_text_start; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  for ( int j = do_whiles[ i ].statement_text_end + 1; j <= do_whiles[ i ].endLine; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  findGroup( do_whiles[ i ].statement_text_start - 1, do_whiles[ i ].statement_text_end - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );

                  for ( int j = do_whiles[ i ].statement_text_start; j <= do_whiles[ i ].statement_text_end; ++j ) {
                        if ( !isFinish[ j - 1 ] ) {
                              check_THIS_Line( j - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                        }
                  }

                  return true;
            }
      }

      return false;
}

void isIFELSE( else_if_struct &elseIf, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      isFinish[ elseIf.startLine ] = true;

      for ( int j = elseIf.startLine; j < (int) elseIf.statement_text_start; ++j ) {
            isFinish[ j - 1 ] = true;
      }

      for ( int j = elseIf.statement_text_end + 1; j <= elseIf.endLine; ++j ) {
            isFinish[ j - 1 ] = true;
      }

      findGroup( elseIf.statement_text_start - 1, elseIf.statement_text_end - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );

      for ( int j = elseIf.statement_text_start; j <= elseIf.statement_text_end; ++j ) {
            if ( !isFinish[ j - 1 ] ) {
                  check_THIS_Line( j - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
            }
      }
}

void isELSE( else_struct &els, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      isFinish[ els.startLine ] = true;

      for ( int j = els.startLine; j < els.statement_text_start; ++j ) {
            isFinish[ j - 1 ] = true;
      }

      for ( int j = els.statement_text_end + 1; j <= els.endLine; ++j ) {
            isFinish[ j - 1 ] = true;
      }

      findGroup( els.statement_text_start - 1, els.statement_text_end - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );

      for ( int j = els.statement_text_start; j <= els.statement_text_end; ++j ) {
            if ( !isFinish[ j - 1 ] ) {
                  check_THIS_Line( j - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
            }
      }
}

bool isIF( int LN, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      for ( int i = 0; i < (int) ifs.size(); ++i ) {
            if ( ifs[ i ].startLine == LN + 1 ) {
                  for ( int j = ifs[ i ].startLine; j < ifs[ i ].statement_text_start; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  for ( int j = ifs[ i ].statement_text_end + 1; j <= ifs[ i ].endLine; ++j ) {
                        isFinish[ j - 1 ] = true;
                  }

                  findGroup( ifs[ i ].statement_text_start - 1, ifs[ i ].statement_text_end - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );

                  for ( int j = ifs[ i ].statement_text_start; j <= ifs[ i ].statement_text_end; ++j ) {
                        if ( !isFinish[ j - 1 ] ) {
                              check_THIS_Line( j - 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                        }
                  }

                  for ( int j = 0; j < (int) ifs[ i ].if_elses.size(); ++j ) {
                        isIFELSE( ifs[ i ].if_elses[ j ], totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                  }

                  for ( int j = 0; j < (int) ifs[ i ].elses.size(); ++j ) {
                        isELSE( ifs[ i ].elses[ j ], totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                  }

                  return true;
            }
      }

      return false;
}

void checking_statement( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      if ( Tokens[ lineNumber ].size() && Tokens[ lineNumber ].back() != ";" ) {
            errorsTips[ lineNumber + 1 ].insert( addSemiColonTipsModify( lineNumber, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) );
            return;
      }

      if ( Tokens[ lineNumber ].empty() ) {
            return;
      }

      if ( isDeclareVariableLine( lineNumber, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) == thisLine_Done ) {
            return;
      }

      if ( isReturnLine( lineNumber, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) == thisLine_Done ) {
            if ( lineNumber == 23 ) {
                  Debug( "asas" );
            }
            return;
      }

      if ( isBreakContinue( lineNumber, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) == thisLine_Done ) {
            return;
      }

      vector < int > checkList;
      for ( int i = 0; i + 1 < (int) Tokens[ lineNumber ].size(); ++i ) {
            if ( isSpecialoperator( lineNumber, i, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) && TokenType[ lineNumber ][ i + 1 ] == "identifier" ) {
                  ++i;
                  checkList.push_back( i );
            }
            else if ( isSpecialoperator( lineNumber, i, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) ) {
                  errorsTips[ lineNumber + 1 ].insert( "Fix this Line" );
                  return;
            }
            else if ( TokenType[ lineNumber ][ i ] == "identifier" && isSpecialoperator( lineNumber, i + 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) ) {
                  checkList.push_back( i );
                  ++i;
            }
            else {
                  checkList.push_back( i );
            }
      }

      int useless = checking_Equation( lineNumber, checkList, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );

      return;
}

string addSemiColonTipsModify( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
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

int isDeclareVariableLine( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
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
      for ( int i = 1; i < (int) Tokens[ lineNumber ].size(); ++i ) {
            if ( Tokens[ lineNumber ][ i ] == "," || Tokens[ lineNumber ][ i ] == ";" ) {
                  if( checking_Equation( lineNumber, checkList, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) == thisLine_Done ) {
                        return thisLine_Done;
                  }
                  checkList.clear();
            }
            else {
                  if ( isSpecialoperator( lineNumber, i, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) && TokenType[ lineNumber ][ i + 1 ] == "identifier" ) {
                        ++i;
                        checkList.push_back( i );
                  }
                  else if ( isSpecialoperator( lineNumber, i, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) ) {
                        errorsTips[ lineNumber + 1 ].insert( "Fix this Line" );
                        return thisLine_Done;
                  }
                  else if ( TokenType[ lineNumber ][ i ] == "identifier" && isSpecialoperator( lineNumber, i + 1, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) ) {
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

int isReturnLine( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      if ( Tokens[ lineNumber ][ 0 ] != "return" ) {
            return thisLine_NotFinish;
      }

      for ( int i = 0; i < (int) functions.size(); ++i ) {
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
                        for ( int i = 1; i + 1 < (int) Tokens[ lineNumber ].size(); ++i ) {
                              checkList.push_back( i );
                        }

                        checking_Equation( lineNumber, checkList, totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses );
                        return thisLine_Done;
                  }
            }
      }

      errorsTips[ lineNumber + 1 ].insert( "This Line is Out of any Function" );
      return thisLine_Done;
}

int isBreakContinue( int lineNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
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

bool isSpecialoperator( int lineNumber, int columnNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses  )
{
      if ( (int) TokenType[ lineNumber ].size() <= columnNumber || TokenType[ lineNumber ][ columnNumber ] != "operator" || Tokens[ lineNumber ][ columnNumber ].size() > 2 ) {
            return false;
      }

      if ( Tokens[ lineNumber ][ columnNumber ] == "++"  || Tokens[ lineNumber ][ columnNumber ] == "--" ) {
            return true;
      }
      else {
            return false;
      }
}

int checking_Equation( int lineNumber, vector < int > checkList, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses  )
{
      if ( checkList.size() % 2 == 0 && checkList.size() ) {
            errorsTips[ lineNumber + 1 ].insert( "Fix this Line" );
            return thisLine_Done;
      }

      for ( int i = 0; i < (int) checkList.size(); ++i ) {
            if ( i % 2 == 0 && ( TokenType[ lineNumber ][ checkList[ i ] ] != "identifier" && TokenType[ lineNumber ][ checkList[ i ] ] != "integer" && TokenType[ lineNumber ][ checkList[ i ] ] != "double") ) {
                  errorsTips[ lineNumber + 1 ].insert( "Fix this Line" );
                  return thisLine_Done;
            }

            if ( i % 2 == 1 && !validoperator( lineNumber, checkList[ i ], totalLine, Tokens, TokenType, isFinish, errorsTips, fors, functions, whiles, do_whiles, ifs, else_ifs, elses ) ) {
                  errorsTips[ lineNumber + 1 ].insert( "Fix this Line" );
                  return thisLine_Done;
            }
      }

      return thisLine_NotFinish;
}

bool validoperator( int lineNumber, int columnNumber, int totalLine, vector < string > Tokens[], vector < string > TokenType[],  bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors, vector < func > &functions,
               vector < while_struct > &whiles, vector < do_while_struct > &do_whiles, vector < if_struct > &ifs, vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
{
      if ( (int) TokenType[ lineNumber ].size() <= columnNumber || TokenType[ lineNumber ][ columnNumber ] != "operator" || Tokens[ lineNumber ][ columnNumber ].size() > 2 ) {
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


