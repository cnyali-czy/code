import random

def gen(n, m):
	print(str(random.randint(2, n)) + " " + str(random.randint(1, m)))

t = 120
print(t)
A = [20, 2000, 200000]
B = [10 ** 2, 10 ** 5, 10 ** 10]
for i in range(3):
	for j in range(40):
		gen(A[i], B[i])
