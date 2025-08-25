#include <stdio.h>
#include <stdlib.h>

#include <errno.h>

#include <sys/time.h>
#include <time.h>

#define check_error(cond, msg) \
    do{ \
        if(!(cond)){ \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0);

void print_month(int);

int main(int argc, char** argv){
    
    check_error(argc == 3, "Bad args");

    time_t e_time1 = (time_t) atoi(argv[1]);
    time_t e_time2 = e_time1 + ((time_t) atoi(argv[2]) * 24 * 3600);

    struct tm* time1 = localtime(&e_time1);
    print_month(time1->tm_mon);

    printf(" ");

    struct tm* time2 = localtime(&e_time2);
    print_month(time2->tm_mon);

    printf("\n");

    exit(EXIT_SUCCESS);
}

void print_month(int month){

    switch(month){
        case 0: 
            printf("januar"); break;
        case 1: 
            printf("februar"); break;
        case 2: 
            printf("mart"); break;
        case 3: 
            printf("april"); break;
        case 4: 
            printf("maj"); break;
        case 5: 
            printf("jun"); break;
        case 6: 
            printf("jul"); break;
        case 7: 
            printf("avgust"); break;
        case 8: 
            printf("septembar"); break;
        case 9: 
            printf("oktobar"); break;
        case 10: 
            printf("novemar"); break;
        case 11: 
            printf("decembar"); break;
    }  
}