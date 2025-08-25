#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <string.h>

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while(0)

#define RD_END (0)
#define WR_END (1)

#define MAX_SIZE (2048)

int main(int argc, char** argv){
    check_error(argc == 1, "argc");
    (void) argv;

    int cld2par[2];
    check_error(pipe(cld2par) != -1, "pipe");

    pid_t childPid = fork();

    if(childPid == 0) {
        close(cld2par[RD_END]);
        check_error(dup2(cld2par[WR_END], STDOUT_FILENO), "dup2");
        check_error(execlp("pwd", "pwd", NULL) != -1, "execlp");
    }

    close(cld2par[WR_END]);

    int status = 0;
    check_error(wait(&status) != -1, "wait");

    if(WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) {
        char path[MAX_SIZE];
        int readBytes = read(cld2par[RD_END], path, MAX_SIZE - 1);
        check_error(readBytes != -1, "read");
        path[readBytes] = 0;

        char name[MAX_SIZE];
        strncpy(name, path, 6);

        if(strcmp(name, "/home/") == 0) {
            char * ime = strtok(path + 6, "/");
            printf("%s\n", ime);
        }
        else {
            printf("system\n");
        }

    }
    else {
        close(cld2par[RD_END]);
        check_error(0, "puko");
    }

    close(cld2par[RD_END]);
    exit(EXIT_SUCCESS);
}
