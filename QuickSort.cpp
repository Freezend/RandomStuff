#include <stdio.h>

void QuickSort(int* T, int l, int r) {
	if (l < r) {
		int v = *(T+l), i = l, j = r + 1, p;
		do {
			do { ++i; } while (*(T + i) < v && i < r);
			do { --j; } while (*(T + j) > v);
			if (i < j) {
				p = *(T + i);
				*(T + i) = *(T + j);
				*(T + j) = p;
			}
		} while (i < j);
		*(T + l) = *(T + j);
		*(T + j) = v;
		QuickSort(T, l, j - 1);
		QuickSort(T, j + 1, r);
	}
}

int main() {
	int T[] = { 5, 1, 13, 2, 3, 55, 21, 0, 8, 34, 1 };
	int n = 11;

	QuickSort(T, 0, n - 1);

	for (int e : T)
		printf("%d ", e);

	// --- OUTPUT --- //
	//0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
}