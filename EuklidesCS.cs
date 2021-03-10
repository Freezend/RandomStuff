using System;

namespace EuklidesCS {
	class Program {
		static int Euklides(int a, int b) {
			if (b > 0)
				return Euklides(b, a % b);
			else if (b == 0)
				return a;
			else
				return -1;
		}
		static void Main() {
			int a = 54;
			int b = 69;

			int O = Euklides(a, b);

			Console.Write(O);
		}
	}
}
