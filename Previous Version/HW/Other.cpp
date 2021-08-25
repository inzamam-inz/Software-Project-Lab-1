/*struct stmts_struct{
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




//cout << "Name: " << fors[0]. << endl;
    //cout << "Return type: " << fors[0].returnType << endl;
    cout << "Do While:\n";
    cout << "dowhile Start Lin: " << do_whiles[0].startLine << endl;
    cout << "Statement Text start line: " << do_whiles[0].statement_text_start << endl;
    cout << "Statement end start line: " << do_whiles[0].statement_text_end << endl;
    cout << "dowhile end Lin: " << do_whiles[0].endLine << endl;

    cout << "Condition:\n";
    for(int a=0; a<do_whiles[0].condition.size(); a++){
        cout << do_whiles[0].condition[a] << " ";
    }
    cout << "ConditionType:\n";
    for(int a=0; a<do_whiles[0].conditionType.size(); a++){
        cout << do_whiles[0].conditionType[a] << " ";
    }
    cout << endl;
    cout << "\nWhile:\n";
    cout << "while Start Line: " << whiles[0].startLine << endl;
    cout << "Statement Text start line: " << whiles[0].statement_text_start << endl;
    cout << "Statement end start line: " << whiles[0].statement_text_end << endl;
    cout << "while end Line: " << whiles[0].endLine << endl;
    cout << "Condition:\n";
    for(int a=0; a<whiles[0].condition.size(); a++){
        cout << whiles[0].condition[a] << " ";
    }
    cout << "ConditionType:\n";
    for(int a=0; a<whiles[0].conditionType.size(); a++){
        cout << whiles[0].conditionType[a] << " ";
    }
    cout << "\nFor:\n";
    cout << "For Start Line: " << fors[0].startLine << endl;
    cout << "Statement Text start line: " << fors[0].statement_text_start << endl;
    cout << "Statement end start line: " << fors[0].statement_text_end << endl;
    cout << "For end Line: " << fors[0].endLine << endl;
    cout << "\ninitialize:\n";
    for(int a=0; a<fors[0].initialize.size(); a++){
        cout << fors[0].initialize[a] << " ";
    }
    cout << "\ninitializeType:\n";
    for(int a=0; a<fors[0].initializeType.size(); a++){
        cout << fors[0].initializeType[a] << " ";
    }
    cout << "\nCondition:\n";

    for(int a=0; a<fors[0].condition.size(); a++){
        cout << fors[0].condition[a] << " ";
    }
    cout << "\nConditionType:\n";
    for(int a=0; a<fors[0].conditionType.size(); a++){
        cout << fors[0].conditionType[a] << " ";
    }
    cout << "\nChange:\n";
    for(int a=0; a<fors[0].change.size(); a++){
        cout << fors[0].change[a] << " ";
    }
    cout << "\nChangeType:\n";
    for(int a=0; a<fors[0].changeType.size(); a++){
        cout << fors[0].changeType[a] << " ";
    }
    cout << "\nFunction:\n";
    cout << "function Start Line: " << functions[0].startLine << endl;
    cout << "Statement Text start line: " << functions[0].statement_text_start << endl;
    cout << "Statement end start line: " << functions[0].statement_text_end << endl;
    cout << "function end Line: " << functions[0].endLine << endl;
    cout << "Return Type: " << functions[0].returnType << endl;
    cout << "function name: " << functions[0].fname << endl;

    cout << "\nParameter:\n";
    for(int a=0; a<functions[0].parameter.size(); a++){
        cout << functions[0].parameter[a] << " ";
    }
    cout << "\nParameterType:\n";
    for(int a=0; a<functions[0].parameterType.size(); a++){
        cout << functions[0].parameterType[a] << " ";
    }
    cout << endl;


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

    /*
    cout << "If\nstart line = " << ifs[0].startLine << "\n";
    cout <<"end line = " <<  ifs[0].endLine << "\n";
    cout <<"statement_text_start = " << ifs[0].statement_text_start << "\n";
    cout << "statement_text_end = " << ifs[0].statement_text_end << "\n";
    cout << "\nCondition:\n";

    for(int a=0; a<ifs[0].condition.size(); a++){
        cout << ifs[0].condition[a] << " ";
    }
    cout << "\nConditionType:\n";
    for(int a=0; a<ifs[0].conditionType.size(); a++){
        cout << ifs[0].conditionType[a] << " ";
    }

    for(int b=0; b<ifs[0].elses.size(); b++){
        cout << ifs[0].elses[b].startLine << "\n";
        cout << ifs[0].elses[b].endLine << "\n";
        cout << ifs[0].elses[b].statement_text_start << "\n";
        cout << ifs[0].elses[b].statement_text_end << "\n";
    }


    for(int b=0; b<ifs[0].if_elses.size(); b++){
        cout << ifs[0].if_elses[b].startLine << "\n";
        cout << ifs[0].if_elses[b].endLine << "\n";
        cout << ifs[0].if_elses[b].statement_text_start << "\n";
        cout << ifs[0].if_elses[b].statement_text_end << "\n";
        cout << "\nCondition:\n";

    for(int a=0; a<ifs[0].if_elses[b].condition.size(); a++){
        cout << ifs[0].if_elses[b].condition[a] << " ";
    }
    cout << "\nConditionType:\n";
    for(int a=0; a<ifs[0].if_elses[b].conditionType.size(); a++){
        cout << ifs[0].if_elses[b].conditionType[a] << " ";
    }
    }*/


    /*cout << "If\nstart line = " << ifs[1].startLine << "\n";
    cout <<"end line = " <<  ifs[1].endLine << "\n";
    cout <<"statement_text_start = " << ifs[1].statement_text_start << "\n";
    cout << "statement_text_end = " << ifs[1].statement_text_end << "\n";
    cout << "\nCondition:\n";

    for(int a=0; a<ifs[1].condition.size(); a++){
        cout << ifs[1].condition[a] << " ";
    }
    cout << "\nConditionType:\n";
    for(int a=0; a<ifs[1].conditionType.size(); a++){
        cout << ifs[1].conditionType[a] << " ";
    }

    for(int b=0; b<ifs[1].elses.size(); b++){
        cout << "else" << b << endl;
        cout << ifs[1].elses[b].startLine << "\n";
        cout << ifs[1].elses[b].endLine << "\n";
        cout << ifs[1].elses[b].statement_text_start << "\n";
        cout << ifs[1].elses[b].statement_text_end << "\n";
    }


    for(int b=0; b<ifs[1].if_elses.size(); b++){
        cout << "ifelse" << b << endl;
        cout << ifs[1].if_elses[b].startLine << "\n";
        cout << ifs[1].if_elses[b].endLine << "\n";
        cout << ifs[1].if_elses[b].statement_text_start << "\n";
        cout << ifs[1].if_elses[b].statement_text_end << "\n";
        cout << "\nCondition:\n";

    for(int a=0; a<ifs[1].if_elses[b].condition.size(); a++){
        cout << ifs[1].if_elses[b].condition[a] << " ";
    }
    cout << "\nConditionType:\n";
    for(int a=0; a<ifs[1].if_elses[b].conditionType.size(); a++){
        cout << ifs[1].if_elses[b].conditionType[a] << " ";
    }
    }*/
