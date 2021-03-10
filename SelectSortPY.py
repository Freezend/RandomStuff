def SelectSort(T):
	for y in range(0, len(T) - 1):
		p = y
		for x in range(y + 1, len(T)):
			if T[x] < T[p]:
				p = x
		T[y], T[p] = T[p], T[y]
	return T

T = [ 5, 1, 13, 2, 3, 55, 21, 0, 8, 34, 1 ]
T = SelectSort(T)
for i in range(0, len(T)):
	print(T[i])

# --- OUTPUT --- #
# 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55