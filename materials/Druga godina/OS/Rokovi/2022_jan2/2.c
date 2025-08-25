#define _GNU_SOURCE

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while(0)

int main(int argc, char** argv) {
    check_error(argc == 2, "argc");

    struct stat fInfo;
    check_error(stat(argv[1], &fInfo) != -1, "stat");

    check_error(S_ISREG(fInfo.st_mode), "nije reg fajl");

    char* ext = strchr(argv[1], '.');
    check_error(strcmp(ext, ".c") == 0, "nije c fajl");

    int size = strlen(argv[1]);

    char* sName =  malloc(size * sizeof(char));
    check_error(sName != NULL, "malloc");

    strcpy(sName, argv[1]);
    sName[size - 1] = 's';

    pid_t childPid = fork();
    check_error(childPid != -1, "fork");

    if(childPid == 0) {
        check_error(execlp("gcc", "gcc", "-std=c99", "-S", argv[1], "-o", sName, NULL) != -1, "execlp");
    }
    int wstatus = 0;
    check_error(wait(&wstatus) != -1, "wait");

    if(WIFEXITED(wstatus)) {
        if(WEXITSTATUS(wstatus) == EXIT_SUCCESS){
            FILE* f = fopen(sName, "r");
            check_error(f != NULL, "fopen");

            char* line = NULL;
            size_t n = 0;
            int counter = 0;
            while(getline(&line, &n, f) != EOF) {
                if (strstr(line, "mov") != NULL){
                    counter++;
                }
            }

            free(line);
            printf("%d\n", counter);
        }
        else {
            free(sName);
            exit(WEXITSTATUS(wstatus));
        }
    }
    else {
        free(sName);
        check_error(0, "puklo skroz");
    }

    check_error(unlink(sName) != -1, "unlink");

    free(sName);
    exit(EXIT_SUCCESS);
}
