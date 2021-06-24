#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

int N; //ilosc krzesel w poczekalni
int* K; //id klientow w poczekalni
int P = 1; //pierwszy klient w kolejce (id krzesla)
int O = 0; //ostatni klient w kolejce (id krzesla)
bool F = false; //czy fryzjer obsluguje klienta
int R = 0; //klienci, ktorzy zrezygnowali
int X = 0; //obslugiwany klient (id klienta lub 0 - zaden)
int Z = 0; //ilosc zdarzen / watkow pobocznych
bool U = true; //update (fryzjer powinien ogarnac)
bool DEBUG = false; //-debug
int* V; //tablica klientow, ktorzy zrezygnowali (do -debug)

pthread_mutex_t M1 = PTHREAD_MUTEX_INITIALIZER; //MUTEX1 (watki)
pthread_mutex_t M2 = PTHREAD_MUTEX_INITIALIZER; //MUTEX2 (big loop)
pthread_cond_t C = PTHREAD_COND_INITIALIZER; //COND (zmienna warunkowa)

typedef struct sData {
	int x; //numer klienta (0 jesli to nie nowy klient)
	int s; //sekundy do wykonania
	bool t; // true - nowy klient, false - fryzjer konczy scinac
	struct sData* n; //next / kolejne zdarzenie
} Data;

//wczytanie kolejki zdarzen z pliku
Data* readData(char* name) {
	FILE* f = fopen(name, "r");
	Data* new = NULL;
	Data* first = NULL;
	Data* last = NULL;
	int r;
	int d;
	char c;
	
	if (f != NULL) {
		r = fscanf(f, "%d\n", &N);
		if (r != EOF && r != 0 && N >= 1 && N <= 20) {
			K = (int*)malloc((N+1)*sizeof(int));
			while ((r = fscanf(f, "%d %c\n\n", &d, &c)) != EOF) {
				new = (Data*)malloc(sizeof(Data));
				if (c == '+' || c == '-') {
					++Z;
					new->x = (c=='+')?++X:0;
					new->s = d;
					new->t = (c=='+')?true:false;
					if (first == NULL) {
						new->n = NULL;
						first = new;
						last = first;
					} else {
						last->n = new;
						last = new;
					}
				} else {
					printf("Blad w zapisie polecen, przerwano wczytywanie kolejnych.\n");
					break;
				}
			};
		} else {
			printf("Liczba krzesl w poczekalni jest nieprawidlowa (n powinno byc z zakresu <1,20>).\n");
		}
	} else {
		printf("Blad podczas odczytu pliku.\n");
	}
	return first;
}

//wyswietlenie kolejki zdarzen
void showData(Data* d) {
	Data* o = d;
	printf("%d //N\n\n", N);
	while(o != NULL) {
		printf("%d %c\n", o->s, (o->t)?'+':'-');
		o = o->n;
	}
	printf("\n");
}

//usuwanie kolejki
void clearData(Data* d) {
	Data* o;
	free(K);
	while (d != NULL) {
		o = d->n;
		free(d);
		d = o;
	}
}

//-debug
void debugInformation() {
	printf("POCZEKALNIA -> ");
	for (int i=1; i<=N; ++i)
		if (K[i] > 0)
			if (i == P) {
				printf("[_%d_] ", K[i]);
			} else {
				printf("[ %d ] ", K[i]);
			}
		else if (i == P)
			printf("[_-_] ");
		else
			printf("[ - ] ");
	if (R > 0) {
		printf("\nZREZYGNOWANI -> ");
		for (int i=0; i<R; ++i) {
			printf("%d ", V[i]);
		}
	}
	printf("\n");
}

//nowe zdarzenie (nowy klient albo fryzjer konczy scinac)
void* newData(void* arg) {
	Data* curr;
	curr = (Data*)arg;
	int MSC = 0, i;
	sleep(curr->s);
	//zablokowanie mutexu
	pthread_mutex_lock(&M1);
	//oczekiwanie na sygnal zmiennej warunkowej
	pthread_cond_wait(&C, &M1);
	printf("\n");
	if (curr->t == 1) {
		i = O+1;
		do {
			if (i > N)
				i = 1;
			if (K[i] == 0) {
				MSC = i;
				break;
			}
			++i;
		} while(i != O+1);
		if (MSC != 0) {
			O = MSC;
			K[O] = curr->x;
			U = true;
			printf("Nowy klient (%d) zasiada w poczekalni (%d).\n", curr->x, MSC);
		} else {
			V[R] = curr->x;
			++R;
			U = true;
			printf("Nowy klient (%d) nie znalazl miejsca i odszedl.\n", curr->x);
		}
	} else {
		if (F) {
			F = false;
			U = true;
			printf("Klient (%d) zostal obsluzony.\n", X);
		} else {
			printf("Fryzjer nie obsluguje zadnego klienta.\n");
		}
	}
	//odblokowanie mutexu
	pthread_mutex_unlock(&M1);
	pthread_exit(NULL);
}

//ilosc klientow w poczekalni
int calcClients() {
	int x = 0;
	for (int i = 1; i <= N; ++i)
		if (K[i] > 0)
			++x;
	return x;
}

//ogarniecie klientow przez fryzjera (jesli nikogo nie obsluguje to zaczyna)
void checkData() {
	//zablokowanie mutexu
	pthread_mutex_lock(&M1);
	if (!F && K[P] > 0) {
		F = true;
		X = K[P];
		K[P] = 0;
		++P;
		if (P > N)
			P = 1;
		U = true;
		printf("Fryzjer zaczyna obslugiwac klienta (%d).\n", X);
	}
	if (U) {
		U = false;
		printf("Res: %d WRomm: %d/%d [in: %d]\n", R, calcClients(), N, (F?X:0));
		if (DEBUG)
			debugInformation();
	}
	//wyslanie sygnalu, ze fryzjer ogarnal sytuacje
	pthread_cond_signal(&C);
	//odblokowanie mutexu
	pthread_mutex_unlock(&M1);
}

int main(int argc, char* argv[]) {
	Data* first = NULL;
	Data* curr = NULL;
	pthread_t* TH;
	int RC;
	
	if (argc != 2 && argc != 3) {
		printf("Nalezy podac plik z danymi w argumencie.\n");
		exit(EXIT_FAILURE);
	}
	if (argc == 3 && strcmp(argv[2], "-debug") == 0) {
		DEBUG = true;
		printf("Tryb debugowania.\n");	
	}
	
	first = readData(argv[1]);
	
	if (first != NULL) {
		TH = (pthread_t*)malloc(Z*sizeof(pthread_t));
		V = (int*)malloc(X*sizeof(int));
		showData(first);
		
		curr = first;
		for (int i = 0; i < Z && curr != NULL; ++i) {
			RC = pthread_create(&TH[i], NULL, newData, (void*)curr);
			if (RC) {
				printf("Blad podczas tworzenia watku: %d\n", RC);
				exit(-1);
			}
			curr = curr->n;
		}
		
		while (true) {
			//zablokowanie drugiego mutexu
			pthread_mutex_lock(&M2);
			checkData();
			usleep(1000);
			//odblokowanie drugiego mutexu
			pthread_mutex_unlock(&M2);
			//sleep(1);
		}
		
		clearData(first);
		free(TH);
		free(V);
		//pthread_exit(NULL);
		exit(EXIT_SUCCESS);
	} else {
		printf("Blad danych.\n");
		exit(EXIT_FAILURE);
	};
}
