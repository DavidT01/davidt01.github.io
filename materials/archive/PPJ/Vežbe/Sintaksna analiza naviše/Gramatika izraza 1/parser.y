// Komande za Bison
%{
	// Povezujemo zaglavlja
	#include <stdio.h>
	#include <stdlib.h>
	
	// Povezujemo lekser
	extern int yylex();
	
	// Pisemo error funkciju
	void yyerror(char* s) {
		fprintf(stderr, "Sintaksna greska: %s\n", s);
		exit(EXIT_FAILURE);
	}
%}

%union {
	int v;
}

// Imenovani tokeni (ne mora tacka zarez jer je on jedan karakter - ';')
// Ti tokeni ce biti tipa v, tj. int
%token<v> BROJ

// Navodima i kojeg tipa su nasi neterminali
%type<v> f e t

// Startni token
%start program

// Gramaticka pravila i akcije
%%

// Pisemo nasu gramatiku, ako ima vise grana onda imamo vise | znakova, na kraju uvek ide tacka-zarez
// U zgradama idu akcije
// Leva strana akcije je $$, a u desnoj idu redom: $1 $2 $3 (racunajuci i neterminali i tokene)

program: program naredba       {}
	| naredba                  {}
	;
naredba: e ';'                 {printf("Vrednost izraza: %d\n", $1);}
	;
e: e '+' t                     {$$ = $1 + $3;}
	| t                        {$$ = $1;}
	;
t: t '*' f                     {$$ = $1 * $3;}
	| f                        {$$ = $1;}
	;
f: '(' e '('                   {$$ = $2;}
	| BROJ                     {$$ = $1;}
	;

%%

int main() {
	// Pozivamo funkciju parsera i ako vraca 0 sve je u redu
	if(yyparse() == 0)
		printf("Sve ok.\n");
	else
		printf("Sintaksna greska.\n");
	exit(EXIT_SUCCESS);
}
