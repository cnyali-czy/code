#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 100000 + 10, maxm = maxn;

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

int n, m, w[maxn];

int depth[maxn], dfn[maxn], dfs_clock, fa[maxn], top[maxn], wt[maxn], siz[maxn], hson[maxn];

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
			if (siz[to[i]] >= siz[hson[x]]) hson[x] = to[i];
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

#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

int sum[maxn << 2], tag[maxn << 2];
void build(int p, int l, int r)
{
	if (l == r) sum[p] = wt[l];
	else
	{
		build(lson);
		build(rson);
		sum[p] = sum[ls] + sum[rs];
	}
}

void maintain(int p, int l, int r, int val)
{
	tag[p] += val;
	sum[p] += val * (r - l + 1);
}
void pushdown(int p, int l, int r)
{
	maintain(lson, tag[p]);
	maintain(rson, tag[p]);
	tag[p] = 0 ;
}

void update(int p, int l, int r, int L, int R, int val)
{
	if (L <= l && r <= R) maintain(p, l, r, val);
	else
	{
		pushdown(p, l, r);
		if (L <= mid) update(lson, L, R, val);
		if (R >  mid) update(rson, L, R, val);
		sum[p] = sum[ls] + sum[rs];
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
		return query(lson, L, R) + query(rson, L, R);
	}
}

void opt1(int x, int y) {update(1, 1, n, dfn[x], dfn[x], y);}
void opt2(int x, int y) {update(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, y);}
int opt3(int x)
{
	int res = 0;
	while (x)
	{
		res += query(1, 1, n, dfn[top[x]], dfn[x]);
		x = fa[top[x]];
	}
	return res;
}

signed main()
{
#ifdef CraZYali
	freopen("3178.in", "r", stdin);
	freopen("3178.out", "w", stdout);
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
		register int opt = read<int>(), x = read<int>();
		if (opt == 1) opt1(x, read<int>());
		else if (opt == 2) opt2(x, read<int>());
		else printf("%lld\n", opt3(x));
	}
	return 0;
}
