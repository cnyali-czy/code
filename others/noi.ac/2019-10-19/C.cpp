/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.19 15:52
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__), fflush(stderr)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1000 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout), freopen(FILE_NAME".err", "w", stderr);

int n, m, a[maxn];

int siz[maxn], hvy[maxn], fa[maxn], d[maxn];
void dfs1(int x)
{
	siz[x] = 1;
	for (register int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		d[to[i]] = d[x] + 1;
		fa[to[i]] = x;
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}
int top[maxn];
void dfs2(int x, int y)
{
	top[x] = y;
	if (hvy[x])
	{
		dfs2(hvy[x], y);
		for (register int i = bg[x]; i; i = ne[i]) if (to[i] != fa[x] && to[i] != hvy[x])
			dfs2(to[i], to[i]);
	}
}
inline int lca(int x, int y)
{
	while (top[x] ^ top[y])
	{
		if (d[top[x]] < d[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	return d[x] < d[y] ? x : y;
}

int l[maxn][maxn], f[maxn][maxn], g[maxn][maxn], h[maxn][maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		register int u(read<int>()), v(read<int>());
		add(u, v);add(v, u);
	}
	dfs1(1);
	dfs2(1, 1);
	REP(u, 1, n)
		REP(v, 1, n)
		{
			l[u][v] = l[v][u] = lca(u, v);
			if (u == v) continue;
			f[u][v] = (u < v && u != l[u][v] && v != l[u][v]);
			g[u][v] = (u == l[u][v] && a[u] > a[v]);
			h[u][v] = (u == l[u][v] && a[u] < a[v]);
		}
	while (m--)
	{
		register int size = read<int>();
		int ans(2e9);
		REP(S, 0, (1 << n) - 1) if (__builtin_popcount(S) == size)
		{
			int fgo = 0;
			REP(u, 1, n)
				if ((1 << u - 1) & S)
				{
					fgo += d[u];
					REP(v, 1, n) if ((1 << v - 1) & S)
						fgo += f[u][v] + g[u][v];
				}
				else
					REP(v, 1, n) if (!((1 << v - 1) & S))
						fgo += h[u][v];
			chkmin(ans, fgo);
		}
#ifdef CraZYali
		REP(S, 0, (1 << n) - 1) if (__builtin_popcount(S) == size)
		{
			int fgo = 0;
			REP(u, 1, n)
				if ((1 << u - 1) & S)
				{
					fgo += d[u];
					REP(v, 1, n) if ((1 << v - 1) & S)
						fgo += f[u][v] + g[u][v];
				}
				else
					REP(v, 1, n) if (!((1 << v - 1) & S))
						fgo += h[u][v];
			if (ans == fgo)
			{	
				REP(i, 1, n) if (S & (1 << i - 1)) fprintf(stderr,"%d ", i);
				fputs("\n",stderr);
			}
		}
		fputs("------------\n",stderr);
#endif
		cout << ans << endl;
	}
	return 0;
}
