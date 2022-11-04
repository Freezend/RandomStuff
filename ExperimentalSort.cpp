#include <stdio.h>
#include <string.h>

void InsertBinarySort(int* T, int n) {
	int y, m, l, r, w, p;
	for (y = 1; y < n; ++y) {
		l = 0, r = y - 1, p = T[y];

		while (true)
			if (l < r) {
				m = (l + r) / 2;
				if (p < T[m])
					r = m - 1;
				else
					l = m + 1;
			} else {
				w = (p < T[l]) ? l : (l + 1);
				break;
			}

		for (int a = 0; a < n; ++a) if (a == y) printf("<%d> ", T[a]); else if (a == w) printf(">%d< ", T[a]); else printf("%d ", T[a]); printf("\n");
		
		memcpy((T + w + 1), (T + w), (y - w) * sizeof(int));
		T[w] = p;

		//l = y, r = y + 1;
		//while (--r > w)
		//	T[r] = T[--l];
		//T[r] = p;
	}
}

int main() {
	int I2[] = { 2, 1, 13, 2, 3, 55, 21, 0, 8, 34, 1, 2, 3, 55, 34, 5, 1, 34, 1, 6 };
	int n2 = 20;

	InsertBinarySort(I2, n2);

	for (int e : I2)
		printf("%d ", e);
}
