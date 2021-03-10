#include <stdio.h>
#include <locale.h>
#include <math.h>

typedef struct structCircle {
	int x;
	int y;
	int r;
	struct structCircle* next;
} circle;

typedef struct structRectangle {
	int x;
	int y;
	int x2;
	int y2;
	struct structRectangle* next;
} rectangle;

typedef struct structPointer {
	circle* pointerToCircle;
	rectangle* pointerToRectangle;
} pointer;

double square(const int x) {
	return (double)x * (double)x;
}

pointer* readFile(const char* name, pointer* pointers) {
	FILE* file = fopen(name, "r");
	pointer* newObjects = (pointer*)malloc(sizeof(pointer));
	newObjects->pointerToCircle = pointers->pointerToCircle;
	newObjects->pointerToRectangle = pointers->pointerToRectangle;
	char type;

	if (file != NULL) {
		while ((type = fgetc(file)) != EOF)
			if (type == 'o') {
				pointers->pointerToCircle = newObjects->pointerToCircle;
				newObjects->pointerToCircle = (circle*)malloc(sizeof(circle));
				if (fscanf(file, "%d %d %d\n", &newObjects->pointerToCircle->x, &newObjects->pointerToCircle->y, &newObjects->pointerToCircle->r))
					newObjects->pointerToCircle->next = pointers->pointerToCircle;
			} else if (type == 'p') {
				pointers->pointerToRectangle = newObjects->pointerToRectangle;
				newObjects->pointerToRectangle = (rectangle*)malloc(sizeof(rectangle));
				if (fscanf(file, "%d %d %d %d\n", &newObjects->pointerToRectangle->x, &newObjects->pointerToRectangle->y, &newObjects->pointerToRectangle->x2, &newObjects->pointerToRectangle->y2))
					newObjects->pointerToRectangle->next = pointers->pointerToRectangle;
			}
		fclose(file);
	} else
		printf("Nie odnaleziono pliku z danymi.\n");
	return newObjects;
}

circle* deleteCircle(circle* pointerToCircle, circle* deletedCircle) {
	circle* newCircles = pointerToCircle;
	if (pointerToCircle == deletedCircle)
		pointerToCircle = pointerToCircle->next;
	else
		while (newCircles->next != NULL)
			if (newCircles->next == deletedCircle)
				newCircles->next = newCircles->next->next;
			else
				newCircles = newCircles->next;
	free(deletedCircle);
	return pointerToCircle;
}

rectangle* deleteRectangle(rectangle* pointerToRectangle, rectangle* deletedRectangle) {
	rectangle* newRectangles = pointerToRectangle;
	if (pointerToRectangle == deletedRectangle)
		pointerToRectangle = pointerToRectangle->next;
	else
		while (newRectangles->next != NULL)
			if (newRectangles->next == deletedRectangle)
				newRectangles->next = newRectangles->next->next;
			else
				newRectangles = newRectangles->next;
	free(deletedRectangle);
	return pointerToRectangle;
}

circle* deleteCircles(circle* pointerToCircle) {
	circle* oldCircles = pointerToCircle;
	circle* newCircles;
	circle* temporaryCircle = NULL;
	while (oldCircles != NULL) {
		newCircles = pointerToCircle;
		while (newCircles != NULL) {
			temporaryCircle = newCircles->next;
			if (sqrt(square((newCircles->x) - (oldCircles->x)) + square((newCircles->y) - (oldCircles->y))) <= (double)(newCircles->r) + (double)(oldCircles->r))
				if (oldCircles != newCircles && (oldCircles->r) >= (newCircles->r))
					pointerToCircle = deleteCircle(pointerToCircle, newCircles);
			newCircles = temporaryCircle;
		}
		oldCircles = oldCircles->next;
	}
	return pointerToCircle;
}

rectangle* deleteRectangles(rectangle* pointerToRectangle) {
	rectangle* oldRectangles = pointerToRectangle;
	rectangle* newRectangles;
	rectangle* temporaryRectangle = NULL;
	while (oldRectangles != NULL) {
		newRectangles = pointerToRectangle;
		while (newRectangles != NULL) {
			temporaryRectangle = newRectangles->next;
			if (oldRectangles->x < newRectangles->x2 && oldRectangles->x2 > newRectangles->x && oldRectangles->y < newRectangles->y2 && oldRectangles->y2 > newRectangles->y)
				if (oldRectangles != newRectangles && abs((oldRectangles->y) - (oldRectangles->y2)) + abs((oldRectangles->x) - (oldRectangles->x2)) >= abs((newRectangles->y) - (newRectangles->y2)) + abs((newRectangles->x) - (newRectangles->x2)))
					pointerToRectangle = deleteRectangle(pointerToRectangle, newRectangles);
			newRectangles = temporaryRectangle;
		}
		oldRectangles = oldRectangles->next;
	}
	return pointerToRectangle;
}

circle* deleteAllCircles(circle* pointerToCircle) {
	circle* oldCircle = pointerToCircle;
	circle* temporaryCircle = NULL;
	while (oldCircle != NULL) {
		temporaryCircle = oldCircle;
		oldCircle = oldCircle->next;
		pointerToCircle = deleteCircle(pointerToCircle, temporaryCircle);
	}
	return pointerToCircle;
}

rectangle* deleteAllRectangles(rectangle* pointerToRectangle) {
	rectangle* oldRectangles = pointerToRectangle;
	rectangle* temporaryRectangle = NULL;
	while (oldRectangles != NULL) {
		temporaryRectangle = oldRectangles;
		oldRectangles = oldRectangles->next;
		pointerToRectangle = deleteRectangle(pointerToRectangle, temporaryRectangle);
	}
	return pointerToRectangle;
}

void showCircles(const circle* pointerToCircle) {
	circle* newPointer = pointerToCircle;
	if (newPointer != NULL) {
		printf("Okregi:\n");
		while (newPointer != NULL) {
			printf("o %d %d %d\n", newPointer->x, newPointer->y, newPointer->r);
			newPointer = newPointer->next;
		}
	}
}

void showRectangles(const rectangle* pointerToRectangle) {
	rectangle* newPointer = pointerToRectangle;
	if (newPointer != NULL) {
		printf("Prostokaty:\n");
		while (newPointer != NULL) {
			printf("p %d %d %d %d\n", newPointer->x, newPointer->y, newPointer->x2, newPointer->y2);
			newPointer = newPointer->next;
		}
	}
}

void writeToFile(const char* name, const pointer* pointers) {
	FILE* file = fopen(name, "w");
	circle* pointerToCircle = pointers->pointerToCircle;
	rectangle* pointerToRectangle = pointers->pointerToRectangle;
	while (pointerToCircle != NULL) {
		fprintf(file, "o %d %d %d\n", pointerToCircle->x, pointerToCircle->y, pointerToCircle->r);
		pointerToCircle = pointerToCircle->next;
	}
	while (pointerToRectangle != NULL) {
		fprintf(file, "p %d %d %d %d\n", pointerToRectangle->x, pointerToRectangle->y, pointerToRectangle->x2, pointerToRectangle->y2);
		pointerToRectangle = pointerToRectangle->next;
	}
	fclose(file);
}

int main() {
	pointer* pointers = (pointer*)malloc(sizeof(pointer));
	pointers->pointerToCircle = NULL;
	pointers->pointerToRectangle = NULL;

	setlocale(LC_ALL, "");

	//Zadanie 1
	pointers = readFile("dane.txt", pointers);

	//Wyswietlenie wszystkich figur
	showCircles(pointers->pointerToCircle);
	showRectangles(pointers->pointerToRectangle);

	//Zadanie 2
	pointers->pointerToCircle = deleteCircles(pointers->pointerToCircle);

	//Zadanie 3
	pointers->pointerToRectangle = deleteRectangles(pointers->pointerToRectangle);

	//Zadanie 4
	writeToFile("dane wyjsciowe.txt", pointers);

	//Zadanie 5
	pointers->pointerToCircle = deleteAllCircles(pointers->pointerToCircle);
	pointers->pointerToRectangle = deleteAllRectangles(pointers->pointerToRectangle);

	return 0;
}