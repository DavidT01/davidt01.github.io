#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <pthread.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while (0); 

#define thread_check_error(err, msg) \
    do { \
        int err_val = err; \
        if(err_val > 0) { \
            errno = err_val; \
            check_error(0, msg); \
        } \
    } while (0);

typedef struct {

    char* path;
    char* w;
    int start;
    int thread_len;

} tin_t;

int global_sum = 0;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void* thread_func(void*);
int check_match(FILE*, char*);

int main(int argc, char** argv) {
    
    check_error(argc == 4, "Bad args");

    char* path = argv[1];
    char* w = argv[2];
    int n_thrds = atoi(argv[3]);

    struct stat f_info;
    check_error(stat(path, &f_info) != -1, "Failed to get file status");

    int file_size = (int) f_info.st_size;

    int thread_len = file_size / n_thrds; 

    pthread_t* tids = (pthread_t*) malloc (n_thrds * sizeof(pthread_t));
    check_error(tids != NULL, "Failed to allocate tids array");

    tin_t* args = (tin_t*) malloc(n_thrds * sizeof(tin_t));
    check_error(args != NULL, "Failed to allocate args array");

    for(int i = 0; i < n_thrds; i ++) {

        args[i].path = path;
        args[i].w = w;
        args[i].start = i * thread_len;
        args[i].thread_len = thread_len;

        thread_check_error(
            pthread_create(&tids[i], NULL, thread_func, (void*)&args[i]), "Failed to create thread");
        
    }

    for(int i = 0; i < n_thrds; i ++) {

        thread_check_error(
            pthread_join(tids[i], NULL), "Failed to join thread");
    }

    printf("%d\n", global_sum);

    thread_check_error(
        pthread_mutex_destroy(&mut), "Failed to destory mutex");

    exit(EXIT_SUCCESS);
}

void* thread_func(void* a) {

    tin_t* args = (tin_t*) a;

    int fd = open(args->path, O_RDONLY);
    check_error(fd != -1, "Failed to open file");

    check_error(lseek(fd, args->start, SEEK_SET) != -1, "Failed to seek");

    int local_sum = 0;
    char buffer[args->thread_len + 1];

    check_error(read(fd, buffer, args->thread_len) != -1,  "Failed to read substring from file");
    buffer[args->thread_len] = '\0';

    char* pos = buffer;
    while((pos = strstr(pos, args->w)) != NULL) {
        pos += 1;
        local_sum += 1;
    } 

    thread_check_error(
        pthread_mutex_lock(&mut), "Failed to lock mut");

    global_sum += local_sum;

    thread_check_error(
        pthread_mutex_unlock(&mut), "Failed to unlock mut");

    close(fd);
    return NULL;
}