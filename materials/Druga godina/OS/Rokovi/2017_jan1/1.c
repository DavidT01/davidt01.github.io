#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0);

int signal1 = 0;
int signal2 = 0;
int signalterm = 0;

void handle_signal1(int signal) {
    signal1 = 1;
}
void handle_signal2(int signal) {
    signal2 = 1;
}
void handle_term(int signal) {
    signalterm = 1;
}

int main(int argc, char** argv) {

    int counter1 = 0;
    int counter2 = 0;

    while(signalterm != 1) {

        check_error(signal(SIGUSR1, handle_signal1) != SIG_ERR, "signal1");
        check_error(signal(SIGUSR2, handle_signal2) != SIG_ERR, "signal2");
        check_error(signal(SIGTERM, handle_term) != SIG_ERR, "signal3");

        if(signal1 == 1) {
            counter1 ++;
            signal1 = 0;
        }
        else if (signal2 == 1) {
            counter2 ++;
            signal2 = 0;
        }
    }

    printf("%d %d\n", counter1, counter2);
    
    exit(EXIT_SUCCESS);
}
