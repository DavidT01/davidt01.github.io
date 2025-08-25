%option noyywrap

%{

	#include "parser.tab.h"

%}

%%

[0-9]+ {
			// Prosledimo vrednost parseru, yylval je unija iz parsera
			yylval.v = atoi(yytext);
			// Sada ce broj imati vrednost koju gore prepoznamo
			return BROJ;
	   }
[+*();] {return *yytext;}
[ \t\n] {}
.	{
		fprintf(stderr, "Leksicka greska: %s\n", yytext);
		exit(EXIT_FAILURE);
	}

%%
