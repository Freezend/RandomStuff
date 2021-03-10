using System;

namespace InsertSortCS {
	class Program {
		static void InsertSort(int[] T) {
			int p, x;
			for (int y = 1; y < T.Length; ++y) {
				p = T[y];
				x = y - 1;
				while (x >= 0 && T[x] > p)
					T[x + 1] = T[x--];
				T[x + 1] = p;
			}
		}
		static void Main() {
			int[] T = { 5, 1, 13, 2, 3, 55, 21, 0, 8, 34, 1 };

			InsertSort(T);

			foreach (int e in T)
				Console.Write(e + " ");

			// --- OUTPUT --- //
			//0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
		}
	}
}
