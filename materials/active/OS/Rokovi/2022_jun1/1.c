#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while(0)

char* meseci[12] = {"januar", "februar", "mart", "april", "maj", "jun", "jul", "avgust", "septembar", "oktobar", "novembar", "decembar"};

int main(int argc, char** argv){
    check_error(argc == 3, "argc");

    time_t vreme = atoll(argv[1]);
    int br_meseci = atoi(argv[2]);

    struct tm * broken_time = localtime(&vreme);

    printf("%s ", meseci[broken_time->tm_mon]);

    broken_time->tm_mon -= br_meseci;

    time_t novo_vreme = mktime(broken_time);
    check_error(novo_vreme != (time_t)-1, "mktime");

    localtime(&novo_vreme);

    printf("%s\n", meseci[broken_time->tm_mon]);

    exit(EXIT_SUCCESS);
}
