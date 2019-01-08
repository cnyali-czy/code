#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 1e6 + 10, maxm = maxn;

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

int n, c[maxn], dfn[maxn], dfs_clock, ct[maxn], depth[maxn], top[maxn], siz[maxn], hson[maxn], fa[maxn];

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
			if (siz[hson[x]] <= siz[to[i]]) hson[x] = to[i];
		}
}
void dfs2(int x, int y)
{
	top[x] = y;
	ct[dfn[x] = ++dfs_clock] = c[x];
	if (hson[x])
	{
		dfs2(hson[x], y);
		for (register int i = bg[x]; i ; i = ne[i])
			if (to[i] ^ fa[x] && to[i] ^ hson[x]) dfs2(to[i], to[i]);
	}
}

#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

int lc[maxn << 2], rc[maxn << 2], sum[maxn << 2];
bool tag[maxn];

void pushup(int p, int l, int r)
{
	lc[p] = lc[ls];
	rc[p] = rc[rs];
	sum[p] = sum[ls] + sum[rs] - (rc[ls] == lc[rs]);
}

void build(int p, int l, int r)
{
	if (l == r) lc[p] = rc[p] = ct[l], sum[p] = 1;
	else
	{
		build(lson);
		build(rson);
		pushup(p, l, r);
	}
}

void pushdown(int p, int l, int r)
{
	if (tag[p])
	{
		tag[p] = 0;
		tag[ls] = tag[rs] = 1;
		lc[ls] = rc[ls] = lc[rs] = rc[rs] = lc[p];
		sum[ls] = sum[rs] = 1;
	}
}

void update(int p, int l, int r, int L, int R, int c)
{
	if (L <= l && r <= R) lc[p] = rc[p] = c, sum[p] = 1, tag[p] = 1;
	else
	{
		pushdown(p, l, r);
		if (L <= mid) update(lson, L, R, c);
		if (R >  mid) update(rson, L, R, c);
		pushup(p, l, r);
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
int query(int p, int l, int r, int pos)
{
	if (l == r) return lc[p];
	else
	{
		pushdown(p, l, r);
		if (pos >  mid)	return query(rson, pos);
		else			return query(lson, pos);
	}
}

int query(int x, int y)
{
	int res = 0, ans1 = 0, ans2 = 0;
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]])
		{
			swap(x, y);
			swap(ans1, ans2);
		}
		res += query(1, 1, n, dfn[top[x]], dfn[x]);
		int Lc = query(1, 1, n, dfn[top[x]]), Rc = query(1, 1, n, dfn[x]);
		if (Rc == ans1) res--;
		ans1 = Lc;
		x = fa[top[x]];
	}
	if (depth[x] > depth[y]) swap(x, y), swap(ans1, ans2);
	int Lc = query(1, 1, n, dfn[x]), Rc = query(1, 1, n, dfn[y]);
	if (Rc == ans1) res--;
	if (Lc == ans2) res--;
	return res + query(1, 1, n, dfn[x], dfn[y]);
}

void update(int x, int y, int c)
{
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		update(1, 1, n, dfn[top[x]], dfn[x], c);
		x = fa[top[x]];
	}
	if (depth[x] > depth[y]) swap(x, y);
	update(1, 1, n, dfn[x], dfn[y], c);
}
int m;
signed main()
{
#ifdef CraZYali
	freopen("2486.in", "r", stdin);
	freopen("2486.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) c[i] = read<int>();
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
		while (c ^ 'Q' && c ^ 'C') c = getchar();
		register int a = read<int>(), b = read<int>();
		if (c == 'Q') printf("%lld\n", query(a, b));
		else update(a, b, read<int>());
	}
	return 0;
}
