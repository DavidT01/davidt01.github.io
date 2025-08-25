#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX_LEN  (255)
#define RD_END   (0)
#define WR_END   (1)

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while (0);

int main(int argc, char** argv) {
    
    check_error(argc == 2, "Bad args");

    FILE* f = fopen(argv[1], "r");
    check_error(f != NULL, "Failed to open file");

    char command_buffer[MAX_LEN];
    char arg_buffer[MAX_LEN];

    int max_size_output = 0;
    char max_command[MAX_LEN];

    while(fscanf(f, "%s", command_buffer) != EOF) {

        fscanf(f, "%s", arg_buffer);
        //printf("%s %s\n", command_buffer, arg_buffer);

        int cld2par[2];
        check_error(
            pipe(cld2par) != -1, "Failed to create pipes"
        );
        
        pid_t pid = fork();
        check_error(pid != -1, "Failed to fork proccess");

        if(pid > 0) {
            
            close(cld2par[WR_END]);

            char c;
            long counter = 0;

            FILE* f1 = fdopen(cld2par[RD_END], "r");
            check_error(f1 != NULL, "Failed to open pipe read end");

            while((c = fgetc(f1)) != EOF) {
                counter += 1;
            }

            //printf("Size: %ld\n", counter);

            if(counter > max_size_output) {
                max_size_output = counter;
                strcpy(max_command, "");
                strcat(max_command, command_buffer);
                strcat(max_command, " ");
                strcat(max_command, arg_buffer);
            }
            
            fclose(f1);
            close(cld2par[RD_END]);
        }
        else {
            
            close(cld2par[RD_END]);
            close(STDERR_FILENO);

            check_error(dup2(cld2par[WR_END], STDOUT_FILENO) != -1, "Failed to redirec");

            check_error(
                execlp(command_buffer, command_buffer, arg_buffer, NULL) != -1,
                "Failed to exec commenad"
            );

            exit(EXIT_SUCCESS);
        }

        int status = 0;
        check_error(wait(&status) != -1, "Faile to wait chiled");
        if(WIFEXITED(status)) {
            //printf("Chiled proccess finished");
        }
    }
    
    printf("%s\n", max_command);
    exit(EXIT_SUCCESS);
}