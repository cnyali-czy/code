/*
	Problem:	A.cpp
	Time:		2020-06-15 19:52
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

using namespace std;
const int maxn = 5e4 + 10, MOD = 998244353;
#define i64 long long

inline int add(int x, int y) {return (x += y) >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {return (x -= y) <    0 ? x + MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}

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

int n;
int g[maxn], g0[maxn], g1[maxn], g2[maxn], i2[maxn];
int f0[maxn], f1[maxn], f2[maxn];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	g[0] = g[2] = 1;
	REP(i, 4, n) g[i] = add(g[i - 2], g[i - 4]);
	REP(i, 0, n + 2) i2[i] = 1ll * i * i % MOD;
	REP(i, 0, n)
	{
		g0[i] = 1ll * g[i] * i2[i] % MOD;
		g1[i] = 1ll * g[i] * i2[i + 1] % MOD;
		g2[i] = 1ll * g[i] * i2[i + 2] % MOD;

		i64 tmp = 0;
		REP(j, 0, i - 1) tmp += 1ll * g0[j] * f0[i - 1 - j] % MOD;
		REP(j, 0, i - 3) tmp += 1ll * g1[j] * f1[i - 3 - j] % MOD;
		f0[i] = (g0[i] + tmp) % MOD;tmp = 0;

		REP(j, 0, i - 1) tmp += 1ll * g1[j] * f0[i - 1 - j] % MOD;
		REP(j, 0, i - 3) tmp += 1ll * g2[j] * f1[i - 3 - j] % MOD;
		f1[i] = (g1[i] + tmp) % MOD;tmp = 0;

		REP(j, 0, i - 1) tmp += 1ll * g1[j] * f1[i - 1 - j] % MOD;
		REP(j, 0, i - 3) tmp += 1ll * g2[j] * f2[i - 3 - j] % MOD;
		f2[i] = (g2[i] + tmp) % MOD;
	}
	i64 ans = 0;

	ans = 1ll * n * i2[n - 1] % MOD * (g[n - 1] + g[n - 3]) % MOD;
	REP(i, 2, n - 2)
	{
		ans += 1ll * i * i2[i - 1] % MOD *
			((1ll * g[i - 1] * f0[n - i - 1] + 2ll * g[i - 2] * f1[n - i - 2] + (3 <= i && i <= n - 3 ? 1ll * g[i - 3] * f2[n - i - 3] : 0)) % MOD) % MOD;
	}

	cout << ans % MOD << endl;
	return 0;
}
