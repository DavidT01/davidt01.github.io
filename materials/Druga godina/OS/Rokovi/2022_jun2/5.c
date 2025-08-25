#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while (0)

#define MAX_SIZE 256

int main(int argc, char** argv) {
    check_error(argc == 2, "argc");

    int fd = open(argv[1], O_RDWR);
    check_error(fd != -1, "open");

    FILE* f = fdopen(fd, "r+");
    check_error(f != NULL, "fopen");

    char buffer[MAX_SIZE + 1];
    int count = 0;

    while(fscanf(f, "%s", buffer) == 1) {
        if(strncmp(buffer, "test_", 5) == 0) {
            struct flock lock;

            int len = strlen(buffer);

            lock.l_type = F_WRLCK;
            lock.l_whence = SEEK_SET;
            lock.l_start = ftell(f) - len;
            lock.l_len = len;

            int retVal = fcntl(fd, F_SETLK, &lock);

            if (retVal != -1) {
                fseek(f, -len, SEEK_CUR);
                for(int i = 0; buffer[i] != 0; i++)
                    buffer[i] = '#';
                fprintf(f, "%s", buffer);
            }
            else {
                if(errno != EACCES && errno != EAGAIN)
                    check_error(0, "puklo");
                count++;
            }
        }
    }
    printf("%d\n", count);
    fclose(f);
    exit(EXIT_SUCCESS);
}
