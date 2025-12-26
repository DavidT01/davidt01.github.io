/* Gramatika:     Skupovi izbora

E -> T EP           {OZ, BROJ}
EP -> + T EP        {PLUS}
      eps           {EOI, ZZ}
T -> F TP           {OZ, BROJ}
TP -> * F TP        {PUTA}
      eps           {PLUS, EOI, ZZ}
F -> ( E )          {OZ}
      broj          {BROJ}

*/

#include "tokeni.h"

#define MAX_DEPTH (256)

extern int yylex();

// Pravimo svoj stek
int stek[MAX_DEPTH];
int sp = 0; // stack pointer

// Funkcije steka
int empty(void); // Da li je stek prazan
void push(int x); // Ubacuje element na stek
int pop(void); // Skida element sa vrha steka
int peek(void); // Sta se nalazi na vrhu steka
int check(int x); // Da li se na vrhu steka nalazi simbol x

int main() {
	int preduvid = yylex();
	// Na stek stavljamo startni simbol
	push(E);
	// Idemo kroz stek dokle god ima elemenata
	while(!empty()) {
		printf("Izvrsavam...\n");
		// Gledamo sta je na vrhu steka
		switch(peek()) {
			case E:
				if(preduvid == OZ || preduvid == BROJ) {
					// Zamenimo E sa T EP, u stek ubacujemo s' desna
					// E -> T EP
					pop();
					push(EP);
					push(T);
				} else
					check_error(1, "Greska");
				break;
			case EP:
				if(preduvid == PLUS) {
					// EP -> + T EP
					pop();
					push(EP);
					push(T);
					push(PLUS);
				} else if(preduvid == EOI || preduvid == ZZ) {
					// Anuliramo E
					pop();
				} else
					check_error(1, "Greska");
				break;
			case T:
				if(preduvid == BROJ || preduvid == OZ) {
					// T -> F TP 
					pop();
					push(TP);
					push(F);
				} else
					check_error(1, "Greska");
				break;
			case TP:
				if(preduvid == PUTA) {
					// TP -> * F TP
					pop();
					push(TP);
					push(F);
					push(PUTA);
				} else if(preduvid == PLUS || preduvid == EOI || preduvid == ZZ) {
					// Anuliramo E
					pop();
				} else
					check_error(1, "Greska");
				break;
			case F:
				if(preduvid == BROJ) {
					// F -> broj
					pop();
					push(BROJ);
				} else if(preduvid == OZ) {
					// F -> ( E )
					pop();
					push(ZZ);
					push(E);
					push(OZ);
				} else
					check_error(1, "Greska");
				break;
			default: // Ostali su tokeni
				// Proveravamo da li se nakon funkcija na vrhu steka nalazi preduvidni simbol
				if(check(preduvid)) {
					// Ako da, skidamo ga i ucitavamo sledeci
					pop();
					preduvid = yylex();
				} else
					// Inace je doslo do greske
					check_error(1, "Greska");
				break;
		}
	}
	printf("Sve ok\n");
	exit(EXIT_SUCCESS);
}

// Implementiramo funkcije steka
int pop(void) {
	check_error(sp <= 0, "Prazan stek");
	return stek[--sp];
}
void push(int x) {
	check_error(sp >= MAX_DEPTH, "Pun stek");
	stek[sp++] = x;
}
int peek(void) {
	check_error(sp <= 0, "Prazan stek");
	return stek[sp - 1];
}
int empty(void) {
	return sp == 0;
}
int check(int x) {
	check_error(sp <= 0, "Prazan stek");
	return stek[sp - 1] == x;
}
