cout << "1th IF\nstart line = " << ifs[0].startLine << "\n";
    cout <<"end line = " <<  ifs[0].endLine << "\n";
    cout <<"statement_text_start_line = " << ifs[0].statement_text_start << "\n";
    cout << "statement_text_end_line = " << ifs[0].statement_text_end << "\n";
    cout << "Condition:\n";
    for(int a=0; a<ifs[0].condition.size(); a++)
    {
        cout << ifs[0].condition[a] << " ";
    }
    cout << "\nConditionType:\n";
    for(int a=0; a<ifs[0].conditionType.size(); a++)
    {
        cout << ifs[0].conditionType[a] << " ";
    }
    cout << "\n\n2th IF\nstart line = " << ifs[1].startLine << "\n";
    cout <<"end line = " <<  ifs[1].endLine << "\n";
    cout <<"statement_text_start_line = " << ifs[1].statement_text_start << "\n";
    cout << "statement_text_end_line = " << ifs[1].statement_text_end << "\n";
    cout << "Condition:\n";
    for(int a=0; a<ifs[1].condition.size(); a++)
    {
        cout << ifs[1].condition[a] << " ";
    }
    cout << "\nConditionType:\n";
    for(int a=0; a<ifs[1].conditionType.size(); a++)
    {
        cout << ifs[1].conditionType[a] << " ";
    }

    for(int b=0; b<ifs[1].if_elses.size(); b++)
    {
        cout << "\n\n"<< b+1 << "th " << "ELSE_IF\n";
        cout <<"start line = " << ifs[1].if_elses[b].startLine << "\n";
        cout <<"end line = " << ifs[1].if_elses[b].endLine << "\n";
        cout <<"statement_text_start_Line= " << ifs[1].if_elses[b].statement_text_start << "\n";
        cout <<"statement_text_end_line = " << ifs[1].if_elses[b].statement_text_end << "\n";
        cout << "Condition:\n";
        for(int a=0; a<ifs[1].if_elses[b].condition.size(); a++)
        {
            cout << ifs[1].if_elses[b].condition[a] << " ";
        }
        cout << "\nConditionType:\n";
        for(int a=0; a<ifs[1].if_elses[b].conditionType.size(); a++)
        {
            cout << ifs[1].if_elses[b].conditionType[a] << " ";
        }
    }
    for(int b=0; b<ifs[1].elses.size(); b++)
    {
        cout << "\n\n" << b+1 << "th ELSE"<< endl;
        cout <<"start line = "<< ifs[1].elses[b].startLine << "\n";
        cout <<"end line = "<< ifs[1].elses[b].endLine << "\n";
        cout <<"statement_text_start_Line= "<< ifs[1].elses[b].statement_text_start << "\n";
        cout <<"statement_text_end_line = "<< ifs[1].elses[b].statement_text_end << "\n";
    }
