#include <stdio.h>

void InsertSort(int* T, int n) {
	int p, x;
	for (int y = 1; y < n; ++y) {
		p = *(T + y);
		x = y - 1;
		while (x >= 0 && *(T + x) > p)
			*(T + x + 1) = *(T + x--);
		*(T + x + 1) = p;
	}
}

int main() {
	int T[] = { 5, 1, 13, 2, 3, 55, 21, 0, 8, 34, 1 };
	int n = 11;

	InsertSort(T, n);

	for (int e : T)
		printf("%d ", e);

	// --- OUTPUT --- //
	//0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
}