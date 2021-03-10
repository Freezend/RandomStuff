using System;

namespace CountSortCS {
	class Program {
		static void CountSort(int[] T, int k) {
			int n = T.Length;
			int[] B = new int[n];
			int[] D = new int[k + 1];
			Array.Clear(B, 0, B.Length);
			Array.Clear(D, 0, D.Length);
			for (int i = 0; i < n; ++i)
				++D[T[i]];
			for (int i = 1; i <= k; ++i)
				D[i] += D[i - 1];
			for (int i = n - 1; i >= 0; --i) {
				B[D[T[i]] - 1] = T[i];
				--D[T[i]];
			}
			for (int i = 0; i < n; ++i)
				T[i] = B[i];
		}
		static void Main() {
			int[] T = { 5, 1, 13, 2, 3, 55, 21, 0, 8, 34, 1 };
			int k = 100;

			CountSort(T, k);

			foreach (int e in T)
				Console.Write(e + " ");

			// --- OUTPUT --- //
			//0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
		}
	}
}
