#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <errno.h>
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
        int errval = err; \
        if(errval > 0) { \
            errno = errval; \
            check_error(0, msg); \
        }\
    } while(0); 

typedef struct {
    float** vectors;
    int n_vectors; // len(vectors)
    int vector_len; // len(vectors[i])
    int start;
    int to_calc;
} tin_t;

typedef struct {
    float norm;
} tout_t;

void free_all(float**, int);
void* thread_func(void*);

int main(int argc, char** argv) {

    int m; scanf("%d", &m);
    int n; scanf("%d", &n);
    int k; scanf("%d", &k);

    float** vectors = (float**) malloc (m * sizeof(float*));
    check_error(vectors != NULL, "Failed to allocate vectors array");

    pthread_t* tids = (pthread_t*) malloc (k * sizeof(pthread_t));
    check_error(tids != NULL, "Failed to allocate tid array");

    tin_t* args = (tin_t*) malloc (k * sizeof(tin_t));
    check_error(args != NULL, "Failed to allocate args array");

    for(int i = 0; i < m; i ++) {
        vectors[i] = (float*) malloc (n * sizeof(float));
        check_error(vectors[i] != NULL, "Failed to allocate one vector");

        for(int j = 0; j < n; j ++) {
            scanf("%f", &vectors[i][j]);
        }
    }

    int vectors_per_thread = m / k;

    for(int i = 0; i < k; i++) {

        args[i].vectors = vectors;
        args[i].n_vectors = m;
        args[i].vector_len = n;
        args[i].start = i * vectors_per_thread;
        args[i].to_calc = vectors_per_thread;

        thread_check_error(
            pthread_create(&tids[i], NULL, thread_func, &args[i]),
            "Failed to run thread"
        );
    }

    float max = 0;
    int max_thread = 0;

    for( int i = 0; i < k; i++) {

        tout_t* ret_val = NULL;
        thread_check_error(
            pthread_join(tids[i], (void**)&ret_val),
            "Failed to join thread"
        );

        if(ret_val->norm > max) {
            max_thread = i;
            max = ret_val->norm;
        }

        free(ret_val);
    }

    printf("%d %f\n", max_thread, max);

    free(tids);
    free(args);
    free_all(vectors, m);
    
}

float norm(float* vector, int n) {
    
    float square_sume = 0;
    for(int i = 0; i < n;i ++) {
        square_sume += vector[i] * vector[i];
    }
    
    return sqrt(square_sume);
}

void* thread_func(void* a) {

    tin_t* args = (tin_t*) a;
    float local_max = 0;
    for(int i = 0; i < args->to_calc; i ++) {

        float vnorm = norm(args->vectors[args->start + i], args->vector_len);
        if(vnorm > local_max) local_max = vnorm;
    }

    tout_t* ret_val = (tout_t*) malloc (sizeof(tout_t));
    ret_val->norm = local_max;

    return ret_val;
}

void free_all(float** vectors, int m) {
    
    for(int i = 0; i < m; i ++) free(vectors[i]);
    free(vectors);
}