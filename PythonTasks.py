# 1
fname = input("Imie: ")
lname = input("Nazwisko: ")
print("{}, {}".format(lname, fname))

# 2
name = input("Imie i nazwisko: ").split()
print("{}, {}".format(name[1], name[0]))

# 3
import math
print("Przykład: 5 10")
ax, ay = map(int, input("Pierwszy punkt: ").split())
bx, by = map(int, input("Drugi punkt: ").split())
s = round(math.sqrt((ax - bx)**2 + (ay - by)**2), 2)
print("Odleglosc: {}".format(s))

# 4
n = int(input("Liczba gosci: "))
r = 32 // n
z = 32 - n * r
d = round(32/n, 2)
print("Opcja 1: każdy po {} kawalkow, {} zostaje".format(r, z))
print("Opcja 2: kazdy po {} kawalkow".format(d))

# 5 (o to chodzi?)
z = input("Zdanie: ").split()[::-1]
for i in z:
	print(i)

# 6
n = int(input("Dlugosc twojego weza: "))
if n <= 6:
	z = 0.5*n
else:
	z = 0.5*6 + 0.75*(n - 6)
print(z)


# 7
a = [x*x for x in range(0, 10)]
print(a)
b = [x[0] for x in input("Zdanie: ").split()]
print(b)
c = [(i,j) for i in range(2,50) for j in range(2,50) if i*j < 50]
print(c)

# 8
w = input("Wyraz: ").lower()
if w == w[::-1]:
	print("palindrom")
else:
	print("nie palindrom")

# 9
def Poan(x):
	if x >= 10:
		n = 1
		while x > 0:
			r = x % 10
			x = (x - r) // 10
			n *= r
		return 1 + Poan(n)
	else:
		return 0

x = int(input("Liczba: "))
print(Poan(x))
