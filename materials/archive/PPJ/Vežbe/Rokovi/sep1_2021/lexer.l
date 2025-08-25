%option noyywrap

%{
    #include <iostream>
    #include <vector>
    #include <cstdlib>
    #include <map>

    using namespace std;

    #include "parser.tab.hpp"
%}

%%

reshape                                     { return RESHAPE; }
array                                       { return ARRAY; }
print                                       { return PRINT; }
count                                       { return COUNT; }
":="                                        { return DODELA; }
[a-z]                                       { yylval.s = new string(yytext); return ID; }
[+-]?[0-9]+(\.[0-9]*)?                      { yylval.v = atof(yytext); return BROJ; }
[\[\],.()+*;-]                              { return *yytext; }
[ \n\t]                                     { }
.                                           { cerr << "Leksicka greska: " << yytext << endl; exit(EXIT_FAILURE); }


%%