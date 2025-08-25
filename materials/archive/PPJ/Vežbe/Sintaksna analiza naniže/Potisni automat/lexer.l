%option noyywrap

%{

	#include "tokeni.h"

%}

%%

[0-9]+ {return BROJ;}
"+" {return PLUS;}
"*" {return PUTA;}
"(" {return OZ;}
")" {return ZZ;}
[ \t\n] {}
.	{
		fprintf(stderr, "Leksicka greska: %s\n", yytext);
		exit(EXIT_FAILURE);
	}

%%