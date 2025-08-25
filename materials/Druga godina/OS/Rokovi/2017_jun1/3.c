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

typedef struct {

    int i;
    int j;
    double *v1;
    double *v2;
    int len;

} tin_t;

typedef struct {
    double dot;
} tout_t;

void* thread_func(void* a);
double dot(double* v1, double* v2, int len);

double global_max = -INFINITY;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char** argv) {

    check_error(argc == 1, "Bad args");

    int m;
    int n;  
    int k;

    scanf("%d %d", &n, &m);

    double** mat1 = (double**) malloc(n * sizeof(double*));
    check_error(mat1 != NULL, "malloc1");

    for(int i = 0; i < n; i ++) {

        mat1[i] = (double*) malloc(m * sizeof(double));
        check_error(mat1[i] != NULL, "malloc11");

        for(int j = 0; j < m ; j ++) scanf("%lf", &mat1[i][j]);
    }

    scanf("%d %d", &m, &k);

    double** mat2 = (double**) malloc(k * sizeof(double**));
    check_error(mat2 != NULL, "malloc2");

    for(int i = 0; i < k; i++) {
        mat2[i] = (double*) malloc(m * sizeof(double));
        check_error(mat2[i] != NULL, "malloc22");
    }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < k; j++) scanf("%lf\n", &mat2[j][i]);
    }

    double** product = (double**) malloc(n * sizeof(double**));
    check_error(product != NULL, "malloc product");

    for(int i = 0; i < k; i++) {
        product[i] = (double*) malloc (k *sizeof(double));
        check_error(product[i] != NULL, "malloc product[i]");
    }

    int n_thread = n * k;

    pthread_t* pids = (pthread_t*) malloc(n_thread * sizeof(pthread_t));
    check_error(pids != NULL, "malloc pthread_t");

    tin_t* args = (tin_t*) malloc(n_thread * sizeof(tin_t));
    check_error(args != NULL, "malloc tint_t");

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++) {

            args[i*k + j].i = i;
            args[i*k + j].j = j;
            args[i*k + j].v1 = mat1[i];
            args[i*k + j].v2 = mat2[j];
            args[i*k + j].len = m;

            pthread_create(&pids[i*k + j], NULL, thread_func, &args[i*k + j]);
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++) {

            tout_t* ret_val = NULL;
            pthread_join(pids[i*k + j], (void**)&ret_val);

            printf("%d ", (int)ret_val->dot);

            product[i][j] = ret_val->dot;

            free(ret_val);
        }
        printf("\n");
    }

    printf("%d\n", (int) global_max);

    exit(EXIT_SUCCESS);
}

void* thread_func(void* a) {

    tin_t* args = (tin_t*) a;

    double local_dot = dot(args->v1, args->v2, args->len);

    check_error(pthread_mutex_lock(&mut) != -1, "mutex lock");

    if(global_max < local_dot) {
        global_max = local_dot;
    }

    check_error(pthread_mutex_unlock(&mut) != -1, "mutex unlock");

    tout_t* ret_val = (tout_t*) malloc(sizeof(tout_t*));
    check_error(ret_val != NULL, "malloc tout_t");

    ret_val->dot = local_dot;

    return ret_val;

}

double dot(double* v1, double* v2, int len) {

    double dot = 0;

    /*
    for(int i = 0; i < len; i++) {
        printf("%.1lf ", v1[i]);
    }
    printf("\n");

    for(int i = 0; i < len; i++) {
        printf("%.1lf ", v2[i]);
    }
    printf("\n");
    */

    for(int i = 0; i < len; i++) {

        dot += v1[i] * v2[i];
    }

    return dot;
}