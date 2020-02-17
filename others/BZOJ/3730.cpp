/*
	Problem:	3730.cpp
	Time:		2020-02-17 21:43
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100000 + 10;

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
inline int min(const int &x, const int &y) {if (x < y) return x;return y;}
namespace lca
{
	int st[maxn << 1][20], dfn, lg[maxn << 1], dep[maxn], fir[maxn];
	void dfs(int x, int fa = 0)
	{
		st[++dfn][0] = dep[x];
		fir[x] = dfn;
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			dep[to[i]] = dep[x] + 1;
			dfs(to[i], x);
			st[++dfn][0] = dep[x];
		}
	}
	inline int qry(int x, int y)
	{
		int l(fir[x]), r(fir[y]);if (l > r) swap(l, r);
		int k = lg[r - l + 1];
		return min(st[l][k], st[r - (1 << k) + 1][k]);
	}
	inline int dist(int x, int y) {return dep[x] + dep[y] - 2 * qry(x, y);}
	void init()
	{
		dfs(1);
		REP(i, 2, dfn) lg[i] = lg[i >> 1] + 1;
		REP(j, 1, 19)
			REP(i, 1, dfn + 1 - (1 << j))
				st[i][j] = min(st[i][j-1], st[i + (1 << j-1)][j-1]);
	}
}
using lca::dist;
struct bit
{
	int n, *c;
	inline void init(int _n)
	{
		n = _n + 1;
		c = new int[n + 1];
		REP(i, 0, n) c[i] = 0;
	}
	void add(int x, int y) {for (; x <= n; x += x & -x) c[x] += y;}
	int sum(int x) {int res = 0;for (chkmin(x, n); x > 0; x &= (x - 1)) res += c[x];return res;}
}g[maxn], f[maxn];

int siz[maxn], Max[maxn], rt, allnode;
bool vis[maxn];
void findrt(int x, int fa = 0)
{
	siz[x] = 1;Max[x] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && to[i] ^ fa)
	{
		findrt(to[i], x);
		siz[x] += siz[to[i]];
		chkmax(Max[x], siz[to[i]]);
	}
	chkmax(Max[x], allnode - siz[x]);
	if (!rt || Max[x] < Max[rt]) rt = x;
}

int par[maxn];
void dfs2(int x, int fa, int d)
{
	d++;
	f[rt].add(d, v[x]);g[par[rt]].add(d, v[x]);
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && to[i] ^ fa) dfs2(to[i], x, d);
}

void dfs(int x)
{
	vis[x] = 1;
	g[x].add(1, v[x]);
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
	{
		rt = 0;
		allnode = siz[to[i]];
		findrt(to[i]);
		par[rt] = x;
		f[rt].init(allnode);g[rt].init(allnode);
		dfs2(to[i], x, 1);
		dfs(rt);
	}
}

void update(int x, int y)
{
	int delta = y - v[x];
	for (int i = x; i; i = par[i])
	{
		g[i].add(dist(x, i) + 1, delta);
		if (par[i]) f[i].add(dist(par[i], x) + 1, delta);
	}
	v[x] = y;
}
int query(int x, int k)
{
	int res = 0;
	for (int i = x; i; i = par[i])
	{
		res += g[i].sum(k - dist(i, x) + 1);
		if (par[i]) res -= f[i].sum(k - dist(par[i], x) + 1);
	}
	return res;
}

int main()
{
#ifdef CraZYali
	file("3730");
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
	f[rt].init(n);g[rt].init(n);
	dfs(rt);
	int ans = 0;
	REP(Case, 1, m)
	{
		int opt(read<int>()), x(ans ^ read<int>()), y(ans ^ read<int>());
		if (!opt) printf("%d\n", ans = query(x, y));
		else update(x, y);
	}
	return 0;
}
