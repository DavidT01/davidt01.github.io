%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>

    using namespace std;

    #include "razlomak.hpp"
    #include "parser.tab.hpp"

%}

%%

print                           { return PRINT_T; }
nom                             { return NOM_T; }
den                             { return DEN_T; }
double                          { return DOUBLE_T; }
equals                          { return EQUALS_T; }
[a-zA-Z][a-zA-Z0-9]*            { 
                                    yylval.ime = new string(yytext);
                                    return ID;
                                }
[+-]?[0-9]+                     { 
                                    yylval.v = atoi(yytext);
                                    return BROJ;    
                                }
[()\[\],=*+/\n-]                { return *yytext; }
[ \t]                           { }
.                               {
                                    cout << "Leksicka greska: " << yytext << endl;
                                    exit(EXIT_FAILURE);
                                }


%%

