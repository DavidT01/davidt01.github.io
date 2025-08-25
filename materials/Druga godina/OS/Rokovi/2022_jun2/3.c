#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while (0)

#define check_pthread(err, userMsg)\
    do {\
        int _err = (int) err;\
        if(_err > 0) {\
            check_error(0, userMsg);\
        }\
    } while (0)

unsigned* niz = NULL;
unsigned globalSum = 0;
pthread_mutex_t globalLock = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int index;
} pthread_input_t;

void* proccesThread(void* arg) {
    pthread_input_t* data = (pthread_input_t*) arg;

    char num[30];
    sprintf(num, "%u", niz[data->index]);
    int len = strlen(num);
    char tmp = num[len - 1];
    num[len - 1] = num[0];
    num[0] = tmp;

    unsigned localNum = atoi(num);
    niz[data->index] = localNum;

    check_pthread(pthread_mutex_lock(&globalLock), "lock");
    globalSum += localNum;
    check_pthread(pthread_mutex_unlock(&globalLock), "unlock");

    return data;
}

int main(int argc, char** argv) {
    check_error(argc == 1, "argc");
    (void) argv;

    int n;
    scanf("%d", &n);

    pthread_t* pt_ids = malloc(n * sizeof(pthread_t));
    check_error(pt_ids != NULL, "malloc");

    pthread_input_t* args = malloc(n * sizeof(pthread_input_t));
    check_error(args != NULL, "malloc");

    niz = malloc(n * sizeof(int));
    check_error(niz != NULL, "malloc");

    for(int i = 0; i < n; i++) {
        scanf("%d", &niz[i]);
        args[i].index = i;
        check_pthread(pthread_create(&pt_ids[i], NULL, proccesThread, &args[i]), "pc");
    }

    for(int i = 0; i < n; i++) {
        check_pthread(pthread_join(pt_ids[i], NULL), "pc");
    }

    for(int i = 0; i < n; i++)
        printf("%u ", niz[i]);
    printf("\n");

    printf("%d\n", globalSum);

    free(niz);
    free(args);
    free(pt_ids);

    exit(EXIT_SUCCESS);
}
