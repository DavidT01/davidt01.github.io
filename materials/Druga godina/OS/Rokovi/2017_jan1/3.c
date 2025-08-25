#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

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
        int err_val = err_val; \
        if(err > 0) { \
            errno = err; \
            check_error(0, msg); \
        } \
    } while(0);

typedef struct {

    double* row;
    int len; // len(row)
} tin_t;

double min_element = INFINITY;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void free_all(double** mat, int n);
void* thread_func(void* a);

int main(int argc, char** argv) {

    //argv[1] - putanja ka fajlu u kome je upisana matrica

    check_error(argc == 2, "Bad args");

    int n;
    int m;

    //==========================================================
    
    // Ucitavanje matrice iz fajla

    FILE* f = fopen(argv[1], "r");
    check_error(f != NULL, "fopen");

    fscanf(f, "%d %d", &n, &m);

    double** mat = (double**) malloc(n * sizeof(double*));
    check_error(mat != NULL, "maloc mat");

    for(int i = 0; i < n; i ++) {

        mat[i] = (double*) malloc(m * sizeof(double));
        check_error(mat[i] != NULL, "malloc mat[i]");

        for(int j = 0; j < m; j++) fscanf(f, "%lf", &mat[i][j]);
    }

    fclose(f);

    //==========================================================

    // kreiranje potrebnih resursa za kreiranje niti i pokretanje istih

    pthread_t* tids = (pthread_t*) malloc(n * sizeof(pthread_t));
    check_error(tids != NULL, "malloc tids");

    tin_t* args = (tin_t*) malloc(n * sizeof(tin_t));
    check_error(args != NULL, "malloc args");

    for(int i = 0; i < n; i ++) {

        args[i].row = mat[i];
        args[i].len = m;

        thread_check_error(pthread_create(&tids[i], NULL, thread_func, &args[i]), "pthread_creat");
    }


    //==========================================================

    // Prikupljane rezultata i obrada

    for(int i = 0; i < n; i++) {

        thread_check_error(pthread_join(tids[i], NULL), "pthread_join");
    }

    printf("%lf\n", min_element);

    free(tids);
    free(args);

    free_all(mat, n);

    exit(EXIT_SUCCESS);
}

//==========================================================

// Funkcija za oslobadjanje cele matrice

void free_all(double** mat, int n) {
    for(int i = 0; i < n; i++) free(mat[i]);
    free(mat);
}

//==========================================================

// Funckija za obradu niti

void* thread_func(void* a) {

    tin_t* args = (tin_t*) a;

    double local_min = args->row[0];

    for(int i = 1; i < args->len; i ++) {
        if(args->row[i] < local_min) local_min = args->row[i];
    }

    //printf("%lf\n", local_min);

    thread_check_error(pthread_mutex_lock(&mut), "mutex lock");

    if(local_min < min_element) min_element = local_min;

    thread_check_error(pthread_mutex_unlock(&mut), "mutex unlock");

    return NULL;
}