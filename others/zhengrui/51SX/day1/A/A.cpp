/*
	Problem:	A.cpp
	Time:		2020-05-01 08:17
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e7 + 10, MOD = 998244353;
#define i64 long long

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
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
int power_pow(i64 base, int b)
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

int p[maxn], dp[maxn], n, k, x;

int f[maxn], invs[maxn];
int main()
{
#ifdef CraZYali
	file("A");
	freopen("A.err", "w", stderr);
	REP(i, 1, 100) REP(j, i + 1, 100) if (__gcd(i, j) == 1) fprintf(stderr, "%d = %d / %d\n", 1ll * i * inv(j) % MOD, i, j);
#endif
	n = read<int>();k = read<int>();x = read<int>();
	int tot = 0;
	REP(i, 0, k) tot += (p[i] = read<int>());
	tot = inv(tot);
	REP(i, 0, k) p[i] = 1ll * tot * p[i] % MOD;
	invs[0] = invs[1] = 1;
	REP(i, 2, x) invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
	int ip0 = inv(p[0]);
	f[0] = power_pow(p[0], n);
	i64 ans = -1ll * x * f[0] % MOD;
	REP(i, 1, x)
	{
		i64 s = 0;
		REP(j, 1, min(i, k)) (s += (1ll * j * p[j] % MOD * n - 1ll * p[j] * (i - j)) % MOD * f[i - j]) %= MOD;
		f[i] = 1ll * s * ip0 % MOD * invs[i] % MOD;
		(ans += 1ll * f[i] * (i - x)) %= MOD;
	}
	cout << (ans + x + MOD) % MOD << endl;
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
	return 0;
}
