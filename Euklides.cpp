#include <stdio.h>

int Euklides(int a, int b) {
	if (b > 0)
		return Euklides(b, a % b);
	else if (b == 0)
		return a;
	else
		return -1;
}

int main() {
	int a = 54;
	int b = 69;

	int O = Euklides(a, b);

	printf("%d", O);
}