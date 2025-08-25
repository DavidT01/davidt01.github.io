%option noyywrap

%{

	#include "parser.tab.h"

%}

%%

print {return PRINT;}
[a-zA-z][A-Za-z0-9]* {
						yylval.ime = strdup(yytext);
						if(yylval.ime == NULL) {
							fprintf(stderr, "Alokacija nije moguca.\n");
							exit(EXIT_FAILURE);
						}
						return ID;
					 }
[0-9]+(\.[0-9]*)? {
					yylval.v = atof(yytext);
					return BROJ;
				  }
"==" {return EQ;}
"!=" {return NEQ;}
"<=" {return LTE;}
">=" {return GTE;}
[+/*()<>=;-] {return *yytext;}
[ \t\n] {}
. {
	fprintf(stderr, "Leksicka greska: %s\n", yytext);
	exit(EXIT_FAILURE);
}

%%
