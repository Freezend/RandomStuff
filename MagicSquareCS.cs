using System;

namespace MagicSquareCS {
	class Program {
		static char[,] MS(int n, char[,] m, string s, int k = 0) {
			int x = k, y = k, t = 0;

			if (n >= 2) {
				for (int i = 1; i < n; ++i)
					m[y, x++] = s[t++ % s.Length];
				for (int i = 1; i < n; ++i)
					m[y++, x] = s[t++ % s.Length];
				for (int i = 1; i < n; ++i)
					m[y, x--] = s[t++ % s.Length];
				for (int i = 1; i < n; ++i)
					m[y--, x] = s[t++ % s.Length];
			} else if (n == 1) {
				m[y, x] = s[0];
			}

			if (n > 2)
				return MS(n - 2, m, s, k + 1);
			else
				return m;
		}
		static void Main() {
			int n = 13;
			char[,] m = new char[n, n];
			string s = "AlaHasACat!";
			m = MS(n, m, s);

			for (int y = 0; y < n; ++y) {
				for (int x = 0; x < n; ++x)
					Console.Write(m[y, x]);
				Console.Write("\n");
			}

			// --- OUTPUT --- //
			// AlaHasACat!Al
			// HAlaHasACat!a
			// aAAlaHasACaAH
			// lstAlaHasAtla
			// AaalAlaHaC!as
			// !HCAaAlasaAHA
			// taA!HCAHAtlaC
			// alstaAsaC!asa
			// CAaalA!taAHAt
			// A!HCAsaHalaC!
			// stalA!taCAsaA
			// aaCAsaHalA!tl
			// HalA!taCAsaHa
		}
	}
}
