using System;
using System.Collections.Generic;

namespace HighestSectionCS {
	class Program {
		public class HS {
			private List<int> T;
			private int s;
			public HS() {
				this.T = new List<int>();
				this.s = 0;
			}
			public HS(List<int> T, int s) {
				this.T = new List<int>(T);
				this.s = s;
			}
			public HS Clone() {
				return new HS(this.T, this.s);
			}
			public void Insert(int x) {
				this.T.Add(x);
				this.s += x;
			}
			public List<int> GetT() {
				return this.T;
			}
			public int GetS() {
				return this.s;
			}
		}
		static HS HighestSection(int[] I) {
			HS O = new HS();
			HS M = new HS();

			foreach (int x in I) {
				if (O.GetS() < 0)
					O = new HS();
				O.Insert(x);
				if (O.GetS() > M.GetS())
					M = O.Clone();
			};

			return M;
		}
		static void Main() {
			int[] T = { 6, -10, 5, -1, 4, 8, -3, 9, 11, -40, 6, 18 };

			HS O = HighestSection(T);

			Console.Write("Numbers:");
			foreach (int x in O.GetT())
				Console.Write(" " + x);
			Console.Write("\nSum: " + O.GetS());

			// --- OUTPUT --- //
			//Numbers: 5 -1 4 8 -3 9 11
			//Sum: 33
		}
	}
}
