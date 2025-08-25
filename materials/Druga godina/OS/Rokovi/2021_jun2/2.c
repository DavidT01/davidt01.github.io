#define _DEFAULT_SOURCE

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include <signal.h>

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while (0)

int isUSR1 = 0;
int isUSR2 = 0;
int stop = 0;

void signalHandler(int signal) {
    switch(signal) {
        case SIGUSR1:
            isUSR1 = 1;
            break;
        case SIGUSR2:
            isUSR2 = 1;
            break;
        case SIGTERM:
            stop = 1;
            break;
    }
}

int main(int argc, char** argv) {
    check_error(argc == 1, "argc");
    (void) argv;

    pid_t pid = getpid();
    check_error(pid != -1, "getpid");
    fprintf(stderr, "%d\n", pid);

    check_error(signal(SIGUSR1, signalHandler) != SIG_ERR, "signal");
    check_error(signal(SIGUSR2, signalHandler) != SIG_ERR, "signal");
    check_error(signal(SIGTERM, signalHandler) != SIG_ERR, "signal");

    while(1){
        pause();

        if(stop) break;

        int x;
        scanf("%d", &x);

        if(isUSR1) {
            isUSR1 = 0;
            printf("%d\n", x > 0 ? x : -x);
        }
        else if(isUSR2) {
            isUSR2 = 0;
            printf("%d\n", x * x);
        }
    }

    exit(EXIT_SUCCESS);
}
