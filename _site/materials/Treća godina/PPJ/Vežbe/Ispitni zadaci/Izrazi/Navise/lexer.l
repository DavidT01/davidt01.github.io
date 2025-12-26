%option noyywrap

%{

	#include <iosteam>
	#include <cstdlib>

	using namespace std;

	#include "broj.hpp"
	#include "parser.tab.hpp"

%}

%%

list {return LIST_T;}
int {return INT_T;}
print {return PRINT_T;}
_[a-zA-z][a-zA-Z0-9]* {
						yylval.ime = new string(yytext);
						return ID;}
0x[0-9a-fA-F]+ {
						yylval.v = strtol(yytext, NULL, 16);
						return BROJ;}
[1-9][0-9]* {
						yylval.v = strtol(yytext, NULL, 10);
						return BROJ;}
0[0-7]* {
						yylval.v = strtol(yytext, NULL, 8);
						return BROJ;]
"<<" {return SL_T;}
">>" {return SR_T;}
"==" {return EQ_T;}
"!=" {return NEQ_T;}
[+*/%,=()\[\]\n&^|~-] {return *yytext;}
[ \t] {}
. {
	cerr << "Leksicka greska: " << yytext << endl;
	exit(EXIT_FAILURE);
}

%%
