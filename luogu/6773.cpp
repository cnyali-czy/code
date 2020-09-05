/*
	Problem:	6773.cpp
	Time:		2020-09-01 22:24
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
const int maxn = 1e3 + 10, MOD = 998244353;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

int dep[maxn];
void dfs(int x, int fa = 0)
{
	dep[x] = dep[fa] + 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dep[to[i]] = dep[x] + 1;
		dfs(to[i], x);
	}
}
int lim[maxn], f[maxn][1005];

void dp(int x, int fa = 0)
{
	REP(i, 1, lim[x]) f[x][i] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dp(to[i], x);
		REP(j, 1, lim[x])
			f[x][j] = 1ll * f[x][j] * (f[to[i]][1] + f[to[i]][j + 1]) % MOD;
	}
}

int main()
{
#ifdef CraZYali
	file("6773");
#endif
	n = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	dfs(1);
	REP(i, 1, n) lim[i] = dep[i];
	REP(Case, 1, read<int>())
	{
		int x = read<int>(), y = read<int>();
		if (dep[x] < dep[y]) swap(x, y);
		chkmin(lim[x], dep[x] - dep[y]);
	}
	dp(1);
	cout << f[1][1] << endl;
	return 0;
}
