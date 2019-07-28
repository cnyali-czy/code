//consider idft
//NTT

#define REP(i, s, e) for (int i = s; i <= e; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <bits/stdc++.h>
#include "polynomial.h"
using namespace std;
const int maxn = 1000 + 30, g = 3, MOD = 998244353;
int n, m, t, N;
int ans, fx, w[maxn], t1, t2;

inline int power_pow(int a, int b)
{
	int ans = 1, base = a;
	while (b)
	{
		if (b & 1) ans = 1ll * ans * base % MOD;
		base = 1ll * base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}

void Init(int n, int m, int t)
{
	::n=n;
	::m=n-m;
	N = 1024;
	ans = n + 1, fx = n + 2, t1 = n + 3, t2 = n + 4;
	Set(ans, 0);
	Set(fx, 0);
	Set(t1 ,1);
	Set(t2, 1);
	w[0] = 1;
	w[1] = power_pow(3, (MOD - 1) / N);
	REP(i, 2, N - 1) w[i] = 1ll * w[i-1] * w[1] % MOD;
}

inline void Set_Zero(int x) {Minus(x, x, x);}
inline void Copy(int i,int j)
{
	Set_Zero(i);
	Plus(i, i, j);//i = i + j = 0 + j = j
}

inline void Power_pow(int base, int b)
{
	bool first = 1;
	while (b)
	{
		if (b & 1)
			if (first)
			{
				first = 0;
				Copy(t1, base);
			}
			else Multiply(t1, t1, base);
		Multiply(base, base, base);
		b >>= 1;
	}
	Copy(base, t1);
}

inline void Get(int x)
{
	Power_pow(t2, MOD - 1);
	Set_Zero(t1);
	while (x)
	{
		if (x & 1) Plus(t1, t1, t2);
		Plus(t2, t2, t2);
		x >>= 1;
	}
}

void Solve()
{
	REP(i, 0, N - 1)
	{
		Power_pow(t2, MOD-1);
		Copy(fx, t2);
		Get(w[i]);
		REP(j, 1, n)
		{
			Plus(t1, t1, j);
			Multiply(fx, fx, t1);
			Minus(t1, t1, j);
		}
		Get(w[((-i * m % N) + N) % N]);
		Multiply(fx, fx, t1);
		Plus(ans, ans, fx);
	}
	Get(power_pow(N, MOD-2));
	Multiply(ans, ans, t1);
	Answer(ans);
}
