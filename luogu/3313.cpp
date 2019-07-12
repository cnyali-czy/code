#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxm = 1e5 + 10, maxnode = 3330000, inf = 2e9;
int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
void add(int x, int y)
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

int m, n, k;
int w[maxn], c[maxn];

int depth[maxn], fa[maxn], siz[maxn], hvy[maxn];
void dfs1(int x)
{
	siz[x] = 1;
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x])
		{
			fa[to[i]] = x;
			depth[to[i]] = depth[x] + 1;
			dfs1(to[i]);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
		}
}
int top[maxn], dfn[maxn], dfs_clock;
void dfs2(int x, int y)
{
	dfn[x] = ++dfs_clock;
	top[x] = y;
	if (hvy[x]) dfs2(hvy[x], y);
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x] && to[i] ^ hvy[x]) dfs2(to[i], to[i]);
}
int root[maxn], ls[maxnode], rs[maxnode], sum[maxnode], Max[maxnode], cur;
void pushup(int p)
{
	sum[p] = sum[ls[p]] + sum[rs[p]];
	Max[p] = max(Max[ls[p]], Max[rs[p]]);
}
#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
void update(int &p, int l, int r, int pos, int val)
{
	if (!p) p = ++cur;
	if (l == r) sum[p] += val, Max[p] += val;
	else
	{
		if (pos <= mid) update(lson, pos, val);
		else update(rson, pos, val);
		pushup(p);
	}
}
int query_sum(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return sum[p];
	else
	{
		if (L >  mid) return query_sum(rson, L, R);
		if (R <= mid) return query_sum(lson, L, R);
		return query_sum(lson, L, R) + query_sum(rson, L, R);
	}
}
int query_Max(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return Max[p];
	else
	{
		if (L >  mid) return query_Max(rson, L, R);
		if (R <= mid) return query_Max(lson, L, R);
		return max(query_Max(lson, L, R), query_Max(rson, L, R));
	}
}
void CC(int x, int _c)
{
	update(root[c[x]], 1, n, dfn[x], -w[x]);
	update(root[c[x] = _c], 1, n, dfn[x], w[x]);
}
void CW(int x, int _w)
{
	update(root[c[x]], 1, n, dfn[x], _w - w[x]);
	w[x] = _w;
}
int QS(int x, int y)
{
	int res(0), _c(c[x]);
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		res += query_sum(root[_c], 1, n, dfn[top[x]], dfn[x]);
		x = fa[top[x]];
	}
	if (depth[x] > depth[y]) swap(x, y);
	return res + query_sum(root[_c], 1, n, dfn[x], dfn[y]);
}
int QM(int x, int y)
{
	int res(-inf), _c(c[x]);
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		chkmax(res, query_Max(root[_c], 1, n, dfn[top[x]], dfn[x]));
		x = fa[top[x]];
	}
	if (depth[x] > depth[y]) swap(x, y);
	return max(res, query_Max(root[_c], 1, n, dfn[x], dfn[y]));
}
char s[10];

int main()
{
#ifdef CraZYali
	file("3313");
#endif
	cin >> n >> m;
	REP(i, 1, n) w[i] = read<int>(), c[i] = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	depth[1] = 1;
	dfs1(1);
	dfs2(1, 1);
	Max[0] = -inf;
	REP(i, 1, n) update(root[c[i]], 1, n, dfn[i], w[i]);
	while (m--)
	{
		scanf("%s", s);
		int x(read<int>()), y(read<int>());
		switch (s[1])
		{
			case 'C': CC(x, y);break;
			case 'W': CW(x, y);break;
			case 'S': printf("%d\n", QS(x, y));break;
			case 'M': printf("%d\n", QM(x, y));break;
		}
	}
	return 0;
}
