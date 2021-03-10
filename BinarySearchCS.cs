using System;

namespace BinarySearchCS {
	class Program {
		static int BSIterative(int[] A, int x) {
			int n = A.Length, m = 0, l = 0, r = n - 1;
			while (l <= r) {
				m = (l + r) / 2;
				if (A[m] == x)
					return m;
				else if (A[m] > x)
					r = m - 1;
				else
					l = m + 1;
			}
			return -1;
		}

		static int BSRecursively(int[] A, int x, int l = 0, int r = -1) {
			int m = 0;
			if (r < 0)
				r = A.Length;
			if (l <= r) {
				m = (l + r) / 2;
				if (A[m] == x)
					return m;
				else if (A[m] > x)
					return BSRecursively(A, x, l, m - 1);
				else
					return BSRecursively(A, x, m + 1, r);
			}
			return -1;
		}

		static void Main() {
			int[] I = { 1, 3, 5, 6, 6, 8, 11, 14, 16, 18, 19, 24 };
			int x = 11;

			int O1 = BSIterative(I, x);
			int O2 = BSRecursively(I, x);

			Console.Write("Iterative: " + O1 + "\nRecursively: " + O2);

			// --- OUTPUT --- //
			// Iterative: 6
			// Recursively: 6
		}
	}
}
