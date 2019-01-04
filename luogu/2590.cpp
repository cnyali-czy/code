#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 30000 + 10, maxm = maxn, inf = (((1 << 30) - 1) << 1) + 1;

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

int n, m, depth[maxn], w[maxn], wt[maxn], dfs_clock, dfn[maxn], top[maxn], fa[maxn], son[maxn], hson[maxn];
void dfs1(int x)
{
	son[x] = 1;hson[x]=0;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x])
		{
			fa[to[i]] = x;
			depth[to[i]] = depth[x] + 1;
			dfs1(to[i]);
			son[x] += son[to[i]];
			if (son[to[i]] >= son[hson[x]]) hson[x] = to[i];
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

int Sum[maxn << 2], Max[maxn << 2];

void maintain(int p, int l, int r)
{
	Sum[p] = Sum[ls] + Sum[rs];
	Max[p] = max(Max[ls], Max[rs]);
}

void build(int p, int l, int r)
{
	if (l == r) Sum[p] = Max[p] = wt[l];
	else
	{
		build(lson);
		build(rson);
		maintain(p, l, r);
	}
}

int query_sum(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return Sum[p];
	else
	{
		if (L >  mid) return query_sum(rson, L, R);
		if (R <= mid) return query_sum(lson, L, R);
		return query_sum(lson, L, R) + query_sum(rson, L, R);
	}
}

int query_max(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return Max[p];
	else
	{
		if (L >  mid) return query_max(rson, L, R);
		if (R <= mid) return query_max(lson, L, R);
		return max(query_max(lson, L, R), query_max(rson, L, R));
	}
}
void update(int p, int l, int r, int pos, int val)
{
	if (l == r) Sum[p] = Max[p] = val;
	else
	{
		if (pos >  mid) update(rson, pos, val);
		else			update(lson, pos, val);
		maintain(p, l, r);
	}
}

void CHANGE(int u, int t) {update(1, 1, n, dfn[u], t);}
int QMAX(int x, int y)
{
	int res = -inf;
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		chkmax(res, query_max(1, 1, n, dfn[top[x]], dfn[x]));
		x = fa[top[x]];
	}
	if (depth[x] > depth[y]) swap(x, y);
	return max(res, query_max(1, 1, n, dfn[x], dfn[y]));
}

int QSUM(int x, int y)
{
	int res = 0;
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		res += query_sum(1, 1, n, dfn[top[x]], dfn[x]);
		x = fa[top[x]];
	}
	if (depth[x] > depth[y]) swap(x, y);
	return res + query_sum(1, 1, n, dfn[x], dfn[y]);
}

int main()
{
#ifdef CraZYali
	freopen("2590.in", "r", stdin);
	freopen("2590.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 2, n)
	{
		register int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	REP(i, 1, n) w[i] = read<int>();
	depth[1] = 1;
	dfs1(1);dfs2(1, 1);
	build(1, 1, n);
	cin >> m;
	while (m --> 0)
	{
		char s[20];scanf("%s", s + 1);
		register int u = read<int>(), v = read<int>();
		if (s[strlen(s + 1)] == 'E') CHANGE(u, v);
		else if (s[strlen(s + 1)] == 'X') printf("%d\n", QMAX(u, v));
		else printf("%d\n", QSUM(u, v));
	}
	return 0;
}
