#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <semaphore.h>

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
    int array[ARRAY_MAX];
    unsigned arrayLen;
} os_data_input;

void* get_block(char* path, int* size);
bool has_four_ones(int x);

int main(int argc, char** argv) {

    check_error(argc == 2, "Bad args");

    int size;
    os_data_input* data = get_block(argv[1], &size);

    check_error(sem_wait(&data->inDataReady) != -1, "sem_wait");

    for(int i = 0; i < data->arrayLen; i++) {

        if(has_four_ones(data->array[i])) {
            printf("%d ", data->array[i]);
        }
    }
    printf("\n");

    exit(EXIT_SUCCESS);
}

void* get_block(char* path, int* size) {

    int fd = shm_open(path, O_RDWR, 0600);
    check_error(fd != -1, "shm_open");

    struct stat f_stat;
    check_error(fstat(fd, &f_stat) != -1, "fstat");
    *size = f_stat.st_size;

    void* ret_val;

    check_error(
        (ret_val = mmap(NULL, *size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) != MAP_FAILED, 
        "mmap");

    return ret_val;
}

bool has_four_ones(int x) {

    int counter = 0;
    while(x != 0) {

        if((x & 1) != 0) counter++;
        x >>= 1;
    }

    if(counter >= 4) return true;
    else return false;
}