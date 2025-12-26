%option noyywrap

%{
    #include <iostream>
    #include <vector>
    #include <cstdlib>
    #include <map>

    using namespace std;

    #include "niska.hpp"
    #include "parser.tab.hpp"
%}

%%

print                                       { return PRINT; }
$[a-zA-Z]+                                  { yylval.s = new string(yytext); return ID; }
[0-9]+                                      { yylval.v = atoi(yytext); return BROJ; }
\"[^\"]*\"                                  { yylval.str = new string(yytext); return STRING; }                       
[\[\]$()\.x=*+,/;-]                         { return *yytext; }
[ \t\n]                                     { }
.                                           { cerr << "Leksicka greska: " << yytext << endl; exit(EXIT_FAILURE); }


%%