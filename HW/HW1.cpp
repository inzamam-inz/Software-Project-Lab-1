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
ofstream file("output.txt");

bool digitCheck(char ch)
{
    if(ch >= '0' && ch <= '9')
        return true;
    else
        return false;
}

bool oparetorCheck(char ch)
{
    if(ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '(' || ch == ')' || ch == '#' || ch == ';' || ch == ':' || ch == '?' || ch == '.' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '&' ||ch ==  '|' || ch == '!' || ch == '=' || ch == '<' || ch == '>' || ch == ',')
        return true;
    else
        return false;
}

bool oparetorCheckdup(char ch)
{
    if(ch == '+' || ch == '-' || ch == '&' || ch == '|' || ch == '=' || ch == '>' || ch == '<' )
        return true;
    else
        return false;
}



void keyword_identifer_check(int l, int col)
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
        file << "keyword\t" << check << "\t" << perline[l].line << "\t" << col-(check.size())+1 << endl;
    else
        file << "indentifer\t" << check << "\t" << perline[l].line << "\t" << col-(check.size())+1 << endl;

    check = "";
}

void lexing(void)
{
    for(int i=0; i<totalLine; i++){
        int lenPerLine = perline[i].text.size();
        for(int j=0; j<lenPerLine; ){
            if(oparetorCheck(perline[i].text[j]) && oparetorCheckdup(perline[i].text[j+1])){//oparetorChecking(done)
                keyword_identifer_check(i, j);
                file << "oparetor\t" << perline[i].text[j] << perline[i].text[j+1] << "\t" << perline[i].line << "\t" << j+1 << endl;
                j += 2;
            }
            else if(oparetorCheck(perline[i].text[j])){//oparetorChecking(done)
                keyword_identifer_check(i, j);
                file << "oparetor\t" << perline[i].text[j] << "\t" << perline[i].line << "\t" << j+1 << endl;
                j += 1;
            }
            /*bad
            else if(otherCheck(perline[i].text[j])){
                file << "other\t" << perline[i].text[j] << "\t" << perline[i].line << "\t" << j+1 << endl;
                j += 1;
            }*/
            else if(perline[i].text[j] == '\\'){//charChecking(done)
                keyword_identifer_check(i, j);
                file << "character\t" << perline[i].text[j] << perline[i].text[j+1] << "\t" << perline[i].line << "\t" << j+1 << endl;//check which character
                j += 2;
            }
            else if(digitCheck(perline[i].text[j])){//digitChecking(done)
                keyword_identifer_check(i, j);
                int f = 0,  a = perline[i].text[j] - '0';
                j++;
                int temp = j;
                while(digitCheck(perline[i].text[j]) || perline[i].text[j]=='.'){
                    if(perline[i].text[j]=='.'){
                        f = 1;
                        file << "float\t" << a << ".";
                        a = 0;
                    }
                    else
                        a = a*10 + (perline[i].text[j] - '0');
                    j++;
                }
                if(f == 0)
                    file << "integer\t" << a << "\t" << perline[i].line << "\t" << temp << endl;
                else
                    file << a << "\t" << perline[i].line << "\t" << temp << endl;
            }
            else if(perline[i].text[j] == '"'){//stringChecking(done)
                keyword_identifer_check(i, j);
                j++;
                int temp = j;
                string strg;
                while(perline[i].text[j] != '"'){
                    strg = strg + perline[i].text[j];
                    j++;
                }
                j++;
                file << "string\t" << strg  << "\t" << perline[i].line << "\t" << temp+1 << endl;//char check in string
            }
            else if(perline[i].text[j] == ' ' || perline[i].text[j] == '\n'){//keyword_identifer_checking(done)
                //cout << check << i << " " << j <<"\n";
                keyword_identifer_check(i, j);

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
        perline[totalLine].text = str + " ";
        perline[totalLine++].line = totalLine;
    }

    lexing();

    return 0;
}
