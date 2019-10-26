#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;
const int maxn = 3e5 + 10, maxN = 4e7 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> T read()
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, m, w[maxn];

int siz[maxn], hvy[maxn], dep[maxn], fa[maxn], top[maxn];
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

struct seg
{
	int rt[maxn], ls[maxN], rs[maxN], sum[maxN], cur;
	seg()
	{
		int siz = sizeof rt;
		memset(rt, 0, siz);
		memset(ls, 0, siz);
		memset(rs, 0, siz);
		memset(sum, 0, siz);
		cur = 0;
	}
#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
	void update(int &p, int l, int r, int pos, int val = 1)
	{	
		if (!p) p = ++cur;
		sum[p] += val;
		if (l == r) return;
		else if (pos <= mid) update(lson, pos, val);
		else update(rson, pos, val);
	}
	int query(int p, int l, int r, int pos)
	{
		if (!p) return 0;
		if (l == r) return sum[p];
		else if (pos <= mid) return query(lson, pos);
		else return query(rson, pos);
	}
	int merge(int x, int y)
	{
		if (!x || !y) return x | y;
		int p = ++cur;
		sum[p] = sum[x] + sum[y];
		ls[p] = merge(ls[x], ls[y]);
		rs[p] = merge(rs[x], rs[y]);
		return p;
	}
}up, dw;

#define lim_l (-n - 5)
#define lim_r ( n + 5)

int ans[maxn];
void solve(int x)
{
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		solve(to[i]);
		up.rt[x] = up.merge(up.rt[x], up.rt[to[i]]);
		dw.rt[x] = dw.merge(dw.rt[x], dw.rt[to[i]]);
	}
	ans[x] = up.query(up.rt[x], lim_l, lim_r, dep[x] + w[x]) + dw.query(dw.rt[x], lim_l, lim_r, dep[x] - w[x]);
}

int main()
{
#ifdef CraZYali
	file("1600");
#endif
	cin >> n >> m;
	REP(i, 2, n)
	{
		register int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	REP(i, 1, n) w[i] = read<int>();
	dfs1(1);
	dfs2(1, 1);
	while (m--)
	{
		register int u(read<int>()), v(read<int>()), l(lca(u, v));
		up.update(up.rt[u], lim_l, lim_r, dep[u]);
		up.update(up.rt[fa[l]], lim_l, lim_r, dep[u], -1);
		dw.update(dw.rt[v], lim_l, lim_r, dep[l] + dep[l] - dep[u]);
		dw.update(dw.rt[l], lim_l, lim_r, dep[l] + dep[l] - dep[u], -1);
	}
	solve(1);
	REP(i, 1, n) printf("%d%c", ans[i], i == n ? '\n' : ' ');
	return 0;
}
