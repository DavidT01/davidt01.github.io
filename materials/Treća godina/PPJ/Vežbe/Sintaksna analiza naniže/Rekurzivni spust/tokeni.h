#ifndef TOKENI_H // Ako nije definisano (pocetak if-a)
#define TOKENI_H // Definiši tokene

// Ukljucimo zaglavlja
#include <stdio.h>
#include <stdlib.h>

// Makro za greske
#define check_error(userMsg)\
	do {\
			fprintf(stderr, "Sintaksna greska: %s\n", userMsg);\
			exit(EXIT_FAILURE);\
	} while(0)

// Definisemo tokene
#define EOI (0) // EOI mora biti 0
#define BROJ (1)
#define PLUS (2)
#define PUTA (3)
#define OZ (4)
#define ZZ (5)

#endif // Kraj if-a