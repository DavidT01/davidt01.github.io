#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/mman.h>
#include <semaphore.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while (0); 

#define ARRAY_MAX 1024

typedef struct {
    sem_t inDataReady;
    sem_t dataProcessed;
    char str[ARRAY_MAX];
} OsInputData;

void* get_shm_block(char* parth, int* size);
char* inv(char*);

int main(int argc, char** argv) {

    check_error(argc == 2, "Bad args");

    int size = 0;
    OsInputData* data = (OsInputData*) get_shm_block(argv[1], &size);

    int ret;

    sem_wait(&data->inDataReady);

    //printf("%s\n", data->str);
    char* inv_case = inv(data->str);
   
    strcpy(data->str, inv_case);
    //printf("%s\n", data->str);

    sem_post(&data->dataProcessed);

    free(inv_case);
    shm_unlink(argv[1]);

    check_error(munlock(data, size) != -1, "Failed to unmap");

    exit(EXIT_SUCCESS);
}

void* get_shm_block(char* path, int* size) {

    int fd = shm_open(path, O_RDWR, 0600);
    check_error(fd != -1, "Failed to open shm file");

    struct stat f_stat;
    check_error(fstat(fd, &f_stat) != -1, "Failed to stat shm file");
    *size = f_stat.st_size;

    void* ret_val = NULL;
    check_error(
        (ret_val = mmap(NULL, *size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) != MAP_FAILED, 
        "Failed to map shared memery");

    return ret_val;
}

char* inv(char* buffer) {

    int buffer_len = strlen(buffer);

    char* ret_val = (char*) malloc(buffer_len + 1);

    for(int i = 0; i < buffer_len; i ++) {

        char c = buffer[i];
        if(isalpha(c)) {
            if(islower(c)) ret_val[i] = toupper(c);
            else if (isupper(c)) ret_val[i] = tolower(c);
        }
        else {
            ret_val[i] = buffer[i];
        }

    }
    ret_val[buffer_len] = '\0';

    return ret_val;
}