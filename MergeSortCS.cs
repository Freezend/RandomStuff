using System;

namespace MergeSortCS {
	class Program {
		static int[] MergeSort(int[] T) {
			if (T.Length > 1) {
				int l = T.Length / 2, i = 0, j = 0, k = 0;
				int[] L = new int[l], R = new int[T.Length - l];
				for (int z = 0; z < T.Length; ++z)
					if (z < l)
						L[z] = T[z];
					else
						R[z - l] = T[z];

				MergeSort(L);
				MergeSort(R);

				while (i < L.Length && j < R.Length)
					if (L[i] < R[j])
						T[k++] = L[i++];
					else
						T[k++] = R[j++];

				while (i < L.Length)
					T[k++] = L[i++];

				while (j < R.Length)
					T[k++] = R[j++];
			}

			return T;
		}
		static void Main() {
			int[] T = { 5, 1, 13, 2, 3, 55, 21, 0, 8, 34, 1 };

			MergeSort(T);

			foreach (int e in T)
				Console.Write(e + " ");

			// --- OUTPUT --- //
			//0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
		}
	}
}
