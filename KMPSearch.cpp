#include <stdio.h>

int* pref(char* P, int m) {
	int k = 0;
	int* pi = new int[m];
	pi[0] = 0;
	for (int i = 1; i < m; ++i) {
		while (k && P[k] != P[i])
			k = pi[k-1];
		if (P[k] == P[i])
			++k;
		pi[i] = k;
	}
	return pi;
}

int KMP(char* T, char* P, int n, int m) {
	int k = 0;
	int* pi = pref(P, m);
	for (int i = 0; i < n; i++) {
		while (k && P[k] != T[i])
			k = pi[k - 1];
		if (P[k] == T[i])
			k++;
		if (k == m) {
			delete[] pi;
			return i - m + 1;
		}
	}
	delete[] pi;
	return -1;
}

int main() {
	char T[] = "abracadabra";
	char P[] = "adabr";
	int n = 11;
	int m = 5;

	int k = KMP(T, P, n, m);

	printf("%d", k);

	// --- OUTPUT --- //
	// 5
}