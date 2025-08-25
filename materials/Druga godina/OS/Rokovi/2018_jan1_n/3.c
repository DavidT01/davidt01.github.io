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
            exit(EXIT_FAILURE); \
        } \
    } while (0); 

#define RD_END (0)
#define WR_END (1)

int main(int argc, char** argv) {

    check_error(argc == 3, "Bad args");

    int cld2par[2];
    check_error(pipe(cld2par) != -1, "Failed to create pipe");

    pid_t pid = fork();
    check_error(pid != -1, "Failed to fork child proccess");

    int ret_val;

    if(pid > 0) {

        close(cld2par[WR_END]);

        FILE* f = fdopen(cld2par[RD_END], "r");

        size_t size;

        fscanf(f, "%d", &ret_val);

        fclose(f);
        close(cld2par[RD_END]);
    }
    else {
        
        close(cld2par[RD_END]);
        close(STDERR_FILENO);

        check_error(dup2(cld2par[WR_END], STDOUT_FILENO) != -1, "Failed to redirec");
        check_error(
            execlp("wc", "wc", argv[2], argv[1], NULL), "Failed to exec command");

        close(cld2par[WR_END]);
        exit(EXIT_SUCCESS);
    }

    int status = 0;
    check_error(wait(&status), "Failed to wait child");

    if(WIFEXITED(status)) {
        if(WEXITSTATUS(status) == EXIT_SUCCESS) {
            printf("%d\n", ret_val);
        }
        else if(WEXITSTATUS(status) == EXIT_FAILURE) {
            printf("Neuspeh\n");
        }
    }

    exit(EXIT_SUCCESS);
}