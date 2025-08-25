#include <stdio.h>
#include <stdlib.h>

#include <errno.h>

#include <signal.h>

#define check_error(cond, msg) \
    do{ \
        if(!(cond)){ \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0);

int exit_signal = 0;
int score = 0;

void sighand(int sig){
    if(sig == SIGTERM)
        exit_signal = 1;
    else if(sig == SIGUSR1)
        score += 1;
    else if(sig == SIGUSR2)
        score += 2;
    else if(sig == SIGINT)
        score -= 4;
}

int main(int argc, char** argv){


    while(!exit_signal){

        check_error(signal(SIGTERM, sighand) != SIG_ERR, "Failed to asign handler for SIGTERM");
        check_error(signal(SIGUSR1, sighand) != SIG_ERR, "Failed to asign handler for SIGUSR1");
        check_error(signal(SIGUSR2, sighand) != SIG_ERR, "Failed to asign handler for SIGUSR2");
        check_error(signal(SIGINT, sighand) != SIG_ERR, "Failed to asign handler for SIGINT");
    }

    printf("%d\n", score);

    exit(EXIT_SUCCESS);
}