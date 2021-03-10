using System;

namespace SelectSortCS {
	class Program {
		static void SelectSort(int[] T) {
			int p, n = T.Length;
			for (int y = 0; y < n - 1; ++y) {
				p = y;
				for (int x = y + 1; x < n; ++x)
					if (T[x] < T[p])
						p = x;
				(T[y], T[p]) = (T[p], T[y]);
			}
		}
		static void Main() {
			int[] T = { 5, 1, 13, 2, 3, 55, 21, 0, 8, 34, 1 };

			SelectSort(T);

			foreach (int e in T)
				Console.Write(e + " ");

			// --- OUTPUT --- //
			//0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
		}
	}
}
