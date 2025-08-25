%option noyywrap

%{
    #include <iostream>
    #include <vector>
    #include <cstdlib>
    #include <map>

    using namespace std;
    
    #include "vektor.hpp"
    #include "parser.tab.hpp"
%}

%%

print                                           { return PRINT; }
ugao                                            { return UGAO; }
eqv                                             { return EQV; }
":="                                            { return DODELA; }
[a-z]                                           { yylval.s = new string(yytext); return ID; }
[0-9]+(\.[0-9]+)?                               { yylval.d = strtod(yytext, NULL); return BROJ; }
[<>;,()|*.+-]                                   { return *yytext; }
[ \t\n]                                         { }
.                                               { cerr << "Leksicka greska: " << yytext << endl; exit(EXIT_FAILURE); }

%%