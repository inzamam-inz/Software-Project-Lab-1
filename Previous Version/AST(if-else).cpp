#include <bits/stdc++.h>
using namespace std;
#include <stack>
#include <string.h>
#include <algorithm>

struct ifElseStruct{
    int bodyStartLine;//done
    int bodyEndLine;
    ifElseStruct *prevNode = NULL;
    string bodyStatement;//done
    string condition;//done
    string conditionType;//done
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
        string Tem = word;
        getline(Y, word, ' ');

        if(word[0] == '{' || text.compare("else")){
            getline(Y, word, '(');
            getline(Y, word, ')');
            ifElse[ifElseIndex].bodyStartLine = lineNumber;
            ifElse[ifElseIndex].condition = trim_both(word, ' ');
            ifElse[ifElseIndex].conditionType = "ELSE IF";
            //ifElseIndex++;
        }
        else{
            ifElse[ifElseIndex].bodyStartLine = lineNumber;
            ifElse[ifElseIndex].condition = "None";
            ifElse[ifElseIndex].conditionType = "ELSE";
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
    string line, T, t;
    bool res;
    stringstream X(codeText);
    while(getline(X, line, '\n')){
        lineNumber++;
        line = trim_both(line, ' ');
        res = isIfElse(line);
        if(res == true){
            stringstream Z(line);
            getline(Z, t, '{');
            string body;
            stringstream E(codeText);
            for(int i=0; i<lineNumber; i++){
                getline(E, T, '\n');
            }
            T = trim_both(T, ' ');
            line = trim_both(line, ' ');
            if(t.compare(line) != 0){ // { in condition line
                getline(Z, body, '\n');
                if(body[body.size()-1] == '}'){
                    body = trim_both(body, '}');
                }
                else{
                    getline(E, T, '}');
                    body = body + T;
                }
            }
            else{
                getline(E, T, '\n');
                T = trim_both(T, ' ');
                if(T[0] == '{'){  // { in next line
                    stringstream F(T);
                    getline(F, T, '{');
                    if(getline(F, T, '}')){ // } in
                        body = T;
                    }
                    else{ // }
                        getline(E, T, '}');
                        body = body + T;
                    }
                }
                else{ // { out
                    body = "" + T;
                    //cout << "ksd" << T;
                }
            }
            body = modify(body);
            ifElse[ifElseIndex].bodyStatement = body;
            ifElseIndex++;
        }
    }

}

int main()
{
    FILE *fp;
    int i,j=0;
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

    return 0;
}
