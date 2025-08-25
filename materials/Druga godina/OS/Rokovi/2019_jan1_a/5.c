#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while (0);

#define MAX_LEN (255)

int is_unlocked(int, long, long ,int*);

int main(int argc, char** argv) {
    
    check_error(argc == 3, "Bad args");

    int fd = open(argv[1], O_RDWR);
    check_error(fd != -1, "Failed to open file");
    
    long file_pt = 0;
    long word_pt = 0;

    int buff_pt = 0;
    char buffer[MAX_LEN + 1];

    char c;

    while(read(fd, &c, 1) > 0) {

        if(c == ' ' || c == '\n') {

            buffer[buff_pt] = '\0';
            buff_pt = 0;

            if(strcmp(buffer, argv[2]) == 0) {

                int lock_type = 0;
                if(!is_unlocked(fd, word_pt, strlen(buffer), &lock_type)) {
                    
                    printf("%ld ", word_pt);
                    if(lock_type == F_RDLCK) printf("r\n");
                    else if( lock_type == F_WRLCK) printf("w\n");   
                }
                

            }

            word_pt = file_pt + 1;

        }
        else {

            buffer[buff_pt] = c;
            buff_pt += 1;
        }

        file_pt += 1;
    }

    close(fd);
    exit(EXIT_SUCCESS);

}

int is_unlocked(int fd, long start, long len, int* lock_type) {

    //printf("%ld %ld\n", start, len);

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (off_t)start;
    lock.l_len = (off_t) len;

    check_error(
        fcntl(fd, F_GETLK, &lock) != -1, "Failed to get lock information"
    );

    //if(lock.l_type == F_UNLCK) printf("Nije zaljucan\n");

    if(lock.l_type == F_UNLCK) return 1;
    else {
        *lock_type = lock.l_type;
        return 0;
    }
}