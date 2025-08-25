#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ftw.h>

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while (0)

#define MAX_NAME (512)

int proccesFile(const char *fpath, const struct stat *sb,int typeflag, struct FTW *ftw) {
    if(S_ISDIR(sb->st_mode)) {
        if(!(S_IWGRP & sb->st_mode) && !(S_IWOTH & sb->st_mode)) {
            if(strncmp(fpath + ftw->base, "test_", 5) == 0) {
                printf("%s ", fpath + ftw->base);
            }
        }
    }

    return 0;
}

int main(int argc, char** argv) {
    check_error(argc == 2, "argc");

    struct stat fInfo;
    check_error(stat(argv[1], &fInfo) != -1, "stat");

    check_error(S_ISDIR(fInfo.st_mode), "Not a dir");

    check_error(nftw(argv[1], proccesFile, 50, 0) != -1, "nftw");

    exit(EXIT_SUCCESS);
}
