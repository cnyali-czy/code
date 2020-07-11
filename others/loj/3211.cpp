/*
	Problem:	3211.cpp
	Time:		2020-07-09 23:23
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 100 + 5, maxm = 2e3 + 10, MOD = 998244353;

inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

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

#define poly vector <int>

poly work(poly f, int a)
{
	f.push_back(0);
	DEP(i, f.size() - 1, 1)
		inc(f[i], 1ll * f[i - 1] * a % MOD);
	return f;
}

int n, m, a[maxn][maxm], sig[maxn];

int dp[maxn][maxn << 1];

int main()
{
#ifdef CraZYali
	file("3211");
#else
	file("meal");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) REP(j, 1, m) a[i][j] = read<int>();
	poly f(1, 1);
	REP(i, 1, n)
	{
		i64 tot = 0;
		REP(j, 1, m) tot += a[i][j];
		f = work(f, sig[i] = (tot % MOD));
	}
	i64 all = 0;
	REP(i, 1, n) all += f[i];
	REP(gg, 1, m)
	{
		memset(dp, 0, sizeof dp);
		dp[0][0] = 1;
		REP(i, 1, n) REP(j, 0, i - 1 << 1)
		{
			dp[i][j]		=	(dp[i][j] + 1ll * dp[i - 1][j] * (sig[i] + MOD - a[i][gg])) % MOD;
			(dp[i][j + 1] += dp[i - 1][j]) %= MOD;
			dp[i][j + 2] = (dp[i][j + 2] + 1ll * dp[i - 1][j] * a[i][gg]) % MOD;
		}
		i64 res = 0;
		REP(i, n + 1, n + n) res += dp[n][i];
		all -= res % MOD;
	}
	cout << (all % MOD + MOD) % MOD << endl;
	return 0;
}
