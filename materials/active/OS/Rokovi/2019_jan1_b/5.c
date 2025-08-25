#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define check_error(cond, errMsg) \
    do{ \
        if(!(cond)){ \
            exit(EXIT_FAILURE); \
        } \
    }while(0);

#define MAX_LEN (256)
#define LOC (0)
#define ULOC (1)


int is_num(char* buffer);
int lock(int fd, int start, int len, int mod);
int mod(int fd, int start, int len);


int main(int argc, char** argv){

    check_error(argc == 2, "Bad arguments");

    int fd = open(argv[1], O_RDWR);
    check_error(fd != -1, "Failed to open file");

    char buffer[MAX_LEN + 1];
    int pt = 0;
    int word_start = 0;
    int file_pt = 0;

    char c;
    while(read(fd, &c, 1) > 0) {

        if(c == ' ' || c == '\n') {

            buffer[pt] = '\0';
            int ret_val = is_num(buffer);
            printf("\"%s\" is number: %d\n", buffer, ret_val);

            if(ret_val) {
                
                int word_len = strlen(buffer);
                if(lock(fd, word_start, word_len, LOC)) {

                    int mod_ret_val = mod(fd, word_start, word_len);
                    check_error(mod_ret_val != -1, "Failed to seek file");
                    check_error(mod_ret_val != -2, "Failed to write into file");

                    lock(fd, word_start, word_len, ULOC);
                }
            }

            word_start = file_pt + 1;
            pt = 0;
        }
        else {

            buffer[pt] = c;
            pt++;
        }
        file_pt += 1;
    }
    
    close(fd);

}

int num_len(int x) {
    int counter = 1;
    while((x = x / 10)) {
        counter += 1;
    }
    return counter;
}

int is_num(char* buffer) {

    int buff_num = atoi(buffer);
    if(buff_num > 0 && num_len(buff_num) == 4) return 1;
    else return 0;
}

int mod(int fd, int start, int len) {

    off_t seek_ret_val = lseek(fd, -5, SEEK_CUR);

    if(seek_ret_val == (off_t) -1) return -1;
    
    char write_buffer[4] = "####";
    int wr_ret_val = write(fd, write_buffer, 4);

    if(wr_ret_val == -1) {
        lseek(fd, 5, SEEK_CUR);
        return -2;
    }

    lseek(fd, 1, SEEK_CUR);

    return 0;
}

int lock(int fd, int start, int len, int mod) {

    struct flock fs;
    fs.l_type = F_WRLCK;
    fs.l_whence = SEEK_SET;
    fs.l_start = start;
    fs.l_len = len;

    if(mod == LOC) {

        int ret_val = fcntl(fd, F_SETLK, &fs);
        if(ret_val == -1) { 
            return 0;
        }
    }
    else if (mod == ULOC) {

        fs.l_type = F_UNLCK;
        int ret_val = fcntl(fd, F_SETLK, &fs);
        if(ret_val == -1) { 
            return 0;
        }
    }
    
    return 1;
}