#define _XOPEN_SOURCE 700

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include <ftw.h>
#include <time.h>

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while(0)

char* week[7] = {"nedelja", "ponedeljak", "utorak", "sreda", "cetvrtak", "petak", "subota"};

int proccesFile(const char *fpath, const struct stat *sb,int typeflag, struct FTW *ftwbuf) {
    if(S_ISREG(sb->st_mode)) {
        time_t modTime = sb->st_mtime;
        struct tm* broken_time = localtime(&modTime);

        char* realPath = NULL;
        check_error((realPath = realpath(fpath, realPath)) != NULL, "realpath");

        printf("%s %s\n", realPath, week[broken_time->tm_wday]);
        free(realPath);
    }
    return 0;
}

int main(int argc, char** argv) {
    check_error(argc == 2, "argc");

    struct stat fInfo;
    check_error(stat(argv[1], &fInfo) != -1, "stat");
    check_error(S_ISDIR(fInfo.st_mode), "not a dir");

    check_error(nftw(argv[1], proccesFile, 50, 0) != -1, "nftw");

    exit(EXIT_SUCCESS);
}
