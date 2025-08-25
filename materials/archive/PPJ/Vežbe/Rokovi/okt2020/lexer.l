%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <map>
    #include <vector>

    using namespace std;

    #include "broj.hpp"
    #include "parser.tab.hpp"
%}

%%

print                                       { return PRINT; }
">>"                                        { return SHR; }
"<<"                                        { return SHL; }
"=="                                        { return EQ; }
"!="                                        { return NEQ; }
min                                         { return MIN; }
max                                         { return MAX; }
nzs                                         { return NZS; }
nzd                                         { return NZD; }
\"[^\"]*\"                                  { yylval.s = new string(yytext); return STRING; }
0x[0-9a-fA-F]*                              { yylval.v = strtol(yytext, NULL, 16); return BROJ; }
0[0-7]*                                     { yylval.v = strtol(yytext, NULL, 8); return BROJ; }
[1-9][0-9]*                                 { yylval.v = strtol(yytext, NULL, 10); return BROJ; }
[a-z][a-z0-9]*                              { yylval.s = new string(yytext); return ID; }
[A-Z][A-Z0-9]*                              { yylval.s = new string(yytext); return LIST_ID; }
[~^&|<>\[\]()=;,+*/%-]                        { return *yytext; }
[ \t\n]                                     {}
.                                           { cerr << "Lex greska: " << yytext << endl; exit(EXIT_FAILURE); }


%%