import random
import sympy

lim = 10 ** 9
def gen1(limm):
	num = random.randint(1, limm)
	m = sympy.nextprime(num)
	t = 0
	now = 1
	while True:
		if now * m > lim:
			break
		else:
			t += 1
			now *= m
	num = random.randint(1, t)
	K = m ** num
	K *= random.randint(1, lim // K)
	return [m, K]

t = 1000
print(t)
A = []
for i in range(5):
	for j in range(150):
		A.append(gen1(10 ** (i + 1)))
for i in range(250):
	A.append(gen1(random.randint(1, lim - 10000)))
for i in range(t):
	print(str(A[i][0]) + " " + str(A[i][1]))
