#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

#define MAX_LEN (1024)

bool is_lock(char* file, int start, int len);
void lock(char* file, int start, int len);

int main(int argc, char** argv) {

    // argv[1] - putanja do fajla koji obradjujemo
    // argv[2] - prva rec
    // argv[3] - druga rec

    check_error(argc == 4, "Bad args");

    FILE* f = fopen(argv[1], "r+");
    check_error(f != NULL, "Failed to open file");

    char buffer[MAX_LEN];
    int buffer_len;
    int brojac = 0;

    while(fscanf(f, "%s", buffer) != EOF) {

        buffer_len = strlen(buffer);

        if(!is_lock(argv[1], ftell(f), -buffer_len)){

            if (strcmp(buffer, argv[2]) == 0) {
                
                lock(argv[1], ftell(f), -buffer_len);

                fseek(f, -buffer_len, SEEK_CUR);

                fprintf(f, "%s ", argv[3]);
            }
        }
        else {
            brojac ++;
        }

    }

    printf("%d\n", brojac);
    fclose(f);

    exit(EXIT_SUCCESS);
}

bool is_lock(char* file, int start, int len) {

    int fd = open(file, O_RDWR);
    check_error(fd != -1, "Failed to open file descriptor");

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_start = start;
    lock.l_len = len;
    lock.l_whence = SEEK_SET;

    check_error(fcntl(fd, F_GETLK, &lock) != -1, "Faile to get lock");

    close(fd);

    if(lock.l_type == F_UNLCK) return false;
    else return true;
}

void lock(char* file, int start, int len) {

    int fd = open(file, O_RDWR);
    check_error(fd != -1, "Failed to open file descriptor");

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_start = start;
    lock.l_len = len;
    lock.l_whence = SEEK_SET;

    check_error(fcntl(fd, F_SETLK, &lock) != -1, "Faile to get lock");
}