/*
	Problem:	2839.cpp
	Time:		2020-08-04 23:14
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

i64 power_pow(i64 base, int b, const int MOD)
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
#define inv(x) power_pow(x, MOD - 2, MOD)

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

int n, k;
int fac[maxn], Inv[maxn];

inline i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[n - m] % MOD * Inv[m] % MOD;}

int f[maxn], g[maxn];

i64 sgn(int x) {return x & 1 ? MOD - 1 : 1;}

int main()
{
#ifdef CraZYali
	file("2839");
#endif
	n = read<int>();k = read<int>();
	fac[0] = 1;
	REP(i, 1, n) fac[i] = 1ll * i * fac[i - 1] % MOD;
	Inv[n] = inv(fac[n]);
	DEP(i, n - 1, 0) Inv[i] = (i + 1ll) * Inv[i + 1] % MOD;
	REP(i, 0, n) f[i] = C(n, i) * (power_pow(2, power_pow(2, n - i, MOD - 1), MOD) + MOD - 1) % MOD;
	i64 res = 0;
	REP(i, k, n) res += sgn(i - k) * C(i, k) % MOD * f[i] % MOD;
	cout << res % MOD << endl;
	return 0;
}
