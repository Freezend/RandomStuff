#include <stdio.h>

typedef struct {
	int x1;
	int y1;
	int x2;
	int y2;
} BAR;

typedef struct {
	int y1;
	int y2;
} LASER;

typedef struct {
	LASER* L;
	int n;
} LASERS;

LASERS* BubbleSort(LASERS* LS) {
	LASER t;
	for (int y = 0; y < (*LS).n - 1; ++y)
		for (int x = 0; x < (*LS).n - y - 1; ++x)
			if ((*LS).L[x].y1 > (*LS).L[x + 1].y1) {
				t = (*LS).L[x];
				(*LS).L[x] = (*LS).L[x + 1];
				(*LS).L[x + 1] = t;
			};
	return LS;
}

LASERS* Check(BAR* B, int n, int m) {
	LASERS* I = new LASERS{new LASER[m], 0};
	LASERS* O = new LASERS{new LASER[m+1], 0};

	for (int x = 0; x < m; ++x)
		(*I).L[(*I).n++] = { B[x].y1, B[x].y2 };

	I = BubbleSort(I);

	for (int x = 0, i = 0; x <= m; ++x) {
		if (x < m) {
			if (i < (*I).L[x].y1)
				(*O).L[(*O).n++] = { i, (*I).L[x].y1 };
			i = (*I).L[x].y2;
		} else if (i < n) {
			(*O).L[(*O).n++] = { i, n };
		}
	};

	return O;
};

int main() {
	BAR B[] = { {2,5,2,6}, {4,1,4,4}, {4,10,10,10}, {1,6,5,9}, {3,8,7,9} };
	int n = 11;
	int m = 5;

	LASERS* LS = Check(B, n, m);

	for (int x = 0; x < (*LS).n; ++x)
		printf("(%d,%d) ", (*LS).L[x].y1, (*LS).L[x].y2);

	delete[] LS;

	// --- OUTPUT --- //
	//(0,1) (4,5) (9,10) (10,11)
}
