
/*   https://www.cs.uic.edu/~troy/spring01/eecs473/mp2_473.html   */

#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;


#define thisLine_Done           1
#define thisLine_Error          2
#define thisLine_NotFinish      3


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

struct for_struct
{
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

struct while_struct
{
      int startLine;
      int endLine;
      vector < string > condition;
      vector < string > conditionType;
      int statement_text_start;
      int statement_text_end;
};

struct do_while_struct
{
      int startLine;
      int endLine;
      vector < string > condition;
      vector < string > conditionType;
      int statement_text_start;
      int statement_text_end;
};

struct else_struct
{
      int startLine;
      int endLine;
      int statement_text_start;
      int statement_text_end;
};

struct else_if_struct
{
      int startLine;
      int endLine;
      int statement_text_start;
      int statement_text_end;
      vector < string > condition;
      vector < string > conditionType;
};

struct if_struct
{
      int startLine;
      int endLine;
      int statement_text_start;
      int statement_text_end;
      vector < string > condition;
      vector < string > conditionType;
      vector < else_struct > elses;
      vector < else_if_struct > if_elses;
};


vector < for_struct > fors;
vector < func > functions;
vector < while_struct > whiles;
vector < do_while_struct > do_whiles;
vector < if_struct > ifs;
int totalLine = 0;
vector < string > TokenType[ 100 ];
vector < string > Tokens[ 100 ];
bool isFinish[ 100 ], haveERROR[ 100 ];
vector < vector < string > > allVariable;
/*struct perlinestruct
{
      int line;
      string text;
};
perlinestruct perline[ 100 ];
vector < string > lineNumber[ 100 ];
vector < string > position[ 100 ];
*/



// ALL FUNCTIONS PROTOTYPE
string trim_left( string st, char ch );
string trim_right( string &st, char ch );
string trim_both( string st, char ch );
bool isDigit( char ch );
bool isCapitalLetter( char ch );
bool isSmallLetter( char ch );
bool isLetter( char ch );
bool isNumber( string st );
bool validVariableName( string st );
bool availableVariable( string var, set < string > inScope );
bool validOparetor( int lineNumber, int columnNumber );
bool isSpecialOparetor( int lineNumber, int columnNumber );
bool isFunction( int LN );
bool isFor( int LN );
bool isWhile( int LN );
bool isDOWhile( int LN );
bool isIF( int LN );
void checking_statement( int lineNumber );
void findGroup( int startLine, int endLine );
void headerFile_check( int LN );
void find_MAIN_function();
void initialize_Checking( int LN );
void check_THIS_Line ( int LN );
void syntaxChecking();
int checking_Equation( int lineNumber, vector < int > checkList );
int isDeclareVariable( int lineNumber );
int strTint( string str );
int forGroup( int i );
int functionGroup( int i );
int whileGroup( int i );
int doWhileGroup( int i );
int ifGroup( int i );
int headerFiles_check( int LN );
else_if_struct elseIfGroup( int i );
else_struct elseGroup( int i );




string trim_left( string st, char ch )
{
      while ( st.size() && st[ 0 ] == ch )
            st.erase( 0, 1 );

      return st;
}

string trim_right( string &st, char ch )
{
      while ( st.size() && st[ st.size() - 1 ] == ch )
            st.erase( st.size() - 1, 1 );

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
      for ( int i = 0; i < st.size(); ++i )
            if ( !isDigit( st[ i ] ) )
                  return false;

      return true;
}

bool validVariableName( string st )
{
      if ( !( isLetter( st[ 0 ] ) || st[ 0 ] == '_' ) )
            return false;

      for ( int i = 1; i < st.size(); ++i )
            if ( !( isLetter( st[ i ] ) || isDigit( st[ i ] ) || st[ i ] == '_' ) )
                  return false;

      return true;
}

bool availableVariable( string var, set < string > inScope )
{
      return inScope.find( var ) == inScope.end();
}

bool validOparetor( int lineNumber, int columnNumber )
{
      if ( TokenType[ lineNumber ].size() <= columnNumber || TokenType[ lineNumber ][ columnNumber ] != "oparetor" || Tokens[ lineNumber ][ columnNumber ].size() > 2 ) {
            return false;
      }

      set < char > goodOparetor;
      goodOparetor.insert( '+' );
      goodOparetor.insert( '-' );
      goodOparetor.insert( '&' );
      goodOparetor.insert( '|' );
      goodOparetor.insert( '=' );
      goodOparetor.insert( '>' );
      goodOparetor.insert( '<' );
      goodOparetor.insert( '*' );
      goodOparetor.insert( '/' );

      string currentToken = Tokens[ lineNumber ][ columnNumber ];
      if ( currentToken.size() == 1 && goodOparetor.count( currentToken[ 0 ] ) ) {
            return true;
      }
      else if ( currentToken.size() == 2 && goodOparetor.count( currentToken[ 0 ] ) && goodOparetor.count( currentToken[ 1 ] ) ) {
            return true;
      }
      else {
            return false;
      }
}

bool isSpecialOparetor( int lineNumber, int columnNumber )
{
      if ( TokenType[ lineNumber ].size() <= columnNumber || TokenType[ lineNumber ][ columnNumber ] != "oparetor" || Tokens[ lineNumber ][ columnNumber ].size() > 2 ) {
            return false;
      }
      if ( Tokens[ lineNumber ][ columnNumber ] == "++"  || Tokens[ lineNumber ][ columnNumber ] == "--" ) {
            return true;
      }
}

int checking_Equation( int lineNumber, vector < int > checkList )
{
      if ( checkList.size() % 2 == 0 || !checkList.size() ) {
            cout << "Line No - " << lineNumber + 1 << " 5 problem in this line\n";
            return thisLine_Done;
      }

      for ( int i = 0; i < checkList.size(); ++i ) {
            if ( i % 2 == 0 && TokenType[ lineNumber ][ checkList[ i ] ] != "indentifier" ) {
                  cout << "Line No - " << lineNumber + 1 << " 3 problem in this line\n";
                  return thisLine_Done;
            }
            if ( i % 2 == 1 && !validOparetor( lineNumber, checkList[ i ] ) ) {
                  cout << "Line No - " << lineNumber + 1 << " " << i << " 4 problem in this line\n";
                  return thisLine_Done;
            }
      }
      return thisLine_NotFinish;
}

int isDeclareVariable( int lineNumber )
{
      set < string > rightType;
      rightType.insert( "char" );
      rightType.insert( "int" );
      rightType.insert( "double" );

      if ( !rightType.count( Tokens[ lineNumber ][ 0 ] ) ) {
            return thisLine_NotFinish;
      }

      if ( Tokens[ lineNumber ].size() <= 2 ) {
            cout << "Line No - " << lineNumber + 1 << " 1 problem in this line\n";
            return thisLine_Done;
      }

      vector < int > checkList;
      for ( int i = 1; i < Tokens[ lineNumber ].size(); ++i ) {
            if ( Tokens[ lineNumber ][ i ] == "," || Tokens[ lineNumber ][ i ] == ";" ) {
                  cout << i << " ";
                  if( checking_Equation( lineNumber, checkList ) == thisLine_Done ) {
                        return thisLine_Done;
                  }
                  checkList.clear();
            }
            else {
                  if ( isSpecialOparetor( lineNumber, i ) && TokenType[ lineNumber ][ i + 1 ] == "indentifier" ) {
                        ++i;
                        checkList.push_back( i );
                  }
                  else if ( isSpecialOparetor( lineNumber, i ) ) {
                        cout << "Line No - " << lineNumber + 1 << " 6 problem in this line\n";
                        return thisLine_Done;
                  }
                  else if ( TokenType[ lineNumber ][ i ] == "indentifier" && isSpecialOparetor( lineNumber, i + 1 ) ) {
                        checkList.push_back( i );
                        ++i;
                  }
                  else {
                        checkList.push_back( i );
                  }
            }
      }
      cout << "ahsd";
      return thisLine_Done;
}

void checking_statement( int lineNumber )
{
      //, vector < string > availableVariable
      //cout << Tokens[ lineNumber ].size() << " ";
      //return;
      if ( Tokens[ lineNumber ].size() && Tokens[ lineNumber ].back() != ";" ) {
            cout << "Line No - " << lineNumber + 1 << " 1 problem in this line\n";
            //return thisLine_Done;
            return;
      }
      if ( Tokens[ lineNumber ].empty() ) {
            //return thisLine_Done;
            return;
      }

      if ( isDeclareVariable( lineNumber ) == thisLine_Done ) {
            //return thisLine_Done;
            return;
      }

      /*//int iL = 0 + isSpecialOparetor( lineNumber, 0 ), iR = Tokens[ lineNumber ].size() - isSpecialOparetor( lineNumber, Tokens[ lineNumber ].size() - 2 );
      //--iR;
     // if ( iL >= iR ) {
           //  cout << "Line No - " << lineNumber + 1 << " 2 problem in this line\n";
            // return;
      //}
      //cout << iL << " " << iR << " ";*/

      vector < int > checkList;
      for ( int i = 0; i < Tokens[ lineNumber ].size() - 1; ++i ) {
            if ( isSpecialOparetor( lineNumber, i ) && TokenType[ lineNumber ][ i + 1 ] == "indentifier" ) {
                  ++i;
                  checkList.push_back( i );
            }
            else if ( isSpecialOparetor( lineNumber, i ) ) {
                  cout << "Line No - " << lineNumber + 1 << " 6 problem in this line\n";
                  //return thisLine_Done;
                  return;
            }
            else if ( TokenType[ lineNumber ][ i ] == "indentifier" && isSpecialOparetor( lineNumber, i + 1 ) ) {
                  checkList.push_back( i );
                  ++i;
            }
            else {
                  checkList.push_back( i );
            }

      }

      int useless = checking_Equation( lineNumber, checkList );

      //return thisLine_Done;
      return;
      /*if ( checkList.size() % 2 == 0 ) {
            cout << "Line No - " << lineNumber + 1 << " 5 problem in this line\n";
            return;
      }

      for ( int i = 0; i < checkList.size(); ++i ) {
            if ( i % 2 == 0 && TokenType[ lineNumber ][ checkList[ i ] ] != "indentifier" ) {
                  cout << "Line No - " << lineNumber + 1 << " 3 problem in this line\n";
                  return;
            }
            if ( i % 2 == 1 && !validOparetor( lineNumber, checkList[ i ] ) ) {
                  cout << "Line No - " << lineNumber + 1 << " " << i << " 4 problem in this line\n";
                  return;
            }
      }*/
      int a, b;
      //if ( a == b == a )  return;
      //a += a++++b;
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

void printFor()
{
      for ( int i = 0; i < fors.size(); ++i ) {
              cout << i << "th FOR:\n\n";
          cout << "For Start Line: " << fors[ i ].startLine << endl;
          cout << "Statement Text start line: " << fors[ i ].statement_text_start << endl;
          cout << "Statement end start line: " << fors[ i ].statement_text_end << endl;
          cout << "For end Line: " << fors[ i ].endLine << endl;
          cout << "\ninitialize:\n";
          for(int a=0; a<fors[ i ].initialize.size(); a++)
          {
              cout << fors[ i ].initialize[a] << " ";
          }
          cout << "\ninitializeType:\n";
          for(int a=0; a<fors[ i ].initializeType.size(); a++)
          {
              cout << fors[ i ].initializeType[a] << " ";
          }
          cout << "\n\nCondition:\n";
          for(int a=0; a<fors[ i ].condition.size(); a++)
          {
              cout << fors[ i ].condition[a] << " ";
          }
          cout << "\nConditionType:\n";
          for(int a=0; a<fors[ i ].conditionType.size(); a++)
          {
              cout << fors[ i ].conditionType[a] << " ";
          }
          cout << "\n\nChange:\n";
          for(int a=0; a<fors[ i ].change.size(); a++)
          {
              cout << fors[ i ].change[a] << " ";
          }
          cout << "\nChangeType:\n";
          for(int a=0; a<fors[ i ].changeType.size(); a++)
          {
              cout << fors[ i ].changeType[a] << " ";
          }
          cout << endl;
      }
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
            cout << "find error\n";
            return i;
      }

      stack < int > temp;
      int h = fa.statement_text_start - 1;
      temp.push( 1 );
      while( !temp.empty() ) {
            //cout << i;
            for ( int k = 0; k < TokenType[ h ].size(); k++ ) {
                  if ( Tokens[ h ][ k ].compare( "{" ) == 0 ) {
                        temp.push( 1 );
                  }
                  if ( Tokens[ h ][ k ].compare( "}" ) == 0 ) {
                        temp.pop();
                  }
            }
            h++;
      }

      fa.statement_text_end = h - 1;
      fa.endLine = h;
      fors.push_back( fa );
      i = fa.endLine - 1;

      return i;
}

int functionGroup( int i )
{
      //cout << i << " ";
      if ( Tokens[ i ][ TokenType[ i ].size() - 2 ].compare( ")" ) == 0 && Tokens[ i ][ TokenType[ i ].size() - 1 ].compare( ";" ) == 0 ) {
            cout << "function protoType\n";
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
                        if ( Tokens[ i ][ j ].compare( ")" ) == 0 )
                              break;
                        f.parameter.push_back( Tokens[ i ][ j + 2 ] );
                        f.parameterType.push_back( Tokens[ i ][ j + 1 ] );
                        j += 3;
                  }
            }
            f.statement_text_start = i + 3;
            if ( Tokens[ i ][ TokenType[ i ].size() - 1 ].compare( "{" ) == 0 ) {
                  f.statement_text_start = i + 2;
            }
            stack < int > temp;
            int h = f.statement_text_start - 1;
            temp.push( 1 );
            while ( !temp.empty() ) {
                  //cout << i;
                  for ( int k = 0; k < TokenType[ h ].size(); k++ ) {
                        if ( Tokens[ h ][ k ].compare( "{" ) == 0 )
                              temp.push( 1 );
                        if ( Tokens[ h ][ k ].compare( "}" ) == 0 ) {
                              temp.pop();
                        }
                  }
                  h++;
            }
            f.statement_text_end = h - 1;
            f.endLine = h;
            functions.push_back( f );
            i = h - 1;
        //statement & endline
      }
      return i;
}

int whileGroup(int i)
{
    int f = 2;
    while_struct fa;
    fa.startLine = i+1;
    fa.statement_text_start = i+3;
    if(Tokens[i][TokenType[i].size()-1].compare("{") == 0)
    {
        fa.statement_text_start = i+2;
    }
    while(Tokens[i][f].compare(")") != 0)
    {
        fa.condition.push_back(Tokens[i][f]);
        fa.conditionType.push_back(TokenType[i][f]);
        f++;
    }
    stack <int> temp;
    int h = fa.statement_text_start - 1;
    temp.push(1);
    while(!temp.empty())
    {
        //cout << i;
        for(int k=0; k<TokenType[h].size(); k++)
        {
            if(Tokens[h][k].compare("{") == 0)
                temp.push(1);
            if(Tokens[h][k].compare("}") == 0)
            {
                temp.pop();
            }
        }
        h++;
    }
    fa.statement_text_end = h-1;
    fa.endLine = h;
    whiles.push_back(fa);
    i = fa.endLine-1;
    return i;
}

int doWhileGroup(int i)
{
    int f = 2;
    do_while_struct fa;
    fa.startLine = i+1;
    //cout << Tokens[i][0] << " " << i;
    fa.statement_text_start = i+3;
    if(Tokens[i][TokenType[i].size()-1].compare("{") == 0)
    {
        fa.statement_text_start = i+2;
    }
    stack <int> temp;
    int h = fa.statement_text_start - 1;
    temp.push(1);
    while(!temp.empty())
    {
        //cout << i;
        for(int k=0; k<TokenType[h].size(); k++)
        {
            if(Tokens[h][k].compare("{") == 0)
                temp.push(1);
            if(Tokens[h][k].compare("}") == 0)
            {
                temp.pop();
            }
        }
        h++;
    }
    //cout << h;//32
    //if()
    fa.statement_text_end = h-1;
    fa.endLine = h+1;
    if(Tokens[h-1].size() > 1 && Tokens[h-1][1].compare("while") == 0)
    {
        fa.endLine = h;
        f = 3;
        //cout << h;
    }
    //
    while(Tokens[fa.endLine-1][f].compare(")") != 0)
    {
        fa.condition.push_back(Tokens[fa.endLine-1][f]);
        fa.conditionType.push_back(TokenType[fa.endLine-1][f]);
        f++;
    }
    do_whiles.push_back(fa);
    i = fa.endLine-1;
    return i;
}

else_if_struct elseIfGroup(int i)
{
    int f = 3;
    else_if_struct fa;
    fa.startLine = i+1;//24
    fa.statement_text_start = i+3;//26
    while(Tokens[i][f].compare(")") != 0)
    {
        fa.condition.push_back(Tokens[i][f]);
        fa.conditionType.push_back(TokenType[i][f]);
        f++;
    }
    if(Tokens[i][TokenType[i].size()-1].compare("{") == 0)
    {
        fa.statement_text_start = i+2;//25
    }
    if(Tokens[i][TokenType[i].size()-1].compare("{") != 0 && (Tokens[i+1].size() > 0 && Tokens[i+1][0].compare("{") != 0))
    {
        //cout << "jja" << Tokens[i][TokenType[i].size()-1] << Tokens[i+1][0] << i;
        fa.statement_text_start = i+2;
        fa.statement_text_end = i+2;
        fa.endLine = i+2;
        i = i + 1;
    }
    else
    {
        stack <int> temp;
        int h = fa.statement_text_start - 1;
        temp.push(1);
        while(!temp.empty())
        {
            //cout << i;
            for(int k=0; k<TokenType[h].size(); k++)
            {
                if(Tokens[h][k].compare("{") == 0)
                    temp.push(1);
                if(Tokens[h][k].compare("}") == 0)
                {
                    temp.pop();
                }
            }
            h++;
        }
        fa.statement_text_end = h-1;
        fa.endLine = h;
        //whiles.push_back(fa);
        //i = fa.endLine-1;
    }
    return fa;
}

else_struct elseGroup(int i)
{
    else_struct fa;
    fa.startLine = i+1;
    fa.statement_text_start = i+3;

    if(Tokens[i][TokenType[i].size()-1].compare("{") == 0)
    {
        fa.statement_text_start = i+2;
    }
    if(Tokens[i][TokenType[i].size()-1].compare("{") != 0 && (Tokens[i+1].size() > 0 && Tokens[i+1][0].compare("{") != 0))
    {
        fa.statement_text_start = i+2;
        fa.statement_text_end = i+2;
        fa.endLine = i+2;
        i = i + 1;
    }
    else
    {
        stack <int> temp;
        int h = fa.statement_text_start - 1;
        temp.push(1);
        while(!temp.empty())
        {
            //cout << i;
            for(int k=0; k<TokenType[h].size(); k++)
            {
                if(Tokens[h][k].compare("{") == 0)
                    temp.push(1);
                if(Tokens[h][k].compare("}") == 0)
                {
                    temp.pop();
                }
            }
            h++;
        }
        fa.statement_text_end = h-1;
        fa.endLine = h;
        //cout << "h = " << h;
        //whiles.push_back(fa);
        //i = fa.endLine-1;
    }
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
            temp.push( 1 );
            while ( !temp.empty() ) {
                  //cout << i;
                  for ( int k = 0; k < TokenType[ h ].size(); k++ ) {
                        if ( Tokens[ h ][ k ].compare( "{" ) == 0 )
                              temp.push( 1 );
                        if ( Tokens[ h ][ k ].compare( "}" ) == 0 )
                              temp.pop();
                  }
                  h++;
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
      //cout << i+1;
      while ( 1 ) {
            if ( TokenType[ i ].size() > 1 && Tokens[ i ][ 0 ].compare( "else" ) == 0  && Tokens[ i ][ 1 ].compare( "if" ) == 0 ) {
                  //
                  else_if_struct fi = elseIfGroup( i );
                  fa.if_elses.push_back( fi );
                  i = fi.endLine;//cout << i << endl;
            }
            else if ( TokenType[ i ].size() > 0 && Tokens[ i ][ 0 ].compare( "else" ) == 0 ) {
                  else_struct fy = elseGroup( i );//
                  fa.elses.push_back( fy );
                  i = fy.endLine;
                  break;
            }
            else {
                  break;
            }
      }
      ifs.push_back( fa );
      i--;//
      return i;
      //
}

void findGroup( int startLine, int endLine )
{
      for ( int i = startLine; i <= endLine; i++ ) {
            if ( TokenType[ i ].size() > 3 && TokenType[ i ][ 0 ].compare( "keyword" ) == 0  && TokenType[ i ][ 1 ].compare( "indentifier" ) == 0  && Tokens[ i ][ 2 ].compare( "(" ) == 0  && ( Tokens[ i ][ 3 ] == ")" || TokenType[ i ][ 3 ] == "keyword" ) ) { //function
                  i = functionGroup(i);
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

      string H;

      for ( int i = 0; i < Tokens[ LN ].size(); ++i ) {
            H += Tokens[ LN ][ i ];
      }

      for ( int i = 0; i < HEADER.size(); ++i ) {
            if ( H == HEADER[ i ] )
                  return;
      }

      haveERROR[ LN ] = true;
      cout << "Line No: " << LN + 1 << "->" << "Wrong HEADER File or ERROR\n";
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
            //cout << functions[ i ].fTokens << " ";
            if ( functions[ i ].fTokens == "main" )
                  C++;
      }

      if ( C == 1 )
            return;
      else if ( C > 1 )
            cout << "Big ERROR: " << C << " MAIN function in your C file\n";
      else
            cout << "Big ERROR: No MAIN function in your C file\n";
}

void initialize_Checking( int LN )
{
      // header file check
      LN = headerFiles_check( LN );  //DONE
      // find MAIN function
      find_MAIN_function();
}

bool isFunction( int LN )
{
      for ( int i = 0; i < functions.size(); ++i ) {
            //cout << functions[ i ].startLine << " ";
            if ( functions[ i ].startLine == LN + 1 ) {
                  /*cout << functions[ i ].fTokens << "\n" << functions[ i ].startLine;
                  cout << " " << functions[ i ].statement_text_start << " ";
                  cout << functions[ i ].statement_text_end << " " << functions[ i ].endLine << "\n";*/
                  // Function START -> END line checking

                  // Function syntax final check -> BAKI
                  //->

                  for ( int j = functions[ i ].startLine; j < functions[ i ].statement_text_start; ++j ) {
                        isFinish[ j - 1 ] = true;
                        //cout << j << "-> ok\n";
                  }

                  for ( int j = functions[ i ].statement_text_end + 1; j <= functions[ i ].endLine; ++j ) {
                        isFinish[ j - 1 ] = true;
                        //cout << j << "-> ok\n";
                  }

                  // <-

                  findGroup( functions[ i ].statement_text_start - 1, functions[ i ].statement_text_end - 1 );

                  for ( int j = functions[ i ].statement_text_start; j <= functions[ i ].statement_text_end; ++j ) {
                        if ( !isFinish[ j - 1 ] )
                              check_THIS_Line( j - 1 );
                        //cout << j << "-> CK\n";
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
                  // start - end check kore finish true kore dibo
                  //LM =
                  // BAKI ase ekhane

                  for ( int j = fors[ i ].startLine; j <= fors[ i ].endLine; ++j )
                        isFinish[ j - 1 ] = true;

                  return true;
            }
      }

      return false;
}

bool isWhile( int LN )
{
      for ( int i = 0; i < whiles.size(); ++i ) {
            if ( whiles[ i ].startLine == LN + 1 ) {
                  // start - end check kore finish true kore dibo
                  //LM =
                  // BAKI ase ekhane

                  for ( int j = whiles[ i ].startLine; j <= whiles[ i ].endLine; ++j )
                        isFinish[ j - 1 ] = true;

                  return true;
            }
      }

      return false;
}

bool isDOWhile( int LN )
{
      for ( int i = 0; i < do_whiles.size(); ++i ) {
            if ( do_whiles[ i ].startLine == LN + 1 ) {
                  // start - end check kore finish true kore dibo
                  //LM =
                  // BAKI ase ekhane

                  for ( int j = do_whiles[ i ].startLine; j <= do_whiles[ i ].endLine; ++j )
                        isFinish[ j - 1 ] = true;

                  return true;
            }
      }

      return false;
}

bool isIF( int LN )
{
      for ( int i = 0; i < ifs.size(); ++i ) {
            if ( ifs[ i ].startLine == LN + 1 ) {
                  // start - end check kore finish true kore dibo
                  //LM =
                  // BAKI ase ekhane

                  for ( int j = ifs[ i ].startLine; j <= ifs[ i ].endLine; ++j )
                        isFinish[ j - 1 ] = true;

                  return true;
            }
      }

      return false;
}

void check_THIS_Line ( int LN )
{
      isFinish[ LN ] = true;

      if ( isFunction( LN ) )
            return;
      else if ( isFor( LN ) )
            return;
      else if ( isWhile( LN ) )
            return;
      else if ( isDOWhile( LN ) )
            return;
      else if ( isIF( LN ) )
            return;
      else
            checking_statement( LN );
}

void syntaxChecking()
{
      int LN = 0;
      initialize_Checking( LN );

      for ( int i = 0; i < totalLine; ++i ) {
            if ( !isFinish[ i ] ) {
                  check_THIS_Line( i );
            }
      }
}

int main()
{
      system("g++ HW1.cpp -o HW1");
      system("HW1");

      FILE *fp;
      string str, Text, strg1, strg2, strg3, strg4;
      char ch;

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

      findGroup( 0, 100 );
      syntaxChecking();
      //printFor();




      return 0;
}
