#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <errno.h>
#include <pthread.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            exit(EXIT_FAILURE); \
        } \
    } while (0);

#define thread_check_error(err, msg) \
    do{ \
        int err_val = err; \
        if(err_val > 0){ \
            errno = err_val; \
            check_error(0, msg); \
        } \
    } while(0); 

typedef struct {

    double* row;
    int n; // len(row)
    double p;
} tin_t;

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
double global_suma = 0;

void free_all(double**, int);
void* thread_func(void* args);

int main(int argc, char** argv) {

    double p; scanf("%lf", &p);
    int m; scanf("%d", &m);
    int n; scanf("%d", &n);

    double** mat = (double**) malloc (m * sizeof(double*));
    check_error(mat != NULL, "Failed to allocate matrix");

    for(int i = 0; i < m; i ++) {

        mat[i] = (double*) malloc (n * sizeof(double));
        check_error(mat[i] != NULL, "Failed to allocate row");
        
        for(int j = 0; j < n; j ++) 
            scanf("%lf", &mat[i][j]);
    }

    pthread_t* tids = (pthread_t*) malloc (m * sizeof(pthread_t));
    check_error(tids != NULL, "Failed to allocate tid array");

    tin_t* args = (tin_t*) malloc (m * sizeof(tin_t));
    check_error(args != NULL, "Failed to allocate args array");

    for(int i = 0; i < m; i ++) {

        args[i].row = mat[i];
        args[i].n = n;
        args[i].p = p;

        thread_check_error(
            pthread_create(&tids[i], NULL, thread_func, (void*)&args[i]),
            "Failed to create thread"
        );
    }

    for(int i = 0; i < m; i ++) {

        thread_check_error(
            pthread_join(tids[i], NULL),
            "Failed to join thread"
        ); 

    }

    //printf("%lf\n", global_suma);
    double p_norm = pow(global_suma, 1/p);

    printf("%lf\n", p_norm);

    free(tids);
    free(args);
    free_all(mat, m);

    exit(EXIT_SUCCESS);
}

void free_all(double** mat, int m) {

    for(int i = 0; i < m ; i ++) {
        free(mat[i]);
    }
    free(mat);
}

void* thread_func(void* a) {

    tin_t* args = (tin_t*) a;

    double suma = 0; 

    for(int i = 0; i < args->n; i ++) {
        //printf("%lf na %lf = %lf\n", args->row[i], args->p, pow(args->row[i], args->p));
        suma += pow(fabs(args->row[i]), args->p);
    }

    //printf("%lf\n", suma);

    thread_check_error(
        pthread_mutex_lock(&mut),
        "Failed to lock mutex"
    );
    
    global_suma += suma;

    thread_check_error(
        pthread_mutex_unlock(&mut),
        "Failed to unlock mutex"
    );

    return NULL;

}
