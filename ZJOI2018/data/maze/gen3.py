import random
import sympy


lim = 10 ** 5


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
	now = limR
	if limR > lim // m:
		now = lim // m
	m = m * random.randint(1, now)
	if m == 1:
		m = 2
	K = K * random.randint(1, lim // K)
	return [m, K]


def gen2(limm, limK):
	return [random.randint(2, limm), random.randint(1, limK)]


t = 100
print(t)
A = []
for i in range(50):
	A.append(gen1(random.randint(3, 17), random.randint(5, 200), random.randint(5000, 10000), random.randint(1, 20)))
for i in range(20):
	A.append(gen1(random.randint(3, 5), random.randint(5, 200), random.randint(5000, 10000), random.randint(1, 100)))
for i in range(15):
	A.append(gen2(random.randint(2, lim), random.randint(1, lim)))
for i in range(15):
	A.append(gen2(random.randint(2, lim / 100), random.randint(1, lim)))
for i in range(100):
	print(str(A[i][0]) + " " + str(A[i][1]))
			
