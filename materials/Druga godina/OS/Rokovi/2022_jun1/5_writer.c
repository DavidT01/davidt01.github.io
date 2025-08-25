#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <semaphore.h>
#include <sys/mman.h>

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while(0)

typedef struct {
    sem_t inDataReady;
    float array[1024];
    unsigned arrayLen;
} shared_Mem_t;

void * createMemoryBlock(char* naziv, int size) {
    int fd = shm_open(naziv, O_RDWR | O_CREAT, 0600);
    check_error(fd != -1, "shm_open");

    check_error(ftruncate(fd, size) != -1, "asdas");

    void * addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    check_error(addr != MAP_FAILED, "mmap");

    close(fd);

    return addr;
}

int main(int argc, char** argv){
    check_error(argc == 2, "...");

    shared_Mem_t* data = createMemoryBlock(argv[1], sizeof(shared_Mem_t));

    check_error(sem_init(&data->inDataReady, 1, 0) != -1, "sem_init");

    data->arrayLen = 3;
    data->array[0] = 1;
    data->array[1] = 1;
    data->array[2] = 2;

    check_error(sem_post(&data->inDataReady) != -1, "sem_post");


    exit(EXIT_SUCCESS);
}
