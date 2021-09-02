
/*   ALLAH is Almighty.....  */

#include <bits/stdc++.h>
#include "Header.h"
using namespace std;


void findGroup( int startLine, int endLine, int totalLine, parameterStruct )
{
      for ( int i = startLine; i <= endLine; i++ ) {
            if ( TokenType[ i ].size() > 3 && TokenType[ i ][ 0 ].compare( "keyword" ) == 0  && TokenType[ i ][ 1 ].compare( "identifier" ) == 0  && Tokens[ i ][ 2 ].compare( "(" ) == 0  && ( Tokens[ i ][ 3 ] == ")" || TokenType[ i ][ 3 ] == "keyword" ) ) { //function
                  i = functionGroup( i, Tokens, TokenType, totalLine, isFinish, errorsTips, functions );
            }
            else if ( Tokens[ i ].size() > 4 && Tokens[ i ][ 0 ].compare( "for" ) == 0 && Tokens[ i ][ 1 ].compare( "(" ) == 0 ) { //for
                  i = forGroup( i, Tokens, TokenType, totalLine, isFinish, errorsTips, fors );
            }
            else if ( Tokens[ i ].size() > 3 && Tokens[ i ][ 0 ].compare( "while" ) == 0 && Tokens[ i ][ 1 ].compare( "(" ) == 0 && Tokens[ i ][ 2 ].compare( ")" ) != 0 ) { //while
                  i = whileGroup( i, Tokens, TokenType, totalLine, isFinish, errorsTips, whiles );
            }
            else if ( ( Tokens[ i ].size() <= 2 && Tokens[ i ].size() >= 1 ) && Tokens[ i ][ 0 ].compare( "do" ) == 0 ) { //do-while
                  i = doWhileGroup( i, Tokens, TokenType, totalLine, isFinish, errorsTips, do_whiles );
            }
            else if ( Tokens[ i ].size() > 3 && Tokens[ i ][ 0 ].compare( "if" ) == 0 ) {
                  i = ifGroup( i, Tokens, TokenType, totalLine, isFinish, errorsTips, ifs, else_ifs, elses );
            }
      }
}

int functionGroup( int i, vector < string > Tokens[], vector < string > TokenType[], int totalLine, bool isFinish[], set < string > errorsTips[], vector < func > &functions )
{
      if ( Tokens[ i ][ TokenType[ i ].size() - 2 ].compare( ")" ) == 0 && Tokens[ i ][ TokenType[ i ].size() - 1 ].compare( ";" ) == 0 ) {
            //cout << "function protoType\n";
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
                        if ( j >= (int) Tokens[ i ].size() || ( Tokens[ i ][ j ] != "(" && Tokens[ i ][ j ] != "," && Tokens[ i ][ j ] != ")" ) ) {
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
                  for ( int k = 0; k < (int) TokenType[ h ].size(); k++ ) {
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

int forGroup( int i, vector < string > Tokens[], vector < string > TokenType[], int totalLine, bool isFinish[], set < string > errorsTips[], vector < for_struct > &fors )
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

      if ( Tokens[ i ][ TokenType[ i ].size() - 1 ].compare( "{" ) != 0 && ( Tokens[ i + 1 ].size() > 0 && Tokens[ i + 1 ][ 0 ].compare( "{" ) != 0 ) ) {
            fa.statement_text_start = i + 2;
            fa.statement_text_end = i + 2;
            fa.endLine = i + 2;
            i = i + 1;
            fors.push_back( fa );
            i = fa.endLine - 1;
            return i;
      }

      stack < int > temp;
      int h = fa.statement_text_start - 1;
      temp.push( h - 1 );

      while( !temp.empty() ) {
            for ( int k = 0; k < (int) TokenType[ h ].size(); k++ ) {
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

int whileGroup( int i, vector < string > Tokens[], vector < string > TokenType[], int totalLine, bool isFinish[], set < string > errorsTips[], vector < while_struct > &whiles )
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
            for ( int k  =0; k < (int) TokenType[ h ].size(); k++ ) {
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

int doWhileGroup( int i, vector < string > Tokens[], vector < string > TokenType[], int totalLine, bool isFinish[], set < string > errorsTips[], vector < do_while_struct > &do_whiles )
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
            for ( int k = 0; k < (int) TokenType[ h ].size(); k++ ) {
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

else_if_struct elseIfGroup( int i, vector < string > Tokens[], vector < string > TokenType[], int totalLine, bool isFinish[], set < string > errorsTips[], vector < if_struct > &ifs,
                            vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
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
                  for ( int k = 0; k < (int) TokenType[ h ].size(); k++ ) {
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

else_struct elseGroup( int i, vector < string > Tokens[], vector < string > TokenType[], int totalLine, bool isFinish[], set < string > errorsTips[], vector < if_struct > &ifs,
                            vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
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
                  for ( int k = 0; k < (int) TokenType[ h ].size(); k++ ) {
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

int ifGroup( int i, vector < string > Tokens[], vector < string > TokenType[], int totalLine, bool isFinish[], set < string > errorsTips[], vector < if_struct > &ifs,
                            vector < else_if_struct > &else_ifs, vector < else_struct > &elses )
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
                  for ( int k = 0; k < (int) TokenType[ h ].size(); k++ ) {
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
                  else_if_struct fi = elseIfGroup( i, Tokens, TokenType, totalLine, isFinish, errorsTips, ifs, else_ifs, elses );
                  fa.if_elses.push_back( fi );
                  i = fi.endLine;
            }
            else if ( TokenType[ i ].size() > 0 && Tokens[ i ][ 0 ].compare( "else" ) == 0 ) {
                  else_struct fy = elseGroup( i, Tokens, TokenType, totalLine, isFinish, errorsTips, ifs, else_ifs, elses );
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
