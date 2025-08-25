%option noyywrap

%{

#include "tokeni.h"

%}

%%

[a-zA-z][a-zA-Z0-9]* {return ID;}
[+-]?[0-9]+(\.[0-9]*)? {return BROJ;}
":=" {return DODELA;}
"," {return ZAREZ;}
"<" {return OZ;}
">" {return OZ;}
\n {return NOVIRED;}
[ \t] {}
. {fprintf(stderr, "Leksicka greska"); exit(EXIT_FAILURE);}

%%