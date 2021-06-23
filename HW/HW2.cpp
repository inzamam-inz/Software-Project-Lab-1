
/*   ALLAH is Almighty.....  */
/*   https://www.cs.uic.edu/~troy/spring01/eecs473/mp2_473.html   */

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

struct printCFile {
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
            codeLine.push_back( codeText );             

            stringstream X( codeText );
            while ( getline( X, str, '\n' ) ) {
                  codeLine.push_back( str );
            }
                                
      }

      void printThisLine( int LN ) {
            cout << "\"" << codeLine[ LN ] << "\"\n";
      }

      void printTips( string str ) {
            cout << "  Tips : " << str << ".\n";
      }
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
set < string > errosTips[ 100 ];                       
printCFile CFILE;
                      
 
               
                  
  
                             
                                    
                                  
  



                          
string trim_left( string st, char ch );
string trim_right( string &st, char ch );
string trim_both( string st, char ch );
bool isDigit( char ch );
bool isCapitalLetter( char ch );
bool isSmallLetter( char ch );
bool isLetter( char ch );
bool isNumber( string st );
bool validVariableName( string st );
bool availableVariable( string var, set < string > &inScope );
bool validoperator( int lineNumber, int columnNumber );
bool isSpecialoperator( int lineNumber, int columnNumber );
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
int isDeclareVariableLine( int lineNumber );
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
      if ( !( isLetter( st[ 0 ] ) || st[ 0 ] == '_' ) )
            return false;

      for ( int i = 1; i < st.size(); ++i )
            if ( !( isLetter( st[ i ] ) || isDigit( st[ i ] ) || st[ i ] == '_' ) )
                  return false;

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
                                                                
                                                  
                                                   

            errosTips[ lineNumber + 1 ].insert( "Fixed this Line" );
            return thisLine_Done;
      }

                                 
                                      
         

      for ( int i = 0; i < checkList.size(); ++i ) {
            if ( i % 2 == 0 && ( TokenType[ lineNumber ][ checkList[ i ] ] != "identifier" && TokenType[ lineNumber ][ checkList[ i ] ] != "integer" && TokenType[ lineNumber ][ checkList[ i ] ] != "double") ) {
                                                                                            
                                                                       
                                                                      
                                                        
                                                         
                  errosTips[ lineNumber + 1 ].insert( "Fixed this Line" );
                                
                  return thisLine_Done;
            }
            if ( i % 2 == 1 && !validoperator( lineNumber, checkList[ i ] ) ) {
                                                                                                        

                                                                      
                                                        
                                                         
                  errosTips[ lineNumber + 1 ].insert( "Fixed this Line" );
                                 
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
                                                                
                                                  
                                                      
            errosTips[ lineNumber + 1 ].insert( "Need variable name" );
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
                                                                                                  
                                                                            
                                                              
                                                               
                        errosTips[ lineNumber + 1 ].insert( "Fixed this Line" );
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
                                                                
                                                    
            if ( Tokens[ lineNumber ][ 0 ] == "break" )
                  errosTips[ lineNumber + 1 ].insert( "Replace with \"break;\"" );
                                                                 
            if ( Tokens[ lineNumber ][ 0 ] == "continue" )
                  errosTips[ lineNumber + 1 ].insert( "Replace with \"continue;\"" );
                                                                    
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
                                                                            
                                                              
                                                                                                                    
                        errosTips[ lineNumber + 1 ].insert( "Function name '" + functions[ i ].fTokens + "' have void return type" );
                        return thisLine_Done;
                  }
                  else if ( functions[ i ].returnType != "void" && Tokens[ lineNumber ].size() <= 2 ) {
                                                                            
                                                              
                                                                                                                                           
                        errosTips[ lineNumber + 1 ].insert( "Function name '" + functions[ i ].fTokens + "' have return type, but return value not Found" );
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
                
                                               
                                                          
                                            
                                                              
      errosTips[ lineNumber + 1 ].insert( "This Line is Out of any Function" );
      return thisLine_Done;
}

void checking_statement( int lineNumber )
{
                                             
                                                   
               
      if ( Tokens[ lineNumber ].size() && Tokens[ lineNumber ].back() != ";" ) {
                                                                
                                                  
                                                        
            errosTips[ lineNumber + 1 ].insert( "Add ';' in this line" );
                                            
                                   
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

         /int iL = 0 + isSpecialoperator( lineNumber, 0 ), iR = Tokens[ lineNumber ].size() - isSpecialoperator( lineNumber, Tokens[ lineNumber ].size() - 2 );
             
                         
                                                                                     
                      
         
                                         

      vector < int > checkList;
      for ( int i = 0; i < Tokens[ lineNumber ].size() - 1; ++i ) {
            if ( isSpecialoperator( lineNumber, i ) && TokenType[ lineNumber ][ i + 1 ] == "identifier" ) {
                  ++i;
                  checkList.push_back( i );
            }
            else if ( isSpecialoperator( lineNumber, i ) ) {
                                                                                            
                                                                      
                                                        
                                                         
                  errosTips[ lineNumber + 1 ].insert( "Fixed this Line" );
                                         
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
                                          
                                                                                  
                   
       

                                                    
                                                                                            
                                                                                        
                         
             
                                                                               
                                                                                                    
                         
             
         
      int a, b;
                                   
                    
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
                                                              
                                                
                                                               
            errosTips[ fa.startLine ].insert( "Expected ';' before ')' token" );
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
            errosTips[ temp.top() + 1 ].insert( "Expected identifier or '('" );
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
            int h = f.statement_text_start - 1;
            stack < int > temp;
            temp.push( h - 1 );
                             
            while ( !temp.empty() ) {
                              
                  for ( int k = 0; k < TokenType[ h ].size(); k++ ) {
                        if ( Tokens[ h ][ k ].compare( "{" ) == 0 )
                              temp.push( h );
                        if ( Tokens[ h ][ k ].compare( "}" ) == 0 ) {
                              temp.pop();
                        }
                  }
                  h++;
                  if ( h == totalLine )
                        break;
            }
            while ( !temp.empty() ) {
                  errosTips[ temp.top() + 1 ].insert( "Expected identifier or '('" );
                               
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
      while ( Tokens[ i ][ f ].compare(")") != 0 ) {
            fa.condition.push_back( Tokens[ i ][ f ] );
            fa.conditionType.push_back( TokenType[ i ][ f ] );
            f++;
      }
      stack < int > temp;
      int h = fa.statement_text_start - 1;
      temp.push( h - 1 );
      while ( !temp.empty() ) {
                        
            for ( int k  =0; k < TokenType[ h ].size(); k++ ) {
                  if ( Tokens[ h ][ k ].compare( "{" ) == 0 )
                        temp.push( h );
                  if ( Tokens[ h ][ k ].compare( "}" ) == 0 ) {
                        temp.pop();
                  }
            }
            h++;
            if ( h == totalLine )
                  break;
      }
      while ( !temp.empty() ) {
            errosTips[ temp.top() + 1 ].insert( "Expected identifier or '('" );
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
                  if( Tokens[ h ][ k ].compare( "{" ) == 0 )
                        temp.push( h );
                  if ( Tokens[ h ][ k ].compare( "}" ) == 0 ) {
                        temp.pop();
                  }
            }
            h++;
            if ( h == totalLine )
                  break;
      }
      while ( !temp.empty() ) {
            errosTips[ temp.top() + 1 ].insert( "Expected identifier or '('" );
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
                        if ( Tokens[ h ][ k ].compare( "{" ) == 0 )
                              temp.push( h );
                        if ( Tokens[ h ][ k ].compare( "}" ) == 0 ) {
                              temp.pop();
                        }
                  }
                  h++;
                  if ( h == totalLine )
                        break;
            }
            while ( !temp.empty() ) {
                  errosTips[ temp.top() + 1 ].insert( "Expected identifier or '('" );
                  temp.pop();
            }
            fa.statement_text_end = h - 1;
            fa.endLine = h;
                                   
                               
      }
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
                        if ( Tokens[ h ][ k ].compare( "{" ) == 0 )
                              temp.push( h );
                        if ( Tokens[ h ][ k ].compare( "}" ) == 0 ) {
                              temp.pop();
                        }
                  }
                  h++;
                  if ( h == totalLine )
                        break;
            }
            while ( !temp.empty() ) {
                  errosTips[ temp.top() + 1 ].insert( "Expected identifier or '('" );
                  temp.pop();
            }

            fa.statement_text_end = h - 1;
            fa.endLine = h;
                                  
                                   
                               
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
            temp.push( h - 1 );
            while ( !temp.empty() ) {
                              
                  for ( int k = 0; k < TokenType[ h ].size(); k++ ) {
                        if ( Tokens[ h ][ k ].compare( "{" ) == 0 )
                              temp.push( h );
                        if ( Tokens[ h ][ k ].compare( "}" ) == 0 )
                              temp.pop();
                  }
                  h++;
                  if ( h == totalLine )
                        break;
            }
            while ( !temp.empty() ) {
                  errosTips[ temp.top() + 1 ].insert( "Expected identifier or '('" );
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
            if ( TokenType[ i ].size() > 3 && TokenType[ i ][ 0 ].compare( "keyword" ) == 0  && TokenType[ i ][ 1 ].compare( "identifier" ) == 0  && Tokens[ i ][ 2 ].compare( "(" ) == 0  && ( Tokens[ i ][ 3 ] == ")" || TokenType[ i ][ 3 ] == "keyword" ) ) {           
                  i = functionGroup( i );
            }
            else if ( Tokens[ i ].size() > 4 && Tokens[ i ][ 0 ].compare( "for" ) == 0 && Tokens[ i ][ 1 ].compare( "(" ) == 0 ) {      
                  i = forGroup( i );
            }
            else if ( Tokens[ i ].size() > 3 && Tokens[ i ][ 0 ].compare( "while" ) == 0 && Tokens[ i ][ 1 ].compare( "(" ) == 0 && Tokens[ i ][ 2 ].compare( ")" ) != 0 ) {        
                  i = whileGroup( i );
            }
            else if ( ( Tokens[ i ].size() <= 2 && Tokens[ i ].size() >= 1 ) && Tokens[ i ][ 0 ].compare( "do" ) == 0 ) {           
                  i = doWhileGroup( i );
            }
            else if ( Tokens[ i ].size() > 3 && Tokens[ i ][ 0 ].compare( "if" ) == 0 ) {
                  i = ifGroup( i );
            }
              
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

                               
                                                
                                    
                                                               
                                                                             
      errosTips[ LN + 1 ].insert( "Fatal error: No such file or directory" );
}

int headerFiles_check( int LN )
{
      while ( LN < totalLine ) {
            if ( Tokens[ LN ].empty() ) {
                                           
                  isFinish[ LN ] = true;
                  ++LN;
                  continue;
            }
            else if ( Tokens[ LN ][ 0 ] == "#" ) {
                                                   
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
                                                    
            if ( functions[ i ].fTokens == "main" )
                  C++;
      }

                                            
      if ( C ) return;
      else     cout << "*** No MAIN function in your C file\n";

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
                        if ( i ) tips += ", ";
                        tips += to_string( lineNumbers[ i ] );
                  }
                  for ( int i = 0; i < lineNumbers.size(); ++i ) {
                        errosTips[ lineNumbers[ i ] ].insert( tips );
                  }
            }
      }
}

void initialize_Checking( int LN )
{
                           
      find_MAIN_function();       
                                            
      sameFunctionNameDetection();        
                          
      cout << "\n";
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
                        if ( !isFinish[ j - 1 ] )
                              check_THIS_Line( j - 1 );
                                                 
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
                        if ( !isFinish[ j - 1 ] )
                              check_THIS_Line( j - 1 );
                                                 
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
                        if ( !isFinish[ j - 1 ] )
                              check_THIS_Line( j - 1 );
                                                 
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
                        if ( !isFinish[ j - 1 ] )
                              check_THIS_Line( j - 1 );
                                                 
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
            if ( !isFinish[ j - 1 ] )
                  check_THIS_Line( j - 1 );
                                     
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
            if ( !isFinish[ j - 1 ] )
                  check_THIS_Line( j - 1 );
                                     
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
                        if ( !isFinish[ j - 1 ] )
                              check_THIS_Line( j - 1 );
                                                 
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

void errorPrinting()
{
      for ( int i = 0; i <= totalLine; ++i ) {
            if ( errosTips[ i ].size() ) {
                  cout << "\nLine No - " << i << " : ";
                  CFILE.printThisLine( i );
                  for ( set < string > :: iterator it = errosTips[ i ].begin(); it != errosTips[ i ].end(); ++it )
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

void getVariableFromThisLine( int lineNumber, set < string > &takenVarible )
{
      takenVarible.insert( Tokens[ lineNumber ][ 1 ] );
      if ( !validVariableName( Tokens[ lineNumber ][ 1 ] ) ) {
            errosTips[ lineNumber + 1 ].insert( "'" + Tokens[ lineNumber ][ 1 ] + "' is not valid variable" );
      }
      if( availableVariable( Tokens[ lineNumber ][ 1 ], takenVarible ) ) {
                                     
                                        
            errosTips[ lineNumber + 1 ].insert( "'" + Tokens[ lineNumber ][ 1 ] + "' is already used" );
      }
      else
            takenVarible.insert( Tokens[ lineNumber ][ 1 ] );

      for ( int i = 2; i < Tokens[ lineNumber ].size(); ++i ) {
            if ( Tokens[ lineNumber ][ i ] == "," ) {
                  if ( !validVariableName( Tokens[ lineNumber ][ i + 1 ] ) ) {
                        errosTips[ lineNumber + 1 ].insert( "'" + Tokens[ lineNumber ][ i + 1 ] + "' is not valid variable" );
                  }
                  if( availableVariable( Tokens[ lineNumber ][ i + 1 ], takenVarible ) ) {
                                                 
                                                    
                        errosTips[ lineNumber + 1 ].insert( "'" + Tokens[ lineNumber ][ i + 1 ] + "' is already used" );
                  }
                  else
                        takenVarible.insert( Tokens[ lineNumber ][ i + 1 ] );
            }
      }
}

void tryToGetVariableFromThisLine( int startLine, int endLine, set < string > &takenVarible )
{
                                     
               
      for ( int i = startLine; i <= endLine; ++i ) {            
                               
            if ( errosTips[ i + 1 ].empty() && isItDeclarationLine( i ) ) {
                  getVariableFromThisLine( i, takenVarible );
                               
            }
                       

                  

      }
                              
}

void variableHandling( int startLine, int endLine, set < string > takenVarible )
{
               
      for ( int i = startLine; i <= endLine; ++i ) {            
            if ( !errosTips[ i + 1 ].empty() || Tokens[ i ].empty() || Tokens[ i ][ 0 ] == "#" )
                  continue;
            tryToGetVariableFromThisLine( i, i, takenVarible);

            for ( int j = 0; j < Tokens[ i ].size(); ++j ) {
                  if ( TokenType[ i ][ j ] == "identifier" ) {
                        if ( !validVariableName( Tokens[ i ][ j ] ) ) {
                              errosTips[ i + 1 ].insert( "'" + Tokens[ i ][ j ] + "' is not valid variable" );
                        }
                        if( !availableVariable( Tokens[ i ][ j ], takenVarible ) ) {
                                                       
                                                          
                              errosTips[ i + 1 ].insert( "'" + Tokens[ i ][ j ] + "' is undeclared here" );
                        }
                  }
            }

      }
      Debug( takenVarible );
}

int main()
{
      system( "g++ HW1.cpp -o HW1" );
      system( "HW1" );

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
      Debug( totalLine );

      findGroup( 0, totalLine );
      syntaxChecking();
                   
      set < string > takenVariable;
      variableHandling( 0, totalLine - 1, takenVariable );
      errorPrinting();

      return 0;
}

  
                                                       

                                                        

                                               

                                    

                          
                
  
  
