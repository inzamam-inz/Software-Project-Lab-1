/*
  https://www.cs.uic.edu/~troy/spring01/eecs473/mp1.html
*/

#include <bits/stdc++.h>
using namespace std;

struct perlinestruct{
    int line;
    string text;
};
perlinestruct perline[100];
string keywords[32] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
int totalLine = 0;
string check;

bool digitCheck(char ch)
{
    if(ch >= '0' && ch <= '9')
        return true;
    else
        return false;
}

bool oparetorCheck(char ch)
{
    if(ch == ('{' || '}' || '[' || ']' || '(' || ')' || '#' || ';' || ':' || '?' || '.' || '+' || '-' || '*' || '/' || '%' || '^' || '&' || '|' || '!' || '=' || '<' || '>'))
        return true;
    else
        return false;
}

void keyword_identifer_check(int l)
{
    if(check.size()==0)
        return;
    int flag = 0;
    for(int k=0; k<32; k++){
        if(check.compare(keywords[k])==0){
            flag = 1;
            break;
        }
    }
    if(flag == 1)
        cout << "keyword\t" << check << "\t" << perline[l].line << endl;
    else
        cout << "indentifer\t" << check << "\t" << perline[l].line << endl;

    check = "";
}

void lexing(void)
{
    for(int i=0; i<totalLine; i++){
        int lenPerLine = perline[i].text.size();
        for(int j=0; j<lenPerLine; j++){
            if(oparetorCheck(perline[i].text[j]) && oparetorCheck(perline[i].text[j+1])){//oparetorChecking(done)
                keyword_identifer_check(i);
                cout << "oparetor\t" << perline[i].text[j] << perline[i].text[j+1] << "\t" << perline[i].line << endl;
                j += 2;
            }
            else if(oparetorCheck(perline[i].text[j])){//oparetorChecking(done)
                keyword_identifer_check(i);
                cout << "oparetor\t" << perline[i].text[j] << "\t" << perline[i].line << endl;
                j += 1;
            }
            else if(perline[i].text[j] == '\\'){//charChecking(done)
                keyword_identifer_check(i);
                cout << "character\t" << perline[i].text[j] << perline[i].text[j+1] << "\t" << perline[i].line << endl;
                //check which character
                j += 2;
            }
            else if(digitCheck(perline[i].text[j])){//digitChecking(done)
                keyword_identifer_check(i);
                int f = 0,  a = perline[i].text[j] - '0';
                j++;
                while(digitCheck(perline[i].text[j]) || perline[i].text[j]=='.'){
                    if(perline[i].text[j]=='.'){
                        f = 1;
                        cout << "float\t" << a << ".";
                        a = 0;
                    }
                    else
                        a = a*10 + (perline[i].text[j] - '0');
                    j++;
                }
                if(f == 0)
                    cout << "integer\t" << a << "\t" << perline[i].line << endl;
                else
                    cout << a << "\t" << perline[i].line << endl;
            }
            else if(perline[i].text[j] == '"'){//stringChecking(done)
                keyword_identifer_check(i);
                j++;
                string strg;
                while(perline[i].text[j] != '"'){
                    strg = strg + perline[i].text[j];
                    j++;
                }
                j++;
                cout << "string\t" << strg  << "\t" << perline[i].line << endl;//char check in string
            }
            else if(perline[i].text[j] == ' ' || perline[i].text[j] == '\n'){//keyword_identifer_checking(done)
                keyword_identifer_check(i);
                j++;
            }
            else{
                check = check + perline[i].text[j++];
            }
        }
    }
}

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
        perline[totalLine++].line = totalLine;
        perline[totalLine].text = str;
    }

    lexing();

    return 0;
}
