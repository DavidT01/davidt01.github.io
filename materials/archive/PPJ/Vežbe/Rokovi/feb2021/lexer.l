%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <vector>
    
    using namespace std;

    #include "vektor.hpp"
    #include "parser.tab.hpp"
%}

%%

def                                 { return DEF_T; }
print                               { return PRINT_T; }
sim                                 { return SIM_T; }
reflX                               { return REFLX_T; }
reflY                               { return REFLY_T; }
rot                                 { return ROT_T; }
angle                               { return ANGLE_T; }
list                                { return LIST_T; }
":="                                { return DODELA; }
[a-zA-Z_][a-zA-Z0-9_]*              { 
                                        yylval.ime = new string(yytext);
                                        return ID;
                                    }
[+-]?[0-9]+(\.[0-9]+)?              { 
                                        yylval.v = strtod(yytext, NULL);
                                        return BROJ;
                                    }
[()<>|,+*\n-]                       { return *yytext; }
[ \t]                               { }
.                                   {
                                        cout << "Leksicka greska: " << yytext << endl;
                                        exit(EXIT_FAILURE);
                                    }

%%
