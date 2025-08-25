#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <time.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0);

void print_day(int);

int main(int argc, char** argv) {

    check_error(argc == 2, "Bad args");

    time_t e_time = (time_t) atoi(argv[1]);

    struct tm s_time;
    localtime_r(&e_time, &s_time);

    print_day(s_time.tm_wday);

    exit(EXIT_SUCCESS);
}

void print_day(int wday) {

    switch (wday) {
        case 0: printf("nedelja\n"); break;
        case 1: printf("ponedeljak\n"); break;
        case 2: printf("utorak\n"); break;
        case 3: printf("sreda\n"); break;
        case 4: printf("cetvrtak\n"); break;
        case 5: printf("petak\n"); break;
        case 6: printf("subota\n"); break; 
    }
}