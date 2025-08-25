%{

	#include <stdio.h>
	#include <stdlib.h>
	
	extern int yylex();
	
	void yyerror(char* s) {
		fprintf(stderr, "Sintaksna greska: %s\n", s);
		exit(EXIT_FAILURE);
	}

%}

%union {
	float v;
}

%left '+' '-'
%left '*' '/'
%right UMINUS // Za unarni minus dajemo novo ime, i dole kazemo to u gramatici

%token<v> BROJ

%type<v> e

%start program

%%

program: program naredba      {}
	| naredba                 {}
	;
naredba: e ';'                {printf("Vrednost izraza: %.2f\n", $1);}
	;
e	: e '+' e                 {$$ = $1 + $3;}
	| e '-' e                 {$$ = $1 - $3;}
	| e '*' e                 {$$ = $1 * $3;}
	| e '/' e                 {$$ = $1 / $3;}
	| '-' e %prec UMINUS      {$$ = -$2;}
	| '(' e ')'               {$$ = $2;}
	| BROJ                    {$$ = $1;}
	;

%%

int main() {
	if(yyparse() == 0)
		printf("Sve ok.\n");
	else
		printf("Sintaksna greska.\n");
	exit(EXIT_SUCCESS);
}
