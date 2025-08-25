#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/wait.h>
#include <pthread.h>
#include <errno.h>

#define checkError(expr,userMsg) \
	do { \
		if (!(expr)) {\
			perror(userMsg); \
			exit(EXIT_FAILURE); \
		}\
	} while (0)
		
#define checkPthread(err,userMsg) { \
	do {\
		int _err = (err);\
		if (_err > 0) { \
			errno = _err; \
			checkError(0,userMsg); \
		}\
	} while (0)
	
#define BUFFER_SIZE (1024)
	
int main(int argc, char** argv) {
	
	checkError(argc == 3, "args");
	//otvaramo fajl koji premestamo
	int srcFd = open(argv[1], O_RDONLY);
	checkError(srcFd != -1, "open src");
	//otvaramo lokaciju na koju ce biti premesten fajl
	int destFd = open(argv[2], O_WRONLY|O_TRUNC|O_CREAT, 0644);
	checkError(destFd != -1, "open dest");
	
	int readBytes = 0;
	char buffer[BUFFER_SIZE];
	//citamo podatke iz polaznog i pisemo ih u ciljani fajl
	while ((readBytes = read(srcFd, buffer, BUFFER_SIZE)) > 0) {
		checkError(write(destFd, buffer, readBytes) != -1, "write");
	}
	
	checkError(readBytes != -1, "read");
	//zatvaramo fajl deskriptore
	close(srcFd);
	close(destFd);
	
	//postavljamo prava ciljanog fajla na prava polaznog
	struct stat fInfo;
	checkError(stat(argv[1], &fInfo) != -1, "stat src");
	checkError(chmod(argv[2], fInfo.st_mode & 0x1ff) != -1, "chmod dest");

	//brisemo polazni fajl
	checkError(unlink(argv[1]) != -1, "unlink src");
	
	exit(EXIT_SUCCESS);
}
