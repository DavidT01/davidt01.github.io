#define _XOPEN_SOURCE 700

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include <semaphore.h>
#include <sys/mman.h>

#define ARRAY_MAX (1024)

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while (0)

typedef struct {
    sem_t inDataReady;
    int array[ARRAY_MAX];
    unsigned arrayLen;
} osData;

void* getMemBlock(char* name, int* size) {
    int fd = shm_open(name, O_RDWR, 0600);
    check_error(fd != -1, "shm_open");

    struct stat fInfo;
    check_error(fstat(fd, &fInfo) != -1, "stat");
    *size = fInfo.st_size;

    void* addr = mmap(NULL, *size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    check_error(addr != MAP_FAILED, "mmap");

    return addr;
}

int checkBits(int x) {
    int mask = 1;
    int num = 0;

    while(mask) {
        if(mask & x) num++;
        mask <<= 1;
    }

    return num >= 4;
}

int main(int argc, char** argv) {
    check_error(argc == 3, "argc");

    int sizeIn = 0;
    int sizeOut = 0;

    osData* inMem = getMemBlock(argv[1], &sizeIn);
    osData* outMem = getMemBlock(argv[2], &sizeOut);

    check_error(sem_wait(&inMem->inDataReady) != -1, "sem_post");

    int outLen = 0;

    for(unsigned i = 0; i < inMem->arrayLen; i++){
        if(checkBits(inMem->array[i])) {
            outMem->array[outLen] = inMem->array[i];
            outLen++;
        }
    }
    outMem->arrayLen = outLen;

    check_error(sem_post(&outMem->inDataReady) != -1, "sem_post");

    check_error(munmap(inMem, sizeIn) != -1, "munmap");
    check_error(munmap(outMem, sizeIn) != -1, "munmap");

    exit(EXIT_SUCCESS);
}
