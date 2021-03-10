#include <stdio.h>
#include <string.h>

char* Reverse(char* s, int n) {
	char* s2 = new char[n + 1];
	memset(s2, '\0', (n + 1) * sizeof(char));
	for (int x = 0; x < n; ++x)
		*(s2 + x) = *(s + n - x - 1);
	delete[] s;
	return s2;
}

int** NWP2(char* a, char* b, int x, int y) {
	int** S = new int*[x + 1];
	for (int i = 0; i <= x; i++)
		S[i] = new int[y + 1];
	for (int i = 0; i <= x; i++)
		S[i][0] = 0;
	for (int i = 0; i <= y; i++)
		S[0][i] = 0;
	for (int i = 1; i <= x; i++)
		for (int j = 1; j <= y; j++)
			if (a[i - 1] == b[j - 1])
				S[i][j] = S[i - 1][j - 1] + 1;
			else
				S[i][j] = (S[i - 1][j] >= S[i][j - 1]) ? S[i - 1][j] : S[i][j - 1];
	return S;
}

char* NWP(char* a, char* b, int x, int y) {
	int** S = NWP2(a, b, x, y);
	char* s = new char[x + 1];
	memset(s, '\0', (x + 1) * sizeof(char));
	int z = 0;
	do {
		if (a[x - 1] == b[y - 1]) {
			s[z++] = a[x - 1];
			--x;
			--y;
		} else if (S[x - 1][y] >= S[x][y - 1]) {
			--x;
		} else {
			--y;
		}
	} while (S[x][y]);
	delete[] S;
	return Reverse(s, z);
}

int main() {
	char a[] = "abrakadabra";
	char b[] = "banaraba";
	int x = 11;
	int y = 8;

	char* c = NWP(a, b, x, y);

	printf("%s", c);

	delete[] c;

	// --- OUTPUT --- //
	// baaaba
}