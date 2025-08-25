#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include <time.h>

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while (0)

char* week[7] = {"nedelja", "ponedeljak", "utorak", "sreda", "cetvrtak", "petak", "subota"};

int main(int argc, char** argv) {
    check_error(argc == 3, "argc");

    time_t time_curr = atoll(argv[1]);
    int br_god = atoi(argv[2]);

    struct tm* broken_time = localtime(&time_curr);

    int day1 = broken_time->tm_wday;

    broken_time->tm_year += br_god;

    time_t time_new = mktime(broken_time);
    check_error(time_new != (time_t) -1, "mktime");

    broken_time = localtime(&time_new);

    int day2 = broken_time->tm_wday;

    printf("%s %s\n", week[day1], week[day2]);



    exit(EXIT_SUCCESS);
}
