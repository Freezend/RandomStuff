#include <stdio.h>

int BSIterative(int *A, int n, int x) {
	int m = 0, l = 0, r = n - 1;
	while (l <= r) {
		m = (l + r) / 2;
		if (A[m] == x)
			return m;
		else if (A[m] > x)
			r = m - 1;
		else
			l = m + 1;
	}
	return -1;
}

int BSRecursively(int *A, int r, int x, int l = 0) {
	int m = 0;
	if (l <= r) {
		m = (l + r) / 2;
		if (A[m] == x)
			return m;
		else if (A[m] > x)
			return BSRecursively(A, m - 1, x, l);
		else
			return BSRecursively(A, r, x, m + 1);
	}
	return -1;
}

int main() {
	int I[] = { 1, 3, 5, 6, 6, 8, 11, 14, 16, 18, 19, 24 };
	int n = 12;
	int x = 11;

	int O1 = BSIterative(I, n, x);
	int O2 = BSRecursively(I, n, x);

	printf("Iterative: %d\nRecursively: %d", O1, O2);

	// --- OUTPUT --- //
	// Iterative: 6
	// Recursively: 6
}