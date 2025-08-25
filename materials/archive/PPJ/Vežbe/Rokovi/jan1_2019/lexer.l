%option noyywrap

%{
    #include <iostream>
    #include <string>
    #include <cstdlib>

    using namespace std;

    #include "parser.tab.hpp"
%}

%%

int                                 { return INT_T; }
print                               { return PRINT_T; }
list                                { return LIST_T; }
0x[0-9a-fA-F]+                      { 
                                        yylval.v = strtol(yytext, NULL, 16);
                                        return BROJ;
                                    }
0[0-7]+                             { 
                                        yylval.v = strtol(yytext, NULL, 8);
                                        return BROJ;
                                    }
[0-9]+                              { 
                                        yylval.v = strtol(yytext, NULL, 10);
                                        return BROJ;
                                    }
_[a-z][a-z0-9]*                     {   
                                        yylval.ime = new string(yytext);
                                        return ID;
                                    }
[a-z]+                              {
                                        yylval.ime = new string(yytext);
                                        return ID_L;
                                    }
[()*/+^&|;,=~%\[\]-]                { return *yytext; }
"=="                                { return EQ; }
"<<"                                { return SHL; }
">>"                                { return SHR; }
[ \n\t]                             { }
.                                   {
                                        cout << "Leksicka greska: " << yytext << endl;
                                        exit(EXIT_FAILURE);
                                    }

                                

%%