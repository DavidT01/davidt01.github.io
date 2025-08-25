#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <libgen.h>

#include <errno.h>
#include <sys/poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <poll.h>

#define check_error(cond, msg) \
    do { \
        if(!(cond)) { \
            perror(msg); \
            exit(EXIT_FAILURE); \
        } \
    } while (0); 

int main(int argc, char** argv) {

    check_error(argc > 1, "Bad args");

    int n_fds = argc - 1;

    struct pollfd* fds = (struct pollfd*) malloc(n_fds * sizeof(struct pollfd));
    check_error(fds != NULL, "Failed to allocate fds array");

    for(int i = 0; i < n_fds; i ++) {

        int fd = open(argv[i + 1], O_RDONLY | O_NONBLOCK);
        check_error(fd != -1, "Failed to open FIFO file");

        fds[i].fd = fd;
        fds[i].events = POLLIN | POLLHUP | POLLERR;
        fds[i].revents = 0;
    }

    int n_active = n_fds;
    int max_count = 0;
    char* max_count_path;

    while(n_active) {

        check_error(
            poll(fds, n_fds, -1), "Failed to poll");

        for(int i = 0; i < n_fds; i ++) {

            int local_cout = 0;

            if(fds[i].revents & POLLIN) {

                char c;
                while(read(fds[i].fd, &c, 1) > 0) local_cout += 1;

                if(local_cout > max_count) {
                    max_count = local_cout;
                    max_count_path = argv[i + 1];
                }

                fds[i].revents = 0;
            }
            else if (fds[i].revents & (POLLHUP | POLLERR)) {

                close(fds[i].fd);

                fds[i].fd = -1;
                fds[i].events = 0;
                fds[i].revents = 0;

                n_active --;
            }
        }
    }

    printf("%s\n", basename(max_count_path));

    exit(EXIT_SUCCESS);
}