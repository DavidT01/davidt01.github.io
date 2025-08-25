#define _XOPEN_SOURCE 700
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
#include <time.h>
#include <ftw.h>

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
	
#define SECS_IN_DAY (24*60*60)
	
char* ext = NULL;
time_t now = 0;

int checkFile(const char* fpath, const struct stat* sb, int typeflag, struct FTW* ftwbuf) {
	//ako je fajl regularan
	if (typeflag == FTW_F) {
		
		int timeDiff = (now - sb->st_mtime)/SECS_IN_DAY;
		//ako je modifikovan u poslednjih 7 dana
		if (timeDiff <= 7) {
			
			char* tacka = strrchr(fpath + ftwbuf->base, '.');
			//ako mu je ekstenzija jednaka zadatoj
			if (tacka != NULL && strcmp(tacka, ext) == 0) {
				
				printf("%s\n", fpath + ftwbuf->base);
			}
		}
	}
	
	return 0;
}
	
int main(int argc, char** argv) {
	
	checkError(argc == 3, "args");
	
	//proveravamo da li je zadat direktorijum
	struct stat fInfo;
	checkError(stat(argv[1], &fInfo) != -1, "...");
	checkError(S_ISDIR(fInfo.st_mode), "...");
	//podesavamo globalne promenljive koje ce se koristiti u funkciji
	ext = argv[2];
	time(&now);
	//rekurzivni obilazak direktorijuma
	checkError(nftw(argv[1], checkFile, 50, 0) != -1, "....");
	
	exit(EXIT_SUCCESS);
}
