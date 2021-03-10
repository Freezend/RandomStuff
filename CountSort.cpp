#include <stdio.h>
#include <string.h>

void CountSort(int* T, int n, int k) {
	int* B = new int[n];
	int* D = new int[k + 1];
	memset(B, 0, n * sizeof(int));
	memset(D, 0, (k + 1) * sizeof(int));
	for (int i = 0; i < n; ++i)
		++*(D + *(T + i));
	for (int i = 1; i <= k; ++i)
		*(D + i) += *(D + i - 1);
	for (int i = n - 1; i >= 0; --i) {
		*(B + *(D + *(T + i)) - 1) = *(T + i);
		--*(D + *(T + i));
	}
	for (int i = 0; i < n; ++i)
		*(T + i) = *(B + i);
	delete[] D, B;
}

int main() {
	int T[] = { 5, 1, 13, 2, 3, 55, 21, 0, 8, 34, 1 };
	int n = 11, k = 100;

	CountSort(T, n, k);

	for (int e : T)
		printf("%d ", e);

	// --- OUTPUT --- //
	//0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
}