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

// Ukljucimo zaglavlja koja koristimo
#include "tokeni.h"

// Makro za debug
#define DEBUG (1)

// Povezemo lekser sa parserom, lekser daje preduvidni simbol
extern int yylex();

// Preduvidni simbol, na pocetku je nula
int preduvid = 0;

// Pisemo funkcije za sve neterminale
void E(void);
void EP(void);
void T(void);
void TP(void);
void F(void);

int main() {
    // Ucitavamo preduvidni simbol, na osonovu njega se poziva funkcija
    preduvid = yylex();

    // Pozivamo startni simbol
    E();

    // Proveravamo da li je na kraju preduvidni simbol kraj izlaza
    if(preduvid == EOI)
        printf("Sve ok.\n");
    else
        printf("Sintaksna greska. Visak tokena na ulazu.\n");
    
    // Zavrsavamo program
    exit(EXIT_SUCCESS);
}

// Implementiramo sve funkcije

// E -> T EP           {OZ, BROJ}
void E(void) {
    // Proverimo da li preduvidni simbol odgovara skupu izbora
    if(preduvid == OZ || preduvid == BROJ) {
        // Ispisemo tekst da bi potvrdili da funkcija radi (ako zelimo)
        #ifdef DEBUG
            printf("E -> T EP\n");
        #endif
        // Pozivamo funkcije
        T();
        EP();
    }
    // Inace vracamo gresku
    else
        check_error("Sintaksna greska. Ocekivano je OZ ili BROJ");
}

// EP -> + T EP        {PLUS}
//       eps           {EOI, ZZ}
void EP(void) {
    if(preduvid == PLUS) {
        #ifdef DEBUG
            printf("EP -> + T EP\n");
        #endif
        // Pojedemo token, tj. ucitamo sledeci
        preduvid = yylex();
        T();
        EP();
    } else if(preduvid == EOI || preduvid == ZZ) {
        // Ne radimo nista (anuliramo)
        #ifdef DEBUG
            printf("E -> eps\n");
        #endif
    } else
        check_error("Sintaksna greska. Ocekivano je PLUS, EOI ili ZZ");
}

// T -> F TP           {OZ, BROJ}
void T(void) {
    if(preduvid == OZ || preduvid == BROJ) {
        #ifdef DEBUG
            printf("T -> F TP\n");
        #endif
        F();
        TP();
    } else
        check_error("Sintaksna greska. Ocekivano je OZ ili BROJ");
}

// TP -> * F TP        {PUTA}
//       eps           {PLUS, EOI, ZZ}
void TP(void) {
    if(preduvid == PUTA) {
        #ifdef DEBUG
            printf("TP -> * F TP\n");
        #endif
        preduvid = yylex();
        F();
        TP();
    } else if(preduvid == PLUS || preduvid == EOI || preduvid == ZZ) {
        #ifdef DEBUG
            printf("TP -> eps\n");
        #endif
    } else
        check_error("Sintaksna greska. Ocekivano je PUTA, PLUS, EOI ili ZZ");
}

// F -> ( E )          {OZ}
//       broj          {BROJ}
void F(void) {
    if(preduvid == OZ) {
        #ifdef DEBUG
            printf("F -> ( E )\n");
        #endif
        // Pojedemo otvorenu zagradu
        preduvid = yylex();
        // Pozovemo funkciju
        E();
        // Proveravamo da li je vracena zatvorena zagrada
        if(preduvid != ZZ)
            check_error("Sintaksna greska. Ocekivano je ZZ");
        // Pojedemo zatvorenu zagradu
        preduvid = yylex();
    } else if(preduvid == BROJ) {
        #ifdef DEBUG
            printf("F -> broj\n");
        #endif
        // Pojedemo broj
        preduvid = yylex();
    } else
        check_error("Sintaksna greska. Ocekivano je OZ ili BROJ");
}