#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define check_error(cond, errMsg) \
    do{ \
        if(!(cond)){ \
            exit(EXIT_FAILURE); \
        } \
    }while(0);

#define ARRAY_MAX 1024

void* get_shm_block(char* path, unsigned* size){

    int fd = shm_open(path, O_RDWR, 0600);
    check_error(fd != -1, "Failed to open shared memory object");

    struct stat f_info;
    check_error(fstat(fd, &f_info) != -1, "Failed to fetch file status");
    *size = f_info.st_size;

    void* addr = 0;
    check_error(
        (addr = mmap(NULL, *size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) != MAP_FAILED,
        "Failed to map memory"
    );

    close(fd);

    return addr;
}

int bin_ones(int x){

    int count = 0;
    while(x != 0){
        if((x & 1) == 1) count ++;
        x = x >> 1;
    }

    return count;
}

typedef struct {
    sem_t inDataReady;
    int array[ARRAY_MAX];
    unsigned arrayLen;
} OsData;

int main(int argc, char** argv){

    check_error(argc == 3, "Bad args");

    unsigned size = 0;
    OsData* data = (OsData*) get_shm_block(argv[1], &size);
    
    check_error(sem_wait(&(data->inDataReady)) != -1, "Failed to wait sem");

    int local_array[ARRAY_MAX];
    int local_array_len = 0;
    int shared_array_len = data->arrayLen;

    for(int i = 0; i < shared_array_len; i ++){
        if(bin_ones(data->array[i]) >= 4){
            local_array[local_array_len] = data->array[i];
            local_array_len += 1;
        } 
    }

    check_error(munmap(data, size) != -1, "Failed to unmap read memory");

    data = (OsData*) get_shm_block(argv[2], &size);

    for(int i = 0; i < local_array_len; i ++){
        data->array[i] = local_array[i];
    }
    data->arrayLen = local_array_len;

    check_error(sem_post(&(data->inDataReady)) != -1, "Failed to post sem");

    check_error(munmap(data, size) != -1, "Failed to unmap write memory");

    exit(EXIT_SUCCESS);

}