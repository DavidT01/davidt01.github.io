%option noyywrap

%{
    #include <iostream>
    #include <vector>
    #include <cstdlib>
    #include <map>
    #include <cstdio>

    using namespace std;

    #include "parser.tab.hpp"
%}

%%

int                                             { return INT; }
print                                           { return PRINT; }
list                                            { return LIST; }
"<<"                                            { return SHL; }
">>"                                            { return SHR; }
"=="                                            { return EQ; }
0x[a-fA-F0-9]+                                  { yylval.v = strtol(yytext, NULL, 16); return BROJ; }
0[0-7]+                                         { yylval.v = strtol(yytext, NULL, 8); return BROJ; }
[0-9]+                                          { yylval.v = strtol(yytext, NULL, 10); return BROJ; }
_[a-zA-Z][a-zA-Z0-9_]*                          { yylval.s = new string(yytext); return ID; }
l[a-zA-Z0-9_]*                                  { yylval.s = new string(yytext); return ID_LIST; }
[=;,()+*/%~^|\[\]&_-]                           { return *yytext; }
[ \t\n]                                         { }
.                                               { cerr << "Leksicka greska: " << yytext << endl; exit(EXIT_FAILURE); }

%%