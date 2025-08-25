#define _XOPEN_SOURCE 700

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while (0)

#define MAX_SIZE (256)

int main(int argc, char** argv) {
    check_error(argc == 3, "argc");

    int len = strlen(argv[2]);

    int fd = open(argv[1], O_RDWR);
    check_error(fd != -1, "open");

    FILE* f = fdopen(fd, "r");
    check_error(f != NULL, "fopen");

    char buffer[MAX_SIZE];

    while(fscanf(f, "%s", buffer) == 1) {
        if(strcmp(buffer, argv[2]) == 0) {
            struct flock lock;
            lock.l_type = F_WRLCK;
            lock.l_whence = SEEK_SET;
            lock.l_start = ftell(f);
            lock.l_len = -len;

            check_error(fcntl(fd, F_GETLK, &lock) != -1, "fcntl");

            char lock_type = 'u';

            if(lock.l_type == F_WRLCK) lock_type = 'w';
            if(lock.l_type == F_RDLCK) lock_type = 'r';

            if(lock_type != 'u') printf("%c %ld\n", lock_type, lock.l_start);
        }
    }

    fclose(f);

    exit(EXIT_SUCCESS);
}
