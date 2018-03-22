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


t = 300000
print(t)
A = []
for i in range(5):
	for j in range(8, 13):
		for k in range(7000):
			A.append(gen1(random.randint(3, 20), random.randint(2, 10 ** (i + 1)), random.randint(10 ** (j - 1), 10 ** j), random.randint(1, 20)))
for i in range(5):
	for j in range(8, 13):
		for k in range(3000):
			A.append(gen1(random.randint(3, 20), random.randint(2, 10 ** (i + 1)), random.randint(10 ** (j - 1), 10 ** j), random.randint(1, 10000)))
for i in range(50000):
	a = random.randint(1, 18)
	b = random.randint(1, 18)
	A.append(gen2(10 ** a, 10 ** b))
assert(len(A) == 300000)
for i in range(t):
	print(str(A[i][0]) + " " + str(A[i][1]))
			
