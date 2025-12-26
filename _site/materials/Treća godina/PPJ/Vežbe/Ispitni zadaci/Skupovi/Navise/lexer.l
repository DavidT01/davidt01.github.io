%option noyywrap

%{

#include <iostream>
#include <cstdlib>

using namespace std;

#include "skup.hpp"
#include "parser.tab.hpp"

%}

%%

"UniversalSet" {return USET_T;}
card {return CARD_T;}
check {return CHECK_T;}
print {return PRINT_T;}
[A-Z]+ {
                yylval.ime = new string(yytext);
                return ID;}
[+-]?[0-9]+ {   
                yylval.x = atoi(yytext);
                return BROJ;}
".." {return TT;}
"/\\" {return PRES;}
"\\/" {return UNI;}
"\\" {return RAZ;}
[();,~={}:<] {return *yytext;}
[ \t\n] {}
. {
    cerr << "Leksicka greska: " << yytext << endl;
    exit(EXIT_FAILURE);
}

%%