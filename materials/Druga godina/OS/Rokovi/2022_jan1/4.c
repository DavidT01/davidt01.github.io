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
#define RD_END (0)
#define WR_END (1)
/**
 * Funkcija uzima kao argument liniju opisanu u zadatku i vraca niz argumenata koji ce biti prosledjen execvp-u
 */
char** allocateCommand(char* line) {
	
	int readBytesTotal = 0;
	int readBytes = 0;
	int n = 0;
	//citamo broj reci koje ce predstavljati komandu
	sscanf(line, "%d%n", &n, &readBytes);
	readBytesTotal += readBytes;
	
	char** command = malloc((n+2)*sizeof(char*));
	checkError(command != NULL, "command malloc");
	
	char rec[MAX_SIZE];
	//citamo naziv komande
	sscanf(line + readBytesTotal, "%s%n", rec, &readBytes);
	readBytesTotal += readBytes;
	
	command[0] = malloc(strlen(rec) + 1);
	checkError(command[0] != NULL, "...");
	command[1] = malloc(strlen(rec) + 1);
	checkError(command[1] != NULL, "...");
	
	strcpy(command[0], rec);
	strcpy(command[1], rec);
	//citamo argumente komande
	for (int i = 1; i < n; i++) {
		sscanf(line + readBytesTotal, "%s%n", rec, &readBytes);
		readBytesTotal += readBytes;
		command[i+1] = malloc(strlen(rec) + 1);
		checkError(command[i+1] != NULL, "...");
		strcpy(command[i+1], rec);
	}
	command[n+1] = NULL;
	
	return command;
}	
//funkcija koja stampa komandu
void printCommand(char** command) {
	
	for (int i = 0; command[i] != NULL; i++) {
		
		printf("%s ",command[i]);
	}
	printf("\n");
}
//funkcija koja oslobadja memoriju koja je alocirana za argumente
void deleteCommand(char** command) {
	
	for (int i = 0; command[i] != NULL; i++) {
		
		free(command[i]);
	}
	free(command);
}

int main(int argc, char** argv) {
	
	int cld2par[2];
	
	char* line = NULL;
	size_t lineLen = 0;
	
	int brUspesnih = 0;
	int brNeuspesnih = 0;
	int maxKaraktera = -1;
	char nazivKomande[MAX_SIZE];
	//citamo liniju po liniju sa standardnog ulaza
	while (getline(&line, &lineLen, stdin) > 0) {
		//alociramo memoriju za argumente
		char** command = allocateCommand(line);
		
		//printCommand(command);
		
		checkError(pipe(cld2par) != -1, "...");
		
		pid_t childPid = fork();
		checkError(childPid != -1, "...");
		
		if (childPid == 0) {
			
			close(cld2par[RD_END]);
			//preusmerevamo standardni izlaz deteta i izvrsavamo komandu
			checkError(dup2(cld2par[WR_END], STDOUT_FILENO) != -1, "...");
			checkError(execvp(command[0], command+1) != -1, "...");
		}
		//cekamo da dete obradi komandu i uzimamo status
		int status = 0;
		checkError(wait(&status) != -1, "...");
		
		close(cld2par[WR_END]);
		//ukoliko je komanda uspela belezimo broj uspesnih i koliko karaktera je ispisala
		if (WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) {
			
			brUspesnih++;
			
			int totalRead = 0;
			int readBytes = 0;
			char buffer[MAX_SIZE];
			while ((readBytes = read(cld2par[RD_END], buffer, MAX_SIZE)) > 0) {
				
				totalRead += readBytes;
			}
			
			if (totalRead > maxKaraktera) {
				
				maxKaraktera = totalRead;
				strcpy(nazivKomande, command[0]);
			}
		}
		else {
			//inace modifikujemo broj neuspesnih komandi
			brNeuspesnih++;
		}
		
		
		deleteCommand(command);
		close(cld2par[RD_END]);
	}
	//stampamo rezultat
	printf("%d %s\n", brNeuspesnih, brUspesnih > 0 ? nazivKomande : "nema");
	
	free(line);
	
	exit(EXIT_SUCCESS);
}
