%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <vector>
    #include <map>

    using namespace std;

    #include "vektor.hpp"
    #include "parser.tab.hpp"
%}

%%

print                               { return PRINT_T; }
ugao                                { return UGAO_T; }
eqv                                 { return EQV_T; }
[a-z]                               { yylval.s = new string(yytext); return ID; }
[<>,;()|\.+*-]                      { return *yytext; }
[0-9]+(\.[0-9]+)?              { yylval.v = strtod(yytext, NULL); return BROJ; }
":="                                { return DODELA; }
[ \n\t]                             { }
.                                   { cerr << "Leksicka greska: " << yytext << endl; exit(EXIT_FAILURE); }

%%