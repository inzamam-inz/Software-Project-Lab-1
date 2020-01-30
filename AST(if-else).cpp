#include <bits/stdc++.h>
using namespace std;
#include <stack>
#include <string.h>
#include <algorithm>

struct ifElseStruct{
    int bodyStartLine;
    int bodyEndLine;
    ifElseStruct *prevNode = NULL;
    string bodyStatement;
    string condition;
    string conditionType;
};

string trim_left(string a, char c) {
    int flag = 0;
    string b = "";

    for(int i=0; i<a.size(); i++){
        if(flag == 0 && a[i] != c)
            flag = 1;
        if(flag == 1)
            b = b + a[i];
    }
    b[b.size()] = '\0';
    return b;
}

void trim_right(std::string& s, char c) {
   if (s.empty())
      return;

   std::string::iterator p;
   for (p = s.end(); p != s.begin() && *--p == c;);

   if (*p != c)
      p++;

   s.erase(p, s.end());
}

string trim_both(string a, char c)
 {
    trim_right(a, c);
    a = trim_left(a, c);
    return a;
}

int lineNumber = 0;
ifElseStruct ifElse[100];
int ifElseIndex = 0;
string codeText;
stack <int> s;
vector <string> condition_exp;

/*void checked_if_else(char *line)
{
    string T;
    stringstream X(line);
    while (getline(X, T, ' '))
    {
        int j = 0;
        string condition, body;
        if(T[0]=='i' && T[1]=='f' && (T[2]=='\0' || T[2]=='\n' || T[2]==' ' || T[2]=='\t' || T[2]=='(' || T[2]=='{'))
        {
            while(line[j] != '(')
            {
                j++;
            }
            j++;
            while(line[j] != ')')
            {
                condition = condition + line[j];
                j++;
            }
            cout << "if \nCondition: " << condition << "\n";
            while(!(line[j] == '{' || line[j] == '\n'))
            {
                j++;
            }
            if(line[j] == '{')
            {

                char ch = fgetc(fp);
                while(ch != '}')
                {
                    body = body + ch;
                    ch = fgetc(fp);
                }
            }
            else if(line[j] == '\n')
            {
                char ch = fgetc(fp);
                while(ch != '\n')
                {
                    body = body + ch;
                    ch = fgetc(fp);
                }
            }
            trim(body);
            cout << "Body: " << body << "\n";
        }
        else if(T.compare("else")  == 0)
        {
            getline(X, T, ' ');
            if(T[0]=='i' && T[1]=='f' && (T[2]=='\0' || T[2]=='\n' || T[2]==' ' || T[2]=='\t' || T[2]=='(' || T[2]=='{'))
            {
                while(line[j] != '(')
                {
                    j++;
                }
                j++;
                while(line[j] != ')')
                {
                    condition = condition + line[j];
                    j++;
                }
                cout << "else if\nCondition: " << condition << "\n";
                while(!(line[j] == '{' || line[j] == '\n'))
                {
                    j++;
                }
                if(line[j] == '{')
                {

                    char ch = fgetc(fp);
                    while(ch != '}')
                    {
                        body = body + ch;
                        ch = fgetc(fp);
                    }
                }
                else if(line[j] == '\n')
                {
                    char ch = fgetc(fp);
                    while(ch != '\n')
                    {
                        body = body + ch;
                        ch = fgetc(fp);
                    }
                }
                trim(body);
                cout << "Body: " << body << "\n";

            }
        }
        else if(T[0]=='e' && T[1]=='l'&& T[2]=='s' && T[3]=='e' && (T[4]=='\0' || T[4]=='\n' || T[4]==' ' || T[4]=='\t' || T[4]=='(' || T[4]=='{'))
        {
            cout << "else \n";
            while(!(line[j] == '{' || line[j] == '\n'))
            {
                j++;
            }
            if(line[j] == '{')
            {

                char ch = fgetc(fp);
                while(ch != '}')
                {
                    body = body + ch;
                    ch = fgetc(fp);
                }
            }
            else if(line[j] == '\n')
            {
                char ch = fgetc(fp);
                while(ch != '\n')
                {
                    body = body + ch;
                    ch = fgetc(fp);
                }
            }
            trim(body);
            cout << "Body: " << body << "\n";
        }
        T = '\0';
    }
}*/

bool isIfElse(string text)
{
    string word;
    stringstream X(text);
    getline(X, word, ' ');
    if(word.compare("if") == 0){ //only if
        getline(X, word, '(');
        getline(X, word, ')');
        ifElse[ifElseIndex].bodyStartLine = lineNumber;
        ifElse[ifElseIndex].condition = trim_both(word, ' ');
        ifElse[ifElseIndex].conditionType = "IF";
        //ifElseIndex++;
    }
    else if(word[0] == 'i' && word[1] == 'f' && word[2] == '('){
        stringstream Y(text);
        getline(Y, word, '(');
        getline(Y, word, ')');
        ifElse[ifElseIndex].bodyStartLine = lineNumber;
        ifElse[ifElseIndex].condition = trim_both(word, ' ');
        ifElse[ifElseIndex].conditionType = "IF";
        //ifElseIndex++;
    }
    else if(word.compare("else") == 0){
        stringstream Y(text);
        getline(Y, word, ' ');
        if(word[0] == '{'){
            ifElse[ifElseIndex].bodyStartLine = lineNumber;
            ifElse[ifElseIndex].condition = "None";
            ifElse[ifElseIndex].conditionType = "ELSE";
            //ifElseIndex++;
        }
        else{
            getline(Y, word, '(');
            getline(Y, word, ')');
            ifElse[ifElseIndex].bodyStartLine = lineNumber;
            ifElse[ifElseIndex].condition = trim_both(word, ' ');
            ifElse[ifElseIndex].conditionType = "ELSE IF";
        }
        //ifElseIndex++;
    }
    else if(word[0] == 'e' && word[1] == 'l' && word[2] == 's' && word[3] == 'e' && word[4] == '{'){
        ifElse[ifElseIndex].bodyStartLine = lineNumber;
        ifElse[ifElseIndex].condition = "None";
        ifElse[ifElseIndex].conditionType = "ELSE";
        //ifElseIndex++;
    }
    else
        return false;

    return true;
}

string modify(string a)
{
    string b, c;
    stringstream A(a);
    while(getline(A, b, '\n')){
        trim_both(b, ' ');
        trim_both(b, '\t');
        c = c + b + '\n';
    }
    return c;
}

void checked_if_else(void)
{
    string line, T;
    bool res;
    stringstream X(codeText);
    while(getline(X, line, '\n')){
        lineNumber++;
        line = trim_both(line, ' ');
        res = isIfElse(line);
        if(res == true){
            stringstream Z(line);
            getline(Z, T, '{');
            string body;
            stringstream E(codeText);
            for(int i=0; i<lineNumber; i++){
                getline(E, T, '\n');
            }
            if(T.compare(line) != 0){ // { in
                if(line[line.size()-1] == '}'){
                    stringstream F(line);
                    getline(F, T, '{');
                    getline(F, T, '}');
                    body = "" + T;
                }
                else if(getline(Z, T, '}') !=0){
                    body = body + T + '\n';
                    getline(E, T, '}');
                    body = body + T;
                }
                else{
                    getline(E, T, '}');
                    body = body + T;
                }
                body = modify(body);

                ifElse[ifElseIndex].bodyStatement = body;
                //cout << "BODY: "  << body << endl;
            }
            else{

            }
            ifElseIndex++;
        }
    }

}

int main()
{
    FILE *fp;
    int i,j=0;
    //char line[100], ch;
    char ch;

    fp = fopen("program.c","r");

    if(fp == NULL)
    {
        printf("error while opening the file\n");
        exit(0);
    }

    while((ch = fgetc(fp)) != EOF){
        codeText = codeText + ch;
    }

    checked_if_else();

    while(ifElseIndex--){
        cout << ifElse[ifElseIndex].bodyStartLine << "\n" << ifElse[ifElseIndex].bodyEndLine << endl << ifElse[ifElseIndex].condition << endl << ifElse[ifElseIndex].conditionType << endl << ifElse[ifElseIndex].bodyStatement << "\n\n";
    }

    /*while(fgets(line, 100, fp) != NULL)
    {
        checked_if_else(line);
    }*/

    return 0;
}
