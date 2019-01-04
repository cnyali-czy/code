#define lim while
#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 30000 + 10, maxm = maxn;

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
	T res = 0, p = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		res = res * 10 + c - 48;
		c = getchar();
	}
	return res * p;
}

int n, m, w[maxn], depth[maxn], dfn[maxn], dfs_clock, wt[maxn], fa[maxn], son[maxn], hson[maxn], top[maxn];
void dfs1(int x)
{
	son[x] = 1;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x])
		{
			fa[to[i]] = x;
			depth[to[i]] = depth[x] + 1;
			dfs1(to[i]);
			son[x] += son[to[i]];
			if (son[hson[x]] <= son[to[i]]) hson[x] = to[i];
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

int Max[maxn << 2], Sum[maxn << 2];
void build(int p, int l, int r)
{
	if (l == r) Max[p] = Sum[p] = wt[l];
	else
	{
		build(lson);
		build(rson);
		Max[p] = max(Max[ls], Max[rs]);
		Sum[p] = Sum[ls] + Sum[rs];
	}
}
int qsum(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return Sum[p];
	else
	{
		if (L >  mid) return qsum(rson, L, R);
		if (R <= mid) return qsum(lson, L, R);
		return qsum(lson, L, R) + qsum(rson, L, R);
	}
}
int qmax(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return Max[p];
	else
	{
		if (L >  mid) return qmax(rson, L, R);
		if (R <= mid) return qmax(lson, L, R);
		return max(qmax(lson, L, R), qmax(rson, L, R));
	}
}
void change(int p, int l, int r, int pos, int val)
{
	if (l == r) Max[p] = Sum[p] = val;
	else
	{
		if (pos >  mid) change(rson, pos, val);
		else 			change(lson, pos, val);
		Max[p] = max(Max[ls], Max[rs]);
		Sum[p] = Sum[ls] + Sum[rs];
	}
}

int QMAX(int x, int y)
{
	int res = max(w[x], w[y]);
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		chkmax(res, qmax(1, 1, n, dfn[top[x]], dfn[x]));
		x = fa[top[x]];
	} 
	if (depth[x] > depth[y]) swap(x, y);
	return max(res, qmax(1, 1, n, dfn[x], dfn[y]));
}

int QSUM(int x, int y)
{
    int res = 0;
    while (top[x] != top[y])
    {
        if (depth[top[x]] < depth[top[y]]) swap(x, y);
        res += qsum(1, 1, n, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if (depth[x] > depth[y]) swap(x, y);
    return res + qsum(1, 1, n, dfn[x], dfn[y]);
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
	dfs1(1);
	dfs2(1, 1);
	build(1, 1, n);
	cin >> m;
	lim(m--)
	{
		char s[20];
		scanf("%s", s + 1);
		register int x = read<int>(), y = read<int>();
		int len = strlen(s + 1);
		if (s[len] == 'E') change(1, 1, n, x, y);
		else if (s[len] == 'X') printf("%d\n", QMAX(x, y));
		else printf("%d\n", QSUM(x, y));
	}
	return 0;
}
