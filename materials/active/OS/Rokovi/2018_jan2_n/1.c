#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while (0);

#define TIME_STR_LEN (5) 

int main(int argc, char** argv) {

    check_error(argc == 2, "Bad args");

    time_t e_time = atoi(argv[1]);
    struct tm* s_time = localtime(&e_time);

    char buffer[TIME_STR_LEN + 1];

    strftime(buffer, TIME_STR_LEN + 1, "%H:%M", s_time);

    printf("%s\n", buffer);

    exit(EXIT_SUCCESS);
}