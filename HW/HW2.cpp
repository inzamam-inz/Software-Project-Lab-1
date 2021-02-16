/*
  https://www.cs.uic.edu/~troy/spring01/eecs473/mp2_473.htm
*/

#include <bits/stdc++.h>
using namespace std;

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

struct perlinestruct
{
      int line;
      string text;
};

//perlinestruct perline[ 100 ];
int totalLine = 0;
vector < string > TokenType[ 100 ];
vector < string > Tokens[ 100 ];
//vector < string > lineNumber[ 100 ];
//vector < string > position[ 100 ];

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




/* ---------------------NEW--------------------- */




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

void checking_statement( int lineNumber )
{
      //, vector < string > availableVariable
      //cout << Tokens[ lineNumber ].size() << " ";
      //return;
      if ( Tokens[ lineNumber ].size() && Tokens[ lineNumber ].back() != ";" ) {
            cout << "Line No - " << lineNumber + 1 << " 1 problem in this line\n";
            return;
      }
      if ( Tokens[ lineNumber ].empty() ) {
            return;
      }

      //int iL = 0 + isSpecialOparetor( lineNumber, 0 ), iR = Tokens[ lineNumber ].size() - isSpecialOparetor( lineNumber, Tokens[ lineNumber ].size() - 2 );
      //--iR;
     // if ( iL >= iR ) {
           //  cout << "Line No - " << lineNumber + 1 << " 2 problem in this line\n";
            // return;
      //}
      //cout << iL << " " << iR << " ";

      vector < int > checkList;
      for ( int i = 0; i < Tokens[ lineNumber ].size() - 1; ++i ) {
            if ( isSpecialOparetor( lineNumber, i ) && TokenType[ lineNumber ][ i + 1 ] == "indentifier" ) {
                  ++i;
                  checkList.push_back( i );
            }
            else if ( isSpecialOparetor( lineNumber, i ) ) {
                  cout << "Line No - " << lineNumber + 1 << " 6 problem in this line\n";
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
      if ( checkList.size() % 2 == 0 ) {
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
      }
      int a, b;
      //a += a++++b;
}







/* ---------------------NEW--------------------- */






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
      /*if(semi != 2){
            cout << "find error\n";
            return;
      }*/
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

int functionGroup(int i)
{
    if(Tokens[i][TokenType[i].size()-2].compare(")") == 0 && Tokens[i][TokenType[i].size()-1].compare(";") == 0)
    {
        cout << "function protoType\n";
    }
    else
    {
        func f;

        f.startLine = i+1;
        f.returnType = Tokens[i][0];
        f.fTokens = Tokens[i][1];
        if(Tokens[i][3].compare("void") == 0)
        {
            f.parameter.push_back("None");
            f.parameterType.push_back("void");
        }
        else
        {
            int j = 2;
            while(1)
            {
                if(Tokens[i][j].compare(")") == 0)
                    break;
                f.parameter.push_back(Tokens[i][j+2]);
                f.parameterType.push_back(Tokens[i][j+1]);
                j += 3;
            }
        }
        f.statement_text_start = i+3;
        if(Tokens[i][TokenType[i].size() - 1].compare("{") == 0)
        {
            f.statement_text_start = i+2;
        }
        stack <int> temp;
        int h = f.statement_text_start - 1;
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
        f.statement_text_end = h-1;
        f.endLine = h;
        functions.push_back(f);
        i = h-1;
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

int ifGroup(int i)
{
    int f = 2;
    if_struct fa;
    fa.startLine = i+1;
    fa.statement_text_start = i+3;
    while(Tokens[i][f].compare(")") != 0)
    {
        fa.condition.push_back(Tokens[i][f]);
        fa.conditionType.push_back(TokenType[i][f]);
        f++;
    }
    if(Tokens[i][TokenType[i].size()-1].compare("{") == 0)
    {
        fa.statement_text_start = i+2;
    }
    if(Tokens[i][TokenType[i].size()-1].compare("{") == 0 || (Tokens[i+1].size() > 0 && Tokens[i+1][0].compare("{") == 0))
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
        i = fa.endLine-1;
    }
    else
    {
        fa.statement_text_start = i+2;
        fa.statement_text_end = i+2;
        fa.endLine = i+2;
        i = i + 1;
    }
    i++;
    //cout << i+1;
    while(1)
    {

        if(TokenType[i].size() > 1 && Tokens[i][0].compare("else") == 0  && Tokens[i][1].compare("if") == 0)
        {
            //
            else_if_struct fi = elseIfGroup(i);
            fa.if_elses.push_back(fi);
            i = fi.endLine;//cout << i << endl;
        }
        else if(TokenType[i].size() > 0 && Tokens[i][0].compare("else") == 0)
        {
            else_struct fy = elseGroup(i);//
            fa.elses.push_back(fy);
            i = fy.endLine;
            break;
        }
        else
        {
            break;
        }

    }
    ifs.push_back(fa);
    i--;//
    return i;
    //
}

void findGroup( int startLine, int endLine )
{
    for(int i = startLine; i< endLine; i++)
    {
        if(TokenType[i].size() > 3 && TokenType[i][0].compare("keyword") == 0  && TokenType[i][1].compare("indentifier") == 0  && TokenType[i][2].compare("oparetor") == 0  && TokenType[i][3].compare("keyword") == 0) //function
        {
            i = functionGroup(i);
        }
        else if(Tokens[i].size() > 4 && Tokens[i][0].compare("for") == 0 && Tokens[i][1].compare("(") == 0) //for
        {
            i = forGroup(i);
        }
        else if(Tokens[i].size() > 3 && Tokens[i][0].compare("while") == 0 && Tokens[i][1].compare("(") == 0 && Tokens[i][2].compare(")") != 0) //while
        {
            i = whileGroup(i);
        }
        else if((Tokens[i].size() <= 2 && Tokens[i].size() >= 1) && Tokens[i][0].compare("do") == 0) //do-while
        {
            i = doWhileGroup(i);
        }
        else if(Tokens[i].size() > 3 && Tokens[i][0].compare("if") == 0)
        {
            i = ifGroup(i);
        }
        //
    }
}

int main()
{
      FILE *fp;
      string str, Text, strg1, strg2, strg3, strg4;
      char ch;

      fp = fopen( "output.txt", "r" );

      if(fp == NULL) {
            printf( "error while opening the file\n" );
            exit( 0 );
      }

      while((ch = fgetc(fp)) != EOF) {
            Text = Text + ch;
      }

      stringstream X( Text );
      while( getline(X, str, '\n') ) {
            stringstream Y(str);
            getline( Y, strg1, '\t' );
            getline( Y, strg2, '\t' );
            getline( Y, strg3, '\t' );
            getline( Y, strg4, '\t' );
            int h = strTint( strg3 );
            trim_both( strg1, ' ' );
            trim_both( strg2, ' ' );

            TokenType[ h - 1 ].push_back( strg1 );
            Tokens[ h - 1 ].push_back( strg2 );

      }

      findGroup( 0, 100 );
      //printFor();

      for ( int i = 0; i < 10; ++i )
            checking_statement( i );


      return 0;
}
