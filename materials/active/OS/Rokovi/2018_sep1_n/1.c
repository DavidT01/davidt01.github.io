#include <stdio.h>
#include <stdlib.h>

#include <errno.h>

#include <sys/time.h>
#include <time.h>

#define STR_LEN (16)

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while (0);

int main(int argc, char** argv) {
    
    check_error(argc == 3, "Bad args");

    time_t e_time = atoi(argv[1]) + 60 * atoi(argv[2]);

    struct tm* s_time = localtime(&e_time);
    check_error(s_time != NULL, "Failed to divide time");

    char time_buffer[STR_LEN + 1];

    strftime(time_buffer, STR_LEN + 1, "%d/%m/%Y %H:%M", s_time);

    printf("%s\n", time_buffer);

    exit(EXIT_SUCCESS);
}