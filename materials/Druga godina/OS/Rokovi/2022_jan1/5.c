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
		
#define checkPthread(err,userMsg) \
	do {\
		int _err = (err);\
		if (_err > 0) { \
			errno = _err; \
			checkError(0,userMsg); \
		}\
	} while (0)

#define MAX_SIZE (1024)

int main(int argc, char** argv) {
	
	checkError(argc == 2, "...");
	//otvaramo fajl za citanje i pisanje
	int fd = open(argv[1], O_RDWR);
	checkError(fd != -1, "...");
	
	FILE* f = fdopen(fd, "r+");
	checkError(f != NULL, "...");
	
	char buffer[MAX_SIZE];
	int numChars = 0;
	//citamo rec po rec u fajlu
	while (fscanf(f, "%s", buffer) == 1) {
		//pokusamo da pretvorimo rec u broj
		char* error = NULL;
		int broj = strtol(buffer, &error, 10);
		
		// sve ok
		if (buffer[0] != '\0' && *error == '\0') {
			//struktura koja opisuje katanac
			struct flock lock;
			lock.l_type = F_WRLCK;
			lock.l_start = ftell(f);
			lock.l_len = -strlen(buffer);
			lock.l_whence = SEEK_SET;
			//postavljamo katanac
			int retVal = fcntl(fd, F_SETLK, &lock);
			
			//ukoliko je uspesno postavljen katanac
			if (retVal != -1) {
				//cuvamo odgovarajuci broj znaka '#' u buffer-u
				for (int i = 0; buffer[i] != 0; i++) {
					
					buffer[i] = '#';
				}
				//vracamo se unazad unutar fajla i upisujemo '#'
				fseek(f, -strlen(buffer), SEEK_CUR);
				fprintf(f, "%s", buffer);
				//belezimo broj upisanih karaktera
				numChars += strlen(buffer);
				//otkljucavamo zakljucanu rec
				lock.l_type = F_UNLCK;
				checkError(fcntl(fd, F_SETLK, &lock) != -1, "....");
			}
			else {
				
				if (errno != EACCES && errno != EAGAIN) {
					
					checkError(0, "...");
				}
				//ukoliko nije postavljen katanac jer neko drugi ima katanac, idemo dalje
				continue;
			}
		}
	}
	
	printf("%d\n", numChars);
	
	fclose(f);
	
	exit(EXIT_SUCCESS);
}
