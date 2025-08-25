#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <wait.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            exit(EXIT_FAILURE); \
        } \
    } while (0);

#define RD_END (0) 
#define WR_END (1)

int main(int argc, char** argv) {

    check_error(argc > 1, "Bad args");

    char* cmd = argv[1];

    char** args = (char**) malloc (argc * sizeof(char*));
    for(int i = 1; i < argc; i ++) {
        args[i - 1] = argv[i];
    }
    args[argc -1] = NULL;

    int cld2par[2];
    check_error(pipe(cld2par) != -1, "Failed to create pipses");

    int count = 0;

    // for(int i = 0; i < argc-1; i++) printf("%s\n", args[i]);
    pid_t pid = fork();

    if( pid > 0) {

        close(cld2par[WR_END]);

        FILE* f = fdopen(cld2par[RD_END], "r");

        char* line = NULL;
        size_t size = 0;

        while(getline(&line, &size, f) != -1) {
            count += 1;
        }

        free(line);
        fclose(f);

    }
    else {

        close(cld2par[RD_END]);
        close(STDERR_FILENO);

        check_error(dup2(cld2par[WR_END], STDOUT_FILENO) != -1, "Failed to redirec");

        check_error(execvp(cmd, args), "Failed to exec commad"); 

        exit(EXIT_SUCCESS);
    }

    int status = 0;
    check_error(wait(&status) != -1, "Failed to wait");

    if(WIFEXITED(status)) {
        if(WEXITSTATUS(status) == EXIT_SUCCESS) {
            printf("%d\n", count);
            free(args);
            exit(EXIT_SUCCESS);
        }
        else if(WEXITSTATUS(status) == EXIT_FAILURE) {
            printf("Neuspeh\n");
            free(args);
            exit(EXIT_FAILURE);
        }
    }
    else {
        printf("??\n");
    }
}