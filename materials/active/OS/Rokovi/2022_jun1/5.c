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

void * getMemoryBlock(char* naziv, int* size) {
    int fd = shm_open(naziv, O_RDWR, 0600);
    check_error(fd != -1, "asd");

    struct stat fInfo;
    check_error(fstat(fd, &fInfo) != -1, "...");

    *size = fInfo.st_size;

    void * addr = mmap(NULL, *size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    check_error(addr != MAP_FAILED, "mmap");

    close(fd);

    return addr;
}

int main(int argc, char** argv){
    check_error(argc == 2, "...");

    int size;
    shared_Mem_t* data = getMemoryBlock(argv[1], &size);

    check_error(sem_wait(&data->inDataReady) != -1, "sem_post");

    double sum = 0.0;

    for(unsigned i = 0 ; i < data->arrayLen; i++) {
        sum += 1.0 * data->array[i];
    }

    sum /= 1.0 * data->arrayLen;

    printf("%lf\n", sum);

    check_error(munmap(data, size) != -1, "munmap");

    exit(EXIT_SUCCESS);
}
