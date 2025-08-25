#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
        int err_val = err;\
        if (err_val > 0) { \
            errno = err_val; \
            check_error(0, msg); \
        } \
    } while(0);

typedef struct {

    char* path;
    int letter; // a = 0, b = 1, ...
} tin_t;

typedef struct {

    int letter;
    char count;
} tout_t;

int max_count = 0;
char max_letter = 0;
pthread_mutex_t max_mut = PTHREAD_MUTEX_INITIALIZER;

void* thread_func(void*);

int main(int argc, char** argv) {
    
    check_error(argc == 2, "Bad args");

    pthread_t* tids = (pthread_t*) malloc(26 * sizeof(pthread_t));
    check_error(tids != NULL, "Failed to alocate pids array");


    tin_t* args = (tin_t*) malloc(26 * sizeof(tin_t));
    check_error(args != NULL, "Failed to allocate args array");

    int hist[26];

    for(int i = 0; i < 26; i ++) {

        args[i].path = argv[1];
        args[i].letter = i;

        thread_check_error(
            pthread_create(&tids[i], NULL, thread_func, &args[i]), 
            "Failed to create thread"
        );
    }

    for(int i = 0; i < 26; i ++) {

        tout_t* ret_val;

        thread_check_error(
            pthread_join(tids[i], (void**)&ret_val),
            "Failed to join thread"
        )

        hist[ret_val->letter] = ret_val->count;
        
        free(ret_val);
    }

    for(int i = 0; i < 26; i ++) printf("%d ", hist[i]);
    printf("\n");

    printf("%c\n", max_letter);

    exit(EXIT_SUCCESS);
}

void* thread_func(void* a) {

    tin_t* args = (tin_t*)a;

    FILE* f = fopen(args->path, "r");
    check_error(f != NULL, "Failed to open file");

    int local_coutner = 0;
    char find_c = 'a' + args->letter;
    char temp_c;

    while((temp_c = fgetc(f)) != EOF) {
        if (tolower(temp_c) == tolower(find_c)) local_coutner += 1;
    }

    thread_check_error(pthread_mutex_lock(&max_mut), "Failed to lock mutex");

    if(local_coutner > max_count) {
        max_count = local_coutner;
        max_letter = find_c;
    }
    
    thread_check_error(pthread_mutex_unlock(&max_mut), "Failed to unlock mutex");

    tout_t* ret_val = (tout_t*) malloc(sizeof(tout_t));
    check_error(ret_val != NULL, "Failed to allocate ret val struct");

    ret_val->letter = args->letter;
    ret_val->count = local_coutner;

    fclose(f);
    
    return (void*)ret_val;
}