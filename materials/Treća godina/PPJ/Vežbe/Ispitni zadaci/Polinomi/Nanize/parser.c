#include "tokeni.h"

extern int yylex();

int preduvid = 0;

void program(void);
void programP(void);
void naredba(void);
void naredba2(void);
void naredba3(void);
void polinom(void);
void lista(void);
void listaP(void);

int main() {
    preduvid == yylex();
    program();
    if(preduvid == EOI)
        printf("Sve OK.\n");
    else
        printf("Nije OK\n");
    exit(EXIT_SUCCESS);
}

void program(void) {
    if(preduvid == ID || preduvid == OZ) {
        naredba();
        programP();
    }
    else
        exit(EXIT_FAILURE);
}

void programP(void) {
    if(preduvid == ID || preduvid == OZ) {
        naredba();
        programP();
    } else if(preduvid == EOI)
        return;
    else
        exit(EXIT_FAILURE);
}

void naredba(void) {
    if(preduvid == ID) {
        preduvid = yylex();
        naredba2();
    } else if(preduvid == OZ)
        polinom();
    else
        exit(EXIT_FAILURE);
}

void naredba2(void) {
    if(preduvid == DODELA) {
        preduvid = yylex();
        naredba3();
    } else if(preduvid == NOVIRED) {
        preduvid = yylex();
        return;
    }
    else
        exit(EXIT_FAILURE);
}

void naredba3(void) {
    if(preduvid == ID) {
        preduvid = yylex();
        if(preduvid != NOVIRED)
            exit(EXIT_FAILURE);
        preduvid = yylex();
        return;
    } else if(preduvid == OZ) {
        polinom();
        if(preduvid != NOVIRED)
            exit(EXIT_FAILURE);
        preduvid = yylex();
    }
    else
        exit(EXIT_FAILURE);
}

void polinom(void) {
    if(preduvid == OZ) {
        preduvid = yylex();
        lista();
        if(preduvid != ZZ)
            exit(EXIT_FAILURE);
        preduvid == yylex();
    }
}

void lista(void) {
    if(preduvid == BROJ) {
        preduvid = yylex();
        listaP();
    }
    else
        exit(EXIT_FAILURE);
}

void listaP(void) {
    if(preduvid == ZAREZ) {
        preduvid = yylex();
        if(preduvid != BROJ)
            exit(EXIT_FAILURE);
        preduvid = yylex();
        listaP();
    } else if(preduvid == OZ)
        return;
    else
        exit(EXIT_FAILURE);
}