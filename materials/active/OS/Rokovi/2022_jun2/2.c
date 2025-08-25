#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while (0)

#define RD_END (0)
#define WR_END (1)

char** makeCommand(){

}

int main(int argc, char** argv) {
    check_error(argc == 2, "argc");

    FILE* f = fopen(argv[1], "r");
    check_error(f != NULL, "fopen");

    int cld2par[2];
    check_error(pipe(cld2par) != -1, "pipe");

    char* line = NULL;
    size_t n = 0;
    int readBytes = 0;
    while((readBytes = getline(&line, &n, f)) > 0) {
        if(line[readBytes - 1] == '\n')
            line[readBytes - 1] = '\0';

        char** command = NULL;
    }
    free(line);
    fclose(f);
    exit(EXIT_SUCCESS);
}
