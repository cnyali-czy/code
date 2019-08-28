#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define view(u, i) for (int i(bg[u]); i; i = ne[i])
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxm = maxn << 1;

int bg[maxn], ne[maxm], to[maxm], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

#define mid (l + r >> 1)
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r

#define get(u) (ch[fa[u]][1] == u)
#define notroot(u) (ch[fa[u]][0] == u || ch[fa[u]][1] == u)

int n, q;
int siz[maxn], dfn[maxn], back[maxn], dfs_clock, depth[maxn], top[maxn], hvy[maxn];

namespace tree
{
	int fa[maxn];
	void dfs1(int x)
	{
		siz[x] = 1;
		view(x, i)
			if (to[i] ^ fa[x])
			{
				depth[to[i]] = depth[fa[to[i]] = x] + 1;
				dfs1(to[i]);
				siz[x] += siz[to[i]];
				if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
			}
	}
	void dfs2(int x, int y)
	{
		back[dfn[x] = ++dfs_clock] = x;
		top[x] = y;
		if (hvy[x]) dfs2(hvy[x], y);
		view(x, i)
			if (to[i] ^ fa[x] && to[i] ^ hvy[x]) dfs2(to[i], to[i]);
	}
	inline int lca(int x, int y)
	{
		while (top[x] ^ top[y])
		{
			if (depth[top[x]] < depth[top[y]]) swap(x, y);
			x = fa[top[x]];
		}
		return depth[x] < depth[y] ? x : y;
	}
}
using tree::lca;

int Max[maxn << 2], tag[maxn << 2];

inline void pushup(int p, int l, int r) {Max[p] = max(Max[ls], Max[rs]);}
void build(int p, int l, int r)
{
	if (l == r) Max[p] = depth[back[l]] + 1;
	else
	{
		build(lson);
		build(rson);
		pushup(p, l, r);
	}
}
inline void work(int p, int val)
{
	Max[p] += val;
	tag[p] += val;
}
inline void pushdown(int p, int l, int r)
{
	if (tag[p])
	{
		work(ls, tag[p]);
		work(rs, tag[p]);
		tag[p] = 0;
	}
}
inline void add(int p, int l, int r, int L, int R, int val)
{
	if (L <= l && r <= R) work(p, val);
	else
	{
		pushdown(p, l, r);
		if (L <= mid) add(lson, L, R, val);
		if (R >  mid) add(rson, L, R, val);
		pushup(p, l, r);
	}
}
inline int query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return Max[p];
	else
	{
		pushdown(p, l, r);
		if (L >  mid) return query(rson, L, R);
		if (R <= mid) return query(lson, L, R);
		return max(query(lson, L, R), query(rson, L, R));
	}
}

int ch[maxn][2], fa[maxn];
inline void rotate(int x)
{
	int y(fa[x]);bool k(get(x));
	ch[y][k] = ch[x][k ^ 1];
	if (ch[x][k ^ 1]) fa[ch[x][k ^ 1]] = y;
	ch[x][k ^ 1] = y;
	if (notroot(y)) ch[fa[y]][get(y)] = x;
	fa[x] = fa[y];
	fa[y] = x;
}
void splay(int x)
{
	int y = x, z(0);
	while (notroot(x))
	{
		y = fa[x];z = fa[y];
		if (notroot(y)) rotate((get(x) != get(y)) ? x : y);
		rotate(x);
	}
}
inline int rnxt(int u)
{
	u = ch[u][1];
	while (u && ch[u][0]) u = ch[u][0];
	return u;
}
inline int sroot(int u)
{
	while (u && ch[u][0]) u = ch[u][0];
	return u;
}
inline void access(int x)
{
	for (int u(0); x; u = x, x = fa[x])
	{
		splay(x);
		int t1(rnxt(x)), t2(sroot(u));
		ch[x][1] = u;
		if (t1) add(1, 1, n, dfn[t1], dfn[t1] + siz[t1] - 1, 1);
		if (t2) add(1, 1, n, dfn[t2], dfn[t2] + siz[t2] - 1, -1);
	}
}

int main()
{
#ifdef CraZYali
	freopen("2001.in", "r", stdin);
	freopen("2001.out", "w", stdout);
	freopen("2001.err", "w", stderr);
#endif
	cin >> n >> q;
	REP(i, 2, n)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);add(y, x);
	}
	tree::dfs1(1);
	tree::dfs2(1, 1);
	REP(i, 1, n) fa[i] = tree::fa[i];
	build(1, 1, n);
	while (q--)
	{
		int opt, x;scanf("%d%d", &opt, &x);
		if (opt == 1) access(x);
		else if (opt == 2)
		{
			int y;scanf("%d", &y);
			int l(lca(x, y)), ansx(query(1, 1, n, dfn[x], dfn[x])), ansy(query(1, 1, n, dfn[y], dfn[y])), ansl(query(1, 1, n, dfn[l], dfn[l]));
			printf("%d\n", ansx + ansy - (ansl << 1) + 1);
		}
		else printf("%d\n", query(1, 1, n, dfn[x], dfn[x] + siz[x] - 1));
	}
	return 0;
}
