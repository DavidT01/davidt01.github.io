#define _XOPEN_SOURCE 700

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include <grp.h>
#include <pwd.h>

#define check_error(expr, userMsg)\
    do {\
        if(!(expr)) {\
            perror(userMsg);\
            exit(EXIT_FAILURE);\
        }\
    } while(0)

int main(int argc, char** argv) {
    check_error(argc == 2, "argc");

    struct stat fInfo;
    check_error(lstat(argv[1], &fInfo) != -1, "lstat");

    struct passwd* userInfo;
    check_error((userInfo = getpwuid(fInfo.st_uid)) != NULL, "greska");

    struct group* groupInfo;
    check_error((groupInfo = getgrgid(fInfo.st_gid)) != NULL, "greska");

    printf("%s %s\n", userInfo->pw_name, groupInfo->gr_name);

    exit(EXIT_SUCCESS);
}
