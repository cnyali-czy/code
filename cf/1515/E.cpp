/*
	Problem:	E.cpp
	Time:		2021-05-03 21:34
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64

using namespace std;
const int maxn = 400 + 5;

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

int n, f[maxn][maxn];

int fac[maxn], invs[maxn], Invs[maxn];
inline i64 C(int n, int m, const int MOD) {return 1ll * fac[n] * Invs[m] % MOD * Invs[n - m] % MOD;}

int main()
{
#ifdef CraZYali
	file("E");
#endif
	n = read<int>();
	const int MOD = read<int>();
	fac[0] = invs[0] = Invs[0] = 1;
	fac[1] = invs[1] = Invs[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Invs[i] = 1ll * invs[i] * Invs[i - 1] % MOD;
	}
	f[0][0] = 1;
	f[1][1] = 1;
	const u64 LIM = 17e18;
	REP(x, 2, n) REP(y, 1, x)
	{
		u64 res = 0;
		REP(i, 1, x) REP(j, 0, y)
		{
			res += 1llu * f[i - 1][j] * f[x - i][y - j];
			if (res >= LIM) res %= MOD;
		}
		f[x][y] = res % MOD;
		if (y == x && x % 10 == 0) cerr << x << endl;
	}
//	REP(i, 0, n) REP(j, 0, n) printf("%lld%c", 1ll * fac[j] * f[i][j] % MOD, j == end_j ? '\n' : ' ' );
	i64 ans = 0;
	REP(i, 1, n) (ans += 1ll * fac[i] * f[n][i]) %= MOD;
	cout << ans % MOD << endl;
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
