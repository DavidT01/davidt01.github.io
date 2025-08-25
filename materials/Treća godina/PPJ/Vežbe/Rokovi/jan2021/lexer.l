%option noyywrap

%{
    #include <iostream>
    #include <vector>
    #include <cstdlib>
    #include <map>
    #include <tuple>

    using namespace std;

    #include "ugao.hpp"
    #include "parser.tab.hpp"
%}

%%

kom                                 { return KOM; }
sup                                 { return SUP; }
print                               { return PRINT; }
[a-z][a-z0-9]*                      { yylval.s = new string(yytext); return ID; }
[A-Z]*                              { yylval.s = new string(yytext); return LIST_ID;}
[0-9]+                              { yylval.v = atoi(yytext); return BROJ; }
[+*\[\](),;<>=-]                    { return *yytext; }
[ \t\n]                             { }
.                                   { cerr << "Leksicka greska: " << yytext << endl; exit(EXIT_FAILURE); }

%%

