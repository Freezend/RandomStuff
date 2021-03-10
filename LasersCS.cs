using System;
using System.Collections.Generic;

namespace LasersCS {
	class Program {
		class BAR {
			private int x1;
			private int y1;
			private int x2;
			private int y2;
			public BAR(int x1, int y1, int x2, int y2) {
				this.x1 = x1;
				this.y1 = y1;
				this.x2 = x2;
				this.y2 = y2;
			}
			public int GetY1() {
				return y1;
			}
			public int GetY2() {
				return y2;
			}
		}
		class LASER {
			private int y1;
			private int y2;
			public LASER(int y1, int y2) {
				this.y1 = y1;
				this.y2 = y2;
			}
			public int GetY1() {
				return y1;
			}
			public int GetY2() {
				return y2;
			}
		}
		static List<LASER> BubbleSort(List<LASER> LS) {
			for (int y = 0; y < LS.Count - 1; ++y)
				for (int x = 0; x < LS.Count - y - 1; ++x)
					if (LS[x].GetY1() > LS[x + 1].GetY1())
						(LS[x], LS[x + 1]) = (LS[x + 1], LS[x]);
			return LS;
		}
		static List<LASER> Check(BAR[] B, int n) {
			List<LASER> I = new List<LASER>();
			List<LASER> O = new List<LASER>();
			int m = B.Length;

			for (int x = 0; x < m; ++x)
				I.Add(new LASER(B[x].GetY1(), B[x].GetY2()));

			I = BubbleSort(I);

			for (int x = 0, i = 0; x <= m; ++x) {
				if (x < m) {
					if (i < I[x].GetY1())
						O.Add(new LASER(i, I[x].GetY1()));
					i = I[x].GetY2();
				} else if (i < n) {
					O.Add(new LASER(i, n));
				}
			};

			return O;
		}
		static void Main() {
			BAR[] B = { new BAR(2, 5, 2, 6), new BAR(4, 1, 4, 4), new BAR(4, 10, 10, 10), new BAR(1, 6, 5, 9), new BAR(3, 8, 7, 9) };
			int n = 11;

			List<LASER> LS = Check(B, n);

			for (int x = 0; x < LS.Count; ++x)
				Console.Write("(" + LS[x].GetY1() + "," + LS[x].GetY2() + ") ");

			// --- OUTPUT --- //
			//(0,1) (4,5) (9,10) (10,11)
		}
	}
}
