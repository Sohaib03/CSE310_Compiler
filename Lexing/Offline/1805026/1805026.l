%option c++
%option noyywrap

%x STRING_INPUT
%x SINGLE_COMMENT
%x MULTI_COMMENT
%x CHAR_START

%{
    #include <iostream>
    #include <fstream>
    #include "SymbolTable.cpp"

    const int HASH_TABLE_SIZE = 7;

    using namespace std;

    string cur_str, text;


    ofstream logfile("1805026_log.txt");
    ofstream tfile("1805026_token.txt");
    SymbolTable st(HASH_TABLE_SIZE, &logfile);
    int linenum = 1, temp_line = 0;
    int errornum = 0;

    string toUpper(string text) {
        string nw;
        for (char c: text) nw.push_back(toupper(c));
        return nw;
    }

    string format(string str) {
        string formattedStr;
        for (int i=0; i<str.size(); i++) {
            if (str[i] == '\\' and i+1 < str.size()) {
                if (str[i+1] == '\n' ) { i++; }
                else if (str[i+1] == 'n') {formattedStr.push_back('\n'); i++;}
                else if (str[i+1] == 'r') {formattedStr.push_back('\r'); i++;}
                else if (str[i+1] == 't') {formattedStr.push_back('\t'); i++;}
                else if (str[i+1] == 'v') {formattedStr.push_back('\v'); i++;}
                else if (str[i+1] == 'a') {formattedStr.push_back('\a'); i++;}
                else if (str[i+1] == 'b') {formattedStr.push_back('\b'); i++;}
                else if (str[i+1] == 'f') {formattedStr.push_back('\f'); i++;}
                else if (str[i+1] == '0') {formattedStr.push_back('\0'); i++;}
                else if (str[i+1] == '\"') {formattedStr.push_back('"'); i++;}
                else formattedStr.push_back(str[i]);
            }
            else formattedStr.push_back(str[i]);
        }
        return formattedStr;
    }

%}

NEWLINE [\r]?\n
WHITESPACE [ \t\f\r\v]+
CHAR [ -~]{-}[']
CHARS {CHAR}+
SPECIAL_CHAR '(\\[nt\\afrbv0\"])'
LETTER [a-zA-Z_]
DIGIT [0-9]
WRONGDIGIT {DIGIT}*(\.{DIGIT}+)\.[0-9\.Ee+-]*(\.)* 
INVALIDNUM ([0-9]*(\.[0-9]*)?[Ee][+-]?[0-9]*[0-9\.Ee+-]*(\.)*)|([0-9]+\.)
INVALID_ID ({DIGIT}+{LETTER}+)
ALNUM ({LETTER}|{DIGIT})
INT_NUM {DIGIT}+
FLOAT_NUM {DIGIT}+(\.{DIGIT}+)?([Ee][+-]?{DIGIT}+)?
CHAR_TYPE ('({CHAR})'|{SPECIAL_CHAR})
NON_CHAR '{CHAR}{CHAR}+'
NLT ('\\n'|'\\t')

%%

{WHITESPACE}            { }
{NEWLINE}               { linenum++; }

"if"|"else"|"for"|"while"|"do"|"break"|"int"|"char"|"float"|"double"|"void"|"return"|"switch"|"case"|"defaut"|"continue" {
        string capToken = toUpper(yytext);
        tfile << "<" << capToken << "> ";
        logfile << "Line no "<< linenum <<": Token <"<< capToken <<"> Lexeme " << yytext << " found" << endl << endl;
    }

{INT_NUM}               {
        tfile << "<CONST_INT, " << yytext << "> ";
        logfile << "Line no " << linenum << ": Token <CONST_INT> Lexeme " << yytext << " found" << endl << endl;

        if (st.insert(yytext, "CONST_INT")) {
            st.printAllScopeTable();
        }
    }

{FLOAT_NUM}             {
        tfile << "<CONST_FLOAT, " << yytext << "> ";
        logfile << "Line no " << linenum << ": Token <CONST_FLOAT> Lexeme " << yytext << " found" << endl<< endl;
        if (st.insert(yytext, "CONST_FLOAT")) {
            st.printAllScopeTable();
        }
    }

{WRONGDIGIT}            {
        errornum++;
        logfile << "Line no " << linenum << ": Error : Multiple Decimal Points" << endl<< endl;
    }

{INVALIDNUM}            {
        errornum++;
        logfile << "Line no " << linenum << ": Error : INVALID NUMBER" << endl<< endl;
    }
{INVALID_ID}            {
        errornum++;
        logfile << "Line no " << linenum << ": Error : INVALID ID" << endl<< endl;
    }

\'      {
    text = "";
    BEGIN CHAR_START;
}

<CHAR_START>\\n         text += "\n";
<CHAR_START>\\t         text += "\t";
<CHAR_START>\\\\        text += "\\";
<CHAR_START>\\\'        text += "\'";
<CHAR_START>\\\"        text += "\"";
<CHAR_START>\\a         text += "\a";
<CHAR_START>\\f         text += "\f";
<CHAR_START>\\r         text += "\r";
<CHAR_START>\\v         text += "\v";
<CHAR_START>\\0         text += "\0";

<CHAR_START>\'          {
        string s = format(text);
        if (s.empty()) {
            errornum++;
            logfile << "Line no " << linenum << ": Error Empty Char" << endl<< endl;
        } else if (s.size() > 1) {
            errornum++;
            logfile << "Line no " << linenum << ": Error Multiple Char" << endl<< endl;
        } else {
            tfile<<"<CHAR_CONST, "<< s <<"> ";
			logfile<<"Line no "<< linenum <<": Token " <<"<CONST_CHAR>"<<" Lexeme "<<s<<" found --> <CHAR_CONST,"<<s<<">\n"<<endl;

			if(st.insert(s ,"CONST_CHAR"))
			{
                st.printAllScopeTable();
			}
        }
        BEGIN(INITIAL);
    }
<CHAR_START>{NEWLINE} {
        errornum++;
        logfile << "Line no " << linenum << ": Error Unterminated Char" << endl<< endl;
        BEGIN(INITIAL);
    }
<CHAR_START><<EOF>> {
        errornum++;
        logfile << "Line no " << linenum << ": Error Unterminated Char" << endl<< endl;
        BEGIN(INITIAL);
    }

<CHAR_START>. {
    text += yytext;
}



{LETTER}{ALNUM}*	{
        tfile << "<ID, " << yytext << "> ";
        logfile << "Line no " << linenum << ": Token <ID> Lexeme " << yytext << " found" << endl<< endl;

        if (st.insert(yytext, "ID")) {
            st.printAllScopeTable();
        }
    }

"+"|"-" {
        tfile << "<ADDOP, " << yytext << "> " ;
        logfile << "Line no " << linenum << ": Token <ADDOP> Lexeme " << yytext << " found" << endl<< endl;
    }

"*"|"/"|"%" {
        tfile << "<MULOP, " << yytext << "> " ;
        logfile << "Line no " << linenum << ": Token <MULOP> Lexeme " << yytext << " found" << endl<< endl;
    }

"++"|"--" {
        tfile << "<INCOP, " << yytext << "> " ;
        logfile << "Line no " << linenum << ": Token <INCOP> Lexeme " << yytext << " found" << endl<< endl;
    }

"<"|"<="|">"|">="|"=="|"!=" {
        tfile << "<RELOP, " << yytext << "> " ;
        logfile << "Line no " << linenum << ": Token <INCOP> Lexeme " << yytext << " found" << endl<< endl;
    }

"=" {
        tfile << "<ASSIGNOP, => " ;
        logfile << "Line no " << linenum << ": Token <ASSIGNOP> Lexeme " << yytext << " found" << endl<< endl;
    }

"&&"|"||" {
        tfile << "<LOGICOP, " << yytext << "> " ;
        logfile << "Line no " << linenum << ": Token <LOGICOP> Lexeme " << yytext << " found" << endl<< endl;
    }

"!" {
        tfile << "<NOT, !> " ;
        logfile << "Line no " << linenum << ": Token <NOT> Lexeme " << yytext << " found" << endl<< endl;
    }

"(" {
        tfile << "<LPAREN, (> " ;
        logfile << "Line no " << linenum << ": Token <LPAREN> Lexeme " << yytext << " found" << endl<< endl;
    }

")" {
        tfile << "<RPAREN, )> " ;
        logfile << "Line no " << linenum << ": Token <RPAREN> Lexeme " << yytext << " found" << endl<< endl;
    }

"{" {
        tfile << "<LCURL, {> " ;
        logfile << "Line no " << linenum << ": Token <LCURL> Lexeme " << yytext << " found" << endl<< endl;
        st.enterScope();
    }

"}" {
        tfile << "<RCURL, }> " ;
        logfile << "Line no " << linenum << ": Token <RCURL> Lexeme " << yytext << " found" << endl<< endl;
        st.exitScope();
    }

"[" {
        tfile << "<LTHIRD, [> " ;
        logfile << "Line no " << linenum << ": Token <LTHIRD> Lexeme " << yytext << " found" << endl<< endl;
    }

"]" {
        tfile << "<RTHIRD, ]> " ;
        logfile << "Line no " << linenum << ": Token <RTHIRD> Lexeme " << yytext << " found" << endl<< endl;
    }

"," {
        tfile << "<COMMA, ,> " ;
        logfile << "Line no " << linenum << ": Token <COMMA> Lexeme " << yytext << " found" << endl<< endl;
    }

";" {
        tfile << "<SEMICOLON, ;> " ;
        logfile << "Line no " << linenum << ": Token <SEMICOLON> Lexeme " << yytext << " found" << endl<< endl;
    }

\/\/    {
    text = "//";
    temp_line = 0;

    BEGIN SINGLE_COMMENT;
}

<SINGLE_COMMENT>\\\r\n      {
        temp_line++;
        text += "\\\r\n";
    }

<SINGLE_COMMENT>\\\n        {
        temp_line++;
        text += "\\\n";
    }

<SINGLE_COMMENT>{NEWLINE}   {
        temp_line++;
        linenum += temp_line;
        logfile << "Line no " << linenum - 1 << ": Token <COMMENT> Lexeme " << text << " found" << endl<< endl;
        BEGIN(INITIAL);
    }
<SINGLE_COMMENT>. {
        text += yytext;
    }

\/\*    {
    text = "/*";
    temp_line = 0;
    BEGIN MULTI_COMMENT;
}

<MULTI_COMMENT>{NEWLINE}    {
        temp_line++;
        text += yytext;
    }
<MULTI_COMMENT><<EOF>> {
    errornum++;
    logfile << "Line no " << linenum << ": Error Unterminated Comment" << endl<< endl;
    linenum += temp_line;
    BEGIN(INITIAL);
}
<MULTI_COMMENT>\*\/     {
        linenum += temp_line;
        text += "*/";
        logfile << "Line no " << linenum << ": Token <COMMENT> Lexeme " << text << " found" << endl<< endl;
        BEGIN(INITIAL);
    }

<MULTI_COMMENT>.            {
        text += yytext;
    }

\" {
    text = "";
    temp_line = 0;
    BEGIN STRING_INPUT;
}

<STRING_INPUT>\\\\ { text += "\\\\";}
<STRING_INPUT>{NEWLINE} {
        temp_line++;
        linenum += temp_line;
        errornum++;
        logfile << "Line no " << linenum << ": Error Unterminated String" << endl<< endl;
        BEGIN(INITIAL);
    }
<STRING_INPUT>\\\n { text += "\\\n"; temp_line++;}
<STRING_INPUT><<EOF>>   {
        linenum += temp_line;
        errornum++;
        logfile << "Line no " << linenum << ": Error Unterminated String" << endl<< endl;
        BEGIN(INITIAL);
    }
<STRING_INPUT>\\\"      {
        text += "\\\"";
    }

<STRING_INPUT>\\[nrtvabf0]     {
        text += yytext;
}

<STRING_INPUT>\"          {
        string str = "\"" + text + "\"" ;
        tfile << "<STRING, \"" << format(text) << "\"> ";
        logfile << "Line no " << linenum << ": Token <STRING> Lexeme " << str << " found --> <STRING, \"" << format(text) << "\">" << endl<< endl;
        linenum += temp_line;
        BEGIN(INITIAL);
    }

<STRING_INPUT>.     {
        text.push_back(yytext[0]);
    }

. {
    errornum++;
    logfile << "Line no " << linenum << ": Error Unrecognized character" << endl<< endl;
}
%%

int main( int argc, char** argv)
{
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
    
    ifstream fin(argv[1]);

    if (fin.is_open() == false) {
        cout << "File Not Found" << endl;
        return 0;
    }
    FlexLexer* lexer = new yyFlexLexer(&fin);
    while(lexer->yylex() != 0)
        ;

    st.printAllScopeTable();

    logfile << "Total Line Count : " << linenum << endl;
    logfile << "Total Error Count : " << errornum << endl;

    fin.close();
    tfile.close();
    logfile.close();

    return 0;
}