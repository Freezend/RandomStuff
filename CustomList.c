#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct customList {
	char* s;
	int x;
	struct customList* prev;
	struct customList* next;
} cList;

cList* GetLast(cList* cFirst) {
	cList* o = cFirst;
	if (o != NULL)
		while (o->next != NULL)
			o = o->next;
	return o;
}

cList* GetFirst(cList* cLast) {
	cList* o = cLast;
	if (o != NULL)
		while (o->prev != NULL)
			o = o->prev;
	return o;
}

cList* Insert(cList* cFirst, const char* s, int x) {
	cList* n = (cList*) malloc(sizeof(cList));
	if (n) {
		n->s = (char*) malloc(strlen(s) + 1);
		if (n->s)
			strcpy_s(n->s, strlen(s) + 1, s);
		n->x = x;
		n->prev = NULL;
		n->next = cFirst;
		if (cFirst != NULL)
			cFirst->prev = n;
		return n;
	} else {
		return cFirst;
	}
}

cList* Append(cList* cLast, const char* s, int x) {
	cList* n = (cList*) malloc(sizeof(cList));
	if (n) {
		n->s = (char*)malloc(strlen(s) + 1);
		if (n->s)
			strcpy_s(n->s, strlen(s) + 1, s);
		n->x = x;
		n->prev = cLast;
		n->next = NULL;
		if (cLast != NULL)
			cLast->next = n;
		return n;
	} else {
		return cLast;
	}
}

cList* RemoveFirst(cList* cFirst) {
	cList* n = NULL;
	if (cFirst != NULL) {
		if (cFirst->next != NULL)
			cFirst->next->prev = NULL;
		n = (cList*) malloc(sizeof(cList));
		if (n) {
			if (cFirst->s) {
				n->s = (char*)malloc(strlen(cFirst->s) + 1);
				if (n->s)
					strcpy_s(n->s, strlen(cFirst->s) + 1, cFirst->s);
			} else {
				n->s = NULL;
			}
			n->x = cFirst->x;
		}
		free(cFirst->s);
		free(cFirst);
	}
	return n;
}

cList* RemoveLast(cList* cLast) {
	cList* n = NULL;
	if (cLast != NULL) {
		if (cLast->prev != NULL)
			cLast->prev->next = NULL;
		n = (cList*)malloc(sizeof(cList));
		if (n) {
			if (cLast->s) {
				n->s = (char*)malloc(strlen(cLast->s) + 1);
				if (n->s)
					strcpy_s(n->s, strlen(cLast->s) + 1, cLast->s);
			} else {
				n->s = NULL;
			}
			n->x = cLast->x;
		}
		free(cLast->s);
		free(cLast);
	}
	return n;
}

void WriteOne(cList* cElement) {
	if (cElement != NULL)
		printf("%s %d\n\n", (cElement->s) ? (cElement->s) : "", cElement->x);
	else
		printf("NULL\n\n");
}

void WriteAll(cList* cFirst) {
	cList* o = cFirst;
	if (o != NULL)
		do {
			printf("%s %d\n", (o->s) ? (o->s) : "", o->x);
			o = o->next;
		} while (o != NULL);
	else
		printf("NULL\n");
	printf("\n");
}

int main() {
	cList *cFirst = NULL, *cLast = NULL, *cTemp, *cTempFirstLast = NULL;
	int o = -1;
	int first = 0, last = 0;

	do {
		printf("1. Insert at the beginning.\n");
		printf("2. Append at the end.\n");
		printf("3. Remove first element.\n");
		printf("4. Remove last element.\n");
		printf("5. Write first element.\n");
		printf("6. Write last element.\n");
		printf("7. Write all elements.\n");
		printf("0. Exit.\n");
		printf("> ");
		if (scanf_s("%d", &o) != 0) {
			printf("\n");
			switch (o) {
				case 1:
					cFirst = Insert(cFirst, "Inserted", first--);
					if (!cLast)
						cLast = cFirst;
					break;
				case 2:
					cLast = Append(cLast, "Appended", ++last);
					if (!cFirst)
						cFirst = cLast;
					break;
				case 3:
					if (cFirst)
						cTempFirstLast = cFirst->next;
					cTemp = RemoveFirst(cFirst);
					WriteOne(cTemp);
					cFirst = cTempFirstLast;
					cTempFirstLast = NULL;
					if (!cFirst)
						cLast = NULL;
					break;
				case 4:
					if (cLast)
						cTempFirstLast = cLast->prev;
					cTemp = RemoveLast(cLast);
					WriteOne(cTemp);
					cLast = cTempFirstLast;
					cTempFirstLast = NULL;
					if (!cLast)
						cFirst = NULL;
					break;
				case 5:
					WriteOne(cFirst);
					break;
				case 6:
					WriteOne(cLast);
					break;
				case 7:
					WriteAll(cFirst);
					break;
				default:
					break;
			}
		}
	} while (o != 0);

	return 0;
}
