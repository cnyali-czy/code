import random
import sympy


lim = 10 ** 18


def gen1(limP, limm, limK, limR):
	P = []
	for i in range(2, limP):
		if sympy.isprime(i):
			P.append(i)
	m = 1
	K = 1
	for i in range(100):
		now = P[random.randint(0, len(P) - 1)]
		if now * m <= limm:
			m = m * now
	for i in range(100):
		now = P[random.randint(0, len(P) - 1)]
		if now * K <= limK:
			K = K * now
	if limR > lim / m:
		limR = lim / m
	m = m * random.randint(1, limR)
	if m == 1:
		m = 2
	return [m, K]


def gen2(limm, limK):
	return [random.randint(2, limm), random.randint(1, limK)]


t = 100
print(t)
A = []
for i in range(70):
	A.append(gen1(random.randint(5, 15), random.randint(5, 15), random.randint(50, 100), random.randint(1, 3)))
for i in range(30):
	A.append(gen2(random.randint(2, 50), random.randint(1, 100)))
for i in range(100):
	print(str(A[i][0]) + " " + str(A[i][1]))
			
