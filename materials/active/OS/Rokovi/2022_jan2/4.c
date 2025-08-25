#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include <sys/epoll.h>

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while(0)

typedef struct {
    int index;
    int fd;
} epoll_dt;

#define MAX_ACTIVE 25
#define MAX_SIZE 2048

int main(int argc, char** argv) {
    check_error(argc > 1, "argc");

    int fifoNum = argc - 1;

    int eFd = epoll_create(fifoNum);

    struct epoll_event* evs = malloc(fifoNum * sizeof(struct epoll_event));
    check_error(evs != NULL, "malloc");

    for(int i = 0; i < fifoNum; i++){
        int fd = open(argv[i + 1], O_RDONLY | O_NONBLOCK);
        check_error(fd != -1, "open");

        evs[i].events = EPOLLIN | EPOLLHUP | EPOLLERR;

        epoll_dt* data = malloc(sizeof(epoll_dt));
        data->index = i + 1;
        data->fd = fd;

        evs[i].data.ptr = data;

        check_error(epoll_ctl(eFd, EPOLL_CTL_ADD, fd, &evs[i]) != -1, "ctl");
    }

    struct epoll_event activeEvs[MAX_ACTIVE];
    int aliveFifo = fifoNum;
    char buffer[MAX_SIZE];

    int globalCount = -1;
    int globalIndex = -1;

    while(aliveFifo) {
        int numActive = epoll_wait(eFd, activeEvs, MAX_ACTIVE, -1);
        check_error(numActive != -1, "epoll wait");

        for(int i = 0; i < numActive; i++) {
            epoll_dt* data;

            if(activeEvs[i].events & EPOLLIN) {
                data = activeEvs[i].data.ptr;

                int localCount = 0;
                int readBytes = 0;

                while((readBytes = read(data->fd, buffer, MAX_SIZE)) > 0) {
                    for (int j = 0; j < readBytes; j++) {
                        localCount += isdigit(buffer[j]) ? 1 : 0;
                    }
                }
                check_error(readBytes != -1, "read");

                if(localCount > globalCount) {
                    globalCount = localCount;
                    globalIndex = data->index;
                }

            }
            else if (activeEvs[i].events & (EPOLLHUP | EPOLLERR)) {
                data = activeEvs[i].data.ptr;

                check_error(epoll_ctl(eFd, EPOLL_CTL_DEL, data->fd, &activeEvs[i]) != -1, "ctl");

                close(data->fd);
                free(data);

                aliveFifo--;
            }
        }
    }

    char* name = strrchr(argv[globalIndex], '/');

    printf("%s %d\n", name == NULL ? argv[globalIndex] : name, globalCount);

    free(evs);
    close(eFd);
    exit(EXIT_SUCCESS);
}
