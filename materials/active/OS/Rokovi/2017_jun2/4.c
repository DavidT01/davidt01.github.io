#define _XOPEN_SOURCE 700
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <libgen.h>

#include <sys/poll.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <poll.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while(0);

int get_max(int fd);

int main(int argc, char** argv) {

    // argv[1...] - fajlove koje nadgledamo

    check_error(argc > 1, "Bad args");

    int n_fds = argc - 1;

    struct pollfd* fds = (struct pollfd*) malloc(n_fds * sizeof(struct pollfd));
    check_error(fds != NULL, "Failed to allocate fds array");

    for(int i = 0; i < n_fds; i++) {

        int fd = open(argv[i + 1], O_RDONLY | O_NONBLOCK);
        check_error(fd != -1, "Failed to open file");
        
        fds[i].fd = fd;
        fds[i].events = POLLIN | POLLERR | POLLHUP;
        fds[i].revents = 0;
    }

    //printf("Data loaded\n");

    int active_fds = n_fds;
    int max = -INT_MAX;
    int max_ind;

    while(active_fds > 0) {

        check_error(poll(fds, n_fds, -1) != -1, "Failed to poll");

        for(int i = 0; i < n_fds; i ++) {

            if(fds[i].revents & POLLIN) {

                int file_max = get_max(fds[i].fd);
                //printf("%d\n", file_max);

                if(file_max > max){
                    max = file_max;
                    max_ind = i;
                } 

                fds[i].revents = 0;
            }
            else if(fds[i].revents & (POLLERR | POLLHUP)) {

                //close(fds[i].fd);

                fds[i].fd = -1;
                fds[i].events = 0;
                fds[i].revents = 0;

                active_fds--;
                //printf("Fd closed \n");
            }
        }
    }

    printf("%d %s\n", max, basename(argv[max_ind + 1]));

    exit(EXIT_SUCCESS);
}

int get_max(int fd) {

    FILE* f = fdopen(fd, "r");
    check_error(f != NULL, "Failed to open file stream");

    int num;
    int local_max = -INT_MAX;

    while(fscanf(f, "%d", &num) != EOF) {

        if(num > local_max) local_max = num;
    }

    return local_max;

}