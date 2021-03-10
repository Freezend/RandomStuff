using System;

namespace KnapsackCS {
	class Program {
		static (int[,], int[,]) Knapsack(int[] p, int[] w, int n, int W) {
			int x;
			int[,] S1 = new int[W + 1, n + 1];
			int[,] S2 = new int[W + 1, n + 1];
			for (int i = 0; i <= W; i++) {
				S1[i, 0] = S2[i, 0] = 0;
			}
			for (int i = 0; i <= n; i++) {
				S1[0, i] = S2[0, i] = 0;
			}
			for (int i = 1; i <= W; i++)
				for (int j = 1; j <= n; j++)
					if (i - w[j - 1] >= 0) {
						x = S1[i - w[j - 1], j - 1] + p[j - 1];
						if (x < S1[i, j - 1]) {
							S1[i, j] = S1[i, j - 1];
							S2[i, j] = 0;
						} else {
							S1[i, j] = x;
							S2[i, j] = 1;
						}
					} else {
						S1[i, j] = S1[i, j - 1];
						S2[i, j] = 0;
					}
			return (S1, S2);
		}
		static void Main() {
			int[] p = { 2, 4, 2, 2 };
			int[] w = { 2, 3, 1, 2 };
			int n = 4;
			int W = 6;
			int[,] S1, S2;

			(S1, S2) = Knapsack(p, w, n, W);

			for (int y = 0; y <= W; ++y) {
				for (int x = 0; x <= n; ++x) {
					Console.Write(S1[y, x] + " ");
				}
				Console.Write("\n");
			}
			Console.Write("\n");
			for (int y = 0; y <= W; ++y) {
				for (int x = 0; x <= n; ++x) {
					Console.Write(S2[y, x] + " ");
				}
				Console.Write("\n");
			}

			// --- OUTPUT --- //
			// 0 0 0 0 0
			// 0 0 0 2 2
			// 0 2 2 2 2
			// 0 2 4 4 4
			// 0 2 4 6 6
			// 0 2 6 6 6
			// 0 2 6 8 8

			// 0 0 0 0 0
			// 0 0 0 1 0
			// 0 1 0 1 1
			// 0 1 1 1 1
			// 0 1 1 1 0
			// 0 1 1 1 1
			// 0 1 1 1 1
		}
	}
}
