#include "tokeni.h"

#define MAX_SIZE (256)

extern int yylex();

int stek[MAX_SIZE];
int sp = 0;

void push(int x);
int pop(void);
int peek(void);
int pun(void);
int prazan(void);
int check(int x);

int main() {
    int preduvid = yylex();
    push(PROGRAM);
    while(!prazan()) {
        switch(peek()) {
            case PROGRAM:
                if(preduvid == ID || preduvid == PRINT) {
                    pop();
                    push(PROGRAMP);
                    push(NAREDBA);
                } else {
                    fprintf(stderr, "Sintaksna greska\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case PROGRAMP:
                if(preduvid == ID || preduvid == PRINT) {
                    pop();
                    push(PROGRAMP);
                    push(NAREDBA);
                }
                else if(preduvid == EOI)
                    pop();
                else {
                    fprintf(stderr, "Sintaksna greska\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case NAREDBA:
                if(preduvid == ID) {
                    pop();
                    push(TZ);
                    push(SKUP);
                    push(DODELA);
                    push(ID);
                }
                else if(preduvid == PRINT) {
                    pop();
                    push(TZ);
                    push(SKUP);
                    push(PRINT);
                }
                else {
                    fprintf(stderr, "Sintaksna greska\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case SKUP:
                if(preduvid == OZ) {
                    pop();
                    push(ZZ);
                    push(LISTA);
                    push(OZ);
                }
                else if(preduvid == BROJ) {
                    pop();
                    push(BROJ);
                    push(TT);
                    push(BROJ);
                }
                else if(preduvid == ID) {
                    pop();
                    push(ID);
                }
                else {
                    fprintf(stderr, "Sintaksna greska\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case LISTA:
                if(preduvid == BROJ) {
                    pop();
                    push(LISTAP);
                    push(BROJ);
                }
                else {
                    fprintf(stderr, "Sintaksna greska\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case LISTAP:
                if(preduvid == ZAREZ) {
                    pop();
                    push(LISTAP);
                    push(BROJ);
                    push(ZAREZ);
                }
                else if(preduvid == ZZ)
                    pop();
                else {
                    fprintf(stderr, "Sintaksna greska\n");
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                if(check(preduvid)) {
                    pop();
                    preduvid = yylex();
                }
                else {
                    fprintf(stderr, "Sintaksna greska\n");
                    exit(EXIT_FAILURE);
                }
                break;
        }
    }
    printf("Sve ok\n");
    exit(EXIT_SUCCESS);
}

void push(int x) {
    if(pun()) {
        fprintf(stderr, "Stek je pun\n");
        exit(EXIT_FAILURE);
    }
    stek[sp++] = x;
}

int pop(void) {
    if(prazan()) {
        fprintf(stderr, "Stek je prazan\n");
        exit(EXIT_FAILURE);
    }
    return stek[--sp];
}

int peek(void) {
    if(prazan()) {
        fprintf(stderr, "Stek je prazan\n");
        exit(EXIT_FAILURE);
    }
    return stek[sp - 1];
}

int pun(void) {
    return sp == MAX_SIZE;
}

int prazan(void) {
    return sp == 0;
}

int check(int x) {
    return peek() == x;
}