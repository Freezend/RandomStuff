using System;

namespace BubbleSortCS {
	class Program {
		static void BubbleSort(int[] T) {
			int n = T.Length;
			for (int y = 0; y < n - 1; ++y)
				for (int x = 0; x < n - y - 1; ++x)
					if (T[x] > T[x + 1])
						(T[x], T[x + 1]) = (T[x + 1], T[x]);
		}
		static void Main() {
			int[] T = { 5, 1, 13, 2, 3, 55, 21, 0, 8, 34, 1 };

			BubbleSort(T);

			foreach (int e in T)
				Console.Write(e + " ");

			// --- OUTPUT --- //
			//0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
		}
	}
}
