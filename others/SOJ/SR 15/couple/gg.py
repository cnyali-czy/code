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
    pq = B // C      
    E = phi // C    # (p - 1)(q - 1)
    F = pq - E + 1  # p + q
    G = sqrtInt(F * F - 4 * pq)    # p - q
    p = (F + G) // 2
    q = (F - G) // 2
    
    k1 = 0
    k2 = 0
    while (n % p == 0):
        n = n // p
        k1 = k1 + 1
    while (n % q == 0):
        n = n // q
        k2 = k2 + 1
    if p > q:
        t = p
        p = q
        q = t
        t = k1
        k1 = k2
        k2 = t
    print(p,k1,q,k2)
