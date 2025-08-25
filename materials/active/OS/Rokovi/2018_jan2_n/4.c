#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while (0); 

typedef struct {

    int fd;
    char* name;
} epoll_dt;


#define MAX_ACTIVE (10)

int main(int argc, char** argv) {

    check_error(argc > 1, "Bad args");

    int n_fds = argc - 1;

    struct epoll_event* events = (struct epoll_event*) malloc (n_fds * sizeof(struct epoll_event));
    check_error(events != NULL, "Failed to allocate events array");

    int epoll_fd = epoll_create(n_fds);
    check_error(epoll_fd != -1, "Failed to create epoll");

    for(int i = 0; i < n_fds; i ++) {

        int fd = open(argv[i + 1], O_RDONLY | O_NONBLOCK);
        check_error(fd != -1, "Failed to open FIFO file");

        epoll_dt* data = (epoll_dt*) malloc (sizeof(epoll_dt));
        check_error(data != NULL, "Failed to allocate epoll data obejt");

        data->fd = fd;
        data->name = argv[i + 1];

        events[i].events = EPOLLIN | EPOLLHUP | EPOLLERR;
        events[i].data.ptr = data;

        check_error(
            epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &events[i]) != -1,
            "Faile to add epoll entry"
        );

    }

    int active_events = n_fds;
    struct epoll_event triggered_events[MAX_ACTIVE];

    int min_read = INT_MAX;
    char* min_file_name = NULL;

    while(active_events) {

        int triggered = epoll_wait(epoll_fd, triggered_events, MAX_ACTIVE, -1);
        check_error(triggered != -1, "Failed to wait epoll entry");

        for (int i = 0; i < triggered; i ++) {

            if (triggered_events[i].events & EPOLLIN) {

                epoll_dt* data = (epoll_dt*) triggered_events[i].data.ptr;
                
                int fd = data->fd;
                int count_read = 0;
                int c;
                
                
                while(read(fd, &c, 1) > 0) {
                    count_read += 1;
                }

                
                if(count_read < min_read) {
                    min_read = count_read;
                    
                    min_file_name = (char*) realloc (min_file_name, strlen(data->name) + 1);
                    strcpy(min_file_name, data->name);
                }
                

                count_read = 0;
                
            }
            else if (triggered_events[i].events & (EPOLLHUP | EPOLLERR)){

               epoll_dt* data = (epoll_dt*) triggered_events[i].data.ptr;

               int fd = data->fd;

               check_error(
                   epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &triggered_events[i]) != -1,
                   "Failed to delete epoll entry"
               ) ;

               close(fd);

               free(data);

               active_events --;

            }
        }
    }

    printf("%s\n", min_file_name);

    free(min_file_name);
    
    exit(EXIT_SUCCESS);
}