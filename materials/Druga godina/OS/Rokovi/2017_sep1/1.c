#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

#define STR_LEN (63)

int sig_usr1 = 0;
int sig_usr2 = 0;
int sigterm = 0;

void sig1(int sig) {
    sig_usr1 = 1;
}

void sig2(int sig) {
    sig_usr2 = 1;
}

void term(int sig) {
    sigterm = 1;
}

void invert(char*);
void to_lower_all(char*);

int main(int argc, char** argv) {

    while(1) {

        char buffer[STR_LEN + 1];
        scanf("%s", buffer);

        check_error(signal(SIGUSR1, sig1) != SIG_ERR, "Failed to signal");
        check_error(signal(SIGUSR2, sig2) != SIG_ERR, "Failed to signal");
        check_error(signal(SIGTERM, term) != SIG_ERR, "Failed to signal");

        pause();

        if(sig_usr1 == 1) {
            sig_usr1 = 0;
            invert(buffer);
        }
        else if (sig_usr2 == 1) {
            sig_usr2 = 0;
            to_lower_all(buffer);
        }
        else if( sigterm == 1) {
            break;
        }

        printf("%s\n", buffer);
    }

    exit(EXIT_SUCCESS);
}

void invert(char* buffer) {

    char temp_buffer[STR_LEN + 1];

    int buffer_len = strlen(buffer);

    int i = 0;
    int j = buffer_len - 1;

    while(i < buffer_len) temp_buffer[i++] = buffer[j--];

    temp_buffer[i] = '\0';

    strcpy(buffer, temp_buffer);
}

void to_lower_all(char* buffer) {

    int i = 0;
    while(buffer[i] != '\0') {
        if(islower(buffer[i])) buffer[i] = toupper(buffer[i]);
        i++;
    }
}