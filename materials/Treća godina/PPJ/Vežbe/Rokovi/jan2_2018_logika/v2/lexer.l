%option noyywrap

%{
    #include <iostream>
    #include <vector>
    #include <map>
    #include <vector>

    #define FALSE (0)
    #define TRUE (1)
    #define UNDEF (2)

    using namespace std;

    #include "parser.tab.hpp"
%}

%%

head                                        { return HEAD; }
tail                                        { return TAIL; }
True                                        { yylval.v = TRUE; return CONST; }
False                                       { yylval.v = FALSE; return CONST; }
Undef                                       { yylval.v = UNDEF; return CONST; }
":="                                        { return DODELA; }
"\\/"                                       { return DISJ; }
"/\\"                                       { return CONJ; }
"=>"                                        { return IMPL; }
"<=>"                                       { return EKV; }
[a-z]+[0-9]*                                { yylval.s = new string(yytext); return ID; }
[A-Z]+                                      { yylval.s = new string(yytext); return LIST_ID; }
[0-9]+                                      { yylval.v = atoi(yytext); return BROJ; }
[()\[\],!\n]                                { return *yytext; }
[ \t]                                       { }
.                                           { cerr << "Leksicka greska: " << yytext << endl; exit(EXIT_FAILURE); }

%%