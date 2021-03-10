#include <stdio.h>
#include <stdlib.h>

char* RMS(int n, char* m, char* s, int l, int u = 0, int k = 0, int t = 0) {
	int x = (n + 1) * k;

	if (n - u >= 2) {
		for (int q = 0; q < 4; ++q)
			for (int i = 1; i < n - u; ++i) {
				*(m + x) = *(s + ((t++) % l));
				switch (q) {
				case 0:
					++x;
					break;
				case 1:
					x += n;
					break;
				case 2:
					--x;
					break;
				default:
					x -= n;
					break;
				}
			}
	} else if (n - u == 1) {
		*(m + x) = *(s + t%l);
	}
	if (n - u > 2)
		return RMS(n, m, s, l, u + 2, k + 1, t);
	else
		return m;
}

int main() {
	int n = 13;
	char* m = (char*)malloc(n * n * sizeof(char));
	char s[] = "AlaHasACat!";
	int l = 11;
	m = RMS(n, m, s, l);

	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < n; ++x)
			printf("%c", *(m + y * n + x));
		printf("\n");
	}

	free(m);

	// --- OUTPUT --- //
	// AlaHasACat!Al
	// HasACat!AlaHa
	// a!AlaHasACaaH
	// ltt!AlaHastsa
	// AaaAlaHasA!As
	// !CC!sACaACACA
	// tAAtaaHtCalaC
	// assaHlA!atata
	// CaaCalA!t!H!t
	// AHHAsaHalAaA!
	// saalA!taCAslA
	// alA!taCAsaHal
	// HalA!taCAsaHa
}