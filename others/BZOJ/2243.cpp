#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxm = maxn;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> inline T read()
{
	T ans(0), p(1);
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

int n, m, k, c[maxn];

int siz[maxn], depth[maxn], hvy[maxn], fa[maxn];
void dfs1(int x)
{
	siz[x] = 1;hvy[x] = 0;
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x])
		{
			depth[to[i]] = depth[fa[to[i]] = x] + 1;
			dfs1(to[i]);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
		}
}
int top[maxn], dfn[maxn], dfs_clock, cc[maxn];
void dfs2(int x, int y)
{
	cc[dfn[x] = ++dfs_clock] = c[x];
	top[x] = y;
	if (hvy[x]) dfs2(hvy[x], y);
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ hvy[x] && to[i] ^ fa[x]) dfs2(to[i], to[i]);
}

#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
int sum[maxn << 2], tag[maxn << 2], lft[maxn << 2], rit[maxn << 2];

void pushup(int p, int l, int r)
{
	sum[p] = sum[ls] + sum[rs] - (rit[ls] == lft[rs]);
	lft[p] = lft[ls];rit[p] = rit[rs];
}
void build(int p, int l, int r)
{
	tag[p] = -1;
	if (l == r)
	{
		sum[p] = 1;
		lft[p] = rit[p] = cc[l];
	}
	else
	{
		build(lson);
		build(rson);
		pushup(p, l, r);
	}
}
void maintain(int p, int c)
{
	sum[p] = 1;
	tag[p] = lft[p] = rit[p] = c;
}
void pushdown(int p, int l, int r)
{
	maintain(ls, tag[p]);
	maintain(rs, tag[p]);
	tag[p] = -1;
}
void color(int p, int l, int r, int L, int R, int c)
{
	if (L <= l && r <= R) maintain(p, c);
	else
	{
		if (tag[p] != -1) pushdown(p, l, r);
		if (L <= mid) color(lson, L, R, c);
		if (R >  mid) color(rson, L, R, c);
		pushup(p, l, r);
	}
}

void color(int x, int y, int c)
{
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		color(1, 1, n, dfn[top[x]], dfn[x], c);
		x = fa[top[x]];
	}
	if (depth[x] > depth[y]) swap(x, y);
	color(1, 1, n, dfn[x], dfn[y], c);
}
int query(int p, int l, int r, int pos)
{
	if (!pos) return -1;
	if (l == pos) return lft[p];
	else if (r == pos) return rit[p];
	else
		if (tag[p] != -1) return tag[p];
		else if (pos <= mid) return query(lson, pos);
		else return query(rson, pos);
}
int query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return sum[p];
	else
	{
		if (tag[p] != -1) pushdown(p, l, r);
		int res(0);
		if (L <= mid) res += query(lson, L, R);
		if (R >  mid) res += query(rson, L, R);
		return res - (L <= mid && R > mid && lft[rs] == rit[ls]);
	}
}
int query(int x, int y)
{
	int res(0);
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		res += query(1, 1, n, dfn[top[x]], dfn[x]) - (query(1, 1, n, dfn[top[x]]) == query(1, 1, n, dfn[fa[top[x]]]));
		x = fa[top[x]];
	}
	if (depth[x] > depth[y]) swap(x, y);
	return res + query(1, 1, n, dfn[x], dfn[y]);
}

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("2243.out", "w", stdout);
	freopen("2243.err", "w", stderr);
#endif
	cin >> n >> m;
	REP(i, 1, n) c[i] = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	depth[1] = 1;
	dfs1(1);
	dfs2(1, 1);
	build(1, 1, n);
	/*
	   REP(i, 1, n) printf("%d%c", top[i], i == n ? '\n' : ' ' );
	   REP(i, 1, n)
	   REP(j, i, n)
	   fprintf(stderr, "%d %d %d\n", i,j,query(i,j));
	   fputs("---------\n",stderr);
	   */
	while (m--)
	{
		char c = getchar();
		while (c ^ 'Q' && c ^ 'C') c = getchar();
		int a(read<int>()), b(read<int>());
		if (c == 'C') color(a, b, read<int>());
		else printf("%d\n", query(a, b));
		/*
		   if (c == 'C')
		   {
		   REP(i, 1, n) fprintf(stderr, "%d%c", query(1, 1, n, dfn[i]), i == n ? '\n' : ' ' );
		   cerr << query(1, 1, n, dfn[5]) << ' ' << query(1, 1, n, dfn[fa[5]]) << endl;
		   cerr << query(1, 1, n, dfn[2], dfn[6]) << endl;
		   REP(i, 1, n)
		   REP(j, i, n)
		   fprintf(stderr, "%d %d %d\n", i,j,query(i,j));
		   fputs("---------\n",stderr);

		   }
		   */
	}
	return 0;
}
