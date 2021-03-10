#include <stdio.h>

void Hanoi(int n, char A, char B, char C) {
	if (n > 0) {
		Hanoi(n - 1, A, C, B);
		printf("%c -> %c\n", A, C);
		Hanoi(n - 1, B, A, C);
	}
}

int main() {
	Hanoi(3,'1','2','3');

	// --- OUTPUT --- //
	// 1 -> 3
	// 1 -> 2
	// 3 -> 2
	// 1 -> 3
	// 2 -> 1
	// 2 -> 3
	// 1 -> 3
}