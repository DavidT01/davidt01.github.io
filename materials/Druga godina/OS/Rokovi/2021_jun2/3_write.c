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

void* createMemBlock(char* name, int size) {
    int fd = shm_open(name, O_RDWR | O_CREAT, 0600);
    check_error(fd != -1, "shm_open");

    check_error(ftruncate(fd, size) != -1, "ftruncate");

    void* addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    check_error(addr != MAP_FAILED, "mmap");

    return addr;
}

int main(int argc, char** argv) {
    check_error(argc == 3, "argc");

    osData* inMem = createMemBlock(argv[1], sizeof(osData));
    osData* outMem = createMemBlock(argv[2], sizeof(osData));

    check_error(sem_init(&inMem->inDataReady, 1, 1) != -1, "sem_init");
    check_error(sem_init(&outMem->inDataReady, 1, 0) != -1, "sem_init");

    inMem->arrayLen = 5;
    inMem->array[0] = 1;
    inMem->array[1] = 15;
    inMem->array[2] = 31;
    inMem->array[3] = 32;
    inMem->array[4] = 15;


    check_error(sem_post(&inMem->inDataReady) != -1, "sem_post");

    check_error(sem_wait(&outMem->inDataReady) != -1, "sem_post");

    for(unsigned i = 0; i < outMem->arrayLen; i++)
        printf("%d ", outMem->array[i]);
    printf("\n");

    exit(EXIT_SUCCESS);
}
