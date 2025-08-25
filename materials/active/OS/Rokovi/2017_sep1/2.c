#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <pthread.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0);

#define thread_check_error(err, msg) \
    do { \
        int err_val = err; \
        if(err_val > 0) { \
            errno = err_val; \
            check_error(0, msg); \
        } \
    } while(0); 

typedef struct{

    int ind;
    int n;
    int** mat;;
} tin_t;

void free_all(int**, int);
void* thread_func(void*);

int max_u_stepen = 0;
int max_ind = 0;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char** argv) {

    int n; scanf("%d", &n);

    int** mat = (int**) malloc (n * sizeof(int*));

    for(int i = 0; i < n; i ++) {
        mat[i] = (int*) malloc(n * sizeof(int));
        for(int j = 0; j < n; j ++) {
            scanf("%d", &mat[i][j]);
        }
    }

    pthread_t* tids = (pthread_t*) malloc(n * sizeof(pthread_t));
    check_error(tids != NULL, "Failed to allocate tids array");

    tin_t* args = (tin_t*) malloc(n * sizeof(tin_t));
    check_error(args != NULL, "Failed to allocate args array");

    for(int i = 0; i < n; i++) {

        args[i].ind = i;
        args[i].n = n;
        args[i].mat = mat;

        thread_check_error(
            pthread_create(&tids[i], NULL, thread_func, &args[i]), "Failed to create thread");
    }

    for(int i = 0; i < n; i++) {

        thread_check_error(
            pthread_join(tids[i], NULL), "Failed to join threads");
    }

    printf("%d\n", max_ind);

    free_all(mat, n);
    exit(EXIT_SUCCESS);
}

void* thread_func(void* a) {

    tin_t* args = (tin_t*) a;
    
    int local_count = 0;
    int j = args->ind;

    for(int i = 0; i < args->n; i ++) {

        if(args->mat[i][j] == 1) local_count += 1;
    }

    thread_check_error(
        pthread_mutex_lock(&mut), "Failed to lock mutex");
    
    if(local_count > max_u_stepen) {
        max_u_stepen = local_count;
        max_ind = args->ind;
    }

    thread_check_error(
        pthread_mutex_unlock(&mut), "Failed to unlock mutes");

    return NULL;
}

void free_all(int**mat, int n) {

    for(int i = 0; i < n; i ++) {
        free(mat[i]);
    }
    free(mat);
}