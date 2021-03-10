using System;
using System.Collections.Generic;

namespace FibonacciCS {
	class Program {
		static List<int> FibIterative(int n) {
			List<int> O = new List<int>();
			if (n >= 0) {
				O.Add(0);
				if (n > 0) {
					O.Add(1);
					for (int i = 2; i <= n; ++i)
						O.Add(O[i - 1] + O[i - 2]);
				}
			}
			return O;
		}
		static List<int> FibRecursively(int n, List<int> O) {
			if (O.Count <= n) {
				if (O.Count == 0)
					O.Add(0);
				else if (O.Count == 1)
					O.Add(1);
				else
					O.Add(O[O.Count - 1] + O[O.Count - 2]);
				return FibRecursively(n, O);
			} else {
				return O;
			}
		}
		static void Main() {
			List<int> O;
			int n = 10;

			Console.Write("Iterative: ") ;
			O = FibIterative(n);
			foreach (int x in O)
				Console.Write(x + " ");

			Console.Write("\nRecursively: ");
			O = FibRecursively(n, new List<int>());
			foreach (int x in O)
				Console.Write(x + " ");

			// --- OUTPUT --- //
			//Iterative: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
			//Recursively: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
		}
	}
}
