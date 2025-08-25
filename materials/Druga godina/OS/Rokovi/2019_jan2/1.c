#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <time.h>

#define check_error(cond, errMsg) \
    do{ \
        if(!(cond)){ \
            perror(errMsg); \
            exit(EXIT_FAILURE); \
        } \
    }while(0);

int main(int argc, char** argv){

    check_error(argc == 2, "Bad arguments");

    time_t curr = (time_t) atoi(argv[1]);

    struct tm* curr_time = localtime(&curr);
    

    if(curr_time->tm_hour > 0 && curr_time->tm_hour <= 6){
        printf("noc\n");
    }
    else if(curr_time->tm_hour == 7){
        if(curr_time->tm_min == 0 && curr_time->tm_sec == 0){
            printf("noc\n");
        }
        else{
            printf("jutro\n");
        }
    }
    else if(curr_time->tm_hour > 7 && curr_time->tm_hour <= 8){
        printf("jutro\n");
    }
    else if(curr_time->tm_hour == 9){
        if(curr_time->tm_min == 0 && curr_time->tm_sec == 0){
            printf("jutro\n");
        }
        else{
            printf("prepodne\n");
        }
    }
    else if(curr_time->tm_hour > 9 && curr_time->tm_hour <= 11){
        printf("prepodne\n");
    }
    else if(curr_time->tm_hour == 12){
        if(curr_time->tm_min == 0 && curr_time->tm_sec == 0){
            printf("prepodne\n");
        }
        else{
            printf("popodne\n");
        }
    }
    else if(curr_time->tm_hour > 12 && curr_time->tm_hour <= 18){
        printf("popodne\n");
    }
    else if(curr_time->tm_hour == 19){
        if(curr_time->tm_min == 0 && curr_time->tm_sec == 0){
            printf("popodne\n");
        }
        else{
            printf("vece\n");
        }
    }
    else if(curr_time->tm_hour > 19 && curr_time->tm_hour <= 23){
        printf("vece\n");
    }
    else if(curr_time->tm_hour == 0){
        if(curr_time->tm_min == 0 && curr_time->tm_sec == 0){
            printf("vece\n");
        }
        else{
            printf("noc\n");
        }
    }

    exit(EXIT_SUCCESS);

}