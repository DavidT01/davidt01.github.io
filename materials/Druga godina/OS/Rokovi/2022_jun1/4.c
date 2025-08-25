#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <pthread.h>

#include <string.h>
#include <limits.h>

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while(0)

#define check_pthread(err, userMsg)\
        do {\
            int _err = (int) err;\
            if(_err > 0) {\
                check_error(0, userMsg);\
            }\
        } while (0)

#define MAX_SIZE (1024)

pthread_mutex_t globalLock = PTHREAD_MUTEX_INITIALIZER;
int globalMax = INT_MIN;

typedef struct {
    char niz[MAX_SIZE];
    int n;
} input_Data_t;

void* proccessThread(void * arg) {
    input_Data_t* data = (input_Data_t*) arg;

    int localMax = INT_MIN;

    for(int i = 0; i < data->n; i++)
        if(localMax < data->niz[i])
            localMax = data->niz[i];

    check_pthread(pthread_mutex_lock(&globalLock), "lock");

    if(globalMax < localMax)
        globalMax = localMax;

    check_pthread(pthread_mutex_unlock(&globalLock), "unlock");

    return NULL;
}

int main(int argc, char** argv){
    check_error(argc == 2, "argc");

    FILE* f = fopen(argv[1], "r");
    check_error(f != NULL, "fopen");

    int line_num = 0;
    fscanf(f, "%d", &line_num);

    pthread_t* pt_ids = malloc(line_num * sizeof(pthread_t));
    check_error(pt_ids != NULL, "pt_ids");

    input_Data_t* args = malloc(line_num * sizeof(input_Data_t));
    check_error(args != NULL, "args");

    for(int i = 0; i < line_num; i++) {
        int n = 0;
        fscanf(f, "%d", &n);

        args[i].n = n;

        for(int j = 0; j < n; j++) {
            int tmp;
            fscanf(f, "%d", &tmp);
            args[i].niz[j] = tmp;
        }

        check_pthread(pthread_create(&pt_ids[i], NULL, proccessThread, &args[i]), "pthread_create");
    }

    for(int i = 0; i < line_num; i++) {
        check_pthread(pthread_join(pt_ids[i], NULL), "pthread_join");
    }

    printf("%d\n", globalMax);

    fclose(f);
    free(pt_ids);
    free(args);

    exit(EXIT_SUCCESS);
}
