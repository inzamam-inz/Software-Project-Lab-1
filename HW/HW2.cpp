/*
  https://www.cs.uic.edu/~troy/spring01/eecs473/mp2_473.htm
*/

#include <bits/stdc++.h>
using namespace std;

string trim_left(string a, char c)
{
    int flag = 0;
    string b = "";

    for(int i=0; i<a.size(); i++)
    {
        if(flag == 0 && a[i] != c)
            flag = 1;
        if(flag == 1)
            b = b + a[i];
    }
    b[b.size()] = '\0';
    return b;
}

void trim_right(std::string& s, char c)
{
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

struct perlinestruct
{
    int line;
    string text;
};

perlinestruct perline[100];
int totalLine = 0;
vector <string> input[100];
vector <string> name[100];
vector <string> lineNumber[100];
vector <string> position[100];

struct func
{
    int startLine;
    int endLine;
    string returnType;
    vector <string> parameter;
    vector <string> parameterType;
    int statement_text_start;
    int statement_text_end;
    string fname;
};

struct for_struct
{
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

struct while_struct
{
    int startLine;
    int endLine;
    vector <string> condition;
    vector <string> conditionType;
    int statement_text_start;
    int statement_text_end;
};

struct do_while_struct
{
    int startLine;
    int endLine;
    vector <string> condition;
    vector <string> conditionType;
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
    vector <string> condition;
    vector <string> conditionType;
};

struct if_struct
{
    int startLine;
    int endLine;
    int statement_text_start;
    int statement_text_end;
    vector <string> condition;
    vector <string> conditionType;
    vector <else_struct> elses;
    vector <else_if_struct> if_elses;
};

vector <for_struct> fors;
vector <func> functions;
vector <while_struct> whiles;
vector <do_while_struct> do_whiles;
vector <if_struct> ifs;


int strTint(string str)
{
    int n=0;
    for(int i=0; i<str.size(); i++)
    {
        n *= 10;
        n += str[i]-'0';
    }

    return n;
}

int forGroup(int i)
{
    int semi =  0, f = 2;
    for_struct fa;
    fa.startLine = i+1;
    fa.statement_text_start = i+3;
    if(name[i][input[i].size()-1].compare("{") == 0)
    {
        fa.statement_text_start = i+2;
    }
    while(name[i][f].compare(")") != 0)
    {
        if(name[i][f].compare(";") == 0)
        {
            semi++;
            f++;
            continue;;
        }
        if(semi == 0)
        {
            fa.initialize.push_back(name[i][f]);
            fa.initializeType.push_back(input[i][f]);
        }
        if(semi == 1)
        {

            fa.condition.push_back(name[i][f]);
            fa.conditionType.push_back(input[i][f]);
        }
        if(semi == 2)
        {
            fa.change.push_back(name[i][f]);
            fa.changeType.push_back(input[i][f]);
        }
        f++;
    }
    /*if(semi != 2){
        cout << "find error\n";
        return;
    }*/
    stack <int> temp;
    int h = fa.statement_text_start - 1;
    temp.push(1);
    while(!temp.empty())
    {
        //cout << i;
        for(int k=0; k<input[h].size(); k++)
        {
            if(name[h][k].compare("{") == 0)
                temp.push(1);
            if(name[h][k].compare("}") == 0)
            {
                temp.pop();
            }
        }
        h++;
    }
    fa.statement_text_end = h-1;
    fa.endLine = h;
    fors.push_back(fa);
    i = fa.endLine-1;

    return i;
}

int functionGroup(int i)
{
    if(name[i][input[i].size()-2].compare(")") == 0 && name[i][input[i].size()-1].compare(";") == 0)
    {
        cout << "function protoType\n";
    }
    else
    {
        func f;

        f.startLine = i+1;
        f.returnType = name[i][0];
        f.fname = name[i][1];
        if(name[i][3].compare("void") == 0)
        {
            f.parameter.push_back("None");
            f.parameterType.push_back("void");
        }
        else
        {
            int j = 2;
            while(1)
            {
                if(name[i][j].compare(")") == 0)
                    break;
                f.parameter.push_back(name[i][j+2]);
                f.parameterType.push_back(name[i][j+1]);
                j += 3;
            }
        }
        f.statement_text_start = i+3;
        if(name[i][input[i].size() - 1].compare("{") == 0)
        {
            f.statement_text_start = i+2;
        }
        stack <int> temp;
        int h = f.statement_text_start - 1;
        temp.push(1);
        while(!temp.empty())
        {
            //cout << i;
            for(int k=0; k<input[h].size(); k++)
            {
                if(name[h][k].compare("{") == 0)
                    temp.push(1);
                if(name[h][k].compare("}") == 0)
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
    if(name[i][input[i].size()-1].compare("{") == 0)
    {
        fa.statement_text_start = i+2;
    }
    while(name[i][f].compare(")") != 0)
    {
        fa.condition.push_back(name[i][f]);
        fa.conditionType.push_back(input[i][f]);
        f++;
    }
    stack <int> temp;
    int h = fa.statement_text_start - 1;
    temp.push(1);
    while(!temp.empty())
    {
        //cout << i;
        for(int k=0; k<input[h].size(); k++)
        {
            if(name[h][k].compare("{") == 0)
                temp.push(1);
            if(name[h][k].compare("}") == 0)
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
    //cout << name[i][0] << " " << i;
    fa.statement_text_start = i+3;
    if(name[i][input[i].size()-1].compare("{") == 0)
    {
        fa.statement_text_start = i+2;
    }
    stack <int> temp;
    int h = fa.statement_text_start - 1;
    temp.push(1);
    while(!temp.empty())
    {
        //cout << i;
        for(int k=0; k<input[h].size(); k++)
        {
            if(name[h][k].compare("{") == 0)
                temp.push(1);
            if(name[h][k].compare("}") == 0)
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
    if(name[h-1].size() > 1 && name[h-1][1].compare("while") == 0)
    {
        fa.endLine = h;
        f = 3;
        //cout << h;
    }
    //
    while(name[fa.endLine-1][f].compare(")") != 0)
    {
        fa.condition.push_back(name[fa.endLine-1][f]);
        fa.conditionType.push_back(input[fa.endLine-1][f]);
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
    while(name[i][f].compare(")") != 0)
    {
        fa.condition.push_back(name[i][f]);
        fa.conditionType.push_back(input[i][f]);
        f++;
    }
    if(name[i][input[i].size()-1].compare("{") == 0)
    {
        fa.statement_text_start = i+2;//25
    }
    if(name[i][input[i].size()-1].compare("{") != 0 && (name[i+1].size() > 0 && name[i+1][0].compare("{") != 0))
    {
        //cout << "jja" << name[i][input[i].size()-1] << name[i+1][0] << i;
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
            for(int k=0; k<input[h].size(); k++)
            {
                if(name[h][k].compare("{") == 0)
                    temp.push(1);
                if(name[h][k].compare("}") == 0)
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

    if(name[i][input[i].size()-1].compare("{") == 0)
    {
        fa.statement_text_start = i+2;
    }
    if(name[i][input[i].size()-1].compare("{") != 0 && (name[i+1].size() > 0 && name[i+1][0].compare("{") != 0))
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
            for(int k=0; k<input[h].size(); k++)
            {
                if(name[h][k].compare("{") == 0)
                    temp.push(1);
                if(name[h][k].compare("}") == 0)
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
    while(name[i][f].compare(")") != 0)
    {
        fa.condition.push_back(name[i][f]);
        fa.conditionType.push_back(input[i][f]);
        f++;
    }
    if(name[i][input[i].size()-1].compare("{") == 0)
    {
        fa.statement_text_start = i+2;
    }
    if(name[i][input[i].size()-1].compare("{") == 0 || (name[i+1].size() > 0 && name[i+1][0].compare("{") == 0))
    {
        stack <int> temp;
        int h = fa.statement_text_start - 1;
        temp.push(1);
        while(!temp.empty())
        {
            //cout << i;
            for(int k=0; k<input[h].size(); k++)
            {
                if(name[h][k].compare("{") == 0)
                    temp.push(1);
                if(name[h][k].compare("}") == 0)
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

        if(input[i].size() > 1 && name[i][0].compare("else") == 0  && name[i][1].compare("if") == 0)
        {
            //
            else_if_struct fi = elseIfGroup(i);
            fa.if_elses.push_back(fi);
            i = fi.endLine;//cout << i << endl;
        }
        else if(input[i].size() > 0 && name[i][0].compare("else") == 0)
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

void findGroup(void)
{
    for(int i=0; i<100; i++)
    {
        if(input[i].size() > 3 && input[i][0].compare("keyword") == 0  && input[i][1].compare("indentifier") == 0  && input[i][2].compare("oparetor") == 0  && input[i][3].compare("keyword") == 0) //function
        {
            i = functionGroup(i);
        }
        else if(name[i].size() > 4 && name[i][0].compare("for") == 0 && name[i][1].compare("(") == 0) //for
        {
            i = forGroup(i);
        }
        else if(name[i].size() > 3 && name[i][0].compare("while") == 0 && name[i][1].compare("(") == 0 && name[i][2].compare(")") != 0) //while
        {
            i = whileGroup(i);
        }
        else if((name[i].size() <= 2 && name[i].size() >= 1) && name[i][0].compare("do") == 0) //do-while
        {
            i = doWhileGroup(i);
        }
        else if(name[i].size() > 3 && name[i][0].compare("if") == 0)
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

    fp = fopen("output.txt","r");

    if(fp == NULL)
    {
        printf("error while opening the file\n");
        exit(0);
    }

    while((ch = fgetc(fp)) != EOF)
    {
        Text = Text + ch;
    }

    stringstream X(Text);
    while(getline(X, str, '\n'))
    {
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

    findGroup();

    return 0;
}
