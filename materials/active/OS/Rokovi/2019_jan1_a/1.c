#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <sys/time.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while (0);

void print_day(int day) {
    
    switch(day) {
        case 0: printf("nedelja"); break;
        case 1: printf("ponedeljak"); break;
        case 2: printf("utorak"); break;
        case 3: printf("sreda"); break;
        case 4: printf("cetvrtak"); break;
        case 5: printf("petak"); break;
        case 6: printf("subota"); break;
    }
}

int main(int argc, char** argv) {
    
    // argv[1] - broj sekundi od ephe
    // argv[2] - broj godina

    check_error(argc == 3, "Bad args");

    time_t time1 = atoi(argv[1]);

    struct tm time1_s;
    localtime_r(&time1, &time1_s);
    print_day(time1_s.tm_wday);
    printf(" ");

    int year_to_add = atoi(argv[2]);

    for(int i = 0; i < year_to_add; i ++) {

        struct tm temp_time_s;
        localtime_r(&time1, &temp_time_s);

        if((temp_time_s.tm_mon == 0 || (temp_time_s.tm_mon == 1 && temp_time_s.tm_mday < 29))
           && temp_time_s.tm_year % 4 == 0) 
           { 
               time1 += 366 * 24 * 3600;
           }
        else if (temp_time_s.tm_mon > 1 && (temp_time_s.tm_year + 1) % 4 == 0) {
            time1 += 366 * 24 * 3600; 
        }
        else {
            time1 += 365 * 24 * 3600; 
        }
    }

    localtime_r(&time1, &time1_s);
    
    print_day(time1_s.tm_wday);
    printf("\n");
    
    exit(EXIT_SUCCESS);
}