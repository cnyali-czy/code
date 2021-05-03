/*
	Problem:	F.cpp
	Time:		2021-04-30 15:38
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
const int maxn = 100 + 5, MOD = 1e9 + 7;

i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		if (b >>= 1) (base *= base) %= MOD;
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, k, c0, m, a[maxn];
int f[233][maxn];

int main()
{
#ifdef CraZYali
	file("F");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, n) a[i] = read<int>(), c0 += (!a[i]);
	const i64 tt = n * (n - 1) / 2, it = inv(tt);
	REP(i, 1, c0) m += (!a[i]);
	f[0][m] = 1;
	REP(i, 0, k - 1) REP(j, 0, c0) if (f[i][j])
	{
		f[i + 1][j + 1] = (f[i + 1][j + 1] + 1ll * (c0 - j) * (c0 - j) * f[i][j]) % MOD;
		if (j)
			f[i + 1][j - 1] = (f[i + 1][j - 1] + 1ll * j * (n - c0 - c0 + j) * f[i][j]) % MOD;
		f[i + 1][j] = (f[i + 1][j] + (tt - (c0 - j) * (c0 - j) - j * (n - c0 - c0 + j)) * f[i][j]) % MOD;
	}
	cout << f[k][c0] * power_pow(it, k) % MOD << '\n';
	return 0;
}
