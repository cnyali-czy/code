/*
	Problem:	B.cpp
	Time:		2020-10-15 20:58
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 1e5 + 10, maxm = 1e5 + 10, MOD = 998244353;

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

const int L = 20;
int G[L + 5][maxn], g[maxn], f[maxn][2];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();m = read<int>();
	g[1] = m;
	REP(i, 1, m) G[1][i] = 1;
	REP(i, 2, L)
	{
		i64 tot = 0;
		REP(j, 1, m)
		{
			i64 res = 0;
			for (int k = j + j; k <= m; k += j) res += G[i - 1][k];
			G[i][j] = res % MOD;
			tot += res;
		}
		g[i] = tot % MOD;
	}
	f[0][0] = 1;
	REP(i, 1, n)
		for (int j = 1, sgn = 1; j <= L && j <= i; j++, sgn ^= 1)
		{
			f[i][0] = (f[i][0] + 1ll * f[i - j][!sgn] * g[j]) % MOD;
			f[i][1] = (f[i][1] + 1ll * f[i - j][ sgn] * g[j]) % MOD;
		}
	cout << (f[n][0] - f[n][1] + MOD) % MOD << endl;
	return 0;
}
