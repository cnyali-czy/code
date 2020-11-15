/*
	Problem:	4071.cpp
	Time:		2020-11-15 20:32
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e6 + 10, MOD = 1e9 + 7;

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

int n, m;
int fac[maxn], inv[maxn], Inv[maxn], f[maxn];
struct __init__
{
	__init__(const int n = 1e6)
	{
		fac[0] = inv[0] = Inv[0] = 1;
		fac[1] = inv[1] = Inv[1] = 1;
		REP(i, 2, n)
		{
			fac[i] = 1ll * i * fac[i - 1] % MOD;
			inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
			Inv[i] = 1ll * inv[i] * Inv[i - 1] % MOD;
		}
		f[0] = 1;
		REP(i, 1, n) f[i] = (f[i - 1] + ((i & 1) ? MOD - Inv[i] : Inv[i])) % MOD;
		REP(i, 1, n) f[i] = 1ll * f[i] * fac[i] % MOD;
	}
}__INIT__;
inline i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}

int main()
{
#ifdef CraZYali
	file("4071");
#endif
	register int T = read<int>();
	while (T--)
	{
		int n = read<int>(), m = read<int>();
		if (n < m) {puts("0");continue;}
		printf("%lld\n", C(n, m) * f[n - m] % MOD);
	}
	return 0;
}
