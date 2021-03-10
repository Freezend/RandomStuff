#include <stdio.h>

typedef struct Heap {
	int* T;
	int n;
};

int Max(Heap H, int i, int j) {
	if (j < 2 * i + 1)
		return i;
	if (j == 2 * i + 1)
		return (*(H.T + i) >= *(H.T + 2 * i + 1)) ? i : (2 * i + 1);
	if (*(H.T + i) >= *(H.T + 2 * i + 1))
		return (*(H.T + i) >= *(H.T + 2 * i + 2)) ? i : (2 * i + 2);
	return (*(H.T + 2 * i + 1) >= *(H.T + 2 * i + 2)) ? (2 * i + 1) : (2 * i + 2);
}

void Heapify(Heap H, int i, int j) {
	int p, k = Max(H, i, j);
	if (k != i) {
		p = *(H.T + i);
		*(H.T + i) = *(H.T + k);
		*(H.T + k) = p;
		Heapify(H, k, j);
	}
}

void Build(Heap H) {
	for (int i = ((H.n - 2) / 2); i >= 0; --i)
		Heapify(H, i, H.n - 1);
}

void Show(Heap H) {
	for (int i = 0; i < H.n; ++i)
		printf("%d ", *(H.T + i));
}

void DelMax(Heap H, int i) {
	int p = *(H.T + i);
	*(H.T + i) = *H.T;
	*H.T = p;
	Heapify(H, 0, i - 1);
}

void HeapSort(Heap H) {
	Build(H);
	for (int i = H.n - 1; i >= 1; --i)
		DelMax(H, i);
}

int main() {
	int T[] = { 5, 1, 13, 2, 3, 55, 21, 0, 8, 34, 1 };
	int n = 10;
	Heap H = { T, n };

	HeapSort(H);

	Show(H);

	// --- OUTPUT --- //
	//0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
}