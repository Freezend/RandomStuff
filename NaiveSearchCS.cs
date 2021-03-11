using System;

namespace NaiveSearchCS {
	class Program {
		static int NaiveSearch(string T, string P) {
			int j, s = 0, n = T.Length, m = P.Length;
			while (s <= n - m) {
				j = 0;
				while (j < m)
					if (P[j] == T[j + s])
						++j;
					else
						break;
				if (j == m)
					return s;
				++s;
			}
			return -1;
		}
		static void Main() {
			string T = "abracadabra";
			string P = "adabr";

			int s = NaiveSearch(T, P);

			Console.Write(s);

			// --- OUTPUT --- //
			// 5
		}
	}
}
