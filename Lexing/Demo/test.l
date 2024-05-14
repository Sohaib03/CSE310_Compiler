%option noyywrap c++

%{
    #include <iostream>
    #include <fstream>
    using namespace std;

    ofstream tfile("1805026_token.txt");
    ofstream lfile("1805026_log.txt");
%}

AlphaNumeric [a-zA-Z0-9]

%%
[ \t\n]+ {}
[A-Z]{3}			{ tfile << "A-Z in 3" << endl; }
. 					{ tfile << "Mysterious character %s found\n" << endl; }
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

    fin.close();
    tfile.close();
    lfile.close();

    return 0;
}