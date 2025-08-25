#define _DEFAULT_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while(0)

int globalAction = -1;

#define PALINDROM (0)
#define OBRNI (1)
#define QUIT (2)

void proccessSingal(int signal) {
    switch(signal) {
        case SIGUSR1:
            globalAction = PALINDROM;
            break;
        case SIGUSR2:
            globalAction = OBRNI;
            break;
        case SIGQUIT:
            globalAction = QUIT;
            break;
    }
}

int isPalindrom(char* rec, int n) {
    for(int i = 0, j = n - 1; i < j; i++, j--)
        if(rec[i] != rec[j])
            return 0;
    return 1;
}

void obrniRec(char* rec, int n) {
    for(int i = 0, j = n - 1; i < j; i++, j--){
        char tmp = rec[i];
        rec[i] = rec[j];
        rec[j] = tmp;
    }
    printf("%s ", rec);
}

int main(int argc, char** argv){
    check_error(argc == 1, "argc");
    (void) argv;

    check_error(signal(SIGUSR1, proccessSingal) != SIG_ERR, "sig");
    check_error(signal(SIGUSR2, proccessSingal) != SIG_ERR, "sig");
    check_error(signal(SIGQUIT, proccessSingal) != SIG_ERR, "sig");



    pid_t pid = getpid();
    printf("%d", pid);

    do {
        char rec[1024];
        scanf("%s", rec);
        int n = strlen(rec);

        pause();

        switch(globalAction) {
            case PALINDROM:
                printf("%d ", isPalindrom(rec, n));
                break;
            case OBRNI:
                obrniRec(rec, n);
                break;
            case QUIT:
                exit(EXIT_SUCCESS);
                break;
        }

    } while(1);

    exit(EXIT_SUCCESS);
}
