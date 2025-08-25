#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <wait.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0);

#define RD_END (0)
#define WR_END (1)

int main(int argc, char** argv) {

    // argv[1] - putanja ka fajlu koji statujemo

    check_error(argc == 2, "Bad args");

    int cld2par[2];
    check_error(pipe(cld2par) != -1, "pipe");

    pid_t pid = fork();
    check_error(pid != -1, "fork");

    if(pid == 0) {

        close(cld2par[RD_END]);

        check_error(dup2(cld2par[WR_END], STDOUT_FILENO) != -1, "dup2");

        execlp("stat", "stat", argv[1], NULL);
    }

    close(cld2par[WR_END]);

    FILE* f = fdopen(cld2par[RD_END], "r");
    check_error(f != NULL, "fdopen");

    int size = 0;
    fscanf(f, "%*s %*s %*s %d", &size);

    fclose(f);

    int status = 0;
    check_error(wait(&status) != -1, "wait");

    if(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS) {

        printf("%d\n", size);
    }
    else {
        printf("Neuspeh\n");
    }

    exit(EXIT_SUCCESS);
}