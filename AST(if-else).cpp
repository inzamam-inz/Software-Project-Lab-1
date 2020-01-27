#include <bits/stdc++.h>
using namespace std;
#include <stack>
#include <string>
#include <algorithm>

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s)
{
    return rtrim(ltrim(s));
}

stack <int> s;
vector <string> condition_exp;

FILE *fp;

void checked_if_else(char *line)
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
}


int main()
{

    int i,j=0;
    char line[100];

    fp = fopen("program.c","r");

    if(fp == NULL)
    {
        printf("error while opening the file\n");
        exit(0);
    }

    while(fgets(line, 100, fp) != NULL)
    {
        checked_if_else(line);
    }

    return 0;
}
