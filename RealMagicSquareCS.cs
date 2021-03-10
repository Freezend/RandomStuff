using System;

namespace RealMagicSquareCS {
	class Program {
		static char[,] RMS(int n, char[,] m, string s, int k = 0, int t = 0) {
			int x = k, y = k;

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
				m[y, x] = s[t % s.Length];
			}

			if (n > 2)
				return RMS(n - 2, m, s, k + 1, t);
			else
				return m;
		}
		static void Main() {
			int n = 13;
			char[,] m = new char[n, n];
			string s = "AlaHasACat!";
			m = RMS(n, m, s);

			for (int y = 0; y < n; ++y) {
				for (int x = 0; x < n; ++x)
					Console.Write(m[y, x]);
				Console.Write("\n");
			}

			// --- OUTPUT --- //
			// AlaHasACat!Al
			// HasACat!AlaHa
			// a!AlaHasACaaH
			// ltt!AlaHastsa
			// AaaAlaHasA!As
			// !CC!sACaACACA
			// tAAtaaHtCalaC
			// assaHlA!atata
			// CaaCalA!t!H!t
			// AHHAsaHalAaA!
			// saalA!taCAslA
			// alA!taCAsaHal
			// HalA!taCAsaHa
		}
	}
}
