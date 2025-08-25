#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while (0); 

#define RD_END (0)
#define WR_END (1)

int main(int argc, char** argv) {

    check_error(argc == 3, "Bad args");

    int cld2par[2];
    check_error(pipe(cld2par) != -1, "Failed to create pips");

    pid_t pid = fork();
    check_error(pid != -1, "Failed to fork proccess");

    if(pid > 0) {

        close(cld2par[WR_END]);

        FILE* f = fdopen(cld2par[RD_END], "r");
        check_error(f != NULL, "Failed to open read end of pipe as file stram");

        char* line = NULL;
        size_t size;

        while(getline(&line, &size, f) != -1) {
            printf("%s", line);
        }

        free(line);
        fclose(f);

    } else {
        
        close(cld2par[RD_END]);
        close(STDERR_FILENO);

        check_error(dup2(cld2par[WR_END], STDOUT_FILENO), "Failed to redirec");

        check_error(
            execlp("tail", "tail", "-n", argv[2], argv[1], NULL),
            "Failed to exec command"
        );

        close(cld2par[WR_END]);
        exit(EXIT_SUCCESS);
    }

    int status = 0;
    check_error(wait(&status) != -1, "Failed to wait child proccess");

    if(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE) {
        printf("Neuspeh\n");
    }

    exit(EXIT_SUCCESS);
}