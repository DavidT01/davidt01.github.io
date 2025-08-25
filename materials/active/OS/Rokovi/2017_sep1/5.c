#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <semaphore.h>
#include <sys/mman.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0);

#define ARRAY_MAX (1024)

typedef struct {
    sem_t inDataReady;
    //sem_t dataProccessed;
    int array[ARRAY_MAX];
    unsigned arrayLen;
} OsInputData;

void* get_shm_block(char* path, int* size);
int is_power_three(int x);

int main(int argc, char** argv) {

    check_error(argc == 2, "Bad args");

    int size = 0;
    OsInputData* data = (OsInputData*) get_shm_block(argv[1], &size);

    check_error(sem_wait(&data->inDataReady) != -1, "Faiel to wait sem");

    for(int i = 0; i < data->arrayLen; i ++) {
        if(is_power_three(data->array[i])) {
            printf("%d ", data->array[i]);
        }
    }
    printf("\n");

    //sem_post(&data->dataProccessed);

    exit(EXIT_SUCCESS);
}

void* get_shm_block(char* path, int* size) {

    int fd = shm_open(path, O_RDWR, 0600);
    check_error(fd != -1, "Failed to open shm file");

    struct stat f_stat;
    check_error(fstat(fd, &f_stat) != -1, "Failed to stat file");

    *size = f_stat.st_size;

    void* ret_val;
    
    check_error(
        (ret_val = mmap(NULL, *size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) != MAP_FAILED, 
        "Failed to map");

    return ret_val;
}

int is_power_three(int x) {

    if(x == 1) return 1;

    while(1) {

        if(x % 3 == 0)
            x /= 3;
        else return 0;

        if(x == 1) return 1;
    }
}