#include <stdio.h>
#include <malloc.h>

char* MS(int n, char* m, char* s, int l, int u = 0, int k = 0) {
	int x = (n + 1) * k, t = 0;

	if (n - u >= 2) {
		for (int q=0; q<4; ++q)
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
		*(m + x) = *s;
	}
	if (n - u > 2)
		return MS(n, m, s, l, u + 2, k + 1);
	else
		return m;
}

int main() {
	char s[] = "AlaHasACat!";
	int n = 13;
	char* m = (char*)malloc(n * n * sizeof(char));
	int l = 11;
	m = MS(n, m, s, l);

	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < n; ++x)
			printf("%c", *(m + y * n + x));
		printf("\n");
	}

	free(m);

	// --- OUTPUT --- //
	// AlaHasACat!Al
	// HAlaHasACat!a
	// aAAlaHasACaAH
	// lstAlaHasAtla
	// AaalAlaHaC!as
	// !HCAaAlasaAHA
	// taA!HCAHAtlaC
	// alstaAsaC!asa
	// CAaalA!taAHAt
	// A!HCAsaHalaC!
	// stalA!taCAsaA
	// aaCAsaHalA!tl
	// HalA!taCAsaHa
}