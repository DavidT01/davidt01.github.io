%option noyywrap

%{
    #include <iostream>
    #include <vector>
    #include <cstdlib>
    #include <map>

    using namespace std;

    #include "stringovi.hpp"
    #include "parser.tab.hpp"
%}

%%

print                                           { return PRINT; }
lower                                           { return LOWER; }
upper                                           { return UPPER; }
reverse                                         { return REVERSE; }
index                                           { return INDEX; }
[a-zA-Z_][a-zA-Z0-9_]*                          { yylval.s = new string(yytext); return ID; }
\"[^\"]*\"                                      { yylval.str = new string(yytext); return STRING; }
[0-9]+                                          { yylval.v = atoi(yytext); return BROJ; }
":="                                            { return DODELA; }
[\n()|,+*:\[\]]                                 { return *yytext; }
[ \t]                                           { }
.                                               { cerr << "Leksicka greska: " << yytext << endl; exit(EXIT_FAILURE); }


%%