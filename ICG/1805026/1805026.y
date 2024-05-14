
%{
    //#define YYSTYPE SymbolInfo*

    #include "SymbolTable.cpp"
    #include "parameter.cpp"
    #include <bits/stdc++.h>
    #include <typeinfo>
    #define yydebug 1
    #define ERROR "ERROR"
    #define UNDECLARED "undeclared"

    using namespace std;

    int yyparse(void);
    int yylex(void);
    extern FILE *yyin;



    ofstream logfile("1805026_log.txt"), errfile("1805026_error.txt");
    ofstream code("body.asm");
    ofstream header("code.asm");
    SymbolTable st(7, &logfile);

    extern int linenum;
    extern int errornum;

    int label_count = 0;

    string newLabel() {
        return "@L" + to_string(label_count++);
    }

    string functionReturnType = "";

    vector<string> labels, ret_labels;

    void yyerror(string s){
        logfile<<"Error at line "<<linenum<<": "<<s<<"\n"<<endl;
        errfile<<"Error at line "<<linenum<<": "<<s<<"\n"<<endl;
        errornum++;
    }

    void log(string rule, string token) {
        logfile << "Line " << linenum << ": " << rule << endl << endl << token << endl << endl;
    }
    void err(string err_msg) {
        logfile << "Error at line " << linenum << ": " << err_msg << endl << endl;
        errfile << "Error at line " << linenum << ": " << err_msg << endl << endl;
        errornum++;
    }

    vector<string> tokenize(string text, char delimiter)  {
        vector<string> tokens;
        stringstream textStream(text);
        string token;

        while(getline(textStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    vector<string> getParameterType(string parameterList) {
        vector<string> typeList;
        vector<string> pairs = tokenize(parameterList, ',');

        for (string pair: pairs) {
            typeList.push_back(tokenize(pair, ' ')[0]);
        }
        return typeList;
    }

    vector<Parameter> getParameters(string parameterList) {
        vector<Parameter> paramList;
        vector<string> pairs = tokenize(parameterList, ',');

        for (string pair: pairs) {
            vector<string> p = tokenize(pair, ' ');
            paramList.push_back(Parameter(p[1], p[0]));
        }
        return paramList;
    }

    bool checkArray(string varName) {
        if (varName.back() == ']' and (varName.find("[") != string::npos)) return true;
        return false;
    }

    pair<string, string> getArrayNameSize(string varName) {
        int L = varName.find("[");
        int R = varName.find("]");
        return {varName.substr(0, L), varName.substr(L+1, R - L - 1)};
    }

    bool isInt(string s)
    {
        string::const_iterator it = s.begin();
        while (it != s.end() && isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }

    void enterNewScope() {
        st.enterScope();
    }

    void exitCurScope() {
        st.exitScope();
    }

    void optimize_code() {
        ifstream inFile("code.asm");
        ofstream optCode("optimized_code.asm");
        vector<string> lines;
        string line;

        while(getline(inFile, line)) {
            lines.push_back(line);
        }
        int i;
        for (i=0; i+1 < lines.size(); i++) {
            if (lines[i].size() <= 3 or lines[i+1].size() <= 3) {
                optCode << lines[i] << endl;
            }
            else if (lines[i].substr(1, 3) == "MOV" and lines[i+1].substr(1, 3) == "MOV") {
                vector<string> cur_tokens = tokenize(lines[i], ' ');
                vector<string> nxt_tokens = tokenize(lines[i+1], ' ');

                if ((cur_tokens[1].substr(0, cur_tokens[1].size() - 1) == nxt_tokens[2]) and (nxt_tokens[1].substr(0, nxt_tokens[1].size() - 1) == cur_tokens[2])) {
                    optCode << lines[i++] << endl;
                } else {
                    optCode << lines[i] << endl;
                }
            }
            else if (lines[i].size() > 4 and lines[i+1].size() > 4 and lines[i].substr(1, 4) == "PUSH" and lines[i+1].substr(1, 3) == "POP") {
                vector<string> cur_tokens = tokenize(lines[i], ' ');
                vector<string> nxt_tokens = tokenize(lines[i+1], ' ');
                // cout << lines[i] << " : " << lines[i+1] << endl;
                if (cur_tokens[1].substr(0, cur_tokens[1].size() - 1) == nxt_tokens[1].substr(0, nxt_tokens[1].size() - 1)  ) {
                    i++; 
                } else {
                    optCode << lines[i] << endl;
                }
            }
            else {
                optCode << lines[i] << endl;
            }
        }

        if (i < lines.size()) optCode << lines[i] << endl;
        inFile.close();
        optCode.close();
    }

    void add_print_proc()
    {

        code << "PRINTLN PROC NEAR\n";
        code << "\tPUSH AX\n";
        code << "\tPUSH BX\n";
        code << "\tPUSH CX\n";
        code << "\tPUSH DX\n";
        code << "\t\n";

        code << "\tMOV AX, print_var\n";
        code << "\tOR AX, AX\n";
        code << "\tJGE @END_IF1\n";
        code << "\tPUSH AX\n";
        code << "\tMOV DL, '-'\n";
        code << "\tMOV AH, 2\n";
        code << "\tINT 21H\n";
        code << "\tPOP AX\n";
        code << "\tNEG AX\n";
        code << "\n";

        code << "@END_IF1:\n";
        code << "\tXOR CX, CX\n";
        code << "\tMOV BX, 10D\n";
        code << "\n";

        code << "@REPEAT:\n";
        code << "\tXOR DX, DX\n";
        code << "\tDIV BX\n";
        code << "\tPUSH DX\n";
        code << "\tINC CX\n";
        code << "\tOR AX, AX\n";
        code << "\tJNE @REPEAT\n";
        code << "\tMOV AH, 2\n";
        code << "\n";

        code << "@PRINT_LOOP:\n";
        code << "\tPOP DX\n";
        code << "\tOR DL, 30H\n";
        code << "\tINT 21H\n";
        code << "\tLOOP @PRINT_LOOP\n";

        code << "\tMOV DL, 0DH\n";
        code << "\tMOV AH, 2\n";
        code << "\tINT 21H\n";

        code << "\tMOV DL, 0AH\n";
        code << "\tMOV AH, 2\n";
        code << "\tINT 21H\n";

        code << "\tPOP DX\n";
        code << "\tPOP CX\n";
        code << "\tPOP BX\n";
        code << "\tPOP AX\n";

        code << "\tRET\n";
        code << "\n";
        code << "PRINTLN ENDP\n\n";
    }


%}

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE 

%union {
	SymbolInfo* syminfo;
}

%type <syminfo> start program unit var_declaration func_declaration type_specifier parameter_list
%type <syminfo> compound_statement func_definition statements declaration_list statement
%type <syminfo> expression expression_statement variable logic_expression rel_expression
%type <syminfo> simple_expression term unary_expression factor argument_list arguments if_statement

%token UNRECOGNIZED INCOP DECOP ASSIGNOP NOT LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD
%token BREAK CASE CONTINUE DEFAULT RETURN SWITCH VOID 
%token CHAR DOUBLE FLOAT INT DO WHILE FOR IF ELSE
%token COMMA SEMICOLON PRINTLN


%token <syminfo> ID ERROR_ID
%token <syminfo> CONST_FLOAT ERROR_FLOAT
%token <syminfo> CONST_CHAR
%token <syminfo> CONST_INT

%token <syminfo> ADDOP MULOP RELOP LOGICOP

%%

start:  program
        {
            log("start : program", "");
            $$ = $1;
            code.close();
            header << endl;

            ifstream code_file("body.asm");
            string line;
            while(getline(code_file, line)) {
                header << line << endl;
            }
            code_file.close();
        }
    ;

program: program unit
        {
            string text = $1->getName() + "\n" + $2->getName();
            log("program : program unit", text);
            $$ = new SymbolInfo(text, "program");
        }
        | unit
        {
            log("program : unit", $1->getName());
            $$ = $1;
        }
    ;

unit:   var_declaration 
        {
            $$ = $1;
            log("unit: var_declaration", $$->getName());
        }
        | func_declaration
        {
            $$ = $1;
            log("unit: func_declaration", $$->getName());
        }
        | func_definition 
        {
            $$ = $1;
            log("unit: func_defination", $$->getName());
        }
    ;        

func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
        {
            string returnType   = $1->getName();
            string funcName     = $2->getName();

            SymbolInfo* func = st.lookUp(funcName);
            if (func != nullptr) {
                err("Multiple declaration of function '" + funcName + "'");
            } else {
                vector<string>  param_type_list = getParameterType($4->getName());
                vector<Parameter> param_list = getParameters($4->getName());

                for (int i=0; i<param_list.size(); i++)  {
                    for (int j=i-1; j<i; j++) {
                        if (param_list[i].name == param_list[j].name) {
                            err("Multiple declaration of " + param_list[i].name);
                            break;
                        }
                    }
                }


                SymbolInfo temp("", "");
                temp.setAsFunction(funcName, returnType, param_list);
                temp.defined = false;

                st.insertSymbol(temp);
            }
            string text = $1->getName() + " " + $2->getName() + "(" + $4->getName() + ");";
            $$ = new SymbolInfo(text, "func_declaration");
            log("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON", text);

        }
        | type_specifier ID LPAREN RPAREN SEMICOLON
        {
            string returnType   = $1->getName();
            string funcName     = $2->getName();
            SymbolInfo* func = st.lookUp(funcName);
            if (func != nullptr) {
                err("Multiple declaration of function '" + funcName + "'");
            }
            else {
                vector<Parameter> param_list;
                SymbolInfo temp("", "");
                temp.setAsFunction(funcName, returnType, param_list);
                temp.defined = false;

                st.insertSymbol(temp);
            }
            string text = $1->getName() + " " + $2->getName() + "();";
            $$ = new SymbolInfo(text, "func_declaration");
            log("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON", text);
        }
        | type_specifier ID LPAREN error RPAREN SEMICOLON
        {
            string returnType   = $1->getName();
            string funcName     = $2->getName();
            SymbolInfo* func = st.lookUp(funcName);
            if (func != nullptr) {
                err("Multiple declaration of function '" + funcName + "'");
            }
            else {
                vector<Parameter> param_list;
                SymbolInfo temp("", "");
                temp.setAsFunction(funcName, returnType, param_list);
                temp.defined = false;

                st.insertSymbol(temp);
            }
            string text = $1->getName() + " " + $2->getName() + "();";
            $$ = new SymbolInfo(text, "func_declaration");
            log("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON", text);
        }
    ;

func_definition : type_specifier ID LPAREN parameter_list RPAREN
        {
            string returnType   = $1->getName();
            string funcName     = $2->getName();
            SymbolInfo* func = st.lookUp(funcName);
            vector<Parameter> pList = getParameters($4->getName());

            ret_labels.push_back(newLabel());

            if ($2->getName() == "main") {

                st.offset = 0;
                code << "MAIN PROC\n";
                code << "\tMOV AX, @DATA\n";
                code << "\tMOV DS, AX\n";
                code << "\tPUSH BP \t\t;Storing BP for last scope" << endl;
                code << "\tMOV BP, SP" << endl;

            } else {
                st.offset = 0;
                code << $2->getName() + " PROC\n";
                code << "\tPUSH AX" << endl;
                code << "\tPUSH BX" << endl;
                code << "\tPUSH CX" << endl;
                code << "\tPUSH BP \t\t;Storing BP for last scope" << endl;
                code << "\tMOV BP, SP" << endl;
            }

            if (func == nullptr) {
                SymbolInfo temp("" ,"");

                temp.setAsFunction(funcName, returnType, pList);
                temp.defined = true;
                st.insertSymbol(temp);

                enterNewScope();
                int offset = -8;
                for (int i=pList.size()-1; i >=0; i--) {
                    SymbolInfo paramInfo(pList[i].name, pList[i].type);
                    offset -= 2;
                    if (st.insertSymbol(paramInfo, offset) == false){ 
                        err("Multiple declaration of variable '" + pList[i].name + "' in parameter");
                    }
                }
                st.printAllScopeTable();
            } else {
                if (func->isFunction) {
                    if (func->defined) {
                        err("Re-definition of function '" + funcName + "'");
                    }
                    else {
                        bool errorFound = false;
                        vector<Parameter> decPList = func->paramList;

                        if (decPList.size() != pList.size()) {
                            errorFound = true;
                            err("Total number of arguments mismatch with declaration in function " + funcName);
                        }

                        if (func->getType() != returnType) {
                            errorFound = true;
                            err("Return type mismatch with function declaration in function " + funcName);
                        }

                        if ( decPList.size() == pList.size() ) {
                            for (int i=0; i<decPList.size(); i++) {
                                if (decPList[i].type != pList[i].type) {
                                    errorFound = true;
                                    err(to_string(i+1) + "th argument mismatch in function func");
                                }
                            }
                        }

                        st.remove(funcName);

                        SymbolInfo temp("", "");
                        temp.setAsFunction(funcName, returnType, pList);
                        temp.defined = true;

                        st.insertSymbol(temp);
                        enterNewScope();
                        for (int i=0; i < pList.size(); i++) {
                            SymbolInfo paramInfo(pList[i].name, pList[i].type);
                            if (st.insertSymbol(paramInfo) == false){ 
                                err("Multiple declaration of variable '" + pList[i].name + "' in parameter");
                            }
                        }

                    }
                }
                else {
                    enterNewScope();
                    err("Multiple declaration of '" + funcName + "'");

                    for (int i=0; i < pList.size(); i++) {
                        SymbolInfo paramInfo(pList[i].name, pList[i].type);
                        if (st.insertSymbol(paramInfo) == false){ 
                            err("Multiple declaration of variable '" + pList[i].name + "' in parameter");
                        }
                    }

                }
            }
        }
        compound_statement
        {
            string funcName = $2->getName();
            string cur_ret_label = ret_labels.back();
            ret_labels.pop_back();
            if (funcName == "main") {
                
                code << "\t" << cur_ret_label << ": " << endl;
                code << "\tMOV AX, 4CH\n";
                code << "\tINT 21H\n";
                code << "MAIN ENDP\n";
                code << "END MAIN\n\n";


            } 
            else {
                vector<Parameter> pList = getParameters($4->getName());
                code << "\t" << cur_ret_label << ": " << endl;
                code << "\tMOV SP, BP" << endl;
                code << "\tPOP BP" << endl;
                code << "\tPOP CX" << endl;
                code << "\tPOP BX" << endl;
                code << "\tPOP AX" << endl;
                code << "\tRET " << 2 * pList.size() << endl;
                code << $2->getName() <<  " ENDP\n\n";
            }

            string name = $1->getName() + " " + $2->getName() + "( " + $4->getName() + ") " + $7->getName() + "\n";
            $$ = new SymbolInfo(name, "func_defination");
            log("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement", name);
        }
        | type_specifier ID LPAREN RPAREN 
        {
            string returnType   = $1->getName();
            string funcName     = $2->getName();
            SymbolInfo* func = st.lookUp(funcName);

            vector<Parameter> pList;
            ret_labels.push_back(newLabel());

            if ($2->getName() == "main") {
                st.offset = 0;
                code << "MAIN PROC\n";
                code << "\tMOV AX, @DATA\n";
                code << "\tMOV DS, AX\n";
                code << "\tPUSH BP \t\t;Storing BP for last scope" << endl;
                code << "\tMOV BP, SP" << endl;
            } else {
                st.offset = 0;
                code << $2->getName() + " PROC\n";
                code << "\tPUSH AX" << endl;
                code << "\tPUSH BX" << endl;
                code << "\tPUSH CX" << endl;
                code << "\tPUSH BP \t\t;Storing BP for last scope" << endl;
                code << "\tMOV BP, SP" << endl;
            }

            if (func == nullptr) {
                SymbolInfo temp("" ,"");

                temp.setAsFunction(funcName, returnType, pList);
                temp.defined = true;
                st.insertSymbol(temp);

                enterNewScope();
            } else {
                if (func->isFunction) {
                    if (func->defined) {
                        err("Re-definition of function '" + funcName + "'");
                    }
                    else {
                        bool errorFound = false;
                        vector<Parameter> decPList = func->paramList;

                        if (decPList.size() != pList.size()) {
                            errorFound = true;
                            err("Total number of arguments mismatch with declaration in function " + funcName);
                        }

                        if (func->getType() != returnType) {
                            errorFound = true;
                            err("Return type mismatch with function declaration in function " + funcName);
                        }

                        if ( decPList.size() == pList.size() ) {
                            for (int i=0; i<decPList.size(); i++) {
                                if (decPList[i].type != pList[i].type) {
                                    errorFound = true;
                                    err(to_string(i+1) + "th argument mismatch in function func");
                                }
                            }
                        }

                        if (errorFound == false) {
                            st.remove(funcName);

                            SymbolInfo temp("", "");
                            temp.setAsFunction(funcName, returnType, pList);
                            temp.defined = true;

                            st.insertSymbol(temp);
                        }
                        enterNewScope();

                    }
                }
                else {
                    enterNewScope();
                    err("Multiple declaration of '" + funcName);
                }
            }
            
        }
        compound_statement 
        {
            string funcName = $2->getName();
            string cur_ret_label = ret_labels.back();
            ret_labels.pop_back();
            if (funcName == "main") {
                code << "\t" << cur_ret_label << ": " << endl;
                code << "\tMOV AX, 4CH\n";
                code << "\tINT 21H\n";
                code << "MAIN ENDP\n";
                code << "END MAIN\n\n";
            } 
            else {
                code << "\t" << cur_ret_label << ": " << endl;
                code << "\tMOV SP, BP" << endl;
                code << "\tPOP BP" << endl;
                code << "\tPOP CX" << endl;
                code << "\tPOP BX" << endl;
                code << "\tPOP AX" << endl;
                code << "\tRET 0\n";
                code << $2->getName() <<  " ENDP\n\n";
            }

            string name = $1->getName() + " " + $2->getName() + "() " + $6->getName() + "\n";
            $$ = new SymbolInfo(name, "func_defination");
            log("func_definition : type_specifier ID LPAREN RPAREN compound_statement", name);
        }
        | type_specifier ID LPAREN error RPAREN
        {
            string returnType   = $1->getName();
            string funcName     = $2->getName();
            SymbolInfo* func = st.lookUp(funcName);

            vector<Parameter> pList;

            if (func == nullptr) {
                SymbolInfo temp("" ,"");

                temp.setAsFunction(funcName, returnType, pList);
                temp.defined = true;
                st.insertSymbol(temp);

                enterNewScope();
            } else {
                if (func->isFunction) {
                    if (func->defined) {
                        err("Re-definition of function '" + funcName + "'");
                    }
                    else {
                        bool errorFound = false;
                        vector<Parameter> decPList = func->paramList;

                        if (decPList.size() != pList.size()) {
                            errorFound = true;
                            err("Total number of arguments mismatch with declaration in function " + funcName);
                        }

                        if (func->getType() != returnType) {
                            errorFound = true;
                            err("Return type mismatch with function declaration in function " + funcName);
                        }

                        if ( decPList.size() == pList.size() ) {
                            for (int i=0; i<decPList.size(); i++) {
                                if (decPList[i].type != pList[i].type) {
                                    errorFound = true;
                                    err(to_string(i+1) + "th argument mismatch in function func");
                                }
                            }
                        }

                        if (errorFound == false) {
                            st.remove(funcName);

                            SymbolInfo temp("", "");
                            temp.setAsFunction(funcName, returnType, pList);
                            temp.defined = true;

                            st.insertSymbol(temp);
                        }
                        enterNewScope();

                    }
                }
                else {
                    enterNewScope();
                    err("Multiple declaration of '" + funcName);
                }
            }
            
        }
        compound_statement 
        {
            string name = $1->getName() + " " + $2->getName() + "() " + $7->getName() + "\n";
            $$ = new SymbolInfo(name, "func_defination");
            log("func_definition : type_specifier ID LPAREN RPAREN compound_statement", name);
        }
        ;

parameter_list : parameter_list COMMA type_specifier ID
        {
            $$ = new SymbolInfo($1->getName() + "," + $3->getName() + " " + $4->getName(), "parameter_list");
            log("parameter_list : parameter_list COMMA type_specifier ID" , $$->getName());
        }
        | parameter_list COMMA type_specifier 
        {
            $$ = new SymbolInfo($1->getName() + "," + $3->getName(), "parameter_list");
            log("parameter_list : parameter_list COMMA type_specifier", $$->getName());
        }
        | type_specifier ID
        {
            $$ = new SymbolInfo($1->getName() + " " + $2->getName(), "paramter_list");
            log("parameter_list : type_specifier ID", $$->getName());
        }
        | type_specifier
        {
            err("Parameter Name not given");
            $$ = new SymbolInfo($1->getName(), "parameter_list");
            log("parameter_list : type_specifier" , $$->getName());
        }
        | type_specifier error 
        {
            err("Parameter Name not given");
            $$ = new SymbolInfo($1->getName(), "parameter_list");
            log("parameter_list : type_specifier" , $$->getName());
        }
        ;

compound_statement : LCURL statements RCURL
        {
            $$ = new SymbolInfo("{\n" + $2->getName() + "\n}", "compount_statement");
            log("compound_statement : LCURL statements RCURL" , $$->getName());

            st.printAllScopeTable();
            exitCurScope();
        }
        | LCURL RCURL
        {
            $$ = new SymbolInfo("{\n\n}", "compount_statement");
            log("compound_statement : LCURL RCURL" , $$->getName());
        }
        ;

var_declaration : type_specifier declaration_list SEMICOLON
        {
            string dataType = $1->getName();
            string varNames = $2->getName();

            if (dataType == "void") {
                err("Void type variables not allowed");
            }
            else {
                vector<string> var_name_list = tokenize(varNames, ',');
                SymbolInfo temp("", "");
                for (string vName: var_name_list) {

                    if (checkArray(vName)) {
                        pair<string, string> nameSize = getArrayNameSize(vName);
                        if (isInt(nameSize.second) == false) {
                            err("Non integer size for array provided");
                            continue;
                        }
                        int arraySize = stoi(nameSize.second);
                        temp.setAsArray(nameSize.first, dataType, arraySize);
                    }
                    else {
                        temp = SymbolInfo(vName, dataType);
                    }

                    if (st.getId() == "1") {
                        // global
                        // cout << "Global Variable " << vName << endl;
                        if (temp.size == 1) header << "\t" << temp.getName() << " DW ? " << endl;
                        else header << "\t" << temp.getName() << " DW " << temp.size << " DUP(?) " << endl;
                        temp.isGlobal = true;
                    } else {
                        code << "\tADD SP, -" << temp.size*2 << endl;
                    }

                    if (!st.insertSymbol(temp)) {
                        err("Multiple Declaration of variable '" + temp.getName() + "'");
                    }
                }

                $$ = new SymbolInfo(dataType + " " + varNames + ";", " var_declaration");
                log("var_declaration : type_specifier declaration_list SEMICOLON", $$->getName());
            }
        }
        ;

type_specifier : INT
        {
            $$ = new SymbolInfo("int" , "int");
            log("type_specifier : INT", $$->getName());
        }
        | FLOAT 
        {
            $$ = new SymbolInfo("float" , "float");
            log("type_specifier : FLOAT", $$->getName());
        }
        | VOID 
        {
            $$ = new SymbolInfo("void" , "void");
            log("type_specifier : VOID", $$->getName());
        }
        ;

declaration_list : declaration_list COMMA ID
        {
            $$ = new SymbolInfo($1->getName() + "," + $3->getName(), "declaration_list");
            log("declaration_list : declaration_list COMMA ID", $$->getName());
        }
        | declaration_list error COMMA ID
        {
            $$ = new SymbolInfo($1->getName() + "," + $4->getName(), "declaration_list");
            log("declaration_list : declaration_list COMMA ID", $$->getName());
        }
        | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
        {
            $$ = new SymbolInfo($1->getName() + "," + $3->getName() + "[" + $5->getName() + "]", "declaration_list");
            log("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD", $$->getName());
        }
        | ID
        {
            $$ = new SymbolInfo($1->getName() , "declaration_list");
            log("declaration_list : ID", $$->getName());
        }
        
        | ID LTHIRD CONST_INT RTHIRD
        {
            $$ = new SymbolInfo($1->getName() + "[" + $3->getName() + "]", "declaration_list");
            log("declaration_list : ID LTHIRD CONST_INT RTHIRD", $$->getName());
        }
        ;

statements : statement
        {
            $$ = new SymbolInfo($1->getName(), "statements");
            log("statements : statement", $$->getName());
        }
        | statements statement
        {
            $$ = new SymbolInfo($1->getName() + "\n" + $2->getName(), "statements");
            log("statements : statements statement", $$->getName());
        }
		;

if_statement : IF LPAREN expression RPAREN 
        { 
            string label1 = newLabel(), label2 = newLabel();
            labels.push_back(label1);
            labels.push_back(label2);
            code << "\tPOP AX" << endl;
            code << "\tCMP AX, 0" << endl;
            code << "\tJE " << label1 << endl;
        }
        statement 
        {
            string label1 = labels[((int)labels.size()) - 2], label2 = labels.back();
            $$ = new SymbolInfo("if(" + $3->getName() + ")" + $6->getName(), "if_statement");
			log("if_statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement", $$->getName());
            code << "\tJMP " << label2  << " \t\t ; IF ENDED" << endl;
            code << "\t" << label1 << ": \t\t ; ELSE STARTED" << endl;
        }
        ;


statement : var_declaration
        {
            $$ = new SymbolInfo($1->getName(), "statement");
            log("statement : var_declaration", $$->getName());
        }
        | expression_statement 
        {
            $$ = new SymbolInfo($1->getName(), "statement");
            log("statement : expression_statement", $$->getName());
        }
        | { enterNewScope(); } compound_statement 
        {
            $$ = new SymbolInfo($2->getName(), "statement");
            log("statement : compound_statement", $$->getName());
        }
        | FOR LPAREN expression_statement
        {
            string label1 = newLabel(), label2 = newLabel(), label3 = newLabel(), label4 = newLabel();
            labels.push_back(label1); labels.push_back(label2);
            labels.push_back(label3); labels.push_back(label4);  
            code << "\t" <<label1  << ":  \t\t\t ;LABEL1" << endl;
        } 
        expression_statement
        {
            string label4 = labels[((int)labels.size()) - 1], label3 = labels[((int)labels.size()) - 2];
            string label2 = labels[((int)labels.size()) - 3];
            code << "\tPOP AX" << endl;
            code << "\tCMP AX, 0" << endl;
            code << "\tJE " <<  label4 << endl;
            code << "\tJMP " << label3 << endl;

            code << "\t" << label2  << ": " << endl;
            // code << "\t\t CHECK CONDITION HERE and JUMP OVER INC EXPRESSION" << endl;
        }
        expression
        {
            string label1 = labels[((int)labels.size()) - 4];
            string label3 = labels[((int)labels.size()) - 2];
            code << "\tJMP " << label1 << endl;
            code << "\t" << label3 << ": " << endl;
        }
        RPAREN statement 
        {
            $$ = new SymbolInfo("for (" + $3->getName() + $5->getName() + $7->getName() + ")" + $10->getName(),	"statement");
			log("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement", $$->getName());

            string label2 = labels[((int)labels.size()) - 3];
            string label4 = labels[((int)labels.size()) - 1];
            code << "\tJMP " << label2 << endl;
            code << "\t" << label4 << ": " << endl;

            labels.pop_back();
            labels.pop_back();
            labels.pop_back();
            labels.pop_back();
        }
        | if_statement %prec LOWER_THAN_ELSE
        {
            string label1 = labels[((int)labels.size()) - 2], label2 = labels.back();
            code << "\t" << label2 <<  ":  \t\t;IF END" << endl;
            $$ = $1;
			log("statement : IF LPAREN expression RPAREN statement", $$->getName());
            labels.pop_back();
            labels.pop_back();
        }
        | if_statement ELSE statement
        {
            string label1 = labels[((int)labels.size()) - 2], label2 = labels.back();
            $$ = new SymbolInfo($1->getName() + "else" + $3->getName(),	"statement");
            log("statement : IF LPAREN expression RPAREN statement ELSE statement", $$->getName());
            code << "\t" << label2 << ": \t\t; ELSE END" << endl;
            labels.pop_back();
            labels.pop_back();
        }
        | WHILE 
        {
            string label1 = newLabel(), label2 = newLabel();
            labels.push_back(label1);
            labels.push_back(label2);
            code << "\t" << label1 << ": \t\t;WHILE START" << endl;
        } 
        LPAREN expression RPAREN
        {
            string label2 = labels.back();
            code << "\tPOP AX" << endl;
            code << "\tCMP AX, 0" << endl;
            code << "\tJE " << label2 << endl;
        } 
        statement
        {

            string label2 = labels.back(), label1 = labels[((int)labels.size()) - 2];

            $$ = new SymbolInfo("while(" + $4->getName() + ")" + $7->getName(),	"statement");
            log("statement : WHILE LPAREN expression RPAREN statement", $$->getName());
            code << "\tJMP " << label1 << endl;
            code << "\t" << label2 << ": \t\t;WHILE END" << endl;
            labels.pop_back();
            labels.pop_back();
        }
        | PRINTLN LPAREN ID RPAREN SEMICOLON
        {
            string varName = $3->getName();
            SymbolInfo* sym_var = st.lookUp(varName);

            if (sym_var) {
                if (sym_var->isVar == false) {
                    err("Not a variable : " + varName);
                }
                if (sym_var->isGlobal) {
                    code << "\tMOV AX, " << sym_var->getName() << endl;
                } else {
                    code << "\tMOV AX, [BP - " << sym_var->offset << "]" << endl;
                }
                code << "\tMOV print_var, AX" << endl;
                code << "\tCALL PRINTLN" << endl;
            } else {
                err("Undeclared variable " + varName);
            }
            $$ = new SymbolInfo("printf(" + varName + ");", "statement");
            log("statement : PRINTLN LPAREN ID RPAREN SEMICOLON", $$->getName());
        }
        | RETURN expression SEMICOLON {
            // cout << "HERE" << endl;
            string func_ret_label = ret_labels.back();
            // cout << "HERE" << endl;
            code << "\tPOP DX" << endl;
            code << "\tJMP " << func_ret_label << endl;
            if (functionReturnType == "void") {
                err("Void Function cannot have return statement");
                functionReturnType = "";
            }

            $$ = new SymbolInfo("return " + $2->getName() + ";", "statement");
            log("statement: RETURN expression SEMICOLON", $$->getName());
        }
        | UNRECOGNIZED {
            $$ = new SymbolInfo("", "");
            err("Unrecognized Character");
        }
        | error UNRECOGNIZED {
            $$ = new SymbolInfo("", "");
            err("Unrecognized Character");
        }
        ;

expression_statement : SEMICOLON
        {
            $$ = new SymbolInfo(";", "expression_statement");
            log("expression_statement : SEMICOLON", $$->getName());
        }
        | expression SEMICOLON 
        {
            $$ = new SymbolInfo($1->getName() + ";", "expression_statement");
            log("expression_statement : expression SEMICOLON", $$->getName());
        }
        ;

variable : ID
        {
            string varName = $1->getName();
            SymbolInfo* var_symbol = st.lookUp(varName);

            if (var_symbol) {
                if (var_symbol->isArray) {
                    // SymbolInfo* temp = new SymbolInfo("", "");
                    // temp->setAsArray(var_symbol->getName(), "array", var_symbol->size);
                    // $$ = temp;

                    $$ = var_symbol;
                }
                else if (var_symbol->isFunction)  {
                    SymbolInfo* temp = new SymbolInfo("", "");
                    temp->setAsFunction(var_symbol->getName(), ERROR, vector<Parameter>());
                    $$ = temp;
                }
                else {
                    // $$ = new SymbolInfo(var_symbol->getName(), var_symbol->getType());
                    $$ = var_symbol;
                }
            }
            else {
                err("Undeclared variable " + varName);
                $$ = new SymbolInfo($1->getName(), ERROR);
            }

            log("variable : ID", $$->getName());
        }
        | ID LTHIRD expression RTHIRD
        {
            string varName = $1->getName();
            SymbolInfo* var_symbol = st.lookUp(varName);
            string text = $1->getName() + "[" + $3->getName() + "]";
            
            code <<"\tPOP AX" << endl;
            if (var_symbol) {
                if (var_symbol->isArray) {
                    if ($3->getType() != "int") {
                        err("Expression inside third brackets not an integer");
                    }
                    $$ = new SymbolInfo(text, var_symbol->getType());
                    // cout << var_symbol->offset << endl;
                    $$->isGlobal = var_symbol->isGlobal;
                    $$->offset = stoi($3->getName()) * 2 + var_symbol->offset;
                }
                else if (var_symbol->isFunction)  {
                    SymbolInfo* temp = new SymbolInfo("", "");
                    temp->setAsFunction(var_symbol->getName(), ERROR, vector<Parameter>());
                    $$ = temp;
                }
                else {
                    err(varName+ " is not a array");
                    if ($3->getType() != "int") {
                        err("Expression inside third brackets not an integer");
                    }
                    SymbolInfo* temp = new SymbolInfo(text, ERROR);
                    $$ = temp;
                }
            }
            else {
                err("Undeclared variable " + varName);
                $$ = new SymbolInfo(text , ERROR);
            }
            log("variable : ID LTHIRD expression RTHIRD", $$->getName());
        }
        ;

expression : logic_expression 
        {
            $$ = $1;
            log("expression : logic_expression", $$->getName());
        }
        | error logic_expression
        {
            $$ = $2;
            log("expression : logic_expression", $$->getName());
        }
        | logic_expression error 
        {
            $$ = $1;
            log("expression : logic_expression", $$->getName());
        }
        | variable ASSIGNOP logic_expression
        {
            if ($3->getType() == "void" or $1->getType() == "void") {
                err("Void function used in expression");
            }
            else if ($1->getType() != $3->getType()) {
                if ($1->getType() == ERROR or $3->getType() == ERROR) {
                    if ($1->isArray) {
                        err("Type Mismatch, " + $1->getName() + " is an array");
                    }
                    else if ($3->isArray) {
                        err("Type Mismatch, " + $3->getName() + " is an array");
                    } else {

                    }
                }
                else if ($1->getType() == "float" and $3->getType() == "int"){

                }
                else {
                    err("Type Mismatch ");
                }
            }
            $$ = new SymbolInfo($1->getName() + "=" + $3->getName(), "expression");
            code << "\tPOP AX" << endl;
            if ($1->isGlobal) {
                code << "\tMOV " << $1->getName() << ", AX \t\t; " << $$->getName() << endl << endl;
            } else {
                code << "\tMOV [BP - " << $1->offset << "], AX \t\t;" << $$->getName() << endl << endl;
            }
            // code << "\tPUSH AX  \t\t\t;VALUE OF EXPRESSION" << endl;
            log("expression : variable ASSIGNOP logic_expression", $$->getName());
        }
        ;

logic_expression : rel_expression
        {
            $$ = $1;
            log("logic_expression : rel_expression", $$->getName());
        }
        | rel_expression LOGICOP rel_expression
        {
            code << "\tPOP BX" << endl;
            code << "\tPOP AX" << endl;

            string label1 = newLabel(), label2 = newLabel();
            if ($2->getName() == "&&") {
                code << "\tCMP AX, 0" << endl;
                code << "\tJE " << label2 << endl;
                code << "\tCMP BX, 0" << endl;
                code << "\tJE " << label2 << endl;
                code << "\tPUSH 1" << endl;
                code << "\tJMP " << label1 << endl;
                code << "\t" << label2  << ": " << endl;
                code << "\tPUSH 0" << endl;
                code << "\t" << label1 << ": \t\t;" << $1->getName() << $2->getName() << $3->getName() << endl << endl;
            }
            else {
                code << "\tCMP AX, 0" << endl;
                code << "\tJNE " << label2 << endl;
                code << "\tCMP BX, 0" << endl;
                code << "\tJNE " << label2 << endl;
                code << "\tPUSH 0" << endl;
                code << "\tJMP " << label1 << endl;
                code << "\t" << label2  << ": " << endl;
                code << "\tPUSH 1" << endl;
                code << "\t" << label1 << ": \t\t;" << $1->getName() << $2->getName() << $3->getName() << endl << endl;
            }

            if ($1->getType() == "int" and $3->getType() == "int") {
                $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(),	"int");
            } else {
                err("Both operands must be int type. Given " + $1->getType() + " : " + $3->getType());
                $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(),	ERROR);
            }
            log("logic_expression : rel_expression LOGICOP rel_expression", $$->getName());
        }
        ;

rel_expression : simple_expression
        {
            $$ = $1;
			log("rel_expression : simple_expression", $$->getName());
        }
        | simple_expression RELOP simple_expression
        {
            code << "\tPOP BX" << endl << "\tPOP AX" << endl;
            string label1 = newLabel();
            string label2 = newLabel();
            if ($2->getName() == "<") {
                code << "\tCMP AX, BX" << endl;
                code << "\tJL " << label1 << endl;
                code << "\tPUSH 0" << endl;
                code << "\tJMP " << label2 << endl;
                code << "\t" << label1 << ": " << endl;
                code << "\tPUSH 1" << endl;
                code << "\t" << label2 << ":  \t\t ; " << $1->getName() << $2->getName() << $3->getName() << endl << endl;;
            }
            else if ($2->getName() == ">") {
                code << "\tCMP BX, AX" << endl;
                code << "\tJL " << label1 << endl;
                code << "\tPUSH 0" << endl;
                code << "\tJMP " << label2 << endl;
                code << "\t" << label1 << ": " << endl;
                code << "\tPUSH 1" << endl;
                code << "\t" << label2 << ":  \t\t ; " << $1->getName() << $2->getName() << $3->getName() << endl << endl;;
            }
            else if ($2->getName() == "<=") {
                code << "\tCMP AX, BX" << endl;
                code << "\tJLE " << label1 << endl;
                code << "\tPUSH 0" << endl;
                code << "\tJMP " << label2 << endl;
                code << "\t" << label1 << ": " << endl;
                code << "\tPUSH 1" << endl;
                code << "\t" << label2 << ":  \t\t ; " << $1->getName() << $2->getName() << $3->getName() << endl << endl;;
            }
            else if ($2->getName() == ">=") {
                code << "\tCMP BX, AX" << endl;
                code << "\tJLE " << label1 << endl;
                code << "\tPUSH 0" << endl;
                code << "\tJMP " << label2 << endl;
                code << "\t" << label1 << ": " << endl;
                code << "\tPUSH 1" << endl;
                code << "\t" << label2 << ":  \t\t ; " << $1->getName() << $2->getName() << $3->getName() << endl << endl;;
            }
            else if ($2->getName() == "==") {
                code << "\tCMP BX, AX" << endl;
                code << "\tJE " << label1 << endl;
                code << "\tPUSH 0" << endl;
                code << "\tJMP " << label2 << endl;
                code << "\t" << label1 << ": " << endl;
                code << "\tPUSH 1" << endl;
                code << "\t" << label2 << ":  \t\t ; " << $1->getName() << $2->getName() << $3->getName() << endl << endl;;
            } 
            else if ($2->getName() == "!=") {
                code << "\tCMP BX, AX" << endl;
                code << "\tJNE " << label1 << endl;
                code << "\tPUSH 0" << endl;
                code << "\tJMP " << label2 << endl;
                code << "\t" << label1 << ": " << endl;
                code << "\tPUSH 1" << endl;
                code << "\t" << label2 << ":  \t\t ; " << $1->getName() << $2->getName() << $3->getName() << endl << endl;;
            }
            $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), "int");
            log("rel_expression : simple_expresssion RELOP simple_expression" , $$->getName());
        }
        ;
simple_expression : term 
        {
            $$ = $1;
			log("simple_expression : term", $$->getName());
        }
        | simple_expression ADDOP term 
        {
            if ($1->getType() == "void" or $3->getType() == "void") {
                err("void function used in expression");
            }
            if ($1->getType() == "float" or $3->getType() == "float") {
                $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), "float");
            } else {
                $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), "int");
            }

            if ($2->getName() == "+") {
                code << "\tPOP AX" << endl << "\tPOP BX" << endl;
                code << "\tADD AX, BX" << endl;
                code << "\tPUSH AX" << endl;
            } 
            else {
                code << "\tPOP BX" << endl << "\tPOP AX" << endl;
                code << "\tSUB AX, BX" << endl;
                code << "\tPUSH AX" << endl;
            }


            log("simple_expression : simple_expression ADDOP term", $$->getName());
        }
        ;

term : unary_expression 
        {
            $$ = $1;
			log("term : unary_expression", $$->getName());
        }
        | term MULOP unary_expression
        {
            string retType = UNDECLARED;
            string ops = $2->getName();

            if ($1->getType() == "void" or $3->getType() == "void") {
                err("void function used in expression");
            }

            if (ops == "%") {
                retType = "int";
                if ($1->getType() != "int" or $3->getType() != "int") {
                    err("Non-integer operand on modulus operator");
                    retType = ERROR;
                }
                else if ($3->getName() == "0"){
                    err("Modulus by zero");
                    retType = ERROR;
                }
                code << "\tPOP BX" << endl << "\tPOP AX" << endl;
                code << "\tXOR DX, DX" << endl;
                code << "\tDIV BX" << endl;
                code << "\tPUSH DX" << endl;
            }
            else if (ops == "/") {
                if ($3->getName() == "0"){
                    err("Division by zero");
                    retType = ERROR;
                }
                else if ($1->getType() == "float" or $3->getType() == "float") retType = "float";
                else retType = "int";

                code << "\tPOP BX" << endl << "\tPOP AX" << endl;
                code << "\tXOR DX, DX" << endl;
                code << "\tDIV BX" << endl;
                code << "\tPUSH AX" << endl;
            }
            else if (ops == "*") {
                if ($1->getType() == "float" or $3->getType() == "float") retType = "float";
                else retType = "int";

                code << "\tPOP AX" << endl << "\tPOP BX" << endl;
                code << "\tMUL BX" << endl;
                code << "\tPUSH AX" << endl;
            }

            $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), retType);
			log("term : term MULOP unary_expression", $$->getName());
        }
        ;

unary_expression : ADDOP unary_expression
        {
            if ($1->getName() == "-") {
                code << "\tPOP AX" << endl;
                code << "\tNEG AX" << endl;
                code << "\tPUSH AX" << endl;
            }
            $$ = new SymbolInfo($1->getName() + $2->getName(), $2->getType());
			log("unary_expression : ADDOP unary_expression", $$->getName());
        }
        | NOT unary_expression
        {
            $$ = new SymbolInfo("!" + $2->getName(), $2->getType());
			log("unary_expression : NOT unary_expression", $$->getName());
            string label1 = newLabel(), label2 = newLabel();
            code << "\tPOP AX" << endl;
            code << "\tCMP AX, 0" << endl;
            code << "\tJE " << label1 << endl;
            code << "\tPUSH 0" << endl;
            code << "\tJMP " << label2 << endl;
            code << "\t" << label1 << ": " << endl;
            code << "\tPUSH 1" << endl;
            code << "\t" << label2 << ": " << endl;
        }
        | factor
        {

            $$ = $1;
            log("unary_expression : factor", $$->getName());
        }
        ;

factor : variable
        {
            // cout << $1->getName() << " " << $1->offset << endl;
            // cout <<$1->getName() << " "<<  $1->isGlobal << endl;
            if ($1->isGlobal) {
                code << "\tPUSH " << $1->getName() << endl;
            } else {
                code << "\tPUSH [BP - " << $1->offset << "] " << endl;
            }
            $$ = $1;
            log("factor : variable", $$->getName());
        }
        | ID LPAREN argument_list RPAREN
        {
            string retType = ERROR;
            SymbolInfo* func = st.lookUp($1->getName());

            if (func) {
                if (func->isFunction) {
                    retType = func->getType();
                    vector<string> argNames = tokenize($3->getName(), ',') , argTypes = tokenize($3->getType(), ',');
                    vector<Parameter> pList = func->paramList;
                    
                    code << "\tCALL " << func->getName() << endl;
                    if (retType != "void")  {
                        code << "\tPUSH DX" << endl;
                    }
                    
                    if (pList.size() != argNames.size()) {
                        err("Inconsistent number of arguments in function call " + func->getName());
                    }
                    else {
                        for (int i=0; i<argTypes.size(); i++) {
                            if (argTypes[i] != pList[i].type) {
                                err(to_string(i+1) + " th argument has inconsistent type in function '" + $1->getName() + "'\nType : " + argTypes[i] + " inplace of " + pList[i].type + " " + pList[i].name);
                            }
                        }
                    }

                } else {
                    err("Multiple declaration of '" + $1->getName() + "'");
                }
            } else {
                err("Undeclared function call '" + $1->getName() + "' ");
            }

            $$ = new SymbolInfo($1->getName() + "(" + $3->getName() + ")",	retType);
			log("factor : ID LPAREN argument_list RPAREN", $$->getName());
        }
        | LPAREN expression RPAREN
        {
            $$ = new SymbolInfo("(" + $2->getName() + ")",	$2->getType() );
			log("factor : LPAREN expression RPAREN", $$->getName());
        }
        |CONST_FLOAT
        {
            $$ = new SymbolInfo(yylval.syminfo->getName(), "float");
			log("factor : CONST_FLOAT", $$->getName());
        }
        | CONST_INT
        {
            code << "\tPUSH " << $1->getName() << endl;
            $$ = new SymbolInfo(yylval.syminfo->getName(), "int");
			log("factor : CONST_INT", $$->getName());
        }
        | variable INCOP
        {
            if ($1->getType() == "void") {
                err("Void function cannot be incremented");
            }
            $$ = new SymbolInfo($1->getName() + "++", $1->getType());
			log("factor : variable INCOP", $$->getName());

            code << "\tMOV AX, [BP - "<< $1->offset << "]" << endl;
            code << "\tPUSH AX" << endl;
            code << "\tINC AX" << endl;
            code << "\tMOV [BP - " << $1->offset << "], AX" << endl;
        }
        | variable DECOP
        {
            if ($1->getType() == "void") {
                err("Void function cannot be decremented");
            }
            $$ = new SymbolInfo($1->getName() + "--", $1->getType());
			log("factor : variable DECOP", $$->getName());
            code << "\tMOV AX, [BP - "<< $1->offset << "]" << endl;
            code << "\tPUSH AX" << endl;
            code << "\tDEC AX" << endl;
            code << "\tMOV [BP - " << $1->offset << "], AX" << endl;
        }
        ;

argument_list : arguments
        {
            $$ = $1;
            log("argument_list : arguments", $$->getName());
        }
        | 
        {
            $$ = new SymbolInfo("", "");
            log("argument_list : " , $$->getName());
        }
        ;

arguments : arguments COMMA logic_expression
        {
            // cout << "Adding " << $3->getType() << " " << $3->getName() << endl;
            $$ = new SymbolInfo($1->getName() + "," + $3->getName(), $1->getType() + "," + $3->getType());
            log("arguments : arguments COMMA logic_expression", $$->getName());
        }
        | logic_expression
        {
            $$ = $1;
            log("arguments : logic_expression", $$->getName());
        }
        ;


%%

int main( int argc, char** argv)
{
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
    FILE *fin = fopen(argv[1], "r");

	if(fin == nullptr) {
        cout << "File Not Found" << endl;
        return 0;
	}    

    yyin=fin;

    header << ".MODEL SMALL" << endl << endl;
    header << ".STACK 100H" << endl << endl;
    header << ".DATA \nprint_var DW ?" << endl << endl;
    code << ".CODE" << endl;

    add_print_proc();


	yyparse();

    st.printAllScopeTable();

    logfile << "Total Line Count : " << linenum << endl;
    logfile << "Total Error Count : " << errornum << endl;

    fclose(yyin);
    logfile.close();
    errfile.close();

    optimize_code();

    return 0;
}