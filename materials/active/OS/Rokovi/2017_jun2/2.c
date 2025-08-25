#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0);

#define WR_END (1)
#define RD_END (0)
#define MAX_LEN (1024)

bool has_extension(char* file_name, char* ext);

int main(int argc, char** argv) {

    // argv[1] - ekstenzija koju trazimo (zapisana sa tackom)

    check_error(argc == 2, "Bad args");

    int cld2par[2];
    check_error(pipe(cld2par) != -1, "Failed pipe");

    pid_t pid = fork();
    check_error(pid != -1, "Failed to fork");

    if(pid == 0) {

        close(cld2par[RD_END]);

        check_error(dup2(cld2par[WR_END], STDOUT_FILENO) != -1, "Failed to redirect");

        check_error(execlp("find", "find", ".", "-type", "f", NULL), "Failed to exec")

        exit(EXIT_SUCCESS);
    }

    close(cld2par[WR_END]);

    FILE* f = fdopen(cld2par[RD_END], "r");
    check_error(f != NULL, "Failed to open read end of pipe");

    char file_name[MAX_LEN];
    int brojac = 0;

    while(fscanf(f, "%s", file_name) != EOF) {
        if(has_extension(file_name, argv[1]))
            brojac++;
    }

    printf("%d\n", brojac);
    
    exit(EXIT_SUCCESS);
}

bool has_extension(char* file_name, char* ext) {

    if(strstr(file_name, ext) != NULL) return true;
    else return false;
}