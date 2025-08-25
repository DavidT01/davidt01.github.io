#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>

#include <errno.h>
#include <poll.h>
#include <sys/poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while (0);

int count_a(int);

int main(int argc, char** argv) {

    check_error(argc > 1, "Bad args");

    int n_pfds = argc - 1;

    struct pollfd* pfds = (struct pollfd*) malloc (n_pfds * sizeof(struct pollfd));
    check_error(pfds != NULL, "Failed to allocate poll fds array");

    for (int i = 0; i < n_pfds; i ++) {

        int fd = open(argv[i + 1], O_RDONLY | O_NONBLOCK);
        check_error(fd != -1, "Failed to open file");

        pfds[i].fd = fd;
        pfds[i].events = POLLIN | POLLERR | POLLHUP;
        pfds[i].revents = 0;
    }

    int activeFds = n_pfds;

    int max_count = 0;
    int max_ind = -1;

    while(activeFds) {

        check_error(poll(pfds, n_pfds, -1) != -1, "Failed to poll");

        for (int i = 0; i < n_pfds; i ++) {

            if(pfds[i].revents & POLLIN) {

                int count = count_a(pfds[i].fd);

                if(count > max_count) {
                    max_count = count;
                    max_ind = i;
                }

                pfds[i].revents = 0;
            }
            else if (pfds[i].revents & (POLLHUP | POLLERR)) {

                close(pfds[i].fd);

                pfds[i].fd = -1;
                pfds[i].events = 0;
                pfds[i].revents = 0;

                activeFds --;
            }
        }

    }

    printf("%s %d\n", basename(argv[max_ind + 1]), max_count);
    
    exit(EXIT_SUCCESS);
}

int count_a(int fd) {

    char c;
    int count = 0;

    while(read(fd, &c, 1) > 0) {

        if(c == 'a') count += 1;
    }

    return count;
}