#include <stdio.h>

void SelectSort(int* T, int n) {
	int p, t;
	for (int y = 0; y < n - 1; ++y) {
		p = y;
		for (int x = y + 1; x < n; ++x)
			if (*(T + x) < *(T + p))
				p = x;
		t = *(T + y);
		*(T + y) = *(T + p);
		*(T + p) = t;
	}
}

int main() {
	int T[] = { 5, 1, 13, 2, 3, 55, 21, 0, 8, 34, 1 };
	int n = 11;

	SelectSort(T, n);

	for (int e : T)
		printf("%d ", e);

	// --- OUTPUT --- //
	//0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
}