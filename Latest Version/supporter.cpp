
/*   ALLAH is Almighty.....  */

#include <bits/stdc++.h>
#include "Header.h"
using namespace std;


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
      for ( int i = 0; i < (int) st.size(); ++i ) {
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
      for ( int i = 0; i < (int) str.size(); i++ ) {
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

      for ( int i = 1; i < (int) st.size(); ++i ) {
            if ( !( isLetter( st[ i ] ) || isDigit( st[ i ] ) || st[ i ] == '_' ) ) {
                  return false;
            }
      }

      return true;
}



bool operatorCheck( char ch )
{
      if ( ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '(' || ch == ')' || ch == '#' || ch == ';' || ch == ':' || ch == '?' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '&' ||ch ==  '|' || ch == '!' || ch == '=' || ch == '<' || ch == '>' || ch == ',' ) {
            return true;
      }
      else {
            return false;
      }
}

bool operatorCheckdup( char ch )
{
      if ( ch == '+' || ch == '-' || ch == '&' || ch == '|' || ch == '=' || ch == '>' || ch == '<' ) {
            return true;
      }
      else {
            return false;
      }
}

bool isItInteger( string check )
{
      for ( int i = 0; i < (int) check.size(); ++i ) {
            if ( !isDigit( check[ i ] ) ) {
                  return false;
            }
      }

      return true;
}

bool isItDouble( string check )
{
      int dotCount = 0;

      for ( int i = 0; i < (int) check.size(); ++i ) {
            if ( isDigit( check[ i ] ) ) {
                  continue;
            }

            if ( check[ i ] == '.' ) {
                  dotCount++;
            }
            else {
                  return false;
            }
      }

      return dotCount <= 1;
}

