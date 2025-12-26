%option noyywrap

%{

#include "tokeni.h"

%}

%%

[A-Za-z][A-Za-z0-9]* {return ID;}
[+-]?[0-9]+(\.[0-9]*)? {return BROJ;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return PUTA;}
".*" {return SKMN;}
"=" {return DODELA;}
";" {return TZ;}
[\n] {return NR;}
"(" {return OZ;}
")" {return ZZ;}
"\[" {return OZS;}
"\]" {return ZZS;}
[ \t] {}
. {
    fprintf(stderr, "Leksicka greska: %s\n", yytext);
    exit(EXIT_FAILURE);
}

%%