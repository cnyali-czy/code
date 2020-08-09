/*
	Problem:	3704.cpp
	Time:		2020-08-07 20:51
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 1e6 + 10, MOD = 1e9 + 7;

i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2) 
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

int prime[maxn], mu[maxn], p_cnt, fib[maxn], ssr[maxn], Inv[maxn];
bool notp[maxn];
struct __init__
{
	__init__(const int n = 1e6)
	{
		mu[1] = 1;
		REP(i, 2, n)
		{
			if (!notp[i]) mu[prime[++p_cnt] = i] = -1;
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];if (tmp > n) break;
				notp[tmp] = 1;
				if (i % prime[j]) mu[tmp] = -mu[i];
				else break;
			}
		}
		fib[1] = 1;
		REP(i, 2, n) fib[i] = (fib[i - 2] + fib[i - 1]) % MOD;
		REP(i, 0, n) ssr[i] = 1;
		REP(i, 1, n) if (mu[i])
			REP(j, 1, n / i)
				ssr[i * j] = ssr[i * j] * power_pow(fib[j], mu[i] + MOD - 1) % MOD;
		int fac = 1;
		REP(i, 1, n)
		{
			ssr[i] = 1ll * ssr[i - 1] * ssr[i] % MOD;
			fac = 1ll * fac * ssr[i] % MOD;
		}
		Inv[n] = inv(fac);
		DEP(i, n - 1, 0) Inv[i] = 1ll * Inv[i + 1] * ssr[i + 1] % MOD;
		int cur = 1;
		REP(i, 1, n)
		{
			Inv[i] = 1ll * cur * Inv[i] % MOD;
			cur = 1ll * cur * ssr[i] % MOD;
		}
	}
}__INIT__;

int n, m;

int main()
{
#ifdef CraZYali
	file("3704");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();m = read<int>();
		if (n > m) swap(n, m);
		long long ans = 1;
		for (int i = 1, j; i <= n; i = j + 1)
		{
			j = min(n / (n / i), m / (m / i));
			(ans *= power_pow(1ll * Inv[i - 1] * ssr[j] % MOD, 1ll * (n / i) * (m / i) % (MOD - 1))) %= MOD;
		}
		printf("%d\n", (ans % MOD + MOD) % MOD);
	}
	return 0;
}
