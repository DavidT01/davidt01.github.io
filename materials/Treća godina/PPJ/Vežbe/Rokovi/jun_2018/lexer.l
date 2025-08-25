%option noyywrap

%{
    #include <iostream>
    #include <vector>
    #include <map>
    #include <cstdlib>
    #include <string>

    using namespace std;

    #include "matrice.hpp"
    #include "parser.tab.hpp"
%}

%%

disp                                    { return DISP; }
size                                    { return SIZE; }
".*"                                    { return MUL; }
".+"                                    { return PLUS; }
[a-zA-Z]                                { yylval.s = new string(yytext); return ID; }
[0-9]+                                  { yylval.v = atoi(yytext); return BROJ; }
[\[\](),*\';=\n]                        { return *yytext; }
[ \t]                                   { }
.                                       { cerr << "Leksicka greska: " << yytext << endl; exit(EXIT_FAILURE); }

%%