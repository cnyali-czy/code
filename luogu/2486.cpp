#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e4 + 10 , maxm = maxn;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> T read()
{
	T ans = 0, p = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, m, depth[maxn], dfs_clock, dfn[maxn], wt[maxn], w[maxn], fa[maxn], top[maxn], siz[maxn], hson[maxn];
void dfs1(int x)
{
	siz[x] = 1;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x])
		{
			fa[to[i]] = x;
			depth[to[i]] = depth[x] + 1;
			dfs1(to[i]);
			siz[x] += siz[to[i]];
			if (siz[hson[x]] < siz[to[i]]) hson[x] = to[i];
		}
}
void dfs2(int x, int y)
{
	wt[dfn[x] = ++dfs_clock] = w[x];
	top[x] = y;
	if (hson[x])
	{
		dfs2(hson[x], y);
		for (register int i = bg[x]; i ; i = ne[i])
			if (to[i] ^ fa[x] && to[i] ^ hson[x]) dfs2(to[i], to[i]);
	}
}

int sum[maxn << 2], lc[maxn << 2], rc[maxn << 2];bool pure[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

void maintain(int p, int l, int r)
{
	lc[p] = lc[ls];rc[p] = rc[rs];
	sum[p] = sum[ls] + sum[rs] - (rc[ls] == lc[rs]);
	pure[p] = (pure[ls] && pure[rs] && rc[ls] == lc[rs]);
}

void build(int p, int l, int r)
{
	if (l == r) sum[p] = lc[p] = rc[p] = wt[l], pure[p] = 1;
	else
	{
		build(lson);
		build(rson);
		maintain(p, l, r);
	}
}

void pushdown(int p, int l, int r)
{
	if (pure[p])
	{
		lc[ls] = rc[ls] = lc[rs] = rc[rs] = (lc[p] + rc[p] >> 1);
		sum[ls] = sum[rs] = 1;
		pure[ls] = pure[rs] = 1;
	}
}

void update(int p, int l, int r, int L, int R, int c)
{
	if (L <= l && r <= R) lc[p] = rc[p] = c, sum[p] = pure[p] = 1;
	else
	{
		pushdown(p, l, r);
		if (L <= mid) update(lson, L, R, c);
		if (R >  mid) update(rson, L, R, c);
		maintain(p, l, r);
	}
}
int query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return sum[p];
	else
	{
		pushdown(p, l, r);
		if (L >  mid) return query(rson, L, R);
		if (R <= mid) return query(lson, L, R);
		return query(lson, L, R) + query(rson, L, R) - (rc[ls] == lc[rs]);
	}
}

void paint(int x, int y, int z)
{
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		update(1, 1, n, dfn[top[x]], dfn[x], z);
		x = fa[top[x]];
	}
	if (depth[x] > depth[y]) swap(x, y);
	update(1, 1, n, dfn[x], dfn[y], z);
}
int count(int x, int y)
{
	int cnt = 0;
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		cnt += query(1, 1, n, dfn[top[x]], dfn[x]) - (2 - query(1, 1, n, dfn[fa[x]], dfn[x]));
		x = fa[top[x]];
	}
	if (depth[x] > depth[y]) swap(x, y);
	return cnt + query(1, 1, n, dfn[x], dfn[y]);
}

int main()
{
#ifdef CraZYali
	freopen("2486.in", "r", stdin);
	freopen("2486.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) w[i] = read<int>();
	REP(i, 2, n)
	{
		register int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	depth[1] = 1;
	dfs1(1);dfs2(1, 1);
	build(1, 1, n);
	while (m --> 0)
	{
		register char c = getchar();
		while (c ^ 'C' && c ^ 'Q') c = getchar();
		register int a = read<int>(), b = read<int>();
		if (c == 'C') paint(a, b, read<int>());
		else printf("%d\n", count(a, b));
	}
	return 0;
}
