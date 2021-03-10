#include <stdio.h>

void Triangle(int y, int x = 0) {
	if (y > 2)
		Triangle(y - 2, x + 1);
	for (int i = x * 2 + y; i > 0; --i)
		if (i > x && i <= x + y)
			printf("*");
		else
			printf(" ");
	printf("\n");
}

int main() {
	int x = 7;

	Triangle(x);

	// --- OUTPUT --- //
	//    *   
	//   ***  
	//  ***** 
	// *******
}