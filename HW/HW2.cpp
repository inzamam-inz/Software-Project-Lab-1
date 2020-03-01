/*
  https://www.cs.uic.edu/~troy/spring01/eecs473/mp2_473.htm
*/

#include <bits/stdc++.h>
using namespace std;

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

struct stmts_struct{
    int line;
    string text;
    vector <stmts_struct> stmt_list;
};

struct type_spec_struct{
    int line;
    string text;
    string options;
};

struct var_decl_struct{
    int line;
    string text;
    vector <type_spec_struct> type;
    vector <string> identifer;
};

struct exp_struct{
    int line;
    string text;
    vector <exp_struct> exps;
};

struct while_stmt_struct{
    int line;
    string text;
    stmts_struct stmt;
    exp_struct codition;
};

struct else_struct{
    int line;
    string text;
    stmts_struct stmt;
};

struct if_struct{
    int line;
    string text;
    stmts_struct stmt;
    else_struct elsestmt;
    if_struct *ifstmt;
    exp_struct codition;
};

struct const_value_struct{
    int line;
    string text;
    int integer;
    double floating_point ;
    char character;
};

struct return_struct{
    int line;
    string text;
    exp_struct codition;
};

struct body_struct{
    int line;
    string text;
    if_struct ifstmt;
    while_stmt_struct whilestmt;
    vector <var_decl_struct> identifer;
};

struct func_struct{
    int line;
    string text;
    body_struct bodystmt;
    return_struct return_exp;
};

struct perlinestruct{
    int line;
    string text;
};

perlinestruct perline[100];
int totalLine = 0;
vector <string> input[100];
vector <string> name[100];
vector <string> lineNumber[100];
vector <string> position[100];

struct func{
    int startLine;
    int endLine;
    string returnType;
    vector <string> parameter;
    vector <string> parameterType;
    int statement_text_start;
    int statement_text_end;
    string fname;
};

struct for_struct{
    int startLine;
    int endLine;
    vector <string> condition;
    vector <string> conditionType;
    vector <string> change;
    vector <string> changeType;
    vector <string> initialize;
    vector <string> initializeType;
    int statement_text_start;
    int statement_text_end;
};
vector <for_struct> fors;
vector <func> functions;

int strTint(string str)
{
    int n=0;
    for(int i=0; i<str.size(); i++){
        n *= 10;
        n += str[i]-'0';
    }

    return n;
}

void findError(void)
{
    for(int i=0; i<100; i++){
        if(input[i].size() > 3 && input[i][0].compare("keyword") == 0  && input[i][1].compare("indentifer") == 0  && input[i][2].compare("oparetor") == 0  && input[i][3].compare("keyword") == 0){//function
            if(name[i][input[i].size()-2].compare(")") == 0 && name[i][input[i].size()-1].compare(";") == 0){
                cout << "function protoType\n";
            }
            else{
                func f;

                f.startLine = i+1;
                f.returnType = name[i][0];
                f.fname = name[i][1];
                if(name[i][3].compare("void") == 0){
                    f.parameter.push_back("None");
                    f.parameterType.push_back("void");
                }
                else{
                    int j = 2;
                    while(1){
                        if(name[i][j].compare(")") == 0)
                            break;
                        f.parameter.push_back(name[i][j+2]);
                        f.parameterType.push_back(name[i][j+1]);
                        j += 3;
                    }
                }
                f.statement_text_start = i+3;
                if(name[i][input[i].size() - 1].compare("{") == 0){
                    f.statement_text_start = i+2;
                }
                stack <int> temp;
                int h = f.statement_text_start - 1;
                temp.push(1);
                while(!temp.empty()){
                    //cout << i;
                    for(int k=0; k<input[h].size(); k++){
                        if(name[h][k].compare("{") == 0)
                            temp.push(1);
                        if(name[h][k].compare("}") == 0){
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

            //cout << name[i][1];
        }
        else if(name[i].size() > 4 && name[i][0].compare("for") == 0 && name[i][1].compare("(") == 0){//for
            int semi =  0, f = 2;
            for_struct fa;
            fa.startLine = i+1;
            fa.statement_text_start = i+3;
            if(name[i][input[i].size()-1].compare("{") == 0){
                fa.statement_text_start = i+2;
            }
            while(name[i][f].compare(")") != 0){
                    //cout <<name[i][f] << " ";
                   // cout << semi;
                if(name[i][f].compare(";") == 0){
                    semi++;
                    f++;
                    continue;;
                }
                if(semi == 0){
                    fa.initialize.push_back(name[i][f]);
                    fa.initializeType.push_back(input[i][f]);
                }
                if(semi == 1){

                    fa.condition.push_back(name[i][f]);
                    fa.conditionType.push_back(input[i][f]);
                }
                if(semi == 2){
                    fa.change.push_back(name[i][f]);
                    fa.changeType.push_back(input[i][f]);
                }
                f++;
            }
            stack <int> temp;
            int h = fa.statement_text_start - 1;
            temp.push(1);
            while(!temp.empty()){
                    //cout << i;
             for(int k=0; k<input[h].size(); k++){
                   if(name[h][k].compare("{") == 0)
                        temp.push(1);
                    if(name[h][k].compare("}") == 0){
                        temp.pop();
                    }
                }
                h++;
            }
            fa.statement_text_end = h-1;
            fa.endLine = h;
            fors.push_back(fa);
        }

    }
}

int main()
{
    FILE *fp;
	string str, Text, strg1, strg2, strg3, strg4;
	char ch;

	fp = fopen("output.txt","r");

	if(fp == NULL){
		printf("error while opening the file\n");
		exit(0);
	}

	while((ch = fgetc(fp)) != EOF){
        Text = Text + ch;
    }

    stringstream X(Text);
	 while(getline(X, str, '\n')) {
        stringstream Y(str);
        getline(Y, strg1, '\t');
        getline(Y, strg2, '\t');
        getline(Y, strg3, '\t');
        getline(Y, strg4, '\t');
        int h = strTint(strg3);
        trim_both(strg1, ' ');
        trim_both(strg2, ' ');

        input[h-1].push_back(strg1);
        name[h-1].push_back(strg2);

    }

    /*for(int i=0; i<100;i++){
        for(int y=0; y<input[i].size(); y++){
            cout << input[i][y] << "  ";
        }
        cout << endl;
        for(int y=0; y<name[i].size(); y++){
            cout << name[i][y] << "  ";
        }
        cout << endl;
    }*/
    findError();

    //
    //cout << "Name: " << fors[0]. << endl;
    //cout << "Return type: " << fors[0].returnType << endl;
    cout << "Func Start Lin: " << fors[0].startLine << endl;
    cout << "Statement Text start line: " << fors[0].statement_text_start << endl;
    cout << "Statement end start line: " << fors[0].statement_text_end << endl;
    cout << "Func end Lin: " << fors[0].endLine << endl;

    for(int a=0; a<fors[0].initialize.size(); a++){
        cout << fors[0].initialize[a] << " ";
    }
    cout << endl;
    for(int a=0; a<fors[0].initializeType.size(); a++){
        cout << fors[0].initializeType[a] << " ";
    }
cout << endl;
    for(int a=0; a<fors[0].condition.size(); a++){
        cout << fors[0].condition[a] << " ";
    }
    cout << endl;
    for(int a=0; a<fors[0].conditionType.size(); a++){
        cout << fors[0].conditionType[a] << " ";
    }
cout << endl;
    for(int a=0; a<fors[0].change.size(); a++){
        cout << fors[0].change[a] << " ";
    }
    cout << endl;
    for(int a=0; a<fors[0].changeType.size(); a++){
        cout << fors[0].changeType[a] << " ";
    }
    return 0;
}
