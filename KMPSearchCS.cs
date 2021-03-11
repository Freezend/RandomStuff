using System;

namespace KMPSearchCS {
	class Program {
		static int[] pref(string P) {
			int k = 0, m = P.Length;
			int[] pi = new int[m];
			pi[0] = 0;
			for (int i = 1; i < m; ++i) {
				while (k != 0 && P[k] != P[i])
					k = pi[k - 1];
				if (P[k] == P[i])
					++k;
				pi[i] = k;
			}
			return pi;
		}
		static int KMP(string T, string P) {
			int k = 0, n = T.Length, m = P.Length;
			int[] pi = pref(P);
			for (int i = 0; i < n; i++) {
				while (k != 0 && P[k] != T[i])
					k = pi[k - 1];
				if (P[k] == T[i])
					k++;
				if (k == m) {
					return i - m + 1;
				}
			}
			return -1;
		}
		static void Main() {
			string T = "abracadabra";
			string P = "adabr";

			int k = KMP(T, P);

			Console.Write(k);

			// --- OUTPUT --- //
			// 5
		}
	}
}
