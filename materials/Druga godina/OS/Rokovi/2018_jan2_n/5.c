#define _XOPNE_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <semaphore.h>
#include <sys/mman.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while (0); 

#define ARRAY_MAX (1024)

typedef struct {
    sem_t inDataReady;
    sem_t dataProcessed;
    char str[ARRAY_MAX];
} OsInputData;

void* get_shm_block(char* path, int* size);
char* reverse(char*);

int main(int argc, char** argv) {

    check_error(argc == 2, "Bad args");

    int size = 0;

    printf("%s\n",reverse("proba"));

    OsInputData* data = (OsInputData*) get_shm_block(argv[1], &size);

    char* reversed_str = reverse(data->str);

    check_error(sem_wait(&data->inDataReady) != -1, "Failed to wait sem");

    strcpy(data->str, reversed_str);

    check_error(sem_post(&data->dataProcessed) != -1, "Failed to post sem");

    check_error(munmap(data, size) != -1, "Failed to unmap mem");

    free(reversed_str);

    exit(EXIT_SUCCESS);
}

void* get_shm_block(char* path, int* size) {

    int fd = shm_open(path, O_RDWR, 0600);
    check_error(fd != -1, "Failed to open shm file");

    struct stat fStat;
    check_error(fstat(fd, &fStat) != -1, "Faile to stat shm file");

    *size = fStat.st_size;

    void* ret_val;
    check_error(
        (ret_val = mmap(ret_val, *size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) != MAP_FAILED,
        "Failed to map memory"
    );

    return ret_val;
}

char* reverse(char* str) {

    int len = strlen(str);

    char* ret_val = (char*) malloc (len + 1);

    int i = len - 1;
    int j = 0;

    while(i >= 0) {

        ret_val[j] = str[i];

        j ++;
        i --;
    }

    ret_val[j];

    return ret_val;
}