%{

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	
	extern int yylex();
	
	void yyerror(char* s) {
		fprintf(stderr, "Sintaksna greska: %s\n", s);
		exit(EXIT_FAILURE);
	}
	
	#define INIT_CAPACITY (32)
	#define STEP (2)
	
	typedef struct {
		char* ime;
		float v;
	} prom_t;
	
	prom_t* promenljive = NULL;
	int capacity;
	int n;
	
	void alociraj() {
		capacity = INIT_CAPACITY;
		n = 0;
		promenljive = malloc(capacity * sizeof(prom_t));
		if(promenljive == NULL)
			yyerror("Alokacija");
	}
	
	void dealociraj() {
		int i = 0;
		for(i = 0; i < n; i++)
			free(promenljive[i].ime);
		free(promenljive);
	}
	
	int pronadji(char* s) {
		int i = 0;
		for(i = 0; i < n; i++)
			if(strcmp(s, promenljive[i].ime) == 0)
				return i;
		return -1;
	}

%}

%union {
	int k;
	float v;
	char* ime;
}

%left '+' '-'
%left '*' '/'
%left UMINUS

%token PRINT GTE LTE EQ NEQ
%token<v> BROJ
%token<ime> ID
%type<k> logicka_naredba
%type<v> izraz

%start program

%%

program: program naredba                     {}
	| naredba                                {}
	;
naredba: ID '=' izraz ';'                    {
												int retVal = pronadji($1);
												if(retVal == -1) {
													promenljive[n].ime = strdup($1);
													if(promenljive[n].ime == NULL)
														yyerror("Alokacija nije moguca");
													promenljive[n].v = $3;
													n++;
													if(n == capacity) {
														capacity *= STEP;
														promenljive = realloc(promenljive, capacity * sizeof(prom_t));
														if(promenljive == NULL)
															yyerror("Alokacija nije moguca");
													}
												}
												else
													promenljive[retVal].v = $3;
												free($1);
											 }
	| PRINT '(' izraz ')' ';'                {printf("Vrednost izraza: %.2f\n", $3);}
	| logicka_naredba ';'                    {printf("%s\n", $1 == 1 ? "True" : "False");}
	;
izraz: izraz '+' izraz                       {$$ = $1 + $3;}
	|  izraz '-' izraz                       {$$ = $1 - $3;}
	|  izraz '*' izraz                       {$$ = $1 * $3;}
	|  izraz '/' izraz                       {$$ = $1 / $3;}
	|  '-' izraz %prec UMINUS                {$$ = -$2;}
	| '(' izraz ')'                          {$$ = $2;}
	| BROJ                                   {$$ = $1;}
	| ID                                     {
												int retVal = pronadji($1);
												if(retVal == -1)
													yyerror("Promenljiva nije definisana");
												else
													$$ = promenljive[retVal].v;
												free($1);
											 }
	;
logicka_naredba: izraz '<' izraz             {$$ = $1 < $3 ? 1 : 0;}
	| izraz '>' izraz                        {$$ = $1 > $3 ? 1 : 0;}
	| izraz GTE izraz                        {$$ = $1 >= $3 ? 1 : 0;}
	| izraz LTE izraz                        {$$ = $1 <= $3 ? 1 : 0;}
	| izraz EQ izraz                         {$$ = $1 == $3 ? 1 : 0;}
	| izraz NEQ izraz                        {$$ = $1 != $3 ? 1 : 0;}
	;

%%

int main() {
	alociraj();
	if(yyparse() == 0)
		printf("Sve ok.\n");
	else
		printf("Sintaksna greska.\n");
	dealociraj();
	exit(EXIT_SUCCESS);
}
