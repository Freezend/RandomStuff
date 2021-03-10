#include <iostream>

int* FibIterative(int n) {
	int* O = new int[n+1];
	if (n >= 0) {
		O[0] = 0;
		if (n > 0) {
			O[1] = 1;
			for (int i = 2; i <= n; ++i)
				O[i] = O[i - 1] + O[i - 2];
		}
	}
	return O;
}
int* FibRecursively(int n, int* O, int i = 0) {
	if (i == 0)
		O = new int[n + 1];
	if (i <= n) {
		if (i == 0)
			O[0] = 0;
		else if (i == 1)
			O[1] = 1;
		else
			O[i] = O[i - 1] + O[i - 2];
		return FibRecursively(n, O, i+1);
	} else {
		return O;
	}
}
int main() {
	int n = 10;
	int* O = new int[n + 1];

	printf("Iterative: ");
	O = FibIterative(n);
	for(int x=0; x<=n; ++x)
		printf("%d ", O[x]);

	printf("\nRecursively: ");
	O = FibRecursively(n, O);
	for (int x = 0; x <= n; ++x)
		printf("%d ", O[x]);

	delete[] O;

	// --- OUTPUT --- //
	//Iterative: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
	//Recursively: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
}