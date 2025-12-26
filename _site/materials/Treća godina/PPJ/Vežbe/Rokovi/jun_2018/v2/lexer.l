%option noyywrap

%{
    #include <iostream>
    #include <vector>
    #include <map>

    using namespace std;

    #include "matrice.hpp"
    #include "parser.tab.hpp"
%}

%%

disp                                        { return DISP; }
size                                        { return SIZE; }
".+"                                        { return PPLUS; }
".*"                                        { return PMUL; }
[0-9]+                                      { yylval.v = atoi(yytext); return BROJ; }
[a-zA-Z]                                    { yylval.s = new string(yytext); return ID; }
[\[\]()*\'=;,\n]                            { return *yytext; }
[ \t]                                       { }
.                                           { cerr << "Leksicka greska: " << yytext << endl; exit(EXIT_FAILURE); }

%%