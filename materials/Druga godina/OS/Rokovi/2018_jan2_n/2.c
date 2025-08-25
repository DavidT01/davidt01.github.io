#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

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

    double x;
    double y;
} point;

typedef struct {

    int ind;
    point* points;
    int n_points; // len(ponits)
} tin_t;

void* thread_func(void*);
double d(point, point);

double globa_min = LONG_MAX; 
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char** argv) {

    int n_points = 0;
    int points_all = 10;
    point* points = (point*) malloc (points_all * sizeof(point));
    check_error(points != NULL, "Failed to allocate point array");

    double x;
    double y;
    while(scanf("%lf", &x) != EOF) {

        scanf("%lf", &y);
        points[n_points].x = x;
        points[n_points].y = y;

        n_points += 1;

        if(n_points == points_all) {

            points_all *= points_all;
            points = (point*) realloc(points, points_all * sizeof(point));
            check_error(points != NULL, "Failed to reallocate points array");
        }
    }

    pthread_t* tids = (pthread_t*) malloc (n_points * sizeof(pthread_t));
    check_error(tids != NULL, "Failed to allocate tids array");

    tin_t* args = (tin_t*) malloc (n_points * sizeof(tin_t));
    check_error(args != NULL, "Failed to allocate args array");

    for(int i = 0; i < n_points; i ++) {

        args[i].ind = i;
        args[i].points = points;
        args[i].n_points = n_points;

        thread_check_error(
            pthread_create(&tids[i], NULL, thread_func, (void*)&args[i]),
            "Failed to create thread"
        );
    }

    for(int i = 0; i < n_points; i ++) {

        thread_check_error(
            pthread_join(tids[i], NULL), 
            "Failed to join thread"
        );
    }

    /*
    for(int i = 0; i < n_points; i ++) {
        printf("%lf %lf\n", points[i].x, points[i].y);
    }
    */

    printf("%lf\n", sqrt(globa_min));

    thread_check_error(
        pthread_mutex_destroy(&mut),
        "Failed to destroy mutex"
    );
    
    exit(EXIT_SUCCESS);
}

void* thread_func(void* a) {

    tin_t* args = (tin_t*) a;

    double local_min = LONG_MAX;
    for(int i = 0; i < args->n_points; i ++) {

        if(i != args->ind) {
            point a = args->points[args->ind];
            point b = args->points[i];

            double dist = d(a, b);
            //printf("%d %d %lf\n", args->ind, i, sqrt(dist));

            if(dist < local_min) local_min = dist;
        }
    }

    thread_check_error(
        pthread_mutex_lock(&mut), 
        "Failed to lock mutex"
    );

    if(local_min < globa_min) globa_min = local_min;

    thread_check_error(
        pthread_mutex_unlock(&mut), 
        "Failed to lock unlock"
    );

}

double d(point a, point b) {

    double ret_val = (b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y);
    return ret_val;
}