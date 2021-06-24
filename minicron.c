#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <signal.h>
#include <stddef.h>

const int MAXTASKS = 20;
const int MAXCOMMANDLENGTH = 50;
volatile int FLAG = 0;

typedef struct sTask {
	int hours;
	int minutes;
	char* command;
	int info;
} Task;

typedef struct sTasks {
	Task* T;
	int n;
} Tasks;

void int_handler(int signum) {
	closelog();
	exit(signum);
};

void usr1_handler() {
	syslog(LOG_INFO, "SIGUSR1 received.");
	FLAG = 1;
};

void usr2_handler() {
	syslog(LOG_INFO, "SIGUSR2 received.");
	FLAG = 2;
};

Tasks readTasks(char* name) {
	FILE* f = fopen(name, "r");
	Tasks Ts = { (Task*)malloc(MAXTASKS*sizeof(Task)), 0 };
	int i[4] = {0, 0, 0, 0};
	char s[MAXCOMMANDLENGTH];
	int t = 0, y = 0, x = 0, r = 0;
	char c;
	if (f != NULL) {
		memset(s, '\0', MAXCOMMANDLENGTH * sizeof(char));
		do {
			r = fscanf(f, "%c", &c);
			if (r == EOF || c == '\n') {
				if (i[0] >= 0 && i[1] >= 0 && i[3] >= 0 && i[3] <= 2 && x > 0 && t >= 3) {
					Ts.T[y].hours = i[0];
					Ts.T[y].minutes = i[1];
					Ts.T[y].info = i[3];
					Ts.T[y].command = (char*)malloc(MAXCOMMANDLENGTH * sizeof(char));
					s[MAXCOMMANDLENGTH - 1] = '\0';
					strcpy(Ts.T[y++].command, s);
					Ts.n += 1;
				}
				memset(s, '\0', MAXCOMMANDLENGTH * sizeof(char));
				for (int k = 0; k < 4; ++k)
					i[k] = 0;
				x = 0;
				t = 0;
			} else if (c == ':') {
				++t;
			} else {
				if (t == 2)
					s[x++] = c;
				else if (t <= 3)
					i[t] = i[t] * 10 + ((int)c - 48);
			}
		} while (r != EOF && y < MAXTASKS);
		fclose(f);
	}
	return Ts;
}

void sortTasks(Tasks* Ts) {
	Task* P = (Task*)malloc(sizeof(Task));
	int x;
	for (int y = 1; y < Ts->n; ++y) {
		P->hours = Ts->T[y].hours;
		P->minutes = Ts->T[y].minutes;
		strcpy(P->command, Ts->T[y].command);
		P->info = Ts->T[y].info;
		x = y - 1;
		while (x >= 0 && Ts->T[x].hours >= P->hours && (Ts->T[x].hours > P->hours || Ts->T[x].minutes > P->minutes)) {
			Ts->T[x + 1].hours = Ts->T[x].hours;
			Ts->T[x + 1].minutes = Ts->T[x].minutes;
			strcpy(Ts->T[x + 1].command, Ts->T[x].command);
			Ts->T[x + 1].info = Ts->T[x].info;
			--x;
		}
		Ts->T[x + 1].hours = P->hours;
		Ts->T[x + 1].minutes = P->minutes;
		strcpy(Ts->T[x + 1].command, P->command);
		Ts->T[x + 1].info = P->info;
	}
	free(P);
}

void showTasks(Tasks Ts) {
	for (int x = 0; x < Ts.n; ++x)
		printf("%d %d %s %d\n", Ts.T[x].hours, Ts.T[x].minutes, Ts.T[x].command, Ts.T[x].info);
}

void calculateTasks(Tasks* Ts) {
	for (int x = (Ts->n) - 1; x > 0; --x) {
		Ts->T[x].hours -= Ts->T[x - 1].hours;
		Ts->T[x].minutes -= Ts->T[x - 1].minutes;
		while (Ts->T[x].minutes < 0) {
			Ts->T[x].hours -= 1;
			Ts->T[x].minutes += 60;
		}
	}
}

int main(int argc, char* argv[]) {
	Tasks Ts;
	pid_t pid, sid, cid;
	int x = 0, k = 0;
	
	if ((pid = fork()) < 0)
		exit(EXIT_FAILURE);
	if (pid > 0)
		exit(EXIT_SUCCESS);
	umask(0);
	openlog("minicron1337", LOG_PID, LOG_USER);
	syslog(LOG_INFO, "Minicron1337 initialized.");
	if ((sid = setsid()) < 0) {
		syslog(LOG_INFO, "Can't create new SID for child process.");
		exit(EXIT_FAILURE);
	};
	
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	
	if (argc > 1) {
		Ts = readTasks(argv[1]);
		sortTasks(&Ts);
		calculateTasks(&Ts);
	} else {
		syslog(LOG_INFO, "No read file specified.");
		exit(EXIT_FAILURE);
	};
	
	signal(SIGINT, int_handler);
	signal(SIGUSR1, usr1_handler);
	signal(SIGUSR2, usr2_handler);
	
	while (x < Ts.n || FLAG == 1) {
		sleep(((Ts.T[x].hours*60)+Ts.T[x].minutes)*60); //d
		if(FLAG == 1) {
			FLAG = 0;
			x = 0;
			sleep(((Ts.T[0].hours*60)+Ts.T[0].minutes)*60);
		};
		if (FLAG == 2) {
			FLAG = 0;
			k = x;
			while (k < Ts.n) {
				syslog(LOG_INFO, "Not done: %s", Ts.T[k].command);
				++k;
			};
		};
		syslog(LOG_INFO, "Task done: %s", Ts.T[x].command);
		if ((cid = fork()) == 0) {
			execlp(Ts.T[x].command, Ts.T[x].command, NULL, (char*)NULL);
			syslog(LOG_INFO, "Bad command.");
			exit(0);
		};
		if (Ts.T[x].info == 0 || Ts.T[x].info == 2)
			syslog(LOG_INFO, "STDOUT: %d", fileno(stdout));
		if (Ts.T[x].info == 1 || Ts.T[x].info == 2)
			syslog(LOG_INFO, "STDERR: %s", strerror(errno));
		++x;
	};
	syslog(LOG_INFO, "Minicron1337 finished.");
	closelog();
	exit(EXIT_SUCCESS);
}
