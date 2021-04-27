/*
	Problem:	6145.cpp
	Time:		2021-04-27 09:07
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
const int maxn = 1e5 + 10;
const i64 inf = 1e18;

int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
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

int n, q;

namespace lca
{
	int siz[maxn], hvy[maxn], top[maxn], fa[maxn], dep[maxn];
	i64 dis[maxn];
	void dfs1(int x)
	{
		siz[x] = 1;
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
		{
			fa[to[i]] = x;
			dep[to[i]] = dep[x] + 1;
			dis[to[i]] = dis[x] + w[i];
			dfs1(to[i]);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
		}
	}
	void dfs2(int x, int y)
	{
		top[x] = y;
		if (!hvy[x]) return;
		dfs2(hvy[x], y);
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x])
			dfs2(to[i], to[i]);
	}
	int lca(int x, int y)
	{
		while (top[x] ^ top[y])
		{
			if (dep[top[x]] < dep[top[y]]) swap(x, y);
			x = fa[top[x]];
		}
		return dep[x] < dep[y] ? x : y;
	}
	void init()
	{
		dfs1(1);
		dfs2(1, 1);
	}
	inline i64 dist(int x, int y) {return dis[x] + dis[y] - 2 * dis[lca(x, y)];}
}
using lca :: dist;

int rt, allnode, Max[maxn], siz[maxn];
bool vis[maxn];
void findrt(int x, int fa)
{
	siz[x] = 1;Max[x] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
	{
		findrt(to[i], x);
		siz[x] += siz[to[i]];
		Max[x] = max(Max[x], siz[to[i]]);
	}
	Max[x] = max(Max[x], allnode - siz[x]);
	if (!rt || Max[x] < Max[rt]) rt = x;
}
namespace SMT
{
	const int maxN = 2e7 + 10;
	int ls[maxN], rs[maxN], cur;i64 mi[maxN];
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
	void ins(int &p, int l, int r, int pos, i64 val)
	{
		if (!p) mi[p = ++cur] = inf;
		if (l == r) mi[p] = min(mi[p], val);
		else
		{
			if (pos <= mid) ins(lson, pos, val);
			else ins(rson, pos, val);
			mi[p] = min(mi[ls[p]], mi[rs[p]]);
		}
	}
	i64 query(int p, int l, int r, int L, int R)
	{
		if (!p) return inf;
		if (L <= l && r <= R) return mi[p];
		else
		{
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return min(query(lson, L, R), query(rson, L, R));
		}
	}
}
int r[maxn];
void getall(int x, int fa, i64 d)
{
	SMT :: ins(r[rt], 1, n, x, d);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
		getall(to[i], x, d + w[i]);
}
int par[maxn];

const int L = 25;
i64 up[maxn][L];

void dfs(int x)
{
	for (int l = x, j = 0; l; l = par[l], j++) up[x][j] = dist(x, l);
	vis[x] = 1;
	getall(x, 0, 0);
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
	{
		allnode = siz[to[i]];rt = 0;
		findrt(to[i], x);
		par[rt] = x;dfs(rt);
	}
}

signed main()
{
#ifdef CraZYali
	file("6145");
#endif
	SMT :: mi[0] = inf;
	n = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>(), z = read<int>();
		add(x, y, z);add(y, x, z);
	}
	REP(i, 1, n) REP(j, 0, L - 1) up[i][j] = inf;
	lca :: init();
	allnode = n;findrt(1, 0);dfs(rt);
	q = read<int>();
	while (q--)
	{
		int l = read<int>(), r = read<int>(), x = read<int>();
		i64 ans = inf;
		for (int a = x, j = 0; a; a = par[a], j++)
			ans = min(ans, SMT :: query(::r[a], 1, n, l, r) + up[x][j]);
		printf("%lld\n", ans);
	}
	return 0;
}
