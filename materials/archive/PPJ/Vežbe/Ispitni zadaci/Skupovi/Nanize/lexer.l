%option noyywrap

%{

#include <stdio.h>
#include <stdlib.h>

#include "tokeni.h"

%}

%%

print {return PRINT;}
[A-Z]+ {return ID;}
[+-]?[0-9]+ {return BROJ;}
".." {return TT;}
"," {return ZAREZ;}
";"  {return TZ;}
"=" {return DODELA;}
"{" {return OZ;}
"}" {return ZZ;}
[ \t\n] {}
. {
    fprintf(stderr, "Leksicka greska: %s\n", yytext);
    exit(EXIT_FAILURE);
}

%%