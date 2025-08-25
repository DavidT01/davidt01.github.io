%option noyywrap

%{

	#include <iostream>
	#include <cstdlib>
	
	using namespace std;
	
	#include "polinom.hpp"
	#include "parser.tab.hpp"

%}

%%

[a-zA-Z][a-zA-Z0-9]* {
						yylval.ime = new string(yytext);
						return ID;}
[+-]?[0-9]+(\.[0-9]*)? {
							yylval.v = atof(yytext);
							return BROJ;}
"==" {return EQ;}
"!=" {return NEQ;}
":=" {return DODELA;}
[+*,<>()'\$\[\]|n-] {return *yytext;}
[ \t] {}
. {
	cerr << "Leksicka greska: " << yytext << endl;
	exit(EXIT_FAILURE);
}

%%