%option noyywrap

%{

#include <iostream>
#include <cstdlib>

using namespace std;

#include "matrix.hpp"
#include "parser.tab.hpp"

%}

%%

[A-Za-z][A-Za-z0-9]* {
                            yylval.ime = new string(yytext);
                            return ID;}
[+-]?[0-9]+(\.[0-9]*)? {
                            yylval.x = atof(yytext);
                            return BROJ;}
".*" {return SKMN;}
[()=+*\n;\[\]'-] {return *yytext;}
[ \t] {}
. {
    cerr << "Leksicka greska: " << yytext << endl;
    exit(EXIT_FAILURE);
}

%%