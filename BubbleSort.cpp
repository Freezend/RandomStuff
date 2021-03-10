#include <stdio.h>

void BubbleSort(int* T, int n) {
	int t;
	for (int y = 0; y < n - 1; ++y)
		for (int x = 0; x < n - y - 1; ++x)
			if (*(T + x) > *(T + x + 1)) {
				t = *(T + x);
				*(T + x) = *(T + x + 1);
				*(T + x + 1) = t;
			}
}

int main() {
	int T[] = { 5, 1, 13, 2, 3, 55, 21, 0, 8, 34, 1 };
	int n = 11;

	BubbleSort(T, n);

	for (int e : T)
		printf("%d ", e);

	// --- OUTPUT --- //
	//0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
}