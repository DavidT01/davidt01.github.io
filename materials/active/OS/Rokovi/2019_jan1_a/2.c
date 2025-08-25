#include <stdio.h>
#include <stdlib.h>

#include <signal.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while (0);

int sig_usr1 = 0;
int sig_usr2 = 0;
int sig_term = 0;

void handler_usr1(int sig) {
    sig_usr1 = 1;
}

void handler_usr2(int sig) {
    sig_usr2 = 1;
}

void handler_term(int sig) {
    sig_term = 1;
}

int main(int argc, char** argv) {

    while(!sig_term) {
        signal(SIGUSR1, handler_usr1);
        signal(SIGUSR2, handler_usr2);
        signal(SIGTERM, handler_term);

        if(sig_usr1 == 1) {

            sig_usr1 = 0;
            int broj; scanf("%d", &broj);
            printf("%d\n", abs(broj));
        }
        else if (sig_usr2 == 1) {
            sig_usr2 = 0;
            int broj; scanf("%d", &broj);
            printf("%d\n", broj * broj);
        }
    }
    
}