%option noyywrap

%x STRING_INPUT
%x SINGLE_COMMENT
%x MULTI_COMMENT
%x CHAR_START

%{
    #include <iostream>
    #include <fstream>
    #include "SymbolTable.cpp"
    #include "y.tab.h"

    const int HASH_TABLE_SIZE = 7;

    using namespace std;

    string cur_str, text;

    int linenum = 1, temp_line = 0;
    int errornum = 0;

    extern SymbolTable st;
    extern YYSTYPE yylval;
    extern ofstream logfile;
    extern ofstream errfile;
    

    void yyerror(char *);


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

    void error_unrecognized(string s)
    {
        logfile<<"Error at line "<<linenum<<": "<<"Unrecognized character "<<s<<"\n"<<endl;
        errfile<<"Error at line "<<linenum<<": "<<"Unrecognized character "<<s<<"\n"<<endl;
        errornum++;
    }

    void error_decimal_point(string s)
    {
        logfile<<"Error at line "<<linenum<<": "<<"Too many decimal points "<<s<<"\n"<<endl;
        errfile<<"Error at line "<<linenum<<": "<<"Too many decimal points "<<s<<"\n"<<endl;
        errornum++;
    }

    void error_ill_formed(string s)
    {
        logfile<<"Error at line "<<linenum<<": "<<"Ill formed number "<<s<<"\n"<<endl;
        errfile<<"Error at line "<<linenum<<": "<<"Ill formed number "<<s<<"\n"<<endl;
        errornum++;
    }

    void error_id(string s)
    {
        logfile<<"Error at line "<<linenum<<": "<<"Invalid prefix on ID or invalid suffix on Number "<<s<<"\n"<<endl;
        errfile<<"Error at line "<<linenum<<": "<<"Invalid prefix on ID or invalid suffix on Number "<<s<<"\n"<<endl;
        errornum++;
    }

%}

NEWLINE [\r]?\n
WHITESPACE [ \t\f\r\v]+

BREAK "break"
CASE "case"
CONTINUE "continue"
DEFAULT "default"
RETURN "return"
SWITCH "switch"

DO "do"
WHILE "while"
FOR "for"

IF "if"
ELSE "else"

VOID "void"
CHART "char"
DOUBLE "double"
FLOAT "float"
INT "int"

PRINTLN "printf"


CHAR [ -~]{-}[']
CHARS {CHAR}+
SPECIAL_CHAR '(\\[nt\\afrbv0\"])'
LETTER [a-zA-Z_]
DIGIT [0-9]
WRONGDIGIT {DIGIT}*(\.{DIGIT}+)\.[0-9\.Ee+-]*(\.)* 
INVALIDNUM ([0-9]+(\.[0-9]*)?[Ee][+-]?[0-9]*[0-9\.Ee+-]*(\.)*)|([0-9]+\.)
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

{IF}        { return IF; }
{ELSE}      { return ELSE; }

{VOID}      { return VOID; }
{CHART}     { return CHAR; }
{DOUBLE}    { return DOUBLE; }
{FLOAT}     { return FLOAT; }
{INT}       { return INT; }


{DO}        { return DO; }
{WHILE}     { return WHILE; }
{FOR}       { return FOR; }


{BREAK}     { return BREAK; }
{CASE}      { return CASE; }
{CONTINUE}  { return CONTINUE; }
{DEFAULT}   { return DEFAULT; }
{RETURN}    { return RETURN; }
{SWITCH}    { return SWITCH; }

{PRINTLN}   { return PRINTLN; }

{INT_NUM}               {
        SymbolInfo *s = new SymbolInfo(yytext, "CONST_INT");
        yylval.syminfo = s;
        return CONST_INT;
    }

{FLOAT_NUM}             {
        SymbolInfo *s = new SymbolInfo(yytext, "CONST_FLOAT");
        yylval.syminfo = s;
        return CONST_FLOAT;
    }

{WRONGDIGIT}            {
        error_decimal_point(yytext);

        SymbolInfo *s = new SymbolInfo(yytext, "ERROR_FLOAT");
        yylval.syminfo = s;
        return ERROR_FLOAT;
    }

{INVALIDNUM}            {

        error_ill_formed(yytext);

        SymbolInfo *s = new SymbolInfo(yytext, "ERROR_FLOAT");
        yylval.syminfo = s;
        return ERROR_FLOAT;
    }

{LETTER}{ALNUM}*	{

        SymbolInfo *s = new SymbolInfo(yytext, "ID");
        yylval.syminfo = s;
        return ID;
    }

{INVALID_ID}            {
        error_id(yytext);

	    SymbolInfo *s= new  SymbolInfo(yytext, "ERROR_ID");
	    yylval.syminfo = s;
	    return ERROR_ID;
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
            logfile<<"Error at line "<<linenum<<": "<<"Invalid character "<<s<<"\n"<<endl;
            errfile<<"Error at line "<<linenum<<": "<<"Invalid character"<<s<<"\n"<<endl;
        } else if (s.size() > 1) {
            errornum++;
            logfile<<"Error at line "<<linenum<<": "<<"Invalid character "<<s<<"\n"<<endl;
            errfile<<"Error at line "<<linenum<<": "<<"Invalid character"<<s<<"\n"<<endl;
        } else {
	        SymbolInfo *s= new  SymbolInfo(yytext, "CONST_CHAR");
	        yylval.syminfo = s;
	        return CONST_CHAR;
        }
        BEGIN(INITIAL);
    }
<CHAR_START>{NEWLINE} {
        linenum++;
        errornum++;
        logfile << "Line no " << linenum << ": Error Unterminated Char" << endl<< endl;
        errfile<<"Error at line "<<linenum<<": "<<"Error Unterminated Char"<<"\n"<<endl;
        BEGIN(INITIAL);
    }
<CHAR_START><<EOF>> {
        errornum++;
        logfile << "Line no " << linenum << ": Error Unterminated Char" << endl<< endl;
        errfile<<"Error at line "<<linenum<<": "<<"Error Unterminated Char"<<"\n"<<endl;
        BEGIN(INITIAL);
    }

<CHAR_START>. {
    text += yytext;
}



"+"|"-" {
        SymbolInfo *s = new SymbolInfo(yytext, "ADDOP");
        yylval.syminfo = s;
        return ADDOP;
    }

"*"|"/"|"%" {
        SymbolInfo *s = new SymbolInfo(yytext, "MULOP");
        yylval.syminfo = s;
        return MULOP;
    }

"++" {
        SymbolInfo *s = new SymbolInfo(yytext, "INCOP");
        yylval.syminfo = s;
        return INCOP;
    }

"--" {
        SymbolInfo *s = new SymbolInfo(yytext, "DECOP");
        yylval.syminfo = s;
        return DECOP;
    }

"<"|"<="|">"|">="|"=="|"!=" {
        SymbolInfo *s = new SymbolInfo(yytext, "RELOP");
        yylval.syminfo = s;
        return RELOP;
    }

"=" {
        SymbolInfo *s = new SymbolInfo(yytext, "ASSIGNOP");
        yylval.syminfo = s;
        return ASSIGNOP;
    }

"&&"|"||" {
        SymbolInfo *s = new SymbolInfo(yytext, "LOGICOP");
        yylval.syminfo = s;
        return LOGICOP;
    }

"!" {
        return NOT;
    }

"(" {
        return LPAREN;
    }

")" {
        return RPAREN;
    }

"{" {
        return LCURL;
    }

"}" {
        return RCURL;
    }

"[" {
        return LTHIRD;
    }

"]" {
        return RTHIRD;
    }

"," {
        return COMMA;
    }

";" {
        return SEMICOLON;
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
    linenum += temp_line;
    BEGIN(INITIAL);
}
<MULTI_COMMENT>\*\/     {
        linenum += temp_line;
        text += "*/";
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
        BEGIN(INITIAL);
    }
<STRING_INPUT>\\\n { text += "\\\n"; temp_line++;}
<STRING_INPUT><<EOF>>   {
        linenum += temp_line;
        errornum++;
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
        // tfile << "<STRING, \"" << format(text) << "\"> ";
        // logfile << "Line no " << linenum << ": Token <STRING> Lexeme " << str << " found --> <STRING, \"" << format(text) << "\">" << endl<< endl;
        linenum += temp_line;
        BEGIN(INITIAL);
    }

<STRING_INPUT>.     {
        text.push_back(yytext[0]);
    }

. {
    return UNRECOGNIZED;
}
%%
