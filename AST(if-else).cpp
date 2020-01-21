#include <bits/stdc++.h>
using namespace std;
#include <stack>

stack <int> s;

void checked_if_else(char *line)
{
    string T;
    stringstream X(line);
    while (getline(X, T, ' ')) {
        int j = 0;
        if(T[0]=='i' && T[1]=='f' && (T[2]=='\0' || T[2]=='\n' || T[2]==' ' || T[2]=='\t' || T[2]=='(' || T[2]=='{')){
            /*while(line[j] != '\0'){
                if(line[j] == '('){
                    s.push('(');
                }
                if
           }*/
            cout << "if \n";
        }
        else if(T.compare("else")  == 0){
            getline(X, T, ' ');
            if(T[0]=='i' && T[1]=='f' && (T[2]=='\0' || T[2]=='\n' || T[2]==' ' || T[2]=='\t' || T[2]=='(' || T[2]=='{'))
                cout << "else if \n";
        }
        else if(T[0]=='e' && T[1]=='l'&& T[2]=='s' && T[3]=='e' && (T[4]=='\0' || T[4]=='\n' || T[4]==' ' || T[4]=='\t' || T[4]=='(' || T[4]=='{')){
            cout << "else \n";
        }
        T = '\0';
    }
    //if()
}

int main()
{
    FILE *fp;
	int i,j=0;
	char line[100];

	fp = fopen("program.c","r");

	if(fp == NULL){
		printf("error while opening the file\n");
		exit(0);
	}

	while(fgets(line, 100, fp) != NULL){
        //if()
        checked_if_else(line);
	}





    return 0;
}
