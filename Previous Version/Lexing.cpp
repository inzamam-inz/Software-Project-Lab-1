#include <bits/stdc++.h>
using namespace std;

int isKeyword(char buffer[]){
	char keywords[32][10] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};
	int i, flag = 0;

	for(i = 0; i < 32; ++i){
		if(strcmp(keywords[i], buffer) == 0){
			flag = 1;
			break;
		}
	}

	return flag;
}

int main(){
	char ch, buffer[15], operators[] = "+-*/%=><";
	FILE *fp;
	int i,j=0;

	fp = fopen("program.c","r");

	if(fp == NULL){
		printf("error while opening the file\n");
		exit(0);
	}

	while((ch = fgetc(fp)) != EOF){
        if(ch == '#'){
            char header[100];
            fgets(header, 100, fp);
            header[strlen(header)-1] = '\0';
            if(header[strlen(header)-1] == '>'){
                cout << "#" << header << " HEADER_FILE" << endl;
            }
            else{
                cout << "#" << header << " PRE_PROCESSOR" << endl;
            }
        }
        else{
            inz:
            int d = 0;
            switch(ch)
            {
                case '+': cout << "+ ADD\n"; d = 1; break;
                case '-': cout << "- SUBTRACT\n"; d = 1; break;
                case '*': cout << "* MULTIPLICATION\n"; d = 1; break;
                case '/': cout << "+ DIVISION\n"; d = 1; break;
                case '%': cout << "% MODULUS\n"; d = 1; break;
                case '=': {
                    ch = fgetc(fp);
                    if(ch == '='){
                        cout << "== ASSIGNMENT\n";
                        d = 1;
                    }
                    else{
                        cout << "= EQUAL\n";
                    }
                    break;
                }
                case '>': {
                    ch = fgetc(fp);
                    if(ch == '='){
                        cout << ">= GREATER_EQUAL\n";
                        //d = 1;
                    }
                    else{
                        cout << "> GREATER\n";
                        //d=2;
                        //goto inz;
                    }
                    break;
                }
                case '<': {
                    ch = fgetc(fp);
                    if(ch == '='){
                        cout << "<= LESS_EQUAL\n";
                        d = 1;
                    }
                    else{
                        cout << "< LESS\n";
                        d=2;
                        //goto inz;
                    }
                    break;
                }
                case '(': cout << "( FIRST_BRACKET_OPEN\n"; d = 1; break;
                case ')': cout << ") FIRST_BRACKET_CLOSE\n"; d = 1; break;
                case '{': cout << "{ SECOND_BRACKET_OPEN\n"; d = 1; break;
                case '}': cout << "} SECOND_BRACKET_CLOSE\n"; d = 1; break;
                case '[': cout << "[ THIRD_BRACKET_OPEN\n"; d = 1; break;
                case ']': cout << "] THIRD_BRACKET_CLOSE\n"; d = 1; break;
                case ';': cout << "; SEMICOLON\n"; d = 1; break;
                case ',': cout << ", COMMA\n"; d = 1; break;
                /*case '+': cout << "+ ADD\n"; break;
                case '+': cout << "+ ADD\n"; break;
                case '+': cout << "+ ADD\n"; break;*/
            }

            if(d != 0){
                buffer[j] = '\0';
                j = 0;

                if(isKeyword(buffer) == 1)
                    printf("%s keyword\n", buffer);
                else
                {
                    int checked_constant = -1, c = 0;
                    while(buffer[c] != '\0')
                    {
                        if(buffer[c] >= '0' && buffer[c] <= '9')
                        {
                            checked_constant = 1;
                        }
                        else
                        {
                            checked_constant = 0;
                            break;
                        }
                        c++;
                    }
                    if(checked_constant == 1)
                    {
                        printf("%s constant\n", buffer);
                    }
                    if(checked_constant == 0)
                    {
                        printf("%s INDET\n", buffer);
                    }
                }
            }
            if(d==2){

            }
            if(d == 0){
                if(isalnum(ch))
                {
                    buffer[j++] = ch;
                }

                else if((ch == ' ' || ch == '\n') && (j != 0))
                {
                    buffer[j] = '\0';
                    j = 0;

                    if(isKeyword(buffer) == 1)
                        printf("%s is keyword\n", buffer);
                    else
                    {
                        int checked_constant = 1, c = 0;
                        while(buffer[c] != '\0')
                        {
                            if(buffer[c] >= '0' && buffer[c] <= '9')
                            {
                                checked_constant = 1;
                            }
                            else
                            {
                                checked_constant = 0;
                                break;
                            }
                            c++;
                        }
                        if(checked_constant == 1)
                        {
                            printf("%s is constant\n", buffer);
                        }
                        if(checked_constant == 0)
                        {
                            printf("%s INDET\n", buffer);
                        }
                    }
                }
                else if(!isalnum(ch) && !(ch == ' ' || ch == '\n' || ch == '\t'))
                {
                    printf("%c is special symbol\n", ch);
                }
            }



        }

	}

	fclose(fp);

	return 0;
}
