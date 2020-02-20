/*
  https://www.cs.uic.edu/~troy/spring01/eecs473/mp2_473.htm
*/

#include <bits/stdc++.h>
using namespace std;

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

int main()
{
    FILE *fp;
	string str, codeText;
	char ch;

	fp = fopen("program.c","r");

	if(fp == NULL){
		printf("error while opening the file\n");
		exit(0);
	}

	while((ch = fgetc(fp)) != EOF){
        codeText = codeText + ch;
    }

    stringstream X(codeText);
	 while(getline(X, str, '\n')) {
        perline[totalLine].text = str;
        perline[totalLine++].line = totalLine;
    }


    return 0;
}
