#include "tokeni.h"

extern int yylex();

int preduvid = 0;

void program(void);
void programP(void);
void naredba(void);
void sufiks(void);
void izraz(void);
void izrazP(void);
void T(void);
void TP(void);
void F(void);
void nizVrsta(void);
void nizVrstaP(void);
void vrsta(void);
void vrstaP(void);

int main() {
    preduvid = yylex();
    program();
    if(preduvid == EOI)
        printf("Sve ok\n");
    else
        printf("Sintaksna greska\n");
    exit(EXIT_SUCCESS);
}

void program(void) {
    if(preduvid == ID) {
        naredba();
        programP();
    } else {
        printf("Sintaksna greska 1\n");
        exit(EXIT_FAILURE);
    }
}

void programP(void) {
    if(preduvid == ID) {
        naredba();
        programP();
    } else if(preduvid == EOI)
        return;
    else {
        printf("Sintaksna greska 2\n");
        exit(EXIT_FAILURE);
    }
}

void naredba(void) {
    if(preduvid == ID) {
        preduvid = yylex();
        if(preduvid != DODELA) {
            printf("Sintaksna greska 3\n");
            exit(EXIT_FAILURE);
        }
        preduvid = yylex();
        izraz();
        sufiks();
    } else {
        printf("Sintaksna greska 4\n");
        exit(EXIT_FAILURE);
    }
}

void sufiks(void) {
    if(preduvid == TZ) {
        preduvid = yylex();
        if(preduvid != NR) {
            printf("Sintaksna greska 5\n");
            exit(EXIT_FAILURE);
        }
        preduvid = yylex();
    } else if(preduvid == NR)
        preduvid = yylex();
    else {
        printf("Sintaksna greska 6\n");
        exit(EXIT_FAILURE);
    }
}

void izraz(void) {
    if(preduvid == ID || preduvid == OZ || preduvid == OZS) {
        T();
        izrazP();
    } else {
        printf("Sintaksna greska 7\n");
        exit(EXIT_FAILURE);
    }
}

void izrazP(void) {
    if(preduvid == PLUS) {
        preduvid = yylex();
        T();
        izrazP();
    } else if(preduvid == MINUS) {
        preduvid = yylex();
        T();
        izrazP();
    } else if(preduvid == ZZ || preduvid == TZ || preduvid == NR)
        return;
    else {
        printf("Sintaksna greska 8\n");
        exit(EXIT_FAILURE);
    }
}

void T(void) {
    if(preduvid == ID || preduvid == OZ || preduvid == OZS) {
        F();
        TP();
    } else {
        printf("Sintaksna greska 9\n");
        exit(EXIT_FAILURE);
    }
}

void TP(void) {
    if(preduvid == PUTA) {
        preduvid = yylex();
        F();
        TP();
    } else if(preduvid == SKMN) {
        preduvid = yylex();
        F();
        TP();
    } else if(preduvid == PLUS || preduvid == MINUS || preduvid == ZZ || preduvid == TZ || preduvid == NR)
        return;
    else {
        printf("Sintaksna greska 10\n");
        exit(EXIT_FAILURE);
    }
}

void F(void) {
    if(preduvid == ID)
        preduvid = yylex();
    else if(preduvid == OZ) {
        preduvid = yylex();
        izraz();
        if(preduvid != ZZ) {
            printf("Sintaksna greska 11\n");
            exit(EXIT_FAILURE);
        }
        preduvid = yylex();
    } else if(preduvid == OZS) {
        preduvid = yylex();
        nizVrsta();
        if(preduvid != ZZS) {
            printf("Sintaksna greska 11\n");
            exit(EXIT_FAILURE);
        }
        preduvid = yylex();
    } else {
        printf("Sintaksna greska 11\n");
        exit(EXIT_FAILURE);
    }
}

void nizVrsta(void) {
    if(preduvid == BROJ) {
        vrsta();
        nizVrstaP();
    } else {
        printf("Sintaksna greska 12\n");
        exit(EXIT_FAILURE);
    }
}

void nizVrstaP(void) {
    if(preduvid == TZ) {
        preduvid = yylex();
        vrsta();
        nizVrstaP();
    } else if(preduvid == ZZS)
        return;
    else {
        printf("Sintaksna greska 13\n");
        exit(EXIT_FAILURE);
    }
}

void vrsta(void) {
    if(preduvid == BROJ) {
        preduvid = yylex();
        vrstaP();
    } else {
        printf("Sintaksna greska 14\n");
        exit(EXIT_FAILURE);
    }
}

void vrstaP(void) {
    if(preduvid == BROJ) {
        preduvid = yylex();
        vrstaP();
    } else if(preduvid == ZZS || preduvid == TZ)
        return;
    else {
        printf("Sintaksna greska 15\n");
        exit(EXIT_FAILURE);
    }
}