from math import *
import math
In = open("couple.in", "r")
tmp = In.read().split()

def sqrtInt(x):
    if x < 3:
        return 1
    g1 = x
    g2 = x >> 1
    count = 0
    while g2 < g1:
        count += 1
        g1 = g2
        g2 = ( g1 + x // g1) >> 1
    return g1

for i in range(2, 12):
    n = int(tmp[i + i - 2])
    phi = int(tmp[i + i - 1])
    B = int(n)           # p ^ (k1) * q ^ (k2)
    A = int(phi)         # p ^ (k1 - 1) (p - 1) q ^ (k2 - 1) (q - 1)
    C = int(math.gcd(A, B))   # p ^ (k1 - 1) q ^ (k2 - 1)
    p = int(B // C)
    print(p)
    k = 0
    while (n % p == 0):
        n = n // p
        k = k + 1
    print(p,k)
