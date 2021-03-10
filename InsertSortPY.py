def InsertSort(T):
	for y in range(1, len(T)):
		p = T[y]
		x = y - 1
		while x >= 0 and T[x] > p:
			T[x + 1] = T[x]
			x = x - 1
		T[x + 1] = p
	return T

T = [ 5, 1, 13, 2, 3, 55, 21, 0, 8, 34, 1 ]
T = InsertSort(T)
for i in range(0, len(T)):
	print(T[i])

# --- OUTPUT --- #
# 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55