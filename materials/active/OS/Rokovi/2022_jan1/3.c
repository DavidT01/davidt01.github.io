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

char* fName = NULL;
int globalMax = -1;
//katanac za sinhronizaciju
pthread_mutex_t globalLock = PTHREAD_MUTEX_INITIALIZER;

//struktura koja opisuje argument niti
typedef struct {
	
	char* fPath;
} dataIn_t;

//struktura koja opisuje povratnu vrednost niti
typedef struct {
	
	int localSum;
} dataOut_t;

void* threadFunc(void* arg) {
	
	dataIn_t* data = (dataIn_t*)arg;
	
	//alociramo memoriju za povratnu vrednost niti
	dataOut_t* out = malloc(sizeof(dataOut_t));
	checkError(out != 0, "malloc out");
	out->localSum = 0;
	//otvaramo fajl koju obradjuje nit
	FILE* f_in = fopen(data->fPath, "r");
	checkError(f_in != NULL, "fopen");
	
	char rec[MAX_SIZE];
	//brojimo reci u fajlu
	while (fscanf(f_in, "%s", rec) == 1) {
		
		out->localSum++;
	}
	
	fclose(f_in);
	
	checkPthread(pthread_mutex_lock(&globalLock), "thread lock");
	//ulaz u kriticnu sekciju
	if (out->localSum > globalMax) {
		//modifikujemo globalne vrednosti
		globalMax = out->localSum;
		fName = data->fPath;
	}
	//izlaz iz kriticne sekcije
	checkPthread(pthread_mutex_unlock(&globalLock), "thread unlock");
	
	return out;
}
	
int main(int argc, char** argv) {
	
	checkError(argc > 1, "args");
	
	int n = argc - 1;
	//alociramo memoriju za n thread ID-a
	pthread_t* tids = malloc(n*sizeof(pthread_t));
	checkError(tids != NULL, "malloc tids");
	
	//alociramo memoriju za n argumenata niti
	dataIn_t* args = malloc(n*sizeof(dataIn_t));
	checkError(args != NULL, "malloc tids");
	
	for (int i = 0; i < n; i++) {
		
		args[i].fPath = argv[i+1];
		//pokrecemo niti sa odgovarajucim argumentom
		checkPthread(pthread_create(&tids[i], NULL, threadFunc, &args[i]), "create");
	}
	
	int globalSum = 0;
	for (int i = 0; i < n; i++) {
		
		dataOut_t* out;
		//uzimamo rezultat iz i-te niti
		checkPthread(pthread_join(tids[i], (void**)&out), "join");
		//povecavamo ukupnu sumu
		globalSum += out->localSum;
		//oslobadjamo memoriju koja je alocirana unutar niti
		free(out);
	}

	//ispisujemo trazene vrednosti
	printf("%d ", globalSum);
	char* ime = strrchr(fName, '/');
	printf("%s\n", ime != NULL ? ime + 1 : fName);
	
	//oslobadjamo memoriju
	free(tids);
	free(args);
	
	exit(EXIT_SUCCESS);
}
