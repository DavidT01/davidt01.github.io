#define _XOPEN_SOURCE 700

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include <errno.h>

#define MAX_SIZE 256

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while(0)

int goodWord(char* word) {
    for(int i = 0; word[i] != 0; i++)
        if(!isupper(word[i]))
            return 0;
    return 1;
}

int main(int argc, char** argv) {
    check_error(argc == 2, "argc");

    int fd = open(argv[1], O_RDWR);
    check_error(fd != -1, "open");

    FILE* f = fdopen(fd, "r+");
    check_error(f != NULL, "fopen");


        struct flock lock;
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 10;

        int retVal = fcntl(fd, F_SETLK, &lock);

    sleep(30);

    fclose(f);
    exit(EXIT_SUCCESS);
}
