#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>

#define ARRAY_MAX 1024

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while (0);

typedef struct {

    sem_t dataProcessingFinished;
    int array[ARRAY_MAX];
    unsigned arrayLen;
} OsInputData;

int usr1 = 0;
int usr2 = 0;

void* get_mem_block(char* path, unsigned* size);

void sighandler(int sig) {

    if(sig == SIGUSR1) usr1 = 1;
    else if(sig == SIGUSR2) usr2 = 1;
}

int main(int argc, char** argv) {

    check_error(argc == 2, "Bad args");

    unsigned size = 0;
    OsInputData* data = (OsInputData*) get_mem_block(argv[1], &size);

    signal(SIGUSR1, sighandler);
    signal(SIGUSR2, sighandler);

    pause();

    if(usr1 == 1) {
        usr1 = 0;

        for(int i = 0; i < data->arrayLen; i ++) {
            data->array[i] = - data->array[i];
        }

    }
    else if (usr2 == 1) {
        usr2 = 0;

        for(int i = 0; i < data->arrayLen; i ++) {
            data->array[i] *= 2;
        }
    }

    sem_post(&data->dataProcessingFinished);

    exit(EXIT_SUCCESS);
    
}

void* get_mem_block(char* path, unsigned* size) {

    int fd = shm_open(path, O_RDWR, 0600);
    check_error(fd != -1, "Failed to open shared memory file");

    struct stat f_info;
    check_error(fstat(fd, &f_info) != -1, "Failed to stat file");
    *size = f_info.st_size;

    void* addr;
    check_error(
        (addr = mmap(NULL, *size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) != MAP_FAILED,
        "Failed to map"
    );

    return addr;
}