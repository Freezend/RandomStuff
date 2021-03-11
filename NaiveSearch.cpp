#include <stdio.h>

int NaiveSearch(char* T, char* P, int n, int m) {
	int j, s = 0;
	while (s <= n - m) {
		j = 0;
		while (j < m)
			if (P[j] == T[j + s])
				++j;
			else
				break;
		if (j == m)
			return s;
		++s;
	}
	return -1;
}

int main() {
	char T[] = "abracadabra";
	char P[] = "adabr";
	int n = 11;
	int m = 5;

	int s = NaiveSearch(T, P, n, m);

	printf("%d", s);

	// --- OUTPUT --- //
	// 5
}