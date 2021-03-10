using System;
using System.Collections.Generic;

namespace HeapSortCS {
	class Heap {
		private List<int> T;
		public Heap() {
			this.T = new List<int>();
		}
		public Heap(List<int> T) {
			this.T = T;
		}
		private int Max(int i, int j) {
			if (j < 2 * i + 1)
				return i;
			if (j == 2 * i + 1)
				return (T[i] >= T[2 * i + 1]) ? i : (2 * i + 1);
			if (T[i] >= T[2 * i + 1])
				return (T[i] >= T[2 * i + 2]) ? i : (2 * i + 2);
			return (T[2 * i + 1] >= T[2 * i + 2]) ? (2 * i + 1) : (2 * i + 2);
		}
		private void Heapify(int i, int j) {
			int k = Max(i, j);
			if (k != i) {
				(T[i], T[k]) = (T[k], T[i]);
				Heapify(k, j);
			}
		}
		private void DelMax(int i) {
			(T[0], T[i]) = (T[i], T[0]);
			Heapify(0, i - 1);
		}
		public void Build() {
			for (int i = ((T.Count - 2) / 2); i >= 0; --i)
				Heapify(i, T.Count - 1);
		}
		public void HeapSort() {
			Build();
			for (int i = T.Count - 1; i >= 1; --i)
				DelMax(i);
		}
		public void Show() {
			for (int i = 0; i < T.Count; ++i)
				Console.Write(T[i] + " ");
		}
	}
	class Program {
		static void Main() {
			List<int> T = new List<int> { 5, 1, 13, 2, 3, 55, 21, 0, 8, 34, 1 };
			Heap H = new Heap(T);

			H.HeapSort();

			H.Show();

			// --- OUTPUT --- //
			//0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
		}
	}
}
