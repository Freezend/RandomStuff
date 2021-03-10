def BubbleSort(T):
	for y in range(0, len(T) - 1):
		for x in range(0, len(T) - y - 1):
			if T[x] > T[x+1]:
				T[x], T[x+1] = T[x+1], T[x]
	return T

T = [ 5, 1, 13, 2, 3, 55, 21, 0, 8, 34, 1 ]
T = BubbleSort(T)
for i in range(0, len(T)):
	print(T[i])

# --- OUTPUT --- #
# 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55