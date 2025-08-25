%option noyywrap

%{
    #include <iostream>
    #include <map>
    #include <cstdlib>

    using namespace std;

    #include "razlomak.hpp"
    #include "parser.tab.hpp"
%}

%%

print                                   { return PRINT; }
nom                                     { return NOM; }
den                                     { return DEN; }
double                                  { return DOUBLE; }
equals                                  { return EQUALS; }
[+-]?[0-9]+                             { yylval.v = atoi(yytext); return BROJ; }
[a-z]                                   { yylval.s = new string(yytext); return ID; }
[\[\]()+*=/,\n-]                        { return *yytext; }
[ \t]                                   { }
.                                       { cerr << "Leksicka greska: " << yytext << endl; exit(EXIT_FAILURE); }

%%