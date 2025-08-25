#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/epoll.h>

#define MAX_SIZE (2048)

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while (0)

typedef struct {
    int fd;
    int index;
    FILE* f_in;
} epoll_dt;

int main(int argc, char** argv) {
    check_error(argc > 1, "argc");

    int fifo_num = argc - 1;

    int eFd = epoll_create(fifo_num);
    check_error(eFd != -1, "epoll_create");

    struct epoll_event* evs = malloc(fifo_num * sizeof(struct epoll_event));
    check_error(evs != NULL, "malloc");

    for(int i = 0; i < fifo_num; i++) {
        int fd = open(argv[i + 1], O_RDONLY | O_NONBLOCK);
        check_error(fd != -1, "open");

        evs[i].events = EPOLLIN | EPOLLHUP | EPOLLERR;

        epoll_dt* data = malloc(sizeof(epoll_dt));
        check_error(data != NULL, "malloc");

        data->fd = fd;
        data->index = i + 1;
        data->f_in = fdopen(fd, "r");
        check_error(data->f_in != NULL, "adsadsad");

        evs[i].data.ptr = data;

        check_error(epoll_ctl(eFd, EPOLL_CTL_ADD, fd, &evs[i]) != -1, "ctl");
    }

    int alive_fifo = fifo_num;
    char buffer[MAX_SIZE];
    struct epoll_event activeEvs[20];

    int globalCount = -1;
    int globalIndex = -1;

    while(alive_fifo) {
        int num_active = epoll_wait(eFd, activeEvs, 20, -1);
        check_error(num_active != -1, "epoll_wait");

        for(int i = 0; i < num_active; i++) {
            if(activeEvs[i].events & EPOLLIN) {
                epoll_dt* data = (epoll_dt*) activeEvs[i].data.ptr;
                int index = data->index;
                FILE* f_in = data->f_in;

                int localCount = 0;

                while(fscanf(f_in, "%s", buffer) == 1)
                    localCount++;

                if(localCount > globalCount) {
                    globalCount = localCount;
                    globalIndex = index;
                }

            }
            else if(activeEvs[i].events & (EPOLLHUP | EPOLLERR)){
                epoll_dt* data = (epoll_dt*) activeEvs[i].data.ptr;
                int fd = data->fd;
                FILE* f_in = data->f_in;

                check_error(epoll_ctl(eFd, EPOLL_CTL_DEL, fd, &activeEvs[i]) != -1, "ctl");

                fclose(f_in);
                free(data);

                alive_fifo--;
            }
        }
    }

    char * name = strrchr(argv[globalIndex], '/');
    printf("%s ", name == NULL ? argv[globalIndex] : name);
    printf("%d\n", globalCount);

    close(eFd);
    free(evs);

    exit(EXIT_SUCCESS);
}
