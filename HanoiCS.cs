using System;

namespace HanoiCS {
	class Program {
		static void Hanoi(int n, char A, char B, char C) {
			if (n > 0) {
				Hanoi(n - 1, A, C, B);
				Console.Write(A+" -> "+C+"\n");
				Hanoi(n - 1, B, A, C);
			}
		}
		static void Main() {
			Hanoi(3, '1', '2', '3');

			// --- OUTPUT --- //
			// 1 -> 3
			// 1 -> 2
			// 3 -> 2
			// 1 -> 3
			// 2 -> 1
			// 2 -> 3
			// 1 -> 3
		}
	}
}