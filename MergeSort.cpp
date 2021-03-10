#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void MergeSort(int* T, int n) {
	if (n > 1) {
		int l = n / 2, i = 0, j = 0, k = 0;
		int* L = new int[l];
		int* R = new int[n - l];
		memset(L, 0, l * sizeof(int));
		memset(R, 0, (n - l) * sizeof(int));
		for (int z = 0; z < n; ++z)
			if (z < l)
				*(L + z) = *(T + z);
			else
				*(R + z - l) = *(T + z);
		MergeSort(L, l);
		MergeSort(R, n - l);
		while (i < l && j < n - l)
			if (*(L + i) < *(R + j))
				*(T + k++) = *(L + i++);
			else
				*(T + k++) = *(R + j++);

		while (i < l)
			*(T + k++) = *(L + i++);

		while (j < n - l)
			*(T + k++) = *(R + j++);
		
		delete[] L, R;
	}
}

int main() {
	int T[] = { 5, 1, 13, 2, 3, 55, 21, 0, 8, 34, 1 };
	int n = 11;

	MergeSort(T, n);

	for (int e : T)
		printf("%d ", e);

	// --- OUTPUT --- //
	//0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
}