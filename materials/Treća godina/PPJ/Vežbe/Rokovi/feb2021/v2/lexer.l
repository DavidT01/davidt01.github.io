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

def                             { return DEF; }
print                           { return PRINT; }
sim                             { return SIM; }
reflX                           { return REFX; }
reflY                           { return REFY; }
rot                             { return ROT; }
angle                           { return ANGLE; }
list                            { return LIST; }
":="                            { return DODELA; }
[+-]?[0-9]+(\.[0-9]+)?          { yylval.d = atof(yytext); return BROJ; }
[A-Z]                           { yylval.s = new string(yytext); return LIST_ID; }
[a-zA-Z_][a-zA-Z0-9_]*          { yylval.s = new string(yytext); return ID; }

[()<>,\[\]|+*\n-]                     { return *yytext; }
[ \t]                           { }
.                               { cerr << "Leksicka greska: " << yytext << endl; exit(EXIT_FAILURE); }

%%