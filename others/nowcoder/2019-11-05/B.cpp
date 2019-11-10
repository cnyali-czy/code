/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.06 20:54
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

namespace run
{
	const int maxn = 3000 + 10;

	int n, p, q, len;
	int fa[maxn], dep[maxn], siz[maxn], hvy[maxn], top[maxn];

	int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
	inline void add(int x, int y)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
	}

	void dfs1(int x)
	{
		siz[x] = 1;
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
		{
			fa[to[i]] = x;
			dep[to[i]] = dep[x] + 1;
			dfs1(to[i]);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
		}
	}
	void dfs2(int x, int y)
	{
		top[x] = y;
		if (hvy[x])
		{
			dfs2(hvy[x], y);
			for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x])
				dfs2(to[i], to[i]);
		}
	}
	inline int lca(int x, int y)
	{
		while (top[x] ^ top[y])
		{
			if (dep[top[x]] < dep[top[y]]) swap(x, y);
			x = fa[top[x]];
		}
		return dep[x] < dep[y] ? x : y;
	}
	inline int dist(int x, int y) {return dep[x] + dep[y] - 2 * dep[lca(x, y)];}

	long long f[maxn], g[maxn], h[maxn];

	void dfs(int x)
	{
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
		{
			g[to[i]] += g[x];
			dfs(to[i]);
			f[x] += f[to[i]];
			h[x] += h[to[i]];;
		}
	}
	int main()
	{
		n = read<int>();
		p = read<int>();
		q = read<int>();
		REP(i, 2, n)
		{
			int x(read<int>()), y(read<int>());
			add(x, y);add(y, x);
		}
		dfs1(1);
		dfs2(1, 1);
		REP(u, 1, n)
			REP(v, 1, n)
				if (dist(u, v) == p)
				{
					int l(lca(u, v));
					f[l]++;g[l]++;
					h[u]++;h[v]++;
					h[l]--;h[fa[l]]--;
				}
		dfs(1);
		long long ans = 0;
		REP(u, 1, n)
			REP(v, 1, n)
			if (dist(u, v) == q)
			{
				int l(lca(u, v));
				ans += f[l] - (g[u] + g[v] - g[l] - g[fa[l]]);
				ans += f[1] - f[l] - h[l] + g[l] - g[fa[l]];
			}
		cout << ans << endl;
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	return run::main();
}
