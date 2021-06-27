/*
	Problem:	B.cpp
	Time:		2021-06-22 18:39
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#ifdef CraZYali
#include <ctime>
#endif
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 50000 + 10, inf = 1e7;

vector <int> G[maxn];

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, q, l, r, ans;
bool vis[maxn];

int f[maxn], dep[maxn];
void dfs(int x, int fa = 0)
{
	f[x] = (l <= x && x <= r ? dep[x] : inf);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs(to[i], x);
		ans = min(ans, f[x] + f[to[i]] - 2 * dep[x]);
		f[x] = min(f[x], f[to[i]]);
	}
}
int dfn[maxn], back[maxn], dfs_clock, fa[maxn];
void dfs0(int x)
{
	back[dfn[x] = ++dfs_clock] = x;
	dep[x] = dep[fa[x]] + 1;
	for (int y : G[x]) if (y ^ fa[x]) fa[y] = x, dfs0(y);
}
int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		G[x].emplace_back(y);
		G[y].emplace_back(x);
	}
	dfs0(1);
	REP(T, 1, read<int>())
	{
		ans = 0;
		l = read<int>() ^ ans;r = read<int>() ^ ans;
		REP(i, 1, n) f[i] = inf;
		REP(i, l, r) f[i] = dep[i];
		ans = inf;
		DEP(I, n, 2)
		{
			int x = back[I];
			ans = min(ans, f[fa[x]] + f[x] - 2 * dep[x] + 2);
			f[fa[x]] = min(f[fa[x]], f[x]);
		}
		if (ans < n) printf("%d\n", ans);
		else puts("-1"), ans = 0;
		if (T % 10000 == 0) fprintf(stderr, "Done %d / %d = %.2lf%%\n", T, end_T, T * 100. / end_T);
	}
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
	return 0;
}
