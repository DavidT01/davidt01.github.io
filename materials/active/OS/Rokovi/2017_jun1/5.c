#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    float array[ARRAY_MAX];
    unsigned arrayLen;
} os_input_data;

void* get_shm_block(const char* path, int* size);

int main(int argc, char** argv) {

    // argv[1] - ime objekta deljenej memorije

    check_error(argc == 2, "Bad args");

    int size;
    os_input_data* data = (os_input_data*) get_shm_block(argv[1], &size);

    check_error(sem_wait(&data->inDataReady) != -1, "sem_wait");

    float mi = 0;

    for(int i = 0; i < data->arrayLen; i++) {

        mi += data->array[i];
    }

    mi /= data->arrayLen;

    float devijacija = 0;

    for(int i = 0; i < data->arrayLen; i++) {

        devijacija += pow(data->array[i] - mi, 2);
    }\

    devijacija /= data->arrayLen;
    devijacija = sqrtf(devijacija);

    printf("%f\n", devijacija);

    check_error(munmap(data, size) != -1, "munmap");

    exit(EXIT_SUCCESS);
}

void* get_shm_block(const char* path, int* size) {

    int fd = shm_open(path, O_RDWR, 0600);
    check_error(fd != -1, "shm_ope");

    struct stat shm_stat;
    check_error(fstat(fd, &shm_stat) != -1, "fstat");

    *size = shm_stat.st_size;

    void* ret_val;

    ret_val = mmap(NULL, *size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    check_error(ret_val != MAP_FAILED, "mmap");

    return ret_val;
}