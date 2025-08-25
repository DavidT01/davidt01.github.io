#define _XOPEN_SOURCE 700

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
    } while (0)

#define MAX_SIZE (256)

#define RD_END (0)
#define WR_END (1)

char** makeCommand(char* line) {
    int num = 1; int count = 0;

    char** command = malloc(num * sizeof(char*));
    check_error(command != NULL, "malloc");

    char* word = strtok(line, " ");

    while(word != NULL) {
        if(count >= num) {
            num++;
            command = realloc(command, num * sizeof(char*));
            check_error(command != NULL, "realloc");
        }

        command[count] = malloc(strlen(word) + 1);
        strcpy(command[count], word);

        count++;

        word = strtok(NULL, " ");
    }

    char** tmp = realloc(command, num * sizeof(char*));
    check_error(tmp != NULL, "realloc");

    command[count] = NULL;

    return command;
}

void freeCommand(char** command) {
    for(int i = 0; command[i] != NULL; i++)
        free(command[i]);
    free(command);
}

int main(int argc, char** argv) {
    check_error(argc == 2, "argc");

    FILE* f = fopen(argv[1], "r");
    check_error(f != NULL, "fopen");

    char buffer[MAX_SIZE];

    char* line = NULL;
    size_t n = 0;

    int globalRead = -1;
    char globalCommand [MAX_SIZE];

    while(getline(&line, &n, f) > 0) {

        line[strcspn(line, "\n")] = 0;
        char** command = makeCommand(line);

        int cld2par[2];
        check_error(pipe(cld2par) != -1, "pipe");

        pid_t childPid = fork();
        check_error(childPid != -1, "fork");

        if(childPid == 0) {
            close(cld2par[RD_END]);
            check_error(dup2(cld2par[WR_END], STDOUT_FILENO) != -1, "dup2");
            check_error(execvp(command[0], command) != -1, "exec");
        }

        close(cld2par[WR_END]);

        int wstatus = 0;
        check_error(wait(&wstatus) != -1, "wait");

        if(WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == EXIT_SUCCESS) {
            int readBytes = 0;
            int localRead = 0;

            while((readBytes = read(cld2par[RD_END], buffer, MAX_SIZE)) > 0)
                localRead += readBytes;

            if(localRead > globalRead) {
                strcpy(globalCommand, command[0]);
                globalRead = localRead;
            }
            close(cld2par[RD_END]);
            freeCommand(command);
        }
        else {
            freeCommand(command);
            close(cld2par[RD_END]);
            fclose(f);
            check_error(0, "puklo dete");
        }
    }
    check_error(!ferror(f), "ferror");
    free(line);

    printf("%s\n", globalCommand);

    fclose(f);

    exit(EXIT_SUCCESS);
}
