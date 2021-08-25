cout << "Do While:\n";
    cout << "dowhile Start Lin: " << do_whiles[0].startLine << endl;
    cout << "Statement Text start line: " << do_whiles[0].statement_text_start << endl;
    cout << "Statement end start line: " << do_whiles[0].statement_text_end << endl;
    cout << "dowhile end Lin: " << do_whiles[0].endLine << endl;
    cout << "Condition:\n";
    for(int a=0; a<do_whiles[0].condition.size(); a++)
    {
        cout << do_whiles[0].condition[a] << " ";
    }
    cout << "\nConditionType:\n";
    for(int a=0; a<do_whiles[0].conditionType.size(); a++)
    {
        cout << do_whiles[0].conditionType[a] << " ";
    }
    cout << endl;
    cout << "\nWhile:\n";
    cout << "while Start Line: " << whiles[0].startLine << endl;
    cout << "Statement Text start line: " << whiles[0].statement_text_start << endl;
    cout << "Statement end start line: " << whiles[0].statement_text_end << endl;
    cout << "while end Line: " << whiles[0].endLine << endl;
    cout << "Condition:\n";
    for(int a=0; a<whiles[0].condition.size(); a++)
    {
        cout << whiles[0].condition[a] << " ";
    }
    cout << "\nConditionType:\n";
    for(int a=0; a<whiles[0].conditionType.size(); a++)
    {
        cout << whiles[0].conditionType[a] << " ";
    }
