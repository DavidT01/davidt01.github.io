#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while (0); 

void print_month(int);

int main(int argc, char** argv) {

    check_error(argc == 2, "Bad args");

    time_t e_time = (time_t) atoi(argv[1]);

    struct tm s_time;
    localtime_r(&e_time, &s_time);

    print_month(s_time.tm_mon);

    exit(EXIT_SUCCESS);
}

void print_month(int m) {
    
    switch (m) {
        case 0: printf("januar\n"); break;
        case 1: printf("februar\n"); break;
        case 2: printf("mart\n"); break;
        case 3: printf("april\n"); break;
        case 4: printf("maj\n"); break;
        case 5: printf("jun\n"); break;
        case 6: printf("jul\n"); break;
        case 7: printf("avgust\n"); break;
        case 8: printf("septembar\n"); break;
        case 9: printf("oktobar\n"); break;
        case 10: printf("novembar\n"); break;
        case 11: printf("decembar\n"); break;
    }
}