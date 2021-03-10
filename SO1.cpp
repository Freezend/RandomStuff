#include <stdio.h>
#include <stdlib.h>

int read(char* file) {
	FILE* f = fopen(file, "r");
	int z = 0;
	char c;
	printf("-- %s --\n", file);
	if (f != NULL) {
		while ((c = getc(f)) != EOF) {
			++z;
			printf("%c", c);
		}
		if (z == 0)
			printf("- plik jest pusty -");
		fclose(f);
		printf("\n\n");
		return 1;
	} else {
		printf("- nie znaleziono pliku -\n\n");
		return 0;
	}
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Bledna liczba argumentow. Podaj nazwy plikow.\n");
		return 1;
	}

	for (int x = 1; x < argc; ++x)
		read(argv[x]);

	return 0;
}