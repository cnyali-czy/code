/*
	Problem:	4718-new.cpp
	Time:		2020-06-06 18:56
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstdio>

using namespace std;
#define i64 long long

inline i64 mul(i64 a, i64 b, const i64 p)
{
	i64 res = (a * b - (i64)((long double)a / p * b) * p) % p;
	if (res < 0) res += p;
	return res;
}
i64 power_pow(i64 base, i64 b, const i64 p)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) ans = mul(ans, base, p);
		base = mul(base, base, p);
		b >>= 1;
	}
	return ans;
}
#ifndef CraZYali
#define getchar getchar_unlocked
#endif
template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int totst[] = {2, 3, 13, 17, 19, 23};
bool miller_rabin(i64 n)
{
	if (n < 3) return n == 2;
	if (!(n & 1)) return 0;
	i64 a = n - 1, b = 0;
	while (!(a & 1)) a >>= 1, b++;
	for (i64 x : totst)
	{
		if (n == x) return 1;
		i64 v = power_pow(x, a, n);
		if (v == 1 || v == n - 1) continue;
		REP(i, 0, b)
		{
			if (v == n - 1) break;
			if (i == b) return 0;
			v = mul(v, v, n);
		}
	}
	return 1;
}

inline i64 f(i64 x, i64 c, i64 n) {return (mul(x, x, n) + c) % n;}
inline i64 Rand() {return 1ll * rand() * rand();}
i64 pollard_rho(i64 n)
{
#ifdef CraZYali
	assert(!miller_rabin(n));
#endif
	if (n % 2 == 0) return 2;
	i64 c = Rand() % (n - 1) + 1;
	for (i64 goal = 1, s = 0, t = 0;;goal <<= 1, s = t)
	{
		i64 val = 1;
		REP(stp, 1, goal)
		{
			t = f(t, c, n);
			val = mul(val, abs(s - t), n);
			if (stp % 127 == 0)
			{
				i64 d = __gcd(val, n);
				if (d > 1) return d;
			}
		}
		i64 d = __gcd(val, n);
		if (d > 1) return d;
	}
}
i64 solve(i64 n)
{
	if (n == 1 || miller_rabin(n)) return n;
	i64 m = pollard_rho(n);
	return max(solve(m), solve(n / m));
}

i64 n;
int main()
{
#ifdef CraZYali
	file("4718-new");
#endif
	register int T = read<int>();
	while (T--)
	{
		i64 n = read<i64>();
		if (miller_rabin(n)) puts("Prime");
		else printf("%lld\n", solve(n));
	}
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
