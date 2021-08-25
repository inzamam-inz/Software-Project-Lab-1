    cout << "Function in this program\n\n";
    cout << "Function name             : " << functions[0].fname << endl;
    cout << "Function Start Line       : " << functions[0].startLine << endl;
    cout << "Statement Text start line : " << functions[0].statement_text_start << endl;
    cout << "Statement end start line  : " << functions[0].statement_text_end << endl;
    cout << "Function end Line         : " << functions[0].endLine << endl;
    cout << "Return Type               : " << functions[0].returnType << endl;

    cout << "\nParameterType\tParameter\n";
    for(int a=0; a<functions[0].parameter.size(); a++){
        cout << functions[0].parameterType[a] << "\t\t" << functions[0].parameter[a] << endl;
    }
    cout << endl;
