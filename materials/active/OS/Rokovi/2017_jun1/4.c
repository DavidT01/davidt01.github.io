#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0);

#define MAX_LEN (256)

bool is_num(char* buffer);
bool lock(int fd, int start, int len);

int main(int argc, char** argv) {

    // argv[1] - putanja do fajla iz koga citamo

    check_error(argc == 2, "Bad args");

    // otvaramo fajl strim

    FILE* f = fopen(argv[1], "r");
    check_error(f != NULL, "fopen");

    // citamo rec po rec

    char buffer[MAX_LEN];
    int counter = 0;

    while(fscanf(f, "%s", buffer) != EOF) {

        if(is_num(buffer)) {

            bool locked = lock(f->_fileno, ftell(f), -strlen(buffer));
            if(!locked) counter ++;
        }

    }

    printf("%d\n", counter);

    exit(EXIT_SUCCESS);
}

bool is_num(char* buffer) {

    char* endptr;

    strtol(buffer, &endptr, 10);

    if(*buffer != '\0' && *endptr == '\0') return true;
    else return false;
}

bool lock(int fd, int start, int len) {

    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_start = start;
    lock.l_len = len;
    lock.l_whence = SEEK_SET;

    int ret_val = fcntl(fd, F_SETLK, &lock);

    if(ret_val == -1) {
        if(errno == EACCES || errno == EAGAIN) return true;
        else check_error(0, "fcntl");
    }  
    else return false;
}