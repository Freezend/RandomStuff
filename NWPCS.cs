using System;

namespace NWPCS {
	class Program {
		static int[,] NWP2(string a, string b) {
			int x = a.Length, y = b.Length;
			int[,] S = new int[x + 1, y + 1];
			for (int i = 0; i <= x; i++)
				S[i,0] = 0;
			for (int i = 0; i <= y; i++)
				S[0,i] = 0;
			for (int i = 1; i <= x; i++)
				for (int j = 1; j <= y; j++)
					if (a[i-1] == b[j-1])
						S[i,j] = S[i-1,j-1] + 1;
					else
						S[i,j] = (S[i-1,j] >= S[i,j-1]) ? S[i-1,j] : S[i,j-1];
			return S;
		}
		static string NWP(string a, string b) {
			int[,] S = NWP2(a, b);
			string s = "";
			int x = a.Length, y = b.Length;
			do {
				if (a[x-1] == b[y-1]) {
					s += a[x-1];
					--x;
					--y;
				} else if (S[x-1, y] >= S[x, y-1])
					--x;
				else
					--y;
			} while (S[x, y] != 0);
			return Reverse(s);
		}
		static string Reverse(string s) {
			string s2 = "";
			for (int x = s.Length - 1; x >= 0; --x)
				s2 += s[x];
			return s2;
		}
		static void Main() {
			string a = "abrakadabra";
			string b = "banaraba";

			string c = NWP(a, b);

			Console.Write(c);
		}
	}
}
