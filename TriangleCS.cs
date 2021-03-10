using System;

namespace TriangleCS {
	class Program {
		static void Triangle(int y, int x = 0) {
			if (y > 2)
				Triangle(y - 2, x + 1);
			for (int i = x * 2 + y; i > 0; --i)
				if (i > x && i <= x + y)
					Console.Write("*");
				else
					Console.Write(" ");
			Console.Write("\n");
		}
		static void Main() {
			int x = 7;

			Triangle(x);

			// --- OUTPUT --- //
			//    *   
			//   ***  
			//  ***** 
			// *******
		}
	}
}
