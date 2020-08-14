/*
	Problem:	3730-new.cpp
	Time:		2020-03-25 22:17
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

inline void chkmax(int &x, int y) {if (x < y) x = y;}

#include <cassert>
#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 1e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
void add(int x, int y)
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

int n, m, v[maxn];
inline int min(int x, int y) {if (x < y) return x;return y;}
namespace lca
{
	const int maxn = ::maxn << 1;
	int p[maxn], dfs_clock, st[maxn][20], dep[maxn], pos[maxn];
	void dfs(int x, int fa = 0)
	{
		st[pos[x] = ++dfs_clock][0] = dep[x];
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			dep[to[i]] = dep[x] + 1;
			dfs(to[i], x);
			st[++dfs_clock][0] = dep[x];
		}
	}
	int lg[maxn];
	void init()
	{
		dfs(1);
		REP(i, 2, dfs_clock) lg[i] = lg[i >> 1] + 1;
		REP(j, 1, 19)
			REP(i, 1, dfs_clock - (1 << j) + 1)
			st[i][j] = min(st[i][j-1], st[i + (1 << j - 1)][j-1]);
	}
	int qry(int x, int y)
	{
		int l = pos[x], r = pos[y];
		if (l > r) swap(l, r);
		int k = lg[r - l + 1];
		return min(st[l][k], st[r - (1 << k) + 1][k]);
	}
	inline int dist(int x, int y) {return dep[x] + dep[y] - 2 * qry(x, y);}
}
using lca::dist;
int pool[maxn * 30], *cur = pool;

struct bit
{
	int *s, n;
	void init(int N)
	{
		n = N + 1;
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
		x++;
		if (x > n) x = n;
		int y = 0;
		while (x > 0)
		{
			y += s[x];
			x &= (x - 1);
		}
		return y;
	}
}g[maxn], f[maxn];

int siz[maxn], Max[maxn], allnode, rt;
bool vis[maxn];

int up[maxn][25];
int maxddd;
void findrt(int x, int fa = 0, int ddd = 0)
{
	chkmax(maxddd, ddd);
	siz[x] = 1;Max[x] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] != fa && !vis[to[i]])
	{
		findrt(to[i], x, ddd + 1);
		siz[x] += siz[to[i]];
		chkmax(Max[x], siz[to[i]]);
	}
	chkmax(Max[x], allnode - siz[x]);
	if (!rt || Max[x] < Max[rt]) rt = x;
}
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
		rt = 0;
		allnode = siz[to[i]];
		maxddd = 0;
		findrt(to[i]);
		par[rt] = x;
		f[rt].init(maxddd + 2);g[rt].init(maxddd + 2);
		dfs2(to[i], x, 1);
		dfs(rt);
	}
}
void update(int x, int y)
{
	int delta = y - v[x];v[x] = y;
	for (int i = x, j = 0; i; i = par[i], j++)
	{
		g[i].add(up[x][j], delta);
		if (par[i]) f[i].add(up[x][j + 1], delta);
	}
}
int query(int x, int k)
{
	int res = 0;
	for (int i = x, j = 0; i; i = par[i], j++)
	{
		res += g[i].sum(k - up[x][j]);
		if (par[i]) res -= f[i].sum(k - up[x][j+1]);
	}
	return res;
}
signed main()
{
#ifdef CraZYali
	file("6329");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) v[i] = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	lca::init();
	allnode = n;
	findrt(1);
	f[rt].init(maxddd + 2);g[rt].init(maxddd + 2);
	dfs(rt);
	REP(i, 1, n)
		for (int x = par[i], j = 1; x; x = par[x], j++) up[i][j] = dist(x, i);
	int lastans = 0;
	while (m--)
	{
		int opt(read<int>()), x(lastans ^ read<int>()), y(lastans ^ read<int>());
		if (opt == 0) printf("%d\n", lastans = query(x, y));
		else update(x, y);
	}
	return 0;
}
