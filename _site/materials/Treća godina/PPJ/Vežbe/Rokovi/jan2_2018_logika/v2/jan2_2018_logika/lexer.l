%option noyywrap

%{
    #include <iostream>
    #include <vector>
    #include <cstdlib>
    #include <map>

    using namespace std;

    #include "logika.hpp"
    #include "parser.tab.hpp"
%}

%%

head                                { return HEAD; }
tail                                { return TAIL; }
True                                { return TRUE; }
False                               { return FALSE; }
Undef                               { return UNDEF; }
":="                                { return DODELA; }
"<=>"                               { return EQ; }
"=>"                                { return IMPL; }
"\\/"                               { return DISJ; }
"/\\"                               { return CONJ; }
[a-z][0-9]*                         { yylval.s = new string(yytext); return ID; }
[A-Z][0-9]*                         { yylval.s = new string(yytext); return LIST_ID; }
[0-9]+                              { yylval.val = atoi(yytext); return BROJ; }
[(),!\[\]\n]                        { return *yytext; }
[ \t]                               { }
.                                   { cerr << "Leksicka greska: " << yytext << endl; exit(EXIT_FAILURE); }


%%