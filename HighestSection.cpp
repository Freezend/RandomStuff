#include <stdio.h>

typedef struct {
	int* T;
	int s;
	int n;
} HS;

HS newHS(int n) {
	HS O;
	O.T = new int[n];
	O.s = 0;
	O.n = 0;
	return O;
};

HS HighestSection(int I[], int n) {
	HS O = newHS(n);
	HS M = newHS(n);

	for (int y = 0; y < n; ++y) {
		if (O.s < 0)
			O = newHS(n);
		O.T[O.n++] = I[y];
		O.s += I[y];
		if (O.s > M.s)
			M = O;
	};

	return M;
};

int main() {
	int T[] = { 6, -10, 5, -1, 4, 8, -3, 9, 11, -40, 6, 18 };
	int n = 12;

	HS O = HighestSection(T, n);

	printf("Numbers:");
	for (int x = 0; x < O.n; ++x)
		printf(" %d", O.T[x]);
	printf("\nSum: %d\n", O.s);

	// --- OUTPUT --- //
	//Numbers: 5 -1 4 8 -3 9 11
	//Sum: 33
}