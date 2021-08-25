cout << "1th FOR:\n\n";
    cout << "For Start Line: " << fors[0].startLine << endl;
    cout << "Statement Text start line: " << fors[0].statement_text_start << endl;
    cout << "Statement end start line: " << fors[0].statement_text_end << endl;
    cout << "For end Line: " << fors[0].endLine << endl;
    cout << "\ninitialize:\n";
    for(int a=0; a<fors[0].initialize.size(); a++)
    {
        cout << fors[0].initialize[a] << " ";
    }
    cout << "\ninitializeType:\n";
    for(int a=0; a<fors[0].initializeType.size(); a++)
    {
        cout << fors[0].initializeType[a] << " ";
    }
    cout << "\n\nCondition:\n";
    for(int a=0; a<fors[0].condition.size(); a++)
    {
        cout << fors[0].condition[a] << " ";
    }
    cout << "\nConditionType:\n";
    for(int a=0; a<fors[0].conditionType.size(); a++)
    {
        cout << fors[0].conditionType[a] << " ";
    }
    cout << "\n\nChange:\n";
    for(int a=0; a<fors[0].change.size(); a++)
    {
        cout << fors[0].change[a] << " ";
    }
    cout << "\nChangeType:\n";
    for(int a=0; a<fors[0].changeType.size(); a++)
    {
        cout << fors[0].changeType[a] << " ";
    }
    cout << endl;
