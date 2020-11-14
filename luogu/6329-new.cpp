/*
	Problem:	6329-new.cpp
	Time:		2020-11-03 15:17
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
const int maxn = 1e5 + 10;

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

int n, m, v[maxn];
namespace lca
{
	int st[19][maxn << 1], dfs_clock, dep[maxn], fir[maxn];
	void dfs(int x, int fa = 0)
	{
		dep[x] = dep[fa] + 1;
		st[0][fir[x] = ++dfs_clock] = dep[x];
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			dfs(to[i], x);
			st[0][++dfs_clock] = dep[x];
		}
	}
	const int w = 10;
	int Lg[1 << w];
	inline int lg(int x)
	{
		if (x >> w) return w + Lg[x >> w];
		return Lg[x];
	}
	void init()
	{
		dfs(1);
		REP(i, 2, (1 << w) - 1) Lg[i] = Lg[i >> 1] + 1;
		REP(j, 1, 18)
			REP(i, 1, dfs_clock - (1 << j) + 1)
			st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
	}
	int dist(int x, int y)
	{
		int l = fir[x], r = fir[y];
		if (l > r) swap(l, r);
		int k = lg(r - l + 1);
		return dep[x] + dep[y] - 2 * min(st[k][l], st[k][r - (1 << k) + 1]);
	}
}
using lca :: dist;
bool vis[maxn];
int siz[maxn], Max[maxn], allnode, rt;
int maxD;
void findrt(int x, int fa, int d = 0)
{
	maxD = max(maxD, d);
	siz[x] = 1;Max[x] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
	{
		findrt(to[i], x, d + 1);
		siz[x] += siz[to[i]];
		Max[x] = max(Max[x], siz[to[i]]);
	}
	Max[x] = max(Max[x], allnode - siz[x]);
	if (!rt || Max[x] < Max[rt]) rt = x;
}

int pool[maxn * 40], *cur = pool;
struct fenwick
{
	int *s, n;
	void init(int N)
	{
		n = N;
		s = cur;cur += n + 1;
	}
	void add(int x, int y)
	{
		x++;
		while (x <= n)
		{
			s[x] += y;
			x += x & -x;
		}
	}
	int sum(int x)
	{
		x = min(x + 1, n);

		int y = 0;
		while (x > 0)
		{
			y += s[x];
			x &= (x - 1);
		}
		return y;
	}
}f[maxn], g[maxn];

int par[maxn];
void dfs2(int x, int fa, int d)
{
	f[rt].add(d, v[x]);
	g[par[rt]].add(d, v[x]);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
		dfs2(to[i], x, d + 1);
}

void dfs(int x)
{
	vis[x] = 1;
	g[x].add(0, v[x]);
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
	{
		rt = maxD = 0;
		allnode = siz[to[i]];
		findrt(to[i], x);
		par[rt] = x;
		f[rt].init(maxD + 5);
		g[rt].init(maxD + 5);
		dfs2(to[i], x, 1);
		dfs(rt);
	}
}
int up[maxn][40];
void update(int x, int y)
{
	int delta = y - v[x];v[x] = y;
	for (int i = x, j = 0; i; i = par[i], j++)
	{
		g[i].add(up[x][j], delta);
		if (par[i]) f[i].add(up[x][j + 1], delta);
	}
}
int query(int x, int y)
{
	int res = 0;
	for (int i = x, j = 0; i; i = par[i], j++)
	{
		res += g[i].sum(y - up[x][j]);
		if (par[i]) res -= f[i].sum(y - up[x][j + 1]);
	}
	return res;
}

int main()
{
#ifdef CraZYali
	file("6329-new");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) v[i] = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	lca :: init();
	allnode = n;
	findrt(1, 0);
	f[rt].init(maxD + 5);
	g[rt].init(maxD + 5);
	dfs(rt);
	int lastans = 0;
	REP(x, 1, n)
		for (int i = x, j = 0; i; i = par[i], j++) up[x][j] = dist(x, i);
	while (m--)
	{
		int opt = read<int>(), x = read<int>() ^ lastans, y = read<int>() ^ lastans;
		if (opt) update(x, y);
		else printf("%d\n", lastans = query(x, y));
	}
	return 0;
}
